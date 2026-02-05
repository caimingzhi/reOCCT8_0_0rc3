#pragma once

#include <Geom_Curve.hpp>
#include <Select3D_SensitivePoly.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>

//! A framework to define a sensitive 3D curve.
//! In some cases this class can raise Standard_ConstructionError and
//! Standard_OutOfRange exceptions. For more details see Select3D_SensitivePoly.
class Select3D_SensitiveCurve : public Select3D_SensitivePoly
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveCurve, Select3D_SensitivePoly)
public:
  //! Constructs a sensitive curve object defined by the
  //! owner theOwnerId, the curve theCurve, and the
  //! maximum number of points on the curve: theNbPnts.
  Select3D_SensitiveCurve(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                          const occ::handle<Geom_Curve>&            theCurve,
                          const int                                 theNbPnts = 17)
      : Select3D_SensitivePoly(theOwnerId, true, theNbPnts)
  {
    loadPoints(theCurve, theNbPnts);
    mySFactor = 3;
  }

  //! Constructs a sensitive curve object defined by the
  //! owner theOwnerId and the set of points ThePoints.
  Standard_EXPORT Select3D_SensitiveCurve(
    const occ::handle<SelectMgr_EntityOwner>&       theOwnerId,
    const occ::handle<NCollection_HArray1<gp_Pnt>>& thePoints);

  //! Creation of Sensitive Curve from Points.
  //!          Warning : This Method should disappear in the next version...
  Standard_EXPORT Select3D_SensitiveCurve(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                          const NCollection_Array1<gp_Pnt>&         thePoints);

  //! Returns the copy of this
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
