#include <IntPolyh_Intersection.hpp>

#include <Adaptor3d_Surface.hpp>

#include <IntPolyh_Couple.hpp>
#include <IntPolyh_MaillageAffinage.hpp>
#include <IntPolyh_SectionLine.hpp>
#include <IntPolyh_StartPoint.hpp>
#include <IntPolyh_Tools.hpp>
#include <IntPolyh_Triangle.hpp>

#include <NCollection_Map.hpp>

static int ComputeIntersection(IntPolyh_PMaillageAffinage& theMaillage);

IntPolyh_Intersection::IntPolyh_Intersection(const occ::handle<Adaptor3d_Surface>& theS1,
                                             const occ::handle<Adaptor3d_Surface>& theS2)
{
  mySurf1      = theS1;
  mySurf2      = theS2;
  myNbSU1      = 10;
  myNbSV1      = 10;
  myNbSU2      = 10;
  myNbSV2      = 10;
  myIsDone     = false;
  myIsParallel = false;
  mySectionLines.Init(1000);
  myTangentZones.Init(10000);
  Perform();
}

IntPolyh_Intersection::IntPolyh_Intersection(const occ::handle<Adaptor3d_Surface>& theS1,
                                             const int                             theNbSU1,
                                             const int                             theNbSV1,
                                             const occ::handle<Adaptor3d_Surface>& theS2,
                                             const int                             theNbSU2,
                                             const int                             theNbSV2)
{
  mySurf1      = theS1;
  mySurf2      = theS2;
  myNbSU1      = theNbSU1;
  myNbSV1      = theNbSV1;
  myNbSU2      = theNbSU2;
  myNbSV2      = theNbSV2;
  myIsDone     = false;
  myIsParallel = false;
  mySectionLines.Init(1000);
  myTangentZones.Init(10000);
  Perform();
}

IntPolyh_Intersection::IntPolyh_Intersection(const occ::handle<Adaptor3d_Surface>& theS1,
                                             const NCollection_Array1<double>&     theUPars1,
                                             const NCollection_Array1<double>&     theVPars1,
                                             const occ::handle<Adaptor3d_Surface>& theS2,
                                             const NCollection_Array1<double>&     theUPars2,
                                             const NCollection_Array1<double>&     theVPars2)
{
  mySurf1      = theS1;
  mySurf2      = theS2;
  myNbSU1      = theUPars1.Length();
  myNbSV1      = theVPars1.Length();
  myNbSU2      = theUPars2.Length();
  myNbSV2      = theVPars2.Length();
  myIsDone     = false;
  myIsParallel = false;
  mySectionLines.Init(1000);
  myTangentZones.Init(10000);
  Perform(theUPars1, theVPars1, theUPars2, theVPars2);
}

void IntPolyh_Intersection::GetLinePoint(const int Indexl,
                                         const int Indexp,
                                         double&   x,
                                         double&   y,
                                         double&   z,
                                         double&   u1,
                                         double&   v1,
                                         double&   u2,
                                         double&   v2,
                                         double&   incidence) const
{
  const IntPolyh_SectionLine& msl = mySectionLines[Indexl - 1];
  const IntPolyh_StartPoint&  sp  = msl[Indexp - 1];
  x                               = sp.X();
  y                               = sp.Y();
  z                               = sp.Z();
  u1                              = sp.U1();
  v1                              = sp.V1();
  u2                              = sp.U2();
  v2                              = sp.V2();
  incidence                       = sp.GetAngle();
}

void IntPolyh_Intersection::GetTangentZonePoint(const int Indexz,
                                                const int,
                                                double& x,
                                                double& y,
                                                double& z,
                                                double& u1,
                                                double& v1,
                                                double& u2,
                                                double& v2) const
{
  const IntPolyh_StartPoint& sp = myTangentZones[Indexz - 1];
  x                             = sp.X();
  y                             = sp.Y();
  z                             = sp.Z();
  u1                            = sp.U1();
  v1                            = sp.V1();
  u2                            = sp.U2();
  v2                            = sp.V2();
}

