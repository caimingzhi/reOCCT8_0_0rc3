#include <GccInt_Bisec.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GccInt_Bisec, Standard_Transient)

gp_Circ2d GccInt_Bisec::Circle() const
{
  throw Standard_NotImplemented();
}

gp_Elips2d GccInt_Bisec::Ellipse() const
{
  throw Standard_NotImplemented();
}

gp_Hypr2d GccInt_Bisec::Hyperbola() const
{
  throw Standard_NotImplemented();
}

gp_Lin2d GccInt_Bisec::Line() const
{
  throw Standard_NotImplemented();
}

gp_Parab2d GccInt_Bisec::Parabola() const
{
  throw Standard_NotImplemented();
}

gp_Pnt2d GccInt_Bisec::Point() const
{
  throw Standard_NotImplemented();
}
