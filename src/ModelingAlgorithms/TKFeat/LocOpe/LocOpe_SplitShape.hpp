#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Wire;
class TopoDS_Face;

//! Provides a tool to cut:
//! - edges with a vertices,
//! - faces with wires,
//! and rebuilds the shape containing the edges and
//! the faces.
class LocOpe_SplitShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  LocOpe_SplitShape();

  //! Creates the process with the shape <S>.
  LocOpe_SplitShape(const TopoDS_Shape& S);

  //! Initializes the process on the shape <S>.
  Standard_EXPORT void Init(const TopoDS_Shape& S);

  //! Tests if it is possible to split the edge <E>.
  Standard_EXPORT bool CanSplit(const TopoDS_Edge& E) const;

  //! Adds the vertex <V> on the edge <E>, at parameter <P>.
  Standard_EXPORT void Add(const TopoDS_Vertex& V, const double P, const TopoDS_Edge& E);

  //! Adds the wire <W> on the face <F>.
  Standard_EXPORT bool Add(const TopoDS_Wire& W, const TopoDS_Face& F);

  //! Adds the list of wires <Lwires> on the face <F>.
  Standard_EXPORT bool Add(const NCollection_List<TopoDS_Shape>& Lwires, const TopoDS_Face& F);

  //! Returns the "original" shape.
  const TopoDS_Shape& Shape() const;

  //! Returns the list of descendant shapes of <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& DescendantShapes(const TopoDS_Shape& S);

  //! Returns the "left" part defined by the wire <W> on
  //! the face <F>. The returned list of shape is in
  //! fact a list of faces. The face <F> is considered
  //! with its topological orientation in the original
  //! shape. <W> is considered with its orientation.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& LeftOf(const TopoDS_Wire& W,
                                                               const TopoDS_Face& F);

private:
  Standard_EXPORT bool AddOpenWire(const TopoDS_Wire& W, const TopoDS_Face& F);

  Standard_EXPORT bool AddClosedWire(const TopoDS_Wire& W, const TopoDS_Face& F);

  Standard_EXPORT void Put(const TopoDS_Shape& S);

  Standard_EXPORT bool Rebuild(const TopoDS_Shape& S);

  bool         myDone;
  TopoDS_Shape myShape;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMap;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                                     myDblE;
  NCollection_List<TopoDS_Shape>                                                             myLeft;
};

#include <StdFail_NotDone.hpp>

//=================================================================================================

inline LocOpe_SplitShape::LocOpe_SplitShape()
    : myDone(false)
{
}

//=================================================================================================

inline LocOpe_SplitShape::LocOpe_SplitShape(const TopoDS_Shape& S)
{
  Init(S);
}

//=================================================================================================

inline const TopoDS_Shape& LocOpe_SplitShape::Shape() const
{
  return myShape;
}
