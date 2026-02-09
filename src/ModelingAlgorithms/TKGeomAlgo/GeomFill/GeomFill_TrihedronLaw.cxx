#include <GeomFill_TrihedronLaw.hpp>
#include <gp_Vec.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_TrihedronLaw, Standard_Transient)

bool GeomFill_TrihedronLaw::SetCurve(const occ::handle<Adaptor3d_Curve>& C)
{
  myCurve   = C;
  myTrimmed = myCurve;
  return true;
}

GeomFill_PipeError GeomFill_TrihedronLaw::ErrorStatus() const
{
  return GeomFill_PipeOk;
}

bool GeomFill_TrihedronLaw::D1(const double, gp_Vec&, gp_Vec&, gp_Vec&, gp_Vec&, gp_Vec&, gp_Vec&)
{
  throw Standard_NotImplemented(" GeomFill_TrihedronLaw::D2");
}

bool GeomFill_TrihedronLaw::D2(const double,
                               gp_Vec&,
                               gp_Vec&,
                               gp_Vec&,
                               gp_Vec&,
                               gp_Vec&,
                               gp_Vec&,
                               gp_Vec&,
                               gp_Vec&,
                               gp_Vec&)
{
  throw Standard_NotImplemented(" GeomFill_TrihedronLaw::D2");
}

void GeomFill_TrihedronLaw::SetInterval(const double First, const double Last)
{
  myTrimmed = myCurve->Trim(First, Last, 0);
}

void GeomFill_TrihedronLaw::GetInterval(double& First, double& Last)
{
  First = myTrimmed->FirstParameter();
  Last  = myTrimmed->LastParameter();
}

bool GeomFill_TrihedronLaw::IsConstant() const
{
  return false;
}

bool GeomFill_TrihedronLaw::IsOnlyBy3dCurve() const
{
  return false;
}
