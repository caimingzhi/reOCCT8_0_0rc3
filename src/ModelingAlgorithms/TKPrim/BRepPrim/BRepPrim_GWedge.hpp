#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Builder.hpp>
#include <gp_Ax2.hpp>
#include <TopoDS_Shell.hpp>
#include <Standard_Boolean.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Face.hpp>

enum BRepPrim_Direction
{
  BRepPrim_XMin,
  BRepPrim_XMax,
  BRepPrim_YMin,
  BRepPrim_YMax,
  BRepPrim_ZMin,
  BRepPrim_ZMax
};

class gp_Pln;
class gp_Lin;
class gp_Pnt;

class BRepPrim_GWedge
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_GWedge();

  Standard_EXPORT BRepPrim_GWedge(const BRepPrim_Builder& B,
                                  const gp_Ax2&           Axes,
                                  const double            dx,
                                  const double            dy,
                                  const double            dz);

  Standard_EXPORT BRepPrim_GWedge(const BRepPrim_Builder& B,
                                  const gp_Ax2&           Axes,
                                  const double            dx,
                                  const double            dy,
                                  const double            dz,
                                  const double            ltx);

  Standard_EXPORT BRepPrim_GWedge(const BRepPrim_Builder& B,
                                  const gp_Ax2&           Axes,
                                  const double            xmin,
                                  const double            ymin,
                                  const double            zmin,
                                  const double            z2min,
                                  const double            x2min,
                                  const double            xmax,
                                  const double            ymax,
                                  const double            zmax,
                                  const double            z2max,
                                  const double            x2max);

  Standard_EXPORT gp_Ax2 Axes() const;

  Standard_EXPORT double GetXMin() const;

  Standard_EXPORT double GetYMin() const;

  Standard_EXPORT double GetZMin() const;

  Standard_EXPORT double GetZ2Min() const;

  Standard_EXPORT double GetX2Min() const;

  Standard_EXPORT double GetXMax() const;

  Standard_EXPORT double GetYMax() const;

  Standard_EXPORT double GetZMax() const;

  Standard_EXPORT double GetZ2Max() const;

  Standard_EXPORT double GetX2Max() const;

  Standard_EXPORT void Open(const BRepPrim_Direction d1);

  Standard_EXPORT void Close(const BRepPrim_Direction d1);

  Standard_EXPORT bool IsInfinite(const BRepPrim_Direction d1) const;

  Standard_EXPORT const TopoDS_Shell& Shell();

  Standard_EXPORT bool HasFace(const BRepPrim_Direction d1) const;

  Standard_EXPORT const TopoDS_Face& Face(const BRepPrim_Direction d1);

  Standard_EXPORT gp_Pln Plane(const BRepPrim_Direction d1);

  Standard_EXPORT bool HasWire(const BRepPrim_Direction d1) const;

  Standard_EXPORT const TopoDS_Wire& Wire(const BRepPrim_Direction d1);

  Standard_EXPORT bool HasEdge(const BRepPrim_Direction d1, const BRepPrim_Direction d2) const;

  Standard_EXPORT const TopoDS_Edge& Edge(const BRepPrim_Direction d1, const BRepPrim_Direction d2);

  Standard_EXPORT gp_Lin Line(const BRepPrim_Direction d1, const BRepPrim_Direction d2);

  Standard_EXPORT bool HasVertex(const BRepPrim_Direction d1,
                                 const BRepPrim_Direction d2,
                                 const BRepPrim_Direction d3) const;

  Standard_EXPORT const TopoDS_Vertex& Vertex(const BRepPrim_Direction d1,
                                              const BRepPrim_Direction d2,
                                              const BRepPrim_Direction d3);

  Standard_EXPORT gp_Pnt Point(const BRepPrim_Direction d1,
                               const BRepPrim_Direction d2,
                               const BRepPrim_Direction d3);

  Standard_EXPORT bool IsDegeneratedShape();

private:
  BRepPrim_Builder myBuilder;
  gp_Ax2           myAxes;
  double           XMin;
  double           XMax;
  double           YMin;
  double           YMax;
  double           ZMin;
  double           ZMax;
  double           Z2Min;
  double           Z2Max;
  double           X2Min;
  double           X2Max;
  TopoDS_Shell     myShell;
  bool             ShellBuilt;
  TopoDS_Vertex    myVertices[8];
  bool             VerticesBuilt[8];
  TopoDS_Edge      myEdges[12];
  bool             EdgesBuilt[12];
  TopoDS_Wire      myWires[6];
  bool             WiresBuilt[6];
  TopoDS_Face      myFaces[6];
  bool             FacesBuilt[6];
  bool             myInfinite[6];
};
