#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <BRepToIGES_BREntity.hpp>
#include <Standard_Integer.hpp>
#include <Message_ProgressRange.hpp>

class IGESSolid_EdgeList;
class IGESSolid_VertexList;
class TopoDS_Vertex;
class TopoDS_Edge;
class IGESData_IGESEntity;
class TopoDS_Shape;
class TopoDS_Face;
class IGESSolid_Loop;
class TopoDS_Wire;
class IGESSolid_Face;
class IGESSolid_Shell;
class TopoDS_Shell;
class IGESSolid_ManifoldSolid;
class TopoDS_Solid;
class TopoDS_CompSolid;
class TopoDS_Compound;

//! provides methods to transfer BRep entity from CASCADE to IGESBRep.
class BRepToIGESBRep_Entity : public BRepToIGES_BREntity
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a tool Entity
  Standard_EXPORT BRepToIGESBRep_Entity();

  //! Clears the contents of the fields
  Standard_EXPORT void Clear();

  //! Create the VertexList entity
  Standard_EXPORT void TransferVertexList();

  //! Returns the index of <myvertex> in "myVertices"
  Standard_EXPORT int IndexVertex(const TopoDS_Vertex& myvertex) const;

  //! Stores <myvertex> in "myVertices"
  //! Returns the index of <myvertex>.
  Standard_EXPORT int AddVertex(const TopoDS_Vertex& myvertex);

  //! Transfer an Edge entity from TopoDS to IGES
  Standard_EXPORT void TransferEdgeList();

  //! Returns the index of <myedge> in "myEdges"
  Standard_EXPORT int IndexEdge(const TopoDS_Edge& myedge) const;

  //! Stores <myedge> in "myEdges" and <mycurve3d> in "myCurves".
  //! Returns the index of <myedge>.
  Standard_EXPORT int AddEdge(const TopoDS_Edge&                      myedge,
                              const occ::handle<IGESData_IGESEntity>& mycurve3d);

  //! Returns the result of the transfert of any Shape
  //! If the transfer has failed, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferShape(
    const TopoDS_Shape&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

  //! Transfer an Edge entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferEdge(const TopoDS_Edge& myedge);

  //! Transfer an Edge entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferEdge(const TopoDS_Edge& myedge,
                                                                const TopoDS_Face& myface,
                                                                const double       length);

  //! Transfer a Wire entity from TopoDS to IGES.
  //! Returns the curve associated to mywire in the parametric space of myface.
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESSolid_Loop> TransferWire(const TopoDS_Wire& mywire,
                                                           const TopoDS_Face& myface,
                                                           const double       length);

  //! Transfer a Face entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESSolid_Face> TransferFace(const TopoDS_Face& start);

  //! Transfer an Shell entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESSolid_Shell> TransferShell(
    const TopoDS_Shell&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer a Solid entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESSolid_ManifoldSolid> TransferSolid(
    const TopoDS_Solid&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer an CompSolid entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCompSolid(
    const TopoDS_CompSolid&      start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer a Compound entity from TopoDS to IGES
  //! If this Entity could not be converted, this member returns a NullEntity.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> TransferCompound(
    const TopoDS_Compound&       start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

private:
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myVertices;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myEdges;
  NCollection_Sequence<occ::handle<Standard_Transient>>         myCurves;
  occ::handle<IGESSolid_EdgeList>                               myEdgeList;
  occ::handle<IGESSolid_VertexList>                             myVertexList;
};

