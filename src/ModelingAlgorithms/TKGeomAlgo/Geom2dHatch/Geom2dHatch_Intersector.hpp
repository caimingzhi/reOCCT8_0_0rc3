#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dInt_GInter.hpp>
class Geom2dAdaptor_Curve;
class gp_Lin2d;
class gp_Dir2d;

class Geom2dHatch_Intersector : public Geom2dInt_GInter
{
public:
  DEFINE_STANDARD_ALLOC

  Geom2dHatch_Intersector(const double Confusion, const double Tangency);

  double ConfusionTolerance() const;

  void SetConfusionTolerance(const double Confusion);

  double TangencyTolerance() const;

  void SetTangencyTolerance(const double Tangency);

  void Intersect(const Geom2dAdaptor_Curve& C1, const Geom2dAdaptor_Curve& C2);

  Standard_EXPORT Geom2dHatch_Intersector();

  Standard_EXPORT void Perform(const gp_Lin2d&            L,
                               const double               P,
                               const double               Tol,
                               const Geom2dAdaptor_Curve& E);

  Standard_EXPORT void LocalGeometry(const Geom2dAdaptor_Curve& E,
                                     const double               U,
                                     gp_Dir2d&                  T,
                                     gp_Dir2d&                  N,
                                     double&                    C) const;

private:
  double myConfusionTolerance;
  double myTangencyTolerance;
};

inline Geom2dHatch_Intersector::Geom2dHatch_Intersector(const double Confusion,
                                                        const double Tangency)
    : myConfusionTolerance(Confusion),
      myTangencyTolerance(Tangency)
{
}

inline double Geom2dHatch_Intersector::ConfusionTolerance() const
{
  return myConfusionTolerance;
}

inline void Geom2dHatch_Intersector::SetConfusionTolerance(const double Confusion)
{
  myConfusionTolerance = Confusion;
}

inline double Geom2dHatch_Intersector::TangencyTolerance() const
{
  return myTangencyTolerance;
}

inline void Geom2dHatch_Intersector::SetTangencyTolerance(const double Tangency)
{
  myTangencyTolerance = Tangency;
}

#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dAdaptor_Curve.hpp>

inline void Geom2dHatch_Intersector::Intersect(const Geom2dAdaptor_Curve& C1,
                                               const Geom2dAdaptor_Curve& C2)
{
  Geom2dInt_GInter::Perform(C1, C2, myConfusionTolerance, myTangencyTolerance);
}
