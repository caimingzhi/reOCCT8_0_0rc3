#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <ChFi2d_ConstructionError.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>

class TopoDS_Edge;
class TopoDS_Vertex;

#ifdef Status
  #undef Status
#endif

class ChFi2d_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFi2d_Builder();

  Standard_EXPORT ChFi2d_Builder(const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Face& RefFace, const TopoDS_Face& ModFace);

  Standard_EXPORT TopoDS_Edge AddFillet(const TopoDS_Vertex& V, const double Radius);

  Standard_EXPORT TopoDS_Edge ModifyFillet(const TopoDS_Edge& Fillet, const double Radius);

  Standard_EXPORT TopoDS_Vertex RemoveFillet(const TopoDS_Edge& Fillet);

  Standard_EXPORT TopoDS_Edge AddChamfer(const TopoDS_Edge& E1,
                                         const TopoDS_Edge& E2,
                                         const double       D1,
                                         const double       D2);

  Standard_EXPORT TopoDS_Edge AddChamfer(const TopoDS_Edge&   E,
                                         const TopoDS_Vertex& V,
                                         const double         D,
                                         const double         Ang);

  Standard_EXPORT TopoDS_Edge ModifyChamfer(const TopoDS_Edge& Chamfer,
                                            const TopoDS_Edge& E1,
                                            const TopoDS_Edge& E2,
                                            const double       D1,
                                            const double       D2);

  Standard_EXPORT TopoDS_Edge ModifyChamfer(const TopoDS_Edge& Chamfer,
                                            const TopoDS_Edge& E,
                                            const double       D,
                                            const double       Ang);

  Standard_EXPORT TopoDS_Vertex RemoveChamfer(const TopoDS_Edge& Chamfer);

  TopoDS_Face Result() const;

  bool IsModified(const TopoDS_Edge& E) const;

  const NCollection_Sequence<TopoDS_Shape>& FilletEdges() const;

  int NbFillet() const;

  const NCollection_Sequence<TopoDS_Shape>& ChamferEdges() const;

  int NbChamfer() const;

  bool HasDescendant(const TopoDS_Edge& E) const;

  const TopoDS_Edge& DescendantEdge(const TopoDS_Edge& E) const;

  Standard_EXPORT const TopoDS_Edge& BasisEdge(const TopoDS_Edge& E) const;

  ChFi2d_ConstructionError Status() const;

private:
  Standard_EXPORT void ComputeFillet(const TopoDS_Vertex& V,
                                     const TopoDS_Edge&   E1,
                                     const TopoDS_Edge&   E2,
                                     const double         Radius,
                                     TopoDS_Edge&         TrimE1,
                                     TopoDS_Edge&         TrimE2,
                                     TopoDS_Edge&         Fillet);

  Standard_EXPORT void ComputeChamfer(const TopoDS_Vertex& V,
                                      const TopoDS_Edge&   E1,
                                      const TopoDS_Edge&   E2,
                                      const double         D1,
                                      const double         D2,
                                      TopoDS_Edge&         TrimE1,
                                      TopoDS_Edge&         TrimE2,
                                      TopoDS_Edge&         Chamfer);

  Standard_EXPORT void ComputeChamfer(const TopoDS_Vertex& V,
                                      const TopoDS_Edge&   E1,
                                      const double         D,
                                      const double         Ang,
                                      const TopoDS_Edge&   E2,
                                      TopoDS_Edge&         TrimE1,
                                      TopoDS_Edge&         TrimE2,
                                      TopoDS_Edge&         Chamfer);

  Standard_EXPORT TopoDS_Edge BuildFilletEdge(const TopoDS_Vertex& V,
                                              const TopoDS_Edge&   AdjEdge1,
                                              const TopoDS_Edge&   AdjEdge2,
                                              const double         Radius,
                                              TopoDS_Vertex&       NewExtr1,
                                              TopoDS_Vertex&       NewExtr2);

  Standard_EXPORT TopoDS_Edge BuildChamferEdge(const TopoDS_Vertex& V,
                                               const TopoDS_Edge&   AdjEdge1,
                                               const TopoDS_Edge&   AdjEdge2,
                                               const double         D1,
                                               const double         D2,
                                               TopoDS_Vertex&       NewExtr1,
                                               TopoDS_Vertex&       NewExtr2);

  Standard_EXPORT TopoDS_Edge BuildChamferEdge(const TopoDS_Vertex& V,
                                               const TopoDS_Edge&   AdjEdge2,
                                               const double         D,
                                               const double         Ang,
                                               const TopoDS_Edge&   AdjEdge1,
                                               TopoDS_Vertex&       NewExtr1,
                                               TopoDS_Vertex&       NewExtr2);

  Standard_EXPORT void BuildNewWire(const TopoDS_Edge& OldE1,
                                    const TopoDS_Edge& OldE2,
                                    const TopoDS_Edge& E1,
                                    const TopoDS_Edge& Fillet,
                                    const TopoDS_Edge& E2);

  Standard_EXPORT TopoDS_Edge BuildNewEdge(const TopoDS_Edge&   E1,
                                           const TopoDS_Vertex& OldExtr,
                                           const TopoDS_Vertex& NewExtr) const;

  Standard_EXPORT TopoDS_Edge BuildNewEdge(const TopoDS_Edge&   E1,
                                           const TopoDS_Vertex& OldExtr,
                                           const TopoDS_Vertex& NewExtr,
                                           bool&                IsDegenerated) const;

  Standard_EXPORT void UpDateHistory(const TopoDS_Edge& E1,
                                     const TopoDS_Edge& E2,
                                     const TopoDS_Edge& TrimE1,
                                     const TopoDS_Edge& TrimE2,
                                     const TopoDS_Edge& NewEdge,
                                     const int          Id);

  Standard_EXPORT void UpDateHistory(const TopoDS_Edge& E1,
                                     const TopoDS_Edge& E2,
                                     const TopoDS_Edge& TrimE1,
                                     const TopoDS_Edge& TrimE2);

  Standard_EXPORT bool IsAFillet(const TopoDS_Edge& E) const;

  Standard_EXPORT bool IsAChamfer(const TopoDS_Edge& E) const;

  ChFi2d_ConstructionError                                                 status;
  TopoDS_Face                                                              refFace;
  TopoDS_Face                                                              newFace;
  NCollection_Sequence<TopoDS_Shape>                                       fillets;
  NCollection_Sequence<TopoDS_Shape>                                       chamfers;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> history;
};

#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Face.hpp>

inline TopoDS_Face ChFi2d_Builder::Result() const
{
  TopoDS_Face aFace = newFace;
  aFace.Orientation(refFace.Orientation());
  return aFace;
}

inline bool ChFi2d_Builder::IsModified(const TopoDS_Edge& E) const
{
  return history.IsBound(E);
}

inline const NCollection_Sequence<TopoDS_Shape>& ChFi2d_Builder::FilletEdges() const
{
  return fillets;
}

inline const NCollection_Sequence<TopoDS_Shape>& ChFi2d_Builder::ChamferEdges() const
{
  return chamfers;
}

inline int ChFi2d_Builder::NbFillet() const
{
  return fillets.Length();
}

inline int ChFi2d_Builder::NbChamfer() const
{
  return chamfers.Length();
}

inline bool ChFi2d_Builder::HasDescendant(const TopoDS_Edge& E) const
{
  return history.IsBound(E);
}

inline const TopoDS_Edge& ChFi2d_Builder::DescendantEdge(const TopoDS_Edge& E) const
{
  return TopoDS::Edge(history.Find(E));
}

inline ChFi2d_ConstructionError ChFi2d_Builder::Status() const
{
  return status;
}
