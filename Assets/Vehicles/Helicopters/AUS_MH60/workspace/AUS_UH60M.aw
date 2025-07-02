BaseSource {
 AnimSetTemplate "{CF9D84E7E306E92F}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_MH60M.ast"
 AnimSetInstances {
  "{C0EE91B44A3B02CB}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_MH60M_vehicle.asi"
  "{1728F0319867673E}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_MH60M_player.asi"
 }
 AnimGraph "{DD6FE2E7D4C33DDC}Assets/Vehicles/Helicopters/AUS_MH60/workspace/AUS_MH60M.agr"
 PreviewModels {
  AnimSrcWorkspacePreviewModel "{62E4CD2F8E1000D2}" {
   Model "{790CB9C809DE64B8}Assets/Characters/Animation/AnimTestChar_US_01.xob"
  }
  AnimSrcWorkspacePreviewModel "{62E4CD2F8E1000A4}" {
   Model "{0A93623FF52815EB}Assets/Vehicles/Helicopters/AUS_MH60/AUS_MH60M_Base.xob"
  }
  AnimSrcWorkspacePreviewModel "{62E4CD2F8E1000AF}" {
   Model "{88E119A661FA0159}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Main_Rotor.xob"
  }
  AnimSrcWorkspacePreviewModel "{62E4CD2F8E1000B3}" {
   Model "{49481C9BF1A5DFCA}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Tail_Rotor.xob"
  }
  AnimSrcWorkspacePreviewModel "{62E4CD2F8E1000B7}" {
   Model "{5985F5F7554847F7}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Cockpit/AUS_UH60_CockpitPanel_Main.xob"
  }
 }
 ChildPreviewModels {
  AnimSrcWorkspaceChildPreviewModel "{62E4CD2F8E1000BB}" {
   Enabled 1
   Model "{88E119A661FA0159}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Main_Rotor.xob"
   Bone "Scene_Root"
   Parent "{62E4CD2F8E1000A4}"
  }
  AnimSrcWorkspaceChildPreviewModel "{62E4CD2F8E1000BF}" {
   Enabled 1
   Model "{49481C9BF1A5DFCA}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Rotor/AUS_MH60_Tail_Rotor.xob"
   Bone "Scene_Root"
   Parent "{62E4CD2F8E1000A4}"
  }
  AnimSrcWorkspaceChildPreviewModel "{62E4CD2F8E1000BD}" {
   Enabled 1
   Model "{95D186D2D42256FA}Assets/Vehicles/Helicopters/AUS_MH60/VehParts/Weapons/AUS_Minigun_Mount_Left.xob"
   Bone "v_left_minigun_slot"
   Parent "{62E4CD2F8E1000A4}"
   ChildBone "w_left_minigun_slot"
   OffsetRotation 0 -90 0
  }
  AnimSrcWorkspaceChildPreviewModel "{631AC716C2BD3D8C}" {
   Enabled 1
   Model "{790CB9C809DE64B8}Assets/Characters/Animation/AnimTestChar_US_01.xob"
   Bone "SOAR_Left_Passenger_Middle"
   Parent "{62E4CD2F8E1000A4}"
  }
 }
 AudioTesting AnimSrcWorkspaceAudioTesting "{62E4CD2F8E10008B}" {
 }
 AttachmentTesting AnimSrcWorkspaceAttachmentTesting "{62E4CD2F8E10008C}" {
 }
 IkTesting AnimSrcWorkspaceIkTesting "{62E4CD2F8E100096}" {
 }
}