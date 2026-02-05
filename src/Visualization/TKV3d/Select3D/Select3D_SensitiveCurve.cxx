#include <Select3D_SensitiveCurve.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveCurve, Select3D_SensitivePoly)

//=================================================================================================

Select3D_SensitiveCurve::Select3D_SensitiveCurve(
  const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
  const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints)
    : Select3D_SensitivePoly(theOwnerId, thePoints, true)

{
  SetSensitivityFactor(3);
}

//=================================================================================================

Select3D_SensitiveCurve::Select3D_SensitiveCurve(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
  const NCollection_Array1<gp_Pnt>&         thePoints)
    : Select3D_SensitivePoly(theOwnerId, thePoints, true)
{
  SetSensitivityFactor(3);
}

//=================================================================================================

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveCurve::GetConnected()
{
  occ::handle<NCollection_HArray1<gp_Pnt>> aPoints =
    new NCollection_HArray1<gp_Pnt>(1, myPolyg.Size());
  for (int anIndex = 1; anIndex <= myPolyg.Size(); ++anIndex)
  {
    aPoints->SetValue(anIndex, myPolyg.Pnt(anIndex - 1));
  }
  occ::handle<Select3D_SensitiveEntity> aNewEntity =
    new Select3D_SensitiveCurve(myOwnerId, aPoints);
  return aNewEntity;
}
