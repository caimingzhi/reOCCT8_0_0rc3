#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <FairCurve_AnalysisCode.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_OStream.hpp>
class gp_Vec2d;
class Geom2d_BSplineCurve;

class FairCurve_Batten
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FairCurve_Batten(const gp_Pnt2d& P1,
                                   const gp_Pnt2d& P2,
                                   const double    Height,
                                   const double    Slope = 0);

  Standard_EXPORT virtual ~FairCurve_Batten();

  void SetFreeSliding(const bool FreeSliding);

  void SetConstraintOrder1(const int ConstraintOrder);

  void SetConstraintOrder2(const int ConstraintOrder);

  Standard_EXPORT void SetP1(const gp_Pnt2d& P1);

  Standard_EXPORT void SetP2(const gp_Pnt2d& P2);

  void SetAngle1(const double Angle1);

  void SetAngle2(const double Angle2);

  void SetHeight(const double Height);

  void SetSlope(const double Slope);

  void SetSlidingFactor(const double SlidingFactor);

  Standard_EXPORT virtual bool Compute(FairCurve_AnalysisCode& Code,
                                       const int               NbIterations = 50,
                                       const double            Tolerance    = 1.0e-3);

  Standard_EXPORT double SlidingOfReference() const;

  bool GetFreeSliding() const;

  int GetConstraintOrder1() const;

  int GetConstraintOrder2() const;

  const gp_Pnt2d& GetP1() const;

  const gp_Pnt2d& GetP2() const;

  double GetAngle1() const;

  double GetAngle2() const;

  double GetHeight() const;

  double GetSlope() const;

  double GetSlidingFactor() const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve() const;

  Standard_EXPORT virtual void Dump(Standard_OStream& o) const;

protected:
  Standard_EXPORT double SlidingOfReference(const double D, const double A1, const double A2) const;

  Standard_EXPORT double Compute(const double D, const double A1, const double A2) const;

  Standard_EXPORT double Compute(const double D, const double A) const;

  FairCurve_AnalysisCode                     myCode;
  gp_Pnt2d                                   OldP1;
  gp_Pnt2d                                   OldP2;
  double                                     OldAngle1;
  double                                     OldAngle2;
  double                                     OldHeight;
  double                                     OldSlope;
  double                                     OldSlidingFactor;
  bool                                       OldFreeSliding;
  int                                        OldConstraintOrder1;
  int                                        OldConstraintOrder2;
  gp_Pnt2d                                   NewP1;
  gp_Pnt2d                                   NewP2;
  double                                     NewAngle1;
  double                                     NewAngle2;
  double                                     NewHeight;
  double                                     NewSlope;
  double                                     NewSlidingFactor;
  bool                                       NewFreeSliding;
  int                                        NewConstraintOrder1;
  int                                        NewConstraintOrder2;
  int                                        Degree;
  occ::handle<NCollection_HArray1<gp_Pnt2d>> Poles;
  occ::handle<NCollection_HArray1<double>>   Flatknots;
  occ::handle<NCollection_HArray1<double>>   Knots;
  occ::handle<NCollection_HArray1<int>>      Mults;

private:
  Standard_EXPORT bool Compute(const gp_Vec2d&         DeltaP1,
                               const gp_Vec2d&         DeltaP2,
                               const double            DeltaAngle1,
                               const double            DeltaAngle2,
                               FairCurve_AnalysisCode& ACode,
                               const int               NbIterations,
                               const double            Tolerance);

  Standard_EXPORT void Angles(const gp_Pnt2d& P1, const gp_Pnt2d& P2);
};

#include <Standard_NegativeValue.hpp>

inline Standard_OStream& operator<<(Standard_OStream& o, const FairCurve_Batten& Bat)
{
  Bat.Dump(o);
  return o;
}

inline void FairCurve_Batten::SetFreeSliding(const bool FreeSliding)
{
  NewFreeSliding = FreeSliding;
}

inline void FairCurve_Batten::SetConstraintOrder1(const int ConstraintOrder)
{
  NewConstraintOrder1 = ConstraintOrder;
}

inline void FairCurve_Batten::SetConstraintOrder2(const int ConstraintOrder)
{
  NewConstraintOrder2 = ConstraintOrder;
}

inline void FairCurve_Batten::SetAngle1(const double Angle1)
{
  NewAngle1 = Angle1;
}

inline void FairCurve_Batten::SetAngle2(const double Angle2)
{
  NewAngle2 = Angle2;
}

inline void FairCurve_Batten::SetHeight(const double Height)
{
  if (Height <= 0)
    throw Standard_NegativeValue("FairCurve : Height is no positive");
  NewHeight = Height;
}

inline void FairCurve_Batten::SetSlope(const double Slope)
{
  NewSlope = Slope;
}

inline void FairCurve_Batten::SetSlidingFactor(const double SlidingFactor)
{
  NewSlidingFactor = SlidingFactor;
}

inline bool FairCurve_Batten::GetFreeSliding() const
{
  return OldFreeSliding;
}

inline int FairCurve_Batten::GetConstraintOrder1() const
{
  return OldConstraintOrder1;
}

inline int FairCurve_Batten::GetConstraintOrder2() const
{
  return OldConstraintOrder2;
}

inline const gp_Pnt2d& FairCurve_Batten::GetP1() const
{
  return OldP1;
}

inline const gp_Pnt2d& FairCurve_Batten::GetP2() const
{
  return OldP2;
}

inline double FairCurve_Batten::GetAngle1() const
{
  return OldAngle1;
}

inline double FairCurve_Batten::GetAngle2() const
{
  return OldAngle2;
}

inline double FairCurve_Batten::GetHeight() const
{
  return OldHeight;
}

inline double FairCurve_Batten::GetSlope() const
{
  return OldSlope;
}

inline double FairCurve_Batten::GetSlidingFactor() const
{
  return OldSlidingFactor;
}
