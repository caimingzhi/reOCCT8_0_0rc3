#pragma once


#include <Standard.hpp>

class TopoDS_Shape;
class gp_Pnt;

class BRepExtrema_Poly
{
public:
  //! returns true if OK.
  Standard_EXPORT static bool Distance(const TopoDS_Shape& S1,
                                       const TopoDS_Shape& S2,
                                       gp_Pnt&             P1,
                                       gp_Pnt&             P2,
                                       double&             dist);
};

