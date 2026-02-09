#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPolyh_ArrayOfPointNormal.hpp>
#include <IntPolyh_ArrayOfSectionLines.hpp>
#include <IntPolyh_ArrayOfTangentZones.hpp>
#include <NCollection_List.hpp>
#include <IntPolyh_Couple.hpp>

class IntPolyh_MaillageAffinage;
typedef IntPolyh_MaillageAffinage* IntPolyh_PMaillageAffinage;

#include <NCollection_Array1.hpp>

class IntPolyh_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT IntPolyh_Intersection(const occ::handle<Adaptor3d_Surface>& theS1,
                                        const occ::handle<Adaptor3d_Surface>& theS2);

  Standard_EXPORT IntPolyh_Intersection(const occ::handle<Adaptor3d_Surface>& theS1,
                                        const int                             theNbSU1,
                                        const int                             theNbSV1,
                                        const occ::handle<Adaptor3d_Surface>& theS2,
                                        const int                             theNbSU2,
                                        const int                             theNbSV2);

  Standard_EXPORT IntPolyh_Intersection(const occ::handle<Adaptor3d_Surface>& theS1,
                                        const NCollection_Array1<double>&     theUPars1,
                                        const NCollection_Array1<double>&     theVPars1,
                                        const occ::handle<Adaptor3d_Surface>& theS2,
                                        const NCollection_Array1<double>&     theUPars2,
                                        const NCollection_Array1<double>&     theVPars2);

public:
  bool IsDone() const { return myIsDone; }

  bool IsParallel() const { return myIsParallel; }

  int NbSectionLines() const { return mySectionLines.NbItems(); }

  int NbPointsInLine(const int IndexLine) const
  {
    return mySectionLines[IndexLine - 1].NbStartPoints();
  }

  int NbTangentZones() const { return myTangentZones.NbItems(); }

  int NbPointsInTangentZone(const int) const { return 1; }

  Standard_EXPORT void GetLinePoint(const int IndexLine,
                                    const int IndexPoint,
                                    double&   x,
                                    double&   y,
                                    double&   z,
                                    double&   u1,
                                    double&   v1,
                                    double&   u2,
                                    double&   v2,
                                    double&   incidence) const;

  Standard_EXPORT void GetTangentZonePoint(const int IndexLine,
                                           const int IndexPoint,
                                           double&   x,
                                           double&   y,
                                           double&   z,
                                           double&   u1,
                                           double&   v1,
                                           double&   u2,
                                           double&   v2) const;

private:
  Standard_EXPORT void Perform();

  Standard_EXPORT void Perform(const NCollection_Array1<double>& theUPars1,
                               const NCollection_Array1<double>& theVPars1,
                               const NCollection_Array1<double>& theUPars2,
                               const NCollection_Array1<double>& theVPars2);

  Standard_EXPORT bool PerformStd(const NCollection_Array1<double>& theUPars1,
                                  const NCollection_Array1<double>& theVPars1,
                                  const NCollection_Array1<double>& theUPars2,
                                  const NCollection_Array1<double>& theVPars2,
                                  const double                      theDeflTol1,
                                  const double                      theDeflTol2,
                                  IntPolyh_PMaillageAffinage&       theMaillageS,
                                  int&                              theNbCouples);

  Standard_EXPORT bool PerformAdv(const NCollection_Array1<double>& theUPars1,
                                  const NCollection_Array1<double>& theVPars1,
                                  const NCollection_Array1<double>& theUPars2,
                                  const NCollection_Array1<double>& theVPars2,
                                  const double                      theDeflTol1,
                                  const double                      theDeflTol2,
                                  IntPolyh_PMaillageAffinage&       theMaillageFF,
                                  IntPolyh_PMaillageAffinage&       theMaillageFR,
                                  IntPolyh_PMaillageAffinage&       theMaillageRF,
                                  IntPolyh_PMaillageAffinage&       theMaillageRR,
                                  int&                              theNbCouples);

  Standard_EXPORT bool PerformMaillage(const NCollection_Array1<double>& theUPars1,
                                       const NCollection_Array1<double>& theVPars1,
                                       const NCollection_Array1<double>& theUPars2,
                                       const NCollection_Array1<double>& theVPars2,
                                       const double                      theDeflTol1,
                                       const double                      theDeflTol2,
                                       IntPolyh_PMaillageAffinage&       theMaillage);

  Standard_EXPORT bool PerformMaillage(const NCollection_Array1<double>&  theUPars1,
                                       const NCollection_Array1<double>&  theVPars1,
                                       const NCollection_Array1<double>&  theUPars2,
                                       const NCollection_Array1<double>&  theVPars2,
                                       const double                       theDeflTol1,
                                       const double                       theDeflTol2,
                                       const IntPolyh_ArrayOfPointNormal& thePoints1,
                                       const IntPolyh_ArrayOfPointNormal& thePoints2,
                                       const bool                         theIsFirstFwd,
                                       const bool                         theIsSecondFwd,
                                       IntPolyh_PMaillageAffinage&        theMaillage);

  Standard_EXPORT void MergeCouples(NCollection_List<IntPolyh_Couple>& theArrayFF,
                                    NCollection_List<IntPolyh_Couple>& theArrayFR,
                                    NCollection_List<IntPolyh_Couple>& theArrayRF,
                                    NCollection_List<IntPolyh_Couple>& theArrayRR) const;

  bool AnalyzeIntersection(IntPolyh_PMaillageAffinage& theMaillage);
  bool IsAdvRequired(IntPolyh_PMaillageAffinage& theMaillage);

private:
  occ::handle<Adaptor3d_Surface> mySurf1;
  occ::handle<Adaptor3d_Surface> mySurf2;

  int myNbSU1;
  int myNbSV1;
  int myNbSU2;
  int myNbSV2;

  bool                         myIsDone;
  IntPolyh_ArrayOfSectionLines mySectionLines;
  IntPolyh_ArrayOfTangentZones myTangentZones;
  bool                         myIsParallel;
};
