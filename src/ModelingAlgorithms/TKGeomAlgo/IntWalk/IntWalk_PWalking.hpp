#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Dir.hpp>
#include <IntImp_ConstIsoparametric.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <gp_Dir2d.hpp>
#include <IntWalk_TheInt2S.hpp>
#include <NCollection_Array1.hpp>
#include <IntWalk_StatusDeflection.hpp>

class gp_Pnt;

class IntWalk_PWalking
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntWalk_PWalking(const occ::handle<Adaptor3d_Surface>& Caro1,
                                   const occ::handle<Adaptor3d_Surface>& Caro2,
                                   const double                          TolTangency,
                                   const double                          Epsilon,
                                   const double                          Deflection,
                                   const double                          Increment);

  Standard_EXPORT IntWalk_PWalking(const occ::handle<Adaptor3d_Surface>& Caro1,
                                   const occ::handle<Adaptor3d_Surface>& Caro2,
                                   const double                          TolTangency,
                                   const double                          Epsilon,
                                   const double                          Deflection,
                                   const double                          Increment,
                                   const double                          U1,
                                   const double                          V1,
                                   const double                          U2,
                                   const double                          V2);

  Standard_EXPORT void Perform(const NCollection_Array1<double>& ParDep);

  Standard_EXPORT void Perform(const NCollection_Array1<double>& ParDep,
                               const double                      u1min,
                               const double                      v1min,
                               const double                      u2min,
                               const double                      v2min,
                               const double                      u1max,
                               const double                      v1max,
                               const double                      u2max,
                               const double                      v2max);

  Standard_EXPORT bool PerformFirstPoint(const NCollection_Array1<double>& ParDep,
                                         IntSurf_PntOn2S&                  FirstPoint);

  bool IsDone() const;

  int NbPoints() const;

  const IntSurf_PntOn2S& Value(const int Index) const;

  const occ::handle<IntSurf_LineOn2S>& Line() const;

  bool TangentAtFirst() const;

  bool TangentAtLast() const;

  bool IsClosed() const;

  const gp_Dir& TangentAtLine(int& Index) const;

  Standard_EXPORT IntWalk_StatusDeflection TestDeflection(const IntImp_ConstIsoparametric ChoixIso,
                                                          const IntWalk_StatusDeflection theStatus);

  Standard_EXPORT bool TestArret(const bool                  DejaReparti,
                                 NCollection_Array1<double>& Param,
                                 IntImp_ConstIsoparametric&  ChoixIso);

  Standard_EXPORT void RepartirOuDiviser(bool&                      DejaReparti,
                                         IntImp_ConstIsoparametric& ChoixIso,
                                         bool&                      Arrive);

  void AddAPoint(const IntSurf_PntOn2S& thePOn2S);

  void RemoveAPoint(const int theIndex)
  {
    const int anIdx = (std::min)(theIndex, line->NbPoints());

    if (anIdx < 1)
      return;

    if (anIdx <= myTangentIdx)
    {
      myTangentIdx--;

      if (myTangentIdx < 1)
        myTangentIdx = 1;
    }

    line->RemovePoint(anIdx);
  }

  Standard_EXPORT bool PutToBoundary(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                     const occ::handle<Adaptor3d_Surface>& theASurf2);

  Standard_EXPORT bool SeekAdditionalPoints(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                            const occ::handle<Adaptor3d_Surface>& theASurf2,
                                            const int                             theMinNbPoints);

  double MaxStep(int theIndex)
  {
    Standard_OutOfRange_Raise_if((theIndex < 0) || (theIndex > 3),
                                 "IntWalk_PWalking::MaxStep() - index is out of range");
    return pasInit[theIndex];
  }

