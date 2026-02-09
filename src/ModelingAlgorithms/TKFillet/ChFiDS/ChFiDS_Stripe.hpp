#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ChFiDS_SurfData.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_Transient.hpp>
class ChFiDS_Spine;
class Geom2d_Curve;

class ChFiDS_Stripe : public Standard_Transient
{

public:
  Standard_EXPORT ChFiDS_Stripe();

  Standard_EXPORT void Reset();

  const occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& SetOfSurfData() const;

  const occ::handle<ChFiDS_Spine>& Spine() const;

  TopAbs_Orientation OrientationOnFace1() const;

  TopAbs_Orientation OrientationOnFace2() const;

  int Choix() const;

  occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& ChangeSetOfSurfData();

  occ::handle<ChFiDS_Spine>& ChangeSpine();

  void OrientationOnFace1(const TopAbs_Orientation Or1);

  void OrientationOnFace2(const TopAbs_Orientation Or2);

  void Choix(const int C);

  void FirstParameters(double& Pdeb, double& Pfin) const;

  void LastParameters(double& Pdeb, double& Pfin) const;

  void ChangeFirstParameters(const double Pdeb, const double Pfin);

  void ChangeLastParameters(const double Pdeb, const double Pfin);

  int FirstCurve() const;

  int LastCurve() const;

  void ChangeFirstCurve(const int Index);

  void ChangeLastCurve(const int Index);

  const occ::handle<Geom2d_Curve>& FirstPCurve() const;

  const occ::handle<Geom2d_Curve>& LastPCurve() const;

  occ::handle<Geom2d_Curve>& ChangeFirstPCurve();

  occ::handle<Geom2d_Curve>& ChangeLastPCurve();

  TopAbs_Orientation FirstPCurveOrientation() const;

  TopAbs_Orientation LastPCurveOrientation() const;

  void FirstPCurveOrientation(const TopAbs_Orientation O);

  void LastPCurveOrientation(const TopAbs_Orientation O);

  int IndexFirstPointOnS1() const;

  int IndexFirstPointOnS2() const;

  int IndexLastPointOnS1() const;

  int IndexLastPointOnS2() const;

  void ChangeIndexFirstPointOnS1(const int Index);

  void ChangeIndexFirstPointOnS2(const int Index);

  void ChangeIndexLastPointOnS1(const int Index);

  void ChangeIndexLastPointOnS2(const int Index);

  Standard_EXPORT void Parameters(const bool First, double& Pdeb, double& Pfin) const;

  Standard_EXPORT void SetParameters(const bool First, const double Pdeb, const double Pfin);

  Standard_EXPORT int Curve(const bool First) const;

  Standard_EXPORT void SetCurve(const int Index, const bool First);

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve(const bool First) const;

  Standard_EXPORT occ::handle<Geom2d_Curve>& ChangePCurve(const bool First);

  Standard_EXPORT TopAbs_Orientation Orientation(const int OnS) const;

  Standard_EXPORT void SetOrientation(const TopAbs_Orientation Or, const int OnS);

  Standard_EXPORT TopAbs_Orientation Orientation(const bool First) const;

  Standard_EXPORT void SetOrientation(const TopAbs_Orientation Or, const bool First);

  Standard_EXPORT int IndexPoint(const bool First, const int OnS) const;

  Standard_EXPORT void SetIndexPoint(const int Index, const bool First, const int OnS);

  Standard_EXPORT int SolidIndex() const;

  Standard_EXPORT void SetSolidIndex(const int Index);

  Standard_EXPORT void InDS(const bool First, const int Nb = 1);

  Standard_EXPORT int IsInDS(const bool First) const;

  DEFINE_STANDARD_RTTIEXT(ChFiDS_Stripe, Standard_Transient)

private:
  double                                                           pardeb1;
  double                                                           parfin1;
  double                                                           pardeb2;
  double                                                           parfin2;
  occ::handle<ChFiDS_Spine>                                        mySpine;
  occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>> myHdata;
  occ::handle<Geom2d_Curve>                                        pcrv1;
  occ::handle<Geom2d_Curve>                                        pcrv2;
  int                                                              myChoix;
  int                                                              indexOfSolid;
  int                                                              indexOfcurve1;
  int                                                              indexOfcurve2;
  int                                                              indexfirstPOnS1;
  int                                                              indexlastPOnS1;
  int                                                              indexfirstPOnS2;
  int                                                              indexlastPOnS2;
  int                                                              begfilled;
  int                                                              endfilled;
  TopAbs_Orientation                                               myOr1;
  TopAbs_Orientation                                               myOr2;
  TopAbs_Orientation                                               orcurv1;
  TopAbs_Orientation                                               orcurv2;
};

