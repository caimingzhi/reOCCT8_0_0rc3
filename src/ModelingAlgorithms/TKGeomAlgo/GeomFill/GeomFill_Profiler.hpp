#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
class Geom_Curve;

class GeomFill_Profiler
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_Profiler();
  Standard_EXPORT virtual ~GeomFill_Profiler();

  Standard_EXPORT void AddCurve(const occ::handle<Geom_Curve>& Curve);

  Standard_EXPORT virtual void Perform(const double PTol);

  Standard_EXPORT int Degree() const;

  bool IsPeriodic() const;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT void Poles(const int Index, NCollection_Array1<gp_Pnt>& Poles) const;

  Standard_EXPORT void Weights(const int Index, NCollection_Array1<double>& Weights) const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT void KnotsAndMults(NCollection_Array1<double>& Knots,
                                     NCollection_Array1<int>&    Mults) const;

  const occ::handle<Geom_Curve>& Curve(const int Index) const;

protected:
  NCollection_Sequence<occ::handle<Geom_Curve>> mySequence;
  bool                                          myIsDone;
  bool                                          myIsPeriodic;
};

inline bool GeomFill_Profiler::IsPeriodic() const
{
  return myIsPeriodic;
}

inline const occ::handle<Geom_Curve>& GeomFill_Profiler::Curve(const int Index) const
{
  return mySequence(Index);
}
