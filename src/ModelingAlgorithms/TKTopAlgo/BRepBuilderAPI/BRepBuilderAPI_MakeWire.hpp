#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_MakeWire.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

enum BRepBuilderAPI_WireError
{
  BRepBuilderAPI_WireDone,
  BRepBuilderAPI_EmptyWire,
  BRepBuilderAPI_DisconnectedWire,
  BRepBuilderAPI_NonManifoldWire
};

class TopoDS_Edge;
class TopoDS_Wire;
class TopoDS_Vertex;

class BRepBuilderAPI_MakeWire : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_MakeWire();

  Standard_EXPORT BRepBuilderAPI_MakeWire(const TopoDS_Edge& E);

  Standard_EXPORT BRepBuilderAPI_MakeWire(const TopoDS_Edge& E1, const TopoDS_Edge& E2);

  Standard_EXPORT BRepBuilderAPI_MakeWire(const TopoDS_Edge& E1,
                                          const TopoDS_Edge& E2,
                                          const TopoDS_Edge& E3);

  Standard_EXPORT BRepBuilderAPI_MakeWire(const TopoDS_Edge& E1,
                                          const TopoDS_Edge& E2,
                                          const TopoDS_Edge& E3,
                                          const TopoDS_Edge& E4);

  Standard_EXPORT BRepBuilderAPI_MakeWire(const TopoDS_Wire& W);

  Standard_EXPORT BRepBuilderAPI_MakeWire(const TopoDS_Wire& W, const TopoDS_Edge& E);

  Standard_EXPORT void Add(const TopoDS_Edge& E);

  Standard_EXPORT void Add(const TopoDS_Wire& W);

  Standard_EXPORT void Add(const NCollection_List<TopoDS_Shape>& L);

  Standard_EXPORT bool IsDone() const override;

  Standard_EXPORT BRepBuilderAPI_WireError Error() const;

  Standard_EXPORT const TopoDS_Wire& Wire();
  Standard_EXPORT                    operator TopoDS_Wire();

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT const TopoDS_Vertex& Vertex() const;

private:
  BRepLib_MakeWire myMakeWire;
};
