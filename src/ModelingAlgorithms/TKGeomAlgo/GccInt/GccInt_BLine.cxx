#include <GccInt_BLine.hpp>
#include <gp_Lin2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GccInt_BLine, GccInt_Bisec)

GccInt_BLine::GccInt_BLine(const gp_Lin2d& Line)
{
  lin = gp_Lin2d(Line);
}

GccInt_IType GccInt_BLine::ArcType() const
{
  return GccInt_Lin;
}

gp_Lin2d GccInt_BLine::Line() const
{
  return lin;
}
