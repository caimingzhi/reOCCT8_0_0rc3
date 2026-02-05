#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <gp_XYZ.hpp>
class IGESSolid_ManifoldSolid;
class IGESSolid_Shell;
class IGESSolid_Face;
class IGESData_IGESEntity;
class IGESSolid_Loop;
class IGESSolid_EdgeList;
class IGESSolid_VertexList;
class gp_XYZ;

//! This class manages the creation of an IGES Topologic entity
//! (BREP : ManifoldSolid, Shell, Face)
//! This includes definiting of Vertex and Edge Lists,
//! building of Edges and Loops
class IGESSolid_TopoBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty TopoBuilder
  //! This creates also a unique VertexList and a unique EdgeList,
  //! empty, but which can be referenced from starting
  Standard_EXPORT IGESSolid_TopoBuilder();

  //! Resets the TopoBuilder for an entirely new operation
  //! (with a new EdgeList, a new VertexList, new Shells, ...)
  Standard_EXPORT void Clear();

  //! Adds a Vertex to the VertexList
  Standard_EXPORT void AddVertex(const gp_XYZ& val);

  //! Returns the count of already recorded Vertices
  Standard_EXPORT int NbVertices() const;

  //! Returns a Vertex, given its rank
  Standard_EXPORT const gp_XYZ& Vertex(const int num) const;

  //! Returns the VertexList. It can be referenced, but it remains
  //! empty until call to EndShell or EndSolid
  Standard_EXPORT occ::handle<IGESSolid_VertexList> VertexList() const;

  //! Adds an Edge (3D) to the EdgeList, defined by a Curve and
  //! two number of Vertex, for start and end
  Standard_EXPORT void AddEdge(const occ::handle<IGESData_IGESEntity>& curve,
                               const int                               vstart,
                               const int                               vend);

  //! Returns the count of recorded Edges (3D)
  Standard_EXPORT int NbEdges() const;

  //! Returns the definition of an Edge (3D) given its rank
  Standard_EXPORT void Edge(const int                         num,
                            occ::handle<IGESData_IGESEntity>& curve,
                            int&                              vstart,
                            int&                              vend) const;

  //! Returns the EdgeList. It can be referenced, but it remains
  //! empty until call to EndShell or EndSolid
  Standard_EXPORT occ::handle<IGESSolid_EdgeList> EdgeList() const;

  //! Begins the definition of a new Loop : it is the Current Loop
  //! All Edges (UV) defined by MakeEdge/EndEdge will be added in it
  //! The Loop can then be referenced but is empty. It will be
  //! filled with its Edges(UV) by EndLoop (from SetOuter/AddInner)
  Standard_EXPORT void MakeLoop();

  //! Defines an Edge(UV), to be added in the current Loop by EndEdge
  //! <edgetype> gives the type of the edge
  //! <edge3d> identifies the Edge(3D) used as support
  //! The EdgeList is always the current one
  //! <orientation gives the orientation flag
  //! It is then necessary to :
  //! - give the parametric curves
  //! - close the definition of this edge(UV) by EndEdge, else
  //! the next call to MakeEdge will erase this one
  Standard_EXPORT void MakeEdge(const int edgetype, const int edge3d, const int orientation);

  //! Adds a Parametric Curve (UV) to the current Edge(UV)
  Standard_EXPORT void AddCurveUV(const occ::handle<IGESData_IGESEntity>& curve, const int iso);

  //! Closes the definition of an Edge(UV) and adds it to the
  //! current Loop
  Standard_EXPORT void EndEdge();

  //! Begins the definition of a new Face, on a surface
  //! All Loops defined by MakeLoop will be added in it, according
  //! the closing call : SetOuter for the Outer Loop (by default,
  //! if SetOuter is not called, no OuterLoop is defined);
  //! AddInner for the list of Inner Loops (there can be none)
  Standard_EXPORT void MakeFace(const occ::handle<IGESData_IGESEntity>& surface);

  //! Closes the current Loop and sets it Loop as Outer Loop. If no
  //! current Loop has yet been defined, does nothing.
  Standard_EXPORT void SetOuter();

  //! Closes the current Loop and adds it to the list of Inner Loops
  //! for the current Face
  Standard_EXPORT void AddInner();

  //! Closes the definition of the current Face, fills it and adds
  //! it to the current Shell with an orientation flag (0/1)
  Standard_EXPORT void EndFace(const int orientation);

  //! Begins the definition of a new Shell (either Simple or in a
  //! Solid)
  Standard_EXPORT void MakeShell();

  //! Closes the whole definition as that of a simple Shell
  Standard_EXPORT void EndSimpleShell();

  //! Closes the definition of the current Shell as for the Main
  //! Shell of a Solid, with an orientation flag (0/1)
  Standard_EXPORT void SetMainShell(const int orientation);

  //! Closes the definition of the current Shell and adds it to the
  //! list of Void Shells of a Solid, with an orientation flag (0/1)
  Standard_EXPORT void AddVoidShell(const int orientation);

  //! Closes the whole definition as that of a ManifoldSolid
  //! Its call is exclusive from that of EndSimpleShell
  Standard_EXPORT void EndSolid();

  //! Returns the current Shell. The current Shell is created empty
  //! by MakeShell and filled by EndShell
  Standard_EXPORT occ::handle<IGESSolid_Shell> Shell() const;

  //! Returns the current ManifoldSolid. It is created empty by
  //! Create and filled by EndSolid
  Standard_EXPORT occ::handle<IGESSolid_ManifoldSolid> Solid() const;

protected:
  //! Closes the definition of Vertex and Edge Lists
  //! Warning : Called only by EndSimpleShell and EndSolid
  Standard_EXPORT void EndLists();

  //! Closes the definition of a Loop and fills it
  //! Warning : EndLoop should not be called directly but through
  //! SetOuter or AddInner, which work on the current Face
  Standard_EXPORT void EndLoop();

  //! Closes the definition of the current Shell
  //! Warning : EndShell should not be called directly but through
  //! EndSimpleShell (for a simple Shell), SetMainShell (for main
  //! Shell of a Solid) or AddVoidShell (to a Solid)
  Standard_EXPORT void EndShell();

private:
  occ::handle<IGESSolid_ManifoldSolid>                                thesolid;
  occ::handle<IGESSolid_Shell>                                        themains;
  bool                                                                themflag;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thevoids;
  occ::handle<NCollection_HSequence<int>>                             thevflag;
  occ::handle<IGESSolid_Shell>                                        theshell;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thefaces;
  occ::handle<NCollection_HSequence<int>>                             thefflag;
  occ::handle<IGESSolid_Face>                                         theface;
  occ::handle<IGESData_IGESEntity>                                    thesurf;
  bool                                                                theouter;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> theinner;
  occ::handle<IGESSolid_Loop>                                         theloop;
  occ::handle<NCollection_HSequence<int>>                             theetype;
  occ::handle<NCollection_HSequence<int>>                             thee3d;
  occ::handle<NCollection_HSequence<int>>                             theeflag;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> theeuv;
  occ::handle<NCollection_HSequence<int>>                             theisol;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thecuruv;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> theiso;
  occ::handle<IGESSolid_EdgeList>                                     theedgel;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thecur3d;
  occ::handle<NCollection_HSequence<int>>                             thevstar;
  occ::handle<NCollection_HSequence<int>>                             thevend;
  occ::handle<IGESSolid_VertexList>                                   thevertl;
  occ::handle<NCollection_HSequence<gp_XYZ>>                          thepoint;
};