protected:
  Standard_EXPORT void ComputePasInit(const double theDeltaU1,
                                      const double theDeltaV1,
                                      const double theDeltaU2,
                                      const double theDeltaV2);

  Standard_EXPORT bool DistanceMinimizeByGradient(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                                  const occ::handle<Adaptor3d_Surface>& theASurf2,
                                                  NCollection_Array1<double>&           theInit,
                                                  const double* theStep0 = nullptr);

  Standard_EXPORT bool DistanceMinimizeByExtrema(const occ::handle<Adaptor3d_Surface>& theASurf,
                                                 const gp_Pnt&                         theP0,
                                                 double&                               theU0,
                                                 double&                               theV0,
                                                 const double* theStep0 = nullptr);

  Standard_EXPORT bool SeekPointOnBoundary(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                           const occ::handle<Adaptor3d_Surface>& theASurf2,
                                           const double                          theU1,
                                           const double                          theV1,
                                           const double                          theU2,
                                           const double                          theV2,
                                           const bool                            isTheFirst);

  Standard_EXPORT bool HandleSingleSingularPoint(const occ::handle<Adaptor3d_Surface>& theASurf1,
                                                 const occ::handle<Adaptor3d_Surface>& theASurf2,
                                                 const double                          the3DTol,
                                                 NCollection_Array1<double>&           thePnt);

  Standard_EXPORT bool ExtendLineInCommonZone(const IntImp_ConstIsoparametric theChoixIso,
                                              const bool                      theDirectionFlag);

private:
  bool                          done;
  occ::handle<IntSurf_LineOn2S> line;
  bool                          close;
  bool                          tgfirst;
  bool                          tglast;

  int myTangentIdx;

  gp_Dir tgdir;

  double                    fleche;
  double                    pasMax;
  double                    tolconf;
  double                    myTolTang;
  double                    pasuv[4];
  double                    myStepMin[4];
  double                    pasSav[4];
  double                    pasInit[4];
  double                    Um1;
  double                    UM1;
  double                    Vm1;
  double                    VM1;
  double                    Um2;
  double                    UM2;
  double                    Vm2;
  double                    VM2;
  double                    ResoU1;
  double                    ResoU2;
  double                    ResoV1;
  double                    ResoV2;
  int                       sensCheminement;
  IntImp_ConstIsoparametric choixIsoSav;
  IntSurf_PntOn2S           previousPoint;
  bool                      previoustg;
  gp_Dir                    previousd;
  gp_Dir2d                  previousd1;
  gp_Dir2d                  previousd2;
  gp_Dir2d                  firstd1;
  gp_Dir2d                  firstd2;
  IntWalk_TheInt2S          myIntersectionOn2S;
  int                       STATIC_BLOCAGE_SUR_PAS_TROP_GRAND;
  int                       STATIC_PRECEDENT_INFLEXION;
};

#include <StdFail_NotDone.hpp>
#include <IntSurf_LineOn2S.hpp>

inline bool IntWalk_PWalking::IsDone() const
{
  return done;
}

inline int IntWalk_PWalking::NbPoints() const
{
  if (!done)
    throw StdFail_NotDone();
  return line->NbPoints();
}

inline const IntSurf_PntOn2S& IntWalk_PWalking::Value(const int Index) const
{
  if (!done)
    throw StdFail_NotDone();
  return line->Value(Index);
}

inline const occ::handle<IntSurf_LineOn2S>& IntWalk_PWalking::Line() const
{

  if (!done)
    throw StdFail_NotDone();
  return line;
}

inline bool IntWalk_PWalking::TangentAtFirst() const
{
  if (!done)
    throw StdFail_NotDone();
  return tgfirst;
}

inline bool IntWalk_PWalking::TangentAtLast() const
{
  if (!done)
    throw StdFail_NotDone();
  return tglast;
}

inline bool IntWalk_PWalking::IsClosed() const
{
  if (!done)
    throw StdFail_NotDone();
  return close;
}

inline const gp_Dir& IntWalk_PWalking::TangentAtLine(int& theIndex) const
{
  if (!done)
    throw StdFail_NotDone();
  theIndex = myTangentIdx;
  return tgdir;
}

#define REGLAGE 0

inline void IntWalk_PWalking::AddAPoint(const IntSurf_PntOn2S& POn2S)
{
#if REGLAGE
  int n = line->NbPoints() + 1;
  if (n == 1)
  {
    std::cout << "Dump of WL" << std::endl;
  }

  if (n)
  {
    double u1, v1, u2, v2;
    POn2S.Parameters(u1, v1, u2, v2);
    printf("point p%d  %+10.20f %+10.20f %+10.20f\n",
           n,
           POn2S.Value().X(),
           POn2S.Value().Y(),
           POn2S.Value().Z());
    fflush(stdout);
  }
#endif
  line->Add(POn2S);
  myTangentIdx = std::max(myTangentIdx, 1);
}
