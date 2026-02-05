#include <Approx_SweepFunction.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>
#include <gp_Pnt.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Approx_SweepFunction, Standard_Transient)

// bool Approx_SweepFunction::D1(const double Param,const double
// First,const double Last,NCollection_Array1<gp_Pnt>& Poles,NCollection_Array1<gp_Vec>&
// DPoles,NCollection_Array1<gp_Pnt2d>& Poles2d,NCollection_Array1<gp_Vec2d>&
// DPoles2d,NCollection_Array1<double>& Weigths,NCollection_Array1<double>& DWeigths)
bool Approx_SweepFunction::D1(const double,
                              const double,
                              const double,
                              NCollection_Array1<gp_Pnt>&,
                              NCollection_Array1<gp_Vec>&,
                              NCollection_Array1<gp_Pnt2d>&,
                              NCollection_Array1<gp_Vec2d>&,
                              NCollection_Array1<double>&,
                              NCollection_Array1<double>&)
{
  throw Standard_NotImplemented("Approx_SweepFunction::D1");
}

// bool Approx_SweepFunction::D2(const double Param,const double
// First,const double Last,NCollection_Array1<gp_Pnt>& Poles,NCollection_Array1<gp_Vec>&
// DPoles,NCollection_Array1<gp_Vec>& D2Poles,NCollection_Array1<gp_Pnt2d>&
// Poles2d,NCollection_Array1<gp_Vec2d>& DPoles2d,NCollection_Array1<gp_Vec2d>&
// D2Poles2d,NCollection_Array1<double>& Weigths,NCollection_Array1<double>&
// DWeigths,NCollection_Array1<double>& D2Weigths)
bool Approx_SweepFunction::D2(const double,
                              const double,
                              const double,
                              NCollection_Array1<gp_Pnt>&,
                              NCollection_Array1<gp_Vec>&,
                              NCollection_Array1<gp_Vec>&,
                              NCollection_Array1<gp_Pnt2d>&,
                              NCollection_Array1<gp_Vec2d>&,
                              NCollection_Array1<gp_Vec2d>&,
                              NCollection_Array1<double>&,
                              NCollection_Array1<double>&,
                              NCollection_Array1<double>&)
{
  throw Standard_NotImplemented("Approx_SweepFunction::D2");
}

// void Approx_SweepFunction::Resolution(const int Index,const double
// Tol,double& TolU,double& TolV) const
void Approx_SweepFunction::Resolution(const int, const double, double&, double&) const
{
  throw Standard_NotImplemented("Approx_SweepFunction::Resolution");
}

gp_Pnt Approx_SweepFunction::BarycentreOfSurf() const
{
  throw Standard_NotImplemented("Approx_SweepFunction::BarycentreOfSurf");
}

double Approx_SweepFunction::MaximalSection() const
{
  throw Standard_NotImplemented("Approx_SweepFunction::MaximalSection()");
}

// void Approx_SweepFunction::GetMinimalWeight(NCollection_Array1<double>& Weigths) const
void Approx_SweepFunction::GetMinimalWeight(NCollection_Array1<double>&) const
{
  throw Standard_NotImplemented("Approx_SweepFunction::GetMinimalWeight");
}