void IntPolyh_Intersection::Perform()
{

  NCollection_Array1<double> UPars1, VPars1, UPars2, VPars2;
  IntPolyh_Tools::MakeSampling(mySurf1, myNbSU1, myNbSV1, false, UPars1, VPars1);
  IntPolyh_Tools::MakeSampling(mySurf2, myNbSU2, myNbSV2, false, UPars2, VPars2);

  Perform(UPars1, VPars1, UPars2, VPars2);
}

void IntPolyh_Intersection::Perform(const NCollection_Array1<double>& theUPars1,
                                    const NCollection_Array1<double>& theVPars1,
                                    const NCollection_Array1<double>& theUPars2,
                                    const NCollection_Array1<double>& theVPars2)
{
  myIsDone = true;

  double aDeflTol1 = IntPolyh_Tools::ComputeDeflection(mySurf1, theUPars1, theVPars1);
  double aDeflTol2 = IntPolyh_Tools::ComputeDeflection(mySurf2, theUPars2, theVPars2);

  IntPolyh_PMaillageAffinage pMaillageStd = nullptr;
  int                        nbCouplesStd = 0;
  bool                       isStdDone    = PerformStd(theUPars1,
                              theVPars1,
                              theUPars2,
                              theVPars2,
                              aDeflTol1,
                              aDeflTol2,
                              pMaillageStd,
                              nbCouplesStd);

  if (!isStdDone)
  {

    myIsDone = false;
    if (pMaillageStd)
      delete pMaillageStd;
    return;
  }

  if (!IsAdvRequired(pMaillageStd))
  {

    pMaillageStd->StartPointsChain(mySectionLines, myTangentZones);
  }
  else
  {

    IntPolyh_PMaillageAffinage pMaillageFF  = nullptr;
    IntPolyh_PMaillageAffinage pMaillageFR  = nullptr;
    IntPolyh_PMaillageAffinage pMaillageRF  = nullptr;
    IntPolyh_PMaillageAffinage pMaillageRR  = nullptr;
    int                        nbCouplesAdv = 0;

    bool isAdvDone = PerformAdv(theUPars1,
                                theVPars1,
                                theUPars2,
                                theVPars2,
                                aDeflTol1,
                                aDeflTol2,
                                pMaillageFF,
                                pMaillageFR,
                                pMaillageRF,
                                pMaillageRR,
                                nbCouplesAdv);

    if (isAdvDone && nbCouplesAdv > 0)
    {

      pMaillageFF->StartPointsChain(mySectionLines, myTangentZones);
      pMaillageFR->StartPointsChain(mySectionLines, myTangentZones);
      pMaillageRF->StartPointsChain(mySectionLines, myTangentZones);
      pMaillageRR->StartPointsChain(mySectionLines, myTangentZones);
    }
    else
    {

      if (nbCouplesStd > 0)
        pMaillageStd->StartPointsChain(mySectionLines, myTangentZones);
    }

    if (pMaillageFF)
      delete pMaillageFF;
    if (pMaillageFR)
      delete pMaillageFR;
    if (pMaillageRF)
      delete pMaillageRF;
    if (pMaillageRR)
      delete pMaillageRR;
  }

  if (pMaillageStd)
    delete pMaillageStd;
}

bool IntPolyh_Intersection::PerformStd(const NCollection_Array1<double>& theUPars1,
                                       const NCollection_Array1<double>& theVPars1,
                                       const NCollection_Array1<double>& theUPars2,
                                       const NCollection_Array1<double>& theVPars2,
                                       const double                      theDeflTol1,
                                       const double                      theDeflTol2,
                                       IntPolyh_PMaillageAffinage&       theMaillageS,
                                       int&                              theNbCouples)
{
  bool isDone  = PerformMaillage(theUPars1,
                                theVPars1,
                                theUPars2,
                                theVPars2,
                                theDeflTol1,
                                theDeflTol2,
                                theMaillageS);
  theNbCouples = (isDone) ? (theMaillageS->GetCouples().Extent()) : 0;
  return isDone;
}

