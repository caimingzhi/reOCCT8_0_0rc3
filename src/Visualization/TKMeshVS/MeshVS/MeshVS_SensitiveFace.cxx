#include <MeshVS_SensitiveFace.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_SensitiveFace, Select3D_SensitiveFace)

MeshVS_SensitiveFace::MeshVS_SensitiveFace(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                           const NCollection_Array1<gp_Pnt>&         thePnts,
                                           const Select3D_TypeOfSensitivity          theSensitivity)
    : Select3D_SensitiveFace(theOwnerId, thePnts, theSensitivity)
{
  gp_XYZ aCenter(0.0, 0.0, 0.0);
  int    aNbPnts = thePnts.Upper() - thePnts.Lower() + 1;
  for (int aPntIdx = thePnts.Lower(); aPntIdx <= thePnts.Upper(); aPntIdx++)
    aCenter += thePnts(aPntIdx).XYZ();

  myCenter.SetXYZ(aCenter / aNbPnts);
}