inline const occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& ChFiDS_Stripe::
  SetOfSurfData() const
{
  return myHdata;
}

inline const occ::handle<ChFiDS_Spine>& ChFiDS_Stripe::Spine() const
{
  return mySpine;
}

inline TopAbs_Orientation ChFiDS_Stripe::OrientationOnFace1() const
{
  return myOr1;
}

inline TopAbs_Orientation ChFiDS_Stripe::OrientationOnFace2() const
{
  return myOr2;
}

inline int ChFiDS_Stripe::Choix() const
{
  return myChoix;
}

inline occ::handle<NCollection_HSequence<occ::handle<ChFiDS_SurfData>>>& ChFiDS_Stripe::
  ChangeSetOfSurfData()
{
  return myHdata;
}

inline occ::handle<ChFiDS_Spine>& ChFiDS_Stripe::ChangeSpine()
{
  return mySpine;
}

inline void ChFiDS_Stripe::OrientationOnFace1(const TopAbs_Orientation Or1)
{
  myOr1 = Or1;
}

inline void ChFiDS_Stripe::OrientationOnFace2(const TopAbs_Orientation Or2)
{
  myOr2 = Or2;
}

inline void ChFiDS_Stripe::Choix(const int C)
{
  myChoix = C;
}

inline void ChFiDS_Stripe::FirstParameters(double& Pdeb, double& Pfin) const
{
  Pdeb = pardeb1;
  Pfin = parfin1;
}

inline void ChFiDS_Stripe::LastParameters(double& Pdeb, double& Pfin) const
{
  Pdeb = pardeb2;
  Pfin = parfin2;
}

inline void ChFiDS_Stripe::ChangeFirstParameters(const double Pdeb, const double Pfin)
{
  pardeb1 = Pdeb;
  parfin1 = Pfin;
}

inline void ChFiDS_Stripe::ChangeLastParameters(const double Pdeb, const double Pfin)
{
  pardeb2 = Pdeb;
  parfin2 = Pfin;
}

inline int ChFiDS_Stripe::FirstCurve() const
{
  return indexOfcurve1;
}

inline int ChFiDS_Stripe::LastCurve() const
{
  return indexOfcurve2;
}

inline void ChFiDS_Stripe::ChangeFirstCurve(const int Index)
{
  indexOfcurve1 = Index;
}

inline void ChFiDS_Stripe::ChangeLastCurve(const int Index)
{
  indexOfcurve2 = Index;
}

inline const occ::handle<Geom2d_Curve>& ChFiDS_Stripe::FirstPCurve() const
{
  return pcrv1;
}

inline const occ::handle<Geom2d_Curve>& ChFiDS_Stripe::LastPCurve() const
{
  return pcrv2;
}

inline occ::handle<Geom2d_Curve>& ChFiDS_Stripe::ChangeFirstPCurve()
{
  return pcrv1;
}

inline occ::handle<Geom2d_Curve>& ChFiDS_Stripe::ChangeLastPCurve()
{
  return pcrv2;
}

inline int ChFiDS_Stripe::IndexFirstPointOnS1() const
{
  return indexfirstPOnS1;
}

inline int ChFiDS_Stripe::IndexLastPointOnS1() const
{
  return indexlastPOnS1;
}

inline int ChFiDS_Stripe::IndexFirstPointOnS2() const
{
  return indexfirstPOnS2;
}

inline int ChFiDS_Stripe::IndexLastPointOnS2() const
{
  return indexlastPOnS2;
}

inline void ChFiDS_Stripe::ChangeIndexFirstPointOnS1(const int Index)
{
  indexfirstPOnS1 = Index;
}

inline void ChFiDS_Stripe::ChangeIndexLastPointOnS1(const int Index)
{
  indexlastPOnS1 = Index;
}

inline void ChFiDS_Stripe::ChangeIndexFirstPointOnS2(const int Index)
{
  indexfirstPOnS2 = Index;
}

inline void ChFiDS_Stripe::ChangeIndexLastPointOnS2(const int Index)
{
  indexlastPOnS2 = Index;
}

inline TopAbs_Orientation ChFiDS_Stripe::FirstPCurveOrientation() const
{
  return orcurv1;
}

inline TopAbs_Orientation ChFiDS_Stripe::LastPCurveOrientation() const
{
  return orcurv2;
}

inline void ChFiDS_Stripe::FirstPCurveOrientation(const TopAbs_Orientation O)
{
  orcurv1 = O;
}

inline void ChFiDS_Stripe::LastPCurveOrientation(const TopAbs_Orientation O)
{
  orcurv2 = O;
}
