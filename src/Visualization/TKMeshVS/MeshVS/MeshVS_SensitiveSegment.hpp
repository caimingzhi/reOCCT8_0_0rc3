#pragma once

#include <Select3D_SensitiveSegment.hpp>

//! This class provides custom sensitive face, which will be selected if it center is in rectangle.
class MeshVS_SensitiveSegment : public Select3D_SensitiveSegment
{
public:
  Standard_EXPORT MeshVS_SensitiveSegment(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                          const gp_Pnt&                             theFirstPnt,
                                          const gp_Pnt&                             theLastPnt);

  DEFINE_STANDARD_RTTIEXT(MeshVS_SensitiveSegment, Select3D_SensitiveSegment)
};
