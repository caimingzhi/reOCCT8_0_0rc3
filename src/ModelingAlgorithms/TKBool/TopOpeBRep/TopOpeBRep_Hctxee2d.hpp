#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Edge.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <IntRes2d_Domain.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class BRepAdaptor_Surface;
class TopoDS_Shape;

class TopOpeBRep_Hctxee2d : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRep_Hctxee2d();

  Standard_EXPORT void SetEdges(const TopoDS_Edge&         E1,
                                const TopoDS_Edge&         E2,
                                const BRepAdaptor_Surface& BAS1,
                                const BRepAdaptor_Surface& BAS2);

  Standard_EXPORT const TopoDS_Shape& Edge(const int I) const;

  Standard_EXPORT const Geom2dAdaptor_Curve& Curve(const int I) const;

  Standard_EXPORT const IntRes2d_Domain& Domain(const int I) const;

  DEFINE_STANDARD_RTTIEXT(TopOpeBRep_Hctxee2d, Standard_Transient)

private:
  TopoDS_Edge         myEdge1;
  Geom2dAdaptor_Curve myCurve1;
  IntRes2d_Domain     myDomain1;
  TopoDS_Edge         myEdge2;
  Geom2dAdaptor_Curve myCurve2;
  IntRes2d_Domain     myDomain2;
};
