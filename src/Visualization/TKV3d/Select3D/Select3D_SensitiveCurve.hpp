#pragma once

#include <Geom_Curve.hpp>
#include <Select3D_SensitivePoly.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>

class Select3D_SensitiveCurve : public Select3D_SensitivePoly
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveCurve, Select3D_SensitivePoly)
public:
  Select3D_SensitiveCurve(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                          const occ::handle<Geom_Curve>&            theCurve,
                          const int                                 theNbPnts = 17)
      : Select3D_SensitivePoly(theOwnerId, true, theNbPnts)
  {
    loadPoints(theCurve, theNbPnts);
    mySFactor = 3;
  }

  Standard_EXPORT Select3D_SensitiveCurve(
    const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
    const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints);

  Standard_EXPORT Select3D_SensitiveCurve(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                          const NCollection_Array1<gp_Pnt>&         thePoints);

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

private:
  void loadPoints(const occ::handle<Geom_Curve>& theCurve, const int theNbPnts)
  {
    const double aStep = (theCurve->LastParameter() - theCurve->FirstParameter()) / (theNbPnts - 1);
    double       aParam = theCurve->FirstParameter();
    for (int aPntIdx = 0; aPntIdx < myPolyg.Size(); ++aPntIdx)
    {
      myPolyg.SetPnt(aPntIdx, theCurve->Value(aParam));
      aParam += aStep;
    }
  }
};
