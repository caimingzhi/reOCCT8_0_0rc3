#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <BRep_CurveRepresentation.hpp>
class TopLoc_Location;
class gp_Pnt;

class BRep_GCurve : public BRep_CurveRepresentation
{

public:
  void SetRange(const double First, const double Last);

  void Range(double& First, double& Last) const;

  double First() const;

  double Last() const;

  void First(const double F);

  void Last(const double L);

  Standard_EXPORT virtual void D0(const double U, gp_Pnt& P) const = 0;

  Standard_EXPORT virtual void Update();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_GCurve, BRep_CurveRepresentation)

protected:
  Standard_EXPORT BRep_GCurve(const TopLoc_Location& L, const double First, const double Last);

private:
  double myFirst;
  double myLast;
};

inline void BRep_GCurve::SetRange(const double First, const double Last)
{
  myFirst = First;
  myLast  = Last;
  Update();
}

inline void BRep_GCurve::Range(double& First, double& Last) const
{
  First = myFirst;
  Last  = myLast;
}

inline double BRep_GCurve::First() const
{
  return myFirst;
}

inline double BRep_GCurve::Last() const
{
  return myLast;
}

inline void BRep_GCurve::First(const double F)
{
  myFirst = F;
  Update();
}

inline void BRep_GCurve::Last(const double L)
{
  myLast = L;
  Update();
}
