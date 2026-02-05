#include <GeomFill_TgtField.hpp>
#include <gp_Vec.hpp>
#include <Law_BSpline.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_TgtField, Standard_Transient)

//=================================================================================================

bool GeomFill_TgtField::IsScalable() const
{
  return false;
}

//=================================================================================================

void GeomFill_TgtField::Scale(const occ::handle<Law_BSpline>&) {}