bool IntPolyh_Intersection::PerformAdv(const NCollection_Array1<double>& theUPars1,
                                       const NCollection_Array1<double>& theVPars1,
                                       const NCollection_Array1<double>& theUPars2,
                                       const NCollection_Array1<double>& theVPars2,
                                       const double                      theDeflTol1,
                                       const double                      theDeflTol2,
                                       IntPolyh_PMaillageAffinage&       theMaillageFF,
                                       IntPolyh_PMaillageAffinage&       theMaillageFR,
                                       IntPolyh_PMaillageAffinage&       theMaillageRF,
                                       IntPolyh_PMaillageAffinage&       theMaillageRR,
                                       int&                              theNbCouples)
{

  IntPolyh_ArrayOfPointNormal aPoints1, aPoints2;
  IntPolyh_Tools::FillArrayOfPointNormal(mySurf1, theUPars1, theVPars1, aPoints1);
  IntPolyh_Tools::FillArrayOfPointNormal(mySurf2, theUPars2, theVPars2, aPoints2);

  bool isDone = PerformMaillage(theUPars1,
                                theVPars1,
                                theUPars2,
                                theVPars2,
                                theDeflTol1,
                                theDeflTol2,
                                aPoints1,
                                aPoints2,
                                true,
                                false,
                                theMaillageFR)
                && PerformMaillage(theUPars1,
                                   theVPars1,
                                   theUPars2,
                                   theVPars2,
                                   theDeflTol1,
                                   theDeflTol2,
                                   aPoints1,
                                   aPoints2,
                                   false,
                                   true,
                                   theMaillageRF)
                && PerformMaillage(theUPars1,
                                   theVPars1,
                                   theUPars2,
                                   theVPars2,
                                   theDeflTol1,
                                   theDeflTol2,
                                   aPoints1,
                                   aPoints2,
                                   true,
                                   true,
                                   theMaillageFF)
                && PerformMaillage(theUPars1,
                                   theVPars1,
                                   theUPars2,
                                   theVPars2,
                                   theDeflTol1,
                                   theDeflTol2,
                                   aPoints1,
                                   aPoints2,
                                   false,
                                   false,
                                   theMaillageRR);

  if (isDone)
  {
    theNbCouples = theMaillageFF->GetCouples().Extent() + theMaillageFR->GetCouples().Extent()
                   + theMaillageRF->GetCouples().Extent() + theMaillageRR->GetCouples().Extent();

    if (theNbCouples > 0)
      MergeCouples(theMaillageFF->GetCouples(),
                   theMaillageFR->GetCouples(),
                   theMaillageRF->GetCouples(),
                   theMaillageRR->GetCouples());
  }

  return isDone;
}

bool IntPolyh_Intersection::PerformMaillage(const NCollection_Array1<double>& theUPars1,
                                            const NCollection_Array1<double>& theVPars1,
                                            const NCollection_Array1<double>& theUPars2,
                                            const NCollection_Array1<double>& theVPars2,
                                            const double                      theDeflTol1,
                                            const double                      theDeflTol2,
                                            IntPolyh_PMaillageAffinage&       theMaillage)
{
  theMaillage = new IntPolyh_MaillageAffinage(mySurf1,
                                              theUPars1.Length(),
                                              theVPars1.Length(),
                                              mySurf2,
                                              theUPars2.Length(),
                                              theVPars2.Length(),
                                              0);

  theMaillage->FillArrayOfPnt(1, theUPars1, theVPars1, &theDeflTol1);
  theMaillage->FillArrayOfPnt(2, theUPars2, theVPars2, &theDeflTol2);

  int FinTTC = ComputeIntersection(theMaillage);

  if (FinTTC == 0)
  {

    bool isEnlargeU1, isEnlargeV1, isEnlargeU2, isEnlargeV2;
    IntPolyh_Tools::IsEnlargePossible(mySurf1, isEnlargeU1, isEnlargeV1);
    IntPolyh_Tools::IsEnlargePossible(mySurf2, isEnlargeU2, isEnlargeV2);

    if (isEnlargeU1 || isEnlargeV1 || isEnlargeU2 || isEnlargeV2)
    {
      theMaillage->SetEnlargeZone(true);

      theMaillage->FillArrayOfPnt(1);
      theMaillage->FillArrayOfPnt(2);

      ComputeIntersection(theMaillage);
      theMaillage->SetEnlargeZone(false);
    }
  }

  return AnalyzeIntersection(theMaillage);
}

