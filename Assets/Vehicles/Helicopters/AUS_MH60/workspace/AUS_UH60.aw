BaseSource {
 AnimSetTemplate "{4AFCF1F092D60AD7}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_UH60.ast"
 AnimSetInstances {
  "{F92CF370B061B851}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_UH60_Player.asi"
  "{B564C22BB91A8CCA}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_UH60.asi"
 }
 AnimGraph "{580E97F0A513DE24}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_UH60.agr"
 PreviewModels {
  AnimSrcWorkspacePreviewModel "{5CF0924D10545437}" {
   Model "{790CB9C809DE64B8}Assets/Characters/Animation/AnimTestChar_US_01.xob"
  }
  AnimSrcWorkspacePreviewModel "{5CEEF9CB8837F076}" {
   Model "{CBB2918B56DB040E}Assets/Vehicles/Helicopters/AUS_MH60/AUS_MH60_Base.xob"
  }
  AnimSrcWorkspacePreviewModel "{611E49415674D9C4}" {
   Model "{88E119A661FA0159}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Main_Rotor.xob"
  }
  AnimSrcWorkspacePreviewModel "{61529A2C506A34D2}" {
   Model "{49481C9BF1A5DFCA}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Tail_Rotor.xob"
  }
  AnimSrcWorkspacePreviewModel "{5DE2CDD952B5F2C0}" {
   Model "{7CF0A580603C7F76}Assets/Vehicles/Helicopters/Mi8/VehParts/Cockpit/Mi8_CockpitPanel_Left.xob"
  }
  AnimSrcWorkspacePreviewModel "{5DE4D5DC1536B51A}" {
   Model "{8ACA23E40823B0EB}Assets/Vehicles/Helicopters/Mi8/VehParts/Cockpit/Mi8_CockpitPanel_Right.xob"
  }
  AnimSrcWorkspacePreviewModel "{5DE8761BB154B428}" {
   Model "{E4C7A6C2BC2F766D}Assets/Vehicles/Helicopters/Mi8/VehParts/Cockpit/Mi8_CockpitPanel_Top.xob"
  }
  AnimSrcWorkspacePreviewModel "{5DE2A02FE57EF768}" {
   Model "{B5D5366762ED43AC}Assets/Vehicles/Helicopters/Mi8/VehParts/Cockpit/Mi8_CockpitPanels_Mid.xob"
  }
  AnimSrcWorkspacePreviewModel "{5E387BBB84EB27B3}" {
   Model "{8285569B55146CBB}Assets/Vehicles/Helicopters/Mi8/Dst/Mi8_mainRotor_dst.xob"
  }
  AnimSrcWorkspacePreviewModel "{5E06B7CF4E42949B}" {
   Model "{FBA9C212E83F43B0}Assets/Vehicles/Helicopters/Mi8/VehParts/Rotor/Mi8_rotorblur.xob"
  }
  AnimSrcWorkspacePreviewModel "{5E0728DD33441D4A}" {
   Model "{94D0B42D48753A82}Assets/Vehicles/Helicopters/Mi8/VehParts/Rotor/Mi8_tail_rotorblur.xob"
  }
  AnimSrcWorkspacePreviewModel "{5DCE77ED2AB1605B}" {
   Model "{1F8ADF7BB67C4D30}Assets/Vehicles/Helicopters/Mi8/VehParts/Rotor/Mi8_tailRotor.xob"
  }
  AnimSrcWorkspacePreviewModel "{5E387BBB0EF9E4C4}" {
   Model "{CC6E4327C7F34216}Assets/Vehicles/Helicopters/Mi8/Dst/Mi8_tailRotor_dst.xob"
  }
 }
 ChildPreviewModels {
  AnimSrcWorkspaceChildPreviewModel "{611AC98B3B3076A9}" {
   Enabled 1
   Model "{88E119A661FA0159}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Main_Rotor.xob"
   Bone "v_rotor"
   Parent "{5CEEF9CB8837F076}"
   ChildBone "v_rotor"
  }
  AnimSrcWorkspaceChildPreviewModel "{6122DB9ECD74C155}" {
   Enabled 1
   Model "{49481C9BF1A5DFCA}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Tail_Rotor.xob"
   Bone "v_rear_rotor"
   Parent "{5CEEF9CB8837F076}"
   ChildBone "v_rear_rotor"
  }
  AnimSrcWorkspaceChildPreviewModel "{6452C62498FB1826}" {
   Enabled 1
   Model "{14609C52A624440C}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Tail_Rotor_Blur.xob"
   Bone "v_rear_rotor"
   Parent "{5CEEF9CB8837F076}"
   ChildBone "v_rear_rotor"
  }
 }
 AudioTesting AnimSrcWorkspaceAudioTesting "{5CEEF9CB883F8FF9}" {
 }
 AttachmentTesting AnimSrcWorkspaceAttachmentTesting "{5CEEF9CB883F8FC6}" {
 }
 IkTesting AnimSrcWorkspaceIkTesting "{5CEEF9CB883F8FF6}" {
  IkTargets {
   AnimSrcWorkspaceIkTargetTest "{5C8E9BFC6F8DA197}" {
    Enabled 0
    BindingName "RightSuspension"
    Position 3.128 0.721 -1.965
    Rotation 0 0 0
   }
   AnimSrcWorkspaceIkTargetTest "{5C8E9BC4798D2F93}" {
    Enabled 0
    BindingName "FrontSuspension"
    Position 0.009 0.146 1.971
    Rotation 0 0 0
   }
   AnimSrcWorkspaceIkTargetTest "{5C8E9BFC1D0A1000}" {
    Enabled 1
    BindingName "LeftSuspension"
    Position 0 0 0
    Rotation 0 0 0
   }
  }
 }
}