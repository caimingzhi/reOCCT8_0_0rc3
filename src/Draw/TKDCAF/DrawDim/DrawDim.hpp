#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class TopoDS_Shape;
class gp_Pnt;
class TopoDS_Edge;
class gp_Lin;
class gp_Circ;
class TopoDS_Face;
class gp_Pln;

class DrawDim
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void DrawShapeName(const TopoDS_Shape& ashape, const char* aname);

  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  Standard_EXPORT static void PlanarDimensionCommands(Draw_Interpretor& I);

  Standard_EXPORT static gp_Pnt Nearest(const TopoDS_Shape& aShape, const gp_Pnt& apoint);

  Standard_EXPORT static bool Lin(const TopoDS_Edge& e,
                                  gp_Lin&            l,
                                  bool&              infinite,
                                  double&            first,
                                  double&            last);

  Standard_EXPORT static bool Circ(const TopoDS_Edge& e, gp_Circ& l, double& first, double& last);

  Standard_EXPORT static bool Pln(const TopoDS_Face& f, gp_Pln& p);
};
