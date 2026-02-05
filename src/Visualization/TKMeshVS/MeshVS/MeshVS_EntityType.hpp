#pragma once

typedef enum
{
  MeshVS_ET_NONE   = 0x00,
  MeshVS_ET_Node   = 0x01,
  MeshVS_ET_0D     = 0x02,
  MeshVS_ET_Link   = 0x04,
  MeshVS_ET_Face   = 0x08,
  MeshVS_ET_Volume = 0x10,

  MeshVS_ET_Element = MeshVS_ET_0D | MeshVS_ET_Link | MeshVS_ET_Face | MeshVS_ET_Volume,
  MeshVS_ET_All     = MeshVS_ET_Element | MeshVS_ET_Node

} MeshVS_EntityType;
