#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepPrim_Builder.hpp>
#include <gp_Ax2.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Face.hpp>
class gp_Pnt2d;

class BRepPrim_OneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void SetMeridianOffset(const double MeridianOffset = 0);

  Standard_EXPORT const gp_Ax2& Axes() const;

  Standard_EXPORT void Axes(const gp_Ax2& A);

  Standard_EXPORT double Angle() const;

  Standard_EXPORT void Angle(const double A);

  Standard_EXPORT double VMin() const;

  Standard_EXPORT void VMin(const double V);

  Standard_EXPORT double VMax() const;

  Standard_EXPORT void VMax(const double V);

  Standard_EXPORT virtual TopoDS_Face MakeEmptyLateralFace() const = 0;

  Standard_EXPORT virtual TopoDS_Edge MakeEmptyMeridianEdge(const double Ang) const = 0;

  Standard_EXPORT virtual void SetMeridianPCurve(TopoDS_Edge& E, const TopoDS_Face& F) const = 0;

  Standard_EXPORT virtual gp_Pnt2d MeridianValue(const double V) const = 0;

  Standard_EXPORT virtual bool MeridianOnAxis(const double V) const;

  Standard_EXPORT virtual bool MeridianClosed() const;

  Standard_EXPORT virtual bool VMaxInfinite() const;

  Standard_EXPORT virtual bool VMinInfinite() const;

  Standard_EXPORT virtual bool HasTop() const;

  Standard_EXPORT virtual bool HasBottom() const;

  Standard_EXPORT virtual bool HasSides() const;

  Standard_EXPORT const TopoDS_Shell& Shell();

  Standard_EXPORT const TopoDS_Face& LateralFace();

  Standard_EXPORT const TopoDS_Face& TopFace();

  Standard_EXPORT const TopoDS_Face& BottomFace();

  Standard_EXPORT const TopoDS_Face& StartFace();

  Standard_EXPORT const TopoDS_Face& EndFace();

  Standard_EXPORT const TopoDS_Wire& LateralWire();

  Standard_EXPORT const TopoDS_Wire& LateralStartWire();

  Standard_EXPORT const TopoDS_Wire& LateralEndWire();

  Standard_EXPORT const TopoDS_Wire& TopWire();

  Standard_EXPORT const TopoDS_Wire& BottomWire();

  Standard_EXPORT const TopoDS_Wire& StartWire();

  Standard_EXPORT const TopoDS_Wire& AxisStartWire();

  Standard_EXPORT const TopoDS_Wire& EndWire();

  Standard_EXPORT const TopoDS_Wire& AxisEndWire();

  Standard_EXPORT const TopoDS_Edge& AxisEdge();

  Standard_EXPORT const TopoDS_Edge& StartEdge();

  Standard_EXPORT const TopoDS_Edge& EndEdge();

  Standard_EXPORT const TopoDS_Edge& StartTopEdge();

  Standard_EXPORT const TopoDS_Edge& StartBottomEdge();

  Standard_EXPORT const TopoDS_Edge& EndTopEdge();

  Standard_EXPORT const TopoDS_Edge& EndBottomEdge();

  Standard_EXPORT const TopoDS_Edge& TopEdge();

  Standard_EXPORT const TopoDS_Edge& BottomEdge();

  Standard_EXPORT const TopoDS_Vertex& AxisTopVertex();

  Standard_EXPORT const TopoDS_Vertex& AxisBottomVertex();

  Standard_EXPORT const TopoDS_Vertex& TopStartVertex();

  Standard_EXPORT const TopoDS_Vertex& TopEndVertex();

  Standard_EXPORT const TopoDS_Vertex& BottomStartVertex();

  Standard_EXPORT const TopoDS_Vertex& BottomEndVertex();
  Standard_EXPORT virtual ~BRepPrim_OneAxis();

protected:
  Standard_EXPORT BRepPrim_OneAxis(const BRepPrim_Builder& B,
                                   const gp_Ax2&           A,
                                   const double            VMin,
                                   const double            VMax);

  BRepPrim_Builder myBuilder;

private:
  bool isHeightInverted() const;

  bool areHeightsEqual() const;

  gp_Ax2        myAxes;
  double        myAngle;
  double        myVMin;
  double        myVMax;
  double        myMeridianOffset;
  TopoDS_Shell  myShell;
  bool          ShellBuilt;
  TopoDS_Vertex myVertices[6];
  bool          VerticesBuilt[6];
  TopoDS_Edge   myEdges[9];
  bool          EdgesBuilt[9];
  TopoDS_Wire   myWires[9];
  bool          WiresBuilt[9];
  TopoDS_Face   myFaces[5];
  bool          FacesBuilt[5];
};
