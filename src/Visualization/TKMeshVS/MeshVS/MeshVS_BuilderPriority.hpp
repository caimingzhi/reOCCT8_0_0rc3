#pragma once


typedef int MeshVS_BuilderPriority;

enum
{
  MeshVS_BP_Mesh       = 5,
  MeshVS_BP_NodalColor = 10,
  MeshVS_BP_ElemColor  = 15,
  MeshVS_BP_Text       = 20,
  MeshVS_BP_Vector     = 25,
  MeshVS_BP_User       = 30,
  MeshVS_BP_Default    = MeshVS_BP_User
};

