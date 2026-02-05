#include <GeomFill_TrihedronWithGuide.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_TrihedronWithGuide, GeomFill_TrihedronLaw)

occ::handle<Adaptor3d_Curve> GeomFill_TrihedronWithGuide::Guide() const
{
  return myGuide;
}

//=================================================================================================

gp_Pnt GeomFill_TrihedronWithGuide::CurrentPointOnGuide() const
{
  return myCurPointOnGuide;
}