bool IntPolyh_Intersection::PerformMaillage(const NCollection_Array1<double>&  theUPars1,
                                            const NCollection_Array1<double>&  theVPars1,
                                            const NCollection_Array1<double>&  theUPars2,
                                            const NCollection_Array1<double>&  theVPars2,
                                            const double                       theDeflTol1,
                                            const double                       theDeflTol2,
                                            const IntPolyh_ArrayOfPointNormal& thePoints1,
                                            const IntPolyh_ArrayOfPointNormal& thePoints2,
                                            const bool                         theIsFirstFwd,
                                            const bool                         theIsSecondFwd,
                                            IntPolyh_PMaillageAffinage&        theMaillage)
{
  theMaillage = new IntPolyh_MaillageAffinage(mySurf1,
                                              theUPars1.Length(),
                                              theVPars1.Length(),
                                              mySurf2,
                                              theUPars2.Length(),
                                              theVPars2.Length(),
                                              0);

  theMaillage->FillArrayOfPnt(1, theIsFirstFwd, thePoints1, theUPars1, theVPars1, theDeflTol1);
  theMaillage->FillArrayOfPnt(2, theIsSecondFwd, thePoints2, theUPars2, theVPars2, theDeflTol2);

  ComputeIntersection(theMaillage);

  return AnalyzeIntersection(theMaillage);
}

void IntPolyh_Intersection::MergeCouples(NCollection_List<IntPolyh_Couple>& anArrayFF,
                                         NCollection_List<IntPolyh_Couple>& anArrayFR,
                                         NCollection_List<IntPolyh_Couple>& anArrayRF,
                                         NCollection_List<IntPolyh_Couple>& anArrayRR) const
{

  NCollection_Map<IntPolyh_Couple> aFenceMap;

  NCollection_List<IntPolyh_Couple>* pLists[4] = {&anArrayFF, &anArrayFR, &anArrayRF, &anArrayRR};
  for (int i = 0; i < 4; ++i)
  {
    NCollection_List<IntPolyh_Couple>::Iterator aIt(*pLists[i]);
    for (; aIt.More();)
    {
      if (!aFenceMap.Add(aIt.Value()))
      {
        pLists[i]->Remove(aIt);
        continue;
      }
      aIt.Next();
    }
  }
}

bool IntPolyh_Intersection::IsAdvRequired(IntPolyh_PMaillageAffinage& theMaillage)
{
  if (!theMaillage)
    return true;

  NCollection_List<IntPolyh_Couple>& Couples = theMaillage->GetCouples();

  int aNbCouples = Couples.Extent();

  bool isAdvReq = (aNbCouples == 0) && !IsParallel();
  if (isAdvReq)

    return isAdvReq;

  if (aNbCouples > 10)

    return isAdvReq;

  const double                                anEps = .996;
  NCollection_List<IntPolyh_Couple>::Iterator aIt(Couples);
  for (; aIt.More(); aIt.Next())
  {
    if (std::abs(aIt.Value().Angle()) > anEps)
    {

      isAdvReq = true;
      break;
    }
  }

  return isAdvReq;
}

int ComputeIntersection(IntPolyh_PMaillageAffinage& theMaillage)
{
  if (!theMaillage)
    return 0;

  theMaillage->CommonBox();

  theMaillage->FillArrayOfTriangles(1);
  theMaillage->FillArrayOfTriangles(2);

  theMaillage->FillArrayOfEdges(1);
  theMaillage->FillArrayOfEdges(2);

  theMaillage->TrianglesDeflectionsRefinementBSB();

  return theMaillage->TriangleCompare();
}

bool IntPolyh_Intersection::AnalyzeIntersection(IntPolyh_PMaillageAffinage& theMaillage)
{
  if (!theMaillage)
    return false;

  NCollection_List<IntPolyh_Couple>& Couples = theMaillage->GetCouples();
  int                                FinTTC  = Couples.Extent();
  if (FinTTC > 200)
  {
    const double                                eps   = .996;
    int                                         npara = 0;
    NCollection_List<IntPolyh_Couple>::Iterator aIt(Couples);
    for (; aIt.More(); aIt.Next())
    {
      double cosa = std::abs(aIt.Value().Angle());
      if (cosa > eps)
        ++npara;
    }

    if (npara >= theMaillage->GetArrayOfTriangles(1).NbItems()
        || npara >= theMaillage->GetArrayOfTriangles(2).NbItems())
    {
      Couples.Clear();
      myIsParallel = true;
      return true;
    }
  }
  return true;
}
