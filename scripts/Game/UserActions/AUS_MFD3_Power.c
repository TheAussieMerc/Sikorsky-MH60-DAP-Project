class AUS_MFD2_Power : ScriptedUserAction
{
	//All code originally from AgentZero (colton1070 on Discord) - classnames changed for removal of script conflicts
	//------------------------------------------------------------------------------------------------
	private int m_isMFD2On = false; //-1 is none, 0 is red, 1 is green.
	protected AUS_MultiFunctionDisplay mfd3 = null;
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if(!mfd3) {
//			BaseHUDComponent HUD_Component = BaseHUDComponent.Cast(pOwnerEntity.FindComponent(BaseHUDComponent));
//			ref array<BaseInfoDisplay> infoDisplayArray = new array<BaseInfoDisplay>;
//			HUD_Component.GetInfoDisplays(infoDisplayArray);
	
			mfd3 = AUS_MultiFunctionDisplay.Cast(pOwnerEntity.FindComponent(AUS_MultiFunctionDisplay));
		}
		if(!m_isMFD2On)
		{
			mfd3.TurnOnDisplay(pOwnerEntity);
			//m_isMFD2On = mfd3.IsDisplayOn();
			m_isMFD2On = true;
		}
		else {
			mfd3.TurnOffDisplay(pOwnerEntity);
			m_isMFD2On = false;
		}
		//pOwnerEntity.FindComponent(BaseHUDComponent);
	}
	
	void EOnFrame(IEntity pOwnerEntity)
	{
		if(mfd3)
		{
			if(mfd3.IsDisplayOn())
			{
				mfd3.UpdateDisplay();
			}
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		if(m_isMFD2On)
		{
			outName = "Turn Off MFD";
		} else
		{
			outName = "Turn On MFD";
		}
		return true;
	}
}