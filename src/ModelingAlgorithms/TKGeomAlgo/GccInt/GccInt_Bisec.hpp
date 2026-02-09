#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <GccInt_IType.hpp>
class gp_Pnt2d;
class gp_Lin2d;
class gp_Circ2d;
class gp_Hypr2d;
class gp_Parab2d;
class gp_Elips2d;

class GccInt_Bisec : public Standard_Transient
{

public:
  Standard_EXPORT virtual GccInt_IType ArcType() const = 0;

  Standard_EXPORT virtual gp_Pnt2d Point() const;

  Standard_EXPORT virtual gp_Lin2d Line() const;

  Standard_EXPORT virtual gp_Circ2d Circle() const;

  Standard_EXPORT virtual gp_Hypr2d Hyperbola() const;

  Standard_EXPORT virtual gp_Parab2d Parabola() const;

  Standard_EXPORT virtual gp_Elips2d Ellipse() const;

  DEFINE_STANDARD_RTTIEXT(GccInt_Bisec, Standard_Transient)
};
