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

class IGESSolid_TopoBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESSolid_TopoBuilder();

  Standard_EXPORT void Clear();

  Standard_EXPORT void AddVertex(const gp_XYZ& val);

  Standard_EXPORT int NbVertices() const;

  Standard_EXPORT const gp_XYZ& Vertex(const int num) const;

  Standard_EXPORT occ::handle<IGESSolid_VertexList> VertexList() const;

  Standard_EXPORT void AddEdge(const occ::handle<IGESData_IGESEntity>& curve,
                               const int                               vstart,
                               const int                               vend);

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT void Edge(const int                         num,
                            occ::handle<IGESData_IGESEntity>& curve,
                            int&                              vstart,
                            int&                              vend) const;

  Standard_EXPORT occ::handle<IGESSolid_EdgeList> EdgeList() const;

  Standard_EXPORT void MakeLoop();

  Standard_EXPORT void MakeEdge(const int edgetype, const int edge3d, const int orientation);

  Standard_EXPORT void AddCurveUV(const occ::handle<IGESData_IGESEntity>& curve, const int iso);

  Standard_EXPORT void EndEdge();

  Standard_EXPORT void MakeFace(const occ::handle<IGESData_IGESEntity>& surface);

  Standard_EXPORT void SetOuter();

  Standard_EXPORT void AddInner();

  Standard_EXPORT void EndFace(const int orientation);

  Standard_EXPORT void MakeShell();

  Standard_EXPORT void EndSimpleShell();

  Standard_EXPORT void SetMainShell(const int orientation);

  Standard_EXPORT void AddVoidShell(const int orientation);

  Standard_EXPORT void EndSolid();

  Standard_EXPORT occ::handle<IGESSolid_Shell> Shell() const;

  Standard_EXPORT occ::handle<IGESSolid_ManifoldSolid> Solid() const;

protected:
  Standard_EXPORT void EndLists();

  Standard_EXPORT void EndLoop();

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
