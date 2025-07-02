//All code originally from AgentZero (colton1070 on Discord) - classnames changed for removal of script conflicts
class AUS_MultiFunctionDisplayClass : ScriptComponentClass { }

class AUS_MultiFunctionDisplay : ScriptComponent
{
    [Attribute("", UIWidgets.ResourceNamePicker, "Layout", "layout")]
    protected ResourceName m_LayoutPath;

    [Attribute("", UIWidgets.ResourceNamePicker, "On Material", "emat")]
    protected ResourceName m_OnMaterialPath;

    [Attribute("", UIWidgets.ResourceNamePicker, "Off Material", "emat")]
    protected ResourceName m_OffMaterialPath;

    protected Widget m_wRoot;
    protected RTTextureWidget m_wRTTexture0;
    protected Widget m_wFrame0;

    //protected OverlayWidget m_wOverlay0;

    protected bool m_IsDisplayOn = false;
    protected SignalsManagerComponent m_VehicleSignals;
    protected const ResourceName DEFAULT_LAYOUT = "";

    override void EOnInit(IEntity owner)
    {
        super.EOnInit(owner);

        if (SCR_Global.IsEditMode())
            return;
    }

    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);

        if (m_LayoutPath.IsEmpty())
            m_LayoutPath = DEFAULT_LAYOUT;

        m_VehicleSignals = SignalsManagerComponent.Cast(
            owner.FindComponent(SignalsManagerComponent)
        );
        //Print("AUS_StandbyFlightDisplayComponent: m_VehicleSignals", LogLevel.NORMAL);

        // Initialize the layout
        // Defer layout initialization to ensure all resources are loaded
        //Print("AUS_StandbyFlightDisplayComponent: OnPostInit", LogLevel.NORMAL);
        GetGame().GetCallqueue().CallLater(InitializeLayout, 0, false, owner);
    }

    //	override void EOnFrame(IEntity owner, float timeslice)
    //	{
    //		//Want to avoid doing this...
    //	}

    protected void InitializeLayout(IEntity owner)
    {
        if (!GetGame().GetWorkspace())
        {
            //Print("AUS_StandbyFlightDisplayComponent: Workspace not available", LogLevel.ERROR);
            return;
        }

        m_wRoot = GetGame().GetWorkspace().CreateWidgets(m_LayoutPath);
        if (!m_wRoot)
        {
            //Print("AUS_StandbyFlightDisplayComponent: Failed to create root widget", LogLevel.ERROR);
            return;
        }

        m_wRTTexture0 = RTTextureWidget.Cast(m_wRoot.FindAnyWidget("RTTexture0"));
        m_wFrame0 = m_wRoot.FindAnyWidget("Frame0");
        // m_wVerticalLayout0 = m_wFrame0.FindAnyWidget("VerticalLayout0");
        //m_wOverlay0 = OverlayWidget.Cast(m_wRoot.FindAnyWidget("Overlay0"));

        if (!m_wRTTexture0 || !m_wFrame0)
        {
            //Print("AUS_StandbyFlightDisplayComponent: Failed to find required widgets", LogLevel.ERROR);
            return;
        }

        //Print("AUS_StandbyFlightDisplayComponent: Setting GUI widget.", LogLevel.NORMAL);
        //m_wRTTexture0.SetGUIWidget(owner, 1);



        // Initially hide the display
        SetDisplayVisibility(false);
    }

    void TurnOnDisplay(IEntity owner)
    {
        Print("AUS_StandbyFlightDisplayComponent: Turning on display.", LogLevel.NORMAL);
        if (m_IsDisplayOn)
            return;

        SlotManagerComponent ownerSlotManager = SlotManagerComponent.Cast(
            owner.FindComponent(SlotManagerComponent)
        );
        EntitySlotInfo mfdDisplaySlot = ownerSlotManager.GetSlotByName("MFD3"); //later we will have to have seperate instances, for now hardcoded is fine
        if (mfdDisplaySlot)
        {
            Print("AUS_MFDDisplayComponent: Slot found in slot manager.", LogLevel.NORMAL);
            IEntity mfdEntity = mfdDisplaySlot.GetAttachedEntity();

            m_wRTTexture0.SetGUIWidget(mfdEntity, 1); //Setting index is useless unless you are trying to turn it off/on.
            SetDisplayVisibility(true);
            m_IsDisplayOn = true;

            UpdateDisplay();
        }
    }

    void TurnOffDisplay(IEntity owner)
    {
        //Print("AUS_StandbyFlightDisplayComponent: Turning off display", LogLevel.NORMAL);
        if (!m_IsDisplayOn)
            return;

        SlotManagerComponent ownerSlotManager = SlotManagerComponent.Cast(
            owner.FindComponent(SlotManagerComponent)
        );
        EntitySlotInfo mfdDisplaySlot = ownerSlotManager.GetSlotByName("MFD3"); //later we will have to have seperate instances, for now hardcoded is fine
        if (mfdDisplaySlot)
        {
            Print("AUS_MFDDisplayComponent: Slot found in slot manager.", LogLevel.NORMAL);
            IEntity mfdEntity = mfdDisplaySlot.GetAttachedEntity();
            m_wRTTexture0.SetGUIWidget(mfdEntity, -1);
            SetDisplayVisibility(false);
            //GetGame().GetCallqueue().CallLater(SetDisplayMaterial, 0, false, owner, false);
            m_IsDisplayOn = false;
        }
    }

    protected void SetDisplayVisibility(bool isVisible)
    {
        //Print("AUS_StandbyFlightDisplayComponent: Setting display visibility.", LogLevel.NORMAL);
        if (!m_wRoot)
            return;

        //PrintFormat("AUS_StandbyFlightDisplayComponent: Root is valid, changing visibility %1 now.", isVisible, LogLevel.NORMAL);
        if (!isVisible)
            //m_wRoot.SetOpacity(0); //Why?
            m_wRoot.SetVisible(isVisible);
        m_wRTTexture0.SetVisible(isVisible);
        m_wRoot.SetEnabled(isVisible);
        if (isVisible)
            m_wRoot.SetOpacity(1); //Why?
        m_wRoot.SetVisible(isVisible);
    }

    protected float m_SmoothedTQ = 0.0; // store the smoothed TQ value
    protected float m_SmoothingFactor = 0.05; // control TQ smoothing (adjust as needed)

    // Add these new members for PTIT simulation
    protected float m_CurrentPTIT = 500.0; // Starting PTIT value (adjust as needed)
    protected float m_MaxPTIT = 943.0; // Maximum PTIT value
    protected float m_MinPTIT = 0.0; // Minimum PTIT value
    protected float m_PTITChangeRate = 5.0; // Rate of PTIT change per update

    void UpdateDisplay()
    {
        if (!m_IsDisplayOn)
        {
            return;
        }
        //Print("AUS_StandbyFlightDisplayComponent: Updating display.", LogLevel.NORMAL);
        if (!m_IsDisplayOn || !m_VehicleSignals)
            return;

        //Print("AUS_StandbyFlightDisplayComponent: Display is on, found vehicle signals..", LogLevel.NORMAL);
        int nrIndex = m_VehicleSignals.FindSignal("MainRotorRPM");
        int tqIndex = m_VehicleSignals.FindSignal("MainRotorCollective");
        int engineRPMIndex = m_VehicleSignals.FindSignal("EngineRPM");
        if (tqIndex != -1 && engineRPMIndex != -1 && nrIndex != -1) //this is so chalked
        {
            float rpmValue = m_VehicleSignals.GetSignalValue(engineRPMIndex);
            float nrValue = m_VehicleSignals.GetSignalValue(nrIndex);
            float nrValuePerc = (nrValue / 225) * 100;
            string nrValueString = nrValuePerc.ToString();
            Color nrColor = Color.Green;
            if (nrValuePerc < 97)
            {
                nrColor = Color.Yellow;
            }
            //saved the value for text, however progress widgets go 0-100 so we make sure it doesn't go over.

            if (nrValuePerc > 101)
            {
                nrColor = Color.Yellow;
                //nrValuePerc = 100;
            }

            if (nrValuePerc > 106)
            {
                nrColor = Color.Red;
                //nrValuePerc = 100;
            }

            if (nrValuePerc < 1)
            {
                nrColor = Color.Gray;
                nrValuePerc = 0;
            }

            

            //	        TextWidget airspeedText = TextWidget.Cast(m_wRoot.FindAnyWidget("AirspeedText"));
            //	        if (airspeedText)
            //	            airspeedText.SetText(airspeedFlat.ToString());

            ProgressBarWidget nrPercTape = ProgressBarWidget.Cast(m_wRoot.FindAnyWidget("NR"));
            nrPercTape.SetCurrent(nrValuePerc);
            nrPercTape.SetColor(nrColor);

            TextWidget nrText = TextWidget.Cast(m_wRoot.FindAnyWidget("NRText"));
            if (nrText)
                nrText.SetText(Math.Floor(nrValuePerc).ToString());

            //
            // NP READOUTS
            //

            ProgressBarWidget np1PercTape = ProgressBarWidget.Cast(m_wRoot.FindAnyWidget("NP1"));
            np1PercTape.SetCurrent(nrValuePerc);
            np1PercTape.SetColor(Color.Green);

            TextWidget np1Text = TextWidget.Cast(m_wRoot.FindAnyWidget("NP1Text"));
            if (np1Text)
                np1Text.SetText(
                    (Math.Round((nrValuePerc + Math.RandomFloat(-0.5, 0.5)) * 10) / 10).ToString()
                );

            ProgressBarWidget np2PercTape = ProgressBarWidget.Cast(m_wRoot.FindAnyWidget("NP2"));
            np2PercTape.SetCurrent(nrValuePerc);
            np2PercTape.SetColor(Color.Green);

            TextWidget np2Text = TextWidget.Cast(m_wRoot.FindAnyWidget("NP2Text"));
            if (np2Text)
                np2Text.SetText(
                    (Math.Round((nrValuePerc + Math.RandomFloat(-0.5, 0.5)) * 10) / 10).ToString()
                );

            //
            //	 TORQUE READOUTS
            //


            float tqValue = m_VehicleSignals.GetSignalValue(tqIndex);
            // Apply smoothing to the TQ value
            if (tqValue < 0.05 && rpmValue > 14500)
            {
                tqValue = 0.12 + Math.RandomFloat(-0.2, 0.2);
            }
            else if (rpmValue > 15000 && tqValue < 0.05)
            {
                tqValue = 0.15 + Math.RandomFloat(-0.2, 0.2);
            }

            m_SmoothedTQ = (m_SmoothingFactor * tqValue) + ((1 - m_SmoothingFactor) * m_SmoothedTQ);
            //PrintFormat("TQ Value: %1", tqValue);
            float tqValuePerc = (m_SmoothedTQ) * 100;
            //PrintFormat("Smooth TQ Value: %1", tqValuePerc);
            string tqValueString = Math.Floor(tqValuePerc).ToString();
            Color tqColor = Color.Green;
            //saved the value for text, however progress widgets go 0-100 so we make sure it doesn't go over.
            if (tqValuePerc > 97)
            {
                tqColor = Color.Red;
                tqValuePerc = 100;
            }

            if (tqValuePerc < 97)
            {
                tqColor = Color.Yellow;
            }

            if (tqValuePerc < 95)
            {
                tqColor = Color.Green;
            }
            if (tqValuePerc < 3)
            {
                tqColor = Color.Green;
                tqValuePerc = 0;
            }

            TextWidget tq1Text = TextWidget.Cast(m_wRoot.FindAnyWidget("TQ1Text"));
            if (tq1Text)
                tq1Text.SetText(Math.Floor(tqValuePerc).ToString());

            TextWidget tq2Text = TextWidget.Cast(m_wRoot.FindAnyWidget("TQ2Text"));
            if (tq2Text)
                tq2Text.SetText(Math.Floor(tqValuePerc).ToString());

            ProgressBarWidget tqPercTape1 = ProgressBarWidget.Cast(m_wRoot.FindAnyWidget("TQ1"));
            ProgressBarWidget tqPercTape2 = ProgressBarWidget.Cast(m_wRoot.FindAnyWidget("TQ2"));
            tqPercTape1.SetCurrent(tqValuePerc);
            tqPercTape1.SetColor(tqColor);
            tqPercTape2.SetCurrent(tqValuePerc);
            tqPercTape2.SetColor(tqColor);

            //------------------
            float targetPTIT;

            // Calculate target PTIT based on TQ and RPM

            //nominal rpm = 15000
            //max rpm = 19500
            if (tqValuePerc > 90 && rpmValue > 15000)
                targetPTIT = m_MaxPTIT;
            else if (rpmValue > 1000 && nrValuePerc > 1 && rpmValue < 14500)
                targetPTIT = 600;
            else if (rpmValue > 14500 && nrValuePerc > 1 && tqValuePerc < 30)
                targetPTIT = 500 + Math.RandomFloat(-10, 10);
            else
                targetPTIT = m_MinPTIT + ((tqValuePerc / 100) * (m_MaxPTIT - m_MinPTIT));

            // Gradually change current PTIT towards target
            if (m_CurrentPTIT < targetPTIT)
                m_CurrentPTIT = Math.Min(m_CurrentPTIT + m_PTITChangeRate, targetPTIT);
            else if (m_CurrentPTIT > targetPTIT)
                m_CurrentPTIT = Math.Max(m_CurrentPTIT - m_PTITChangeRate, targetPTIT);

            TextWidget ptitText = TextWidget.Cast(m_wRoot.FindAnyWidget("PTITText"));
            if (ptitText)
                ptitText.SetText(
                    Math.Floor(m_CurrentPTIT).ToString()
                        + " "
                        + Math.Floor(m_CurrentPTIT).ToString()
                );
            ProgressBarWidget ptitBar1 = ProgressBarWidget.Cast(m_wRoot.FindAnyWidget("PTIT1"));
            ProgressBarWidget ptitBar2 = ProgressBarWidget.Cast(m_wRoot.FindAnyWidget("PTIT2"));
            float ptitPerc = (m_CurrentPTIT) / (m_MaxPTIT) * 100;
            ptitBar1.SetCurrent(ptitPerc + Math.RandomFloat(-1, 1));
            ptitBar2.SetCurrent(ptitPerc + Math.RandomFloat(-1, 1));

            // Set color based on PTIT value
            if (m_CurrentPTIT > 899)
            {
                ptitBar1.SetColor(Color.Red);
                ptitBar2.SetColor(Color.Red);
            }
            else if (m_CurrentPTIT > 816)
            {
                ptitBar1.SetColor(Color.Yellow);
                ptitBar2.SetColor(Color.Yellow);
            }
            else
            {
                ptitBar1.SetColor(Color.Green);
                ptitBar2.SetColor(Color.Green);
            }
        }

        //Print("AUS_StandbyFlightDisplayComponent: Finished update for display.", LogLevel.NORMAL);
        GetGame().GetCallqueue().CallLater(UpdateDisplay, (1000 / 15), false); //should loop 15 times a second
    }

    bool IsDisplayOn()
    {
        return m_IsDisplayOn;
    }

    override void OnDelete(IEntity owner)
    {
        super.OnDelete(owner);

        if (m_wRoot)
        {
            m_wRoot.RemoveFromHierarchy();
            m_wRoot = null;
        }
    }
}
