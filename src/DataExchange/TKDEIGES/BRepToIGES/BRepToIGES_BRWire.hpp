#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepToIGES_BREntity.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>

class IGESData_IGESEntity;
class TopoDS_Shape;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class gp_Pnt2d;
class TopoDS_Wire;

class BRepToIGES_BRWire : public BRepToIGES_BREntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepToIGES_BRWire();

  Standard_EXPORT BRepToIGES_BRWire(const BRepToIGES_BREntity& BR);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferWire(const TopoDS_Shape& start);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferVertex(const TopoDS_Vertex& myvertex);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferVertex(const TopoDS_Vertex& myvertex,
                                                                  const TopoDS_Edge&   myedge,
                                                                  double&              parameter);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferVertex(const TopoDS_Vertex& myvertex,
                                                                  const TopoDS_Edge&   myedge,
                                                                  const TopoDS_Face&   myface,
                                                                  double&              parameter);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferVertex(
    const TopoDS_Vertex&             myvertex,
    const TopoDS_Edge&               myedge,
    const occ::handle<Geom_Surface>& mysurface,
    const TopLoc_Location&           myloc,
    double&                          parameter);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferVertex(const TopoDS_Vertex& myvertex,
                                                                  const TopoDS_Face&   myface,
                                                                  gp_Pnt2d&            mypoint);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferEdge(
    const TopoDS_Edge&                                                              theEdge,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theOriginMap,
    const bool                                                                      theIsBRepMode);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferEdge(
    const TopoDS_Edge&                                                              theEdge,
    const TopoDS_Face&                                                              theFace,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theOriginMap,
    const double                                                                    theLength,
    const bool                                                                      theIsBRepMode);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferWire(const TopoDS_Wire& mywire);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferWire(
    const TopoDS_Wire&                                                              theWire,
    const TopoDS_Face&                                                              theFace,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theOriginMap,
    occ::handle<IGESData_IGESEntity>&                                               theCurve2d,
    const double                                                                    theLength);
};
