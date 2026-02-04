#pragma once


#include <Standard.hpp>

#include <Select3D_SensitiveFace.hpp>
#include <Select3D_TypeOfSensitivity.hpp>

//! This class provides custom sensitive face, which will be selected if it center is in rectangle.
class MeshVS_SensitiveFace : public Select3D_SensitiveFace
{
public:
  Standard_EXPORT MeshVS_SensitiveFace(
    const occ::handle<SelectMgr_EntityOwner>& theOwner,
    const NCollection_Array1<gp_Pnt>&         thePoints,
    const Select3D_TypeOfSensitivity          theSensType = Select3D_TOS_INTERIOR);

  DEFINE_STANDARD_RTTIEXT(MeshVS_SensitiveFace, Select3D_SensitiveFace)

protected:
  gp_Pnt myCenter;
};

