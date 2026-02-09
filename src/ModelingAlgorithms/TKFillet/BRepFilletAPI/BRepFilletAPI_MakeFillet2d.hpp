#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ChFi2d_Builder.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_List.hpp>
#include <ChFi2d_ConstructionError.hpp>
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Shape;

#ifdef Status
  #undef Status
#endif

class BRepFilletAPI_MakeFillet2d : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFilletAPI_MakeFillet2d();

  Standard_EXPORT BRepFilletAPI_MakeFillet2d(const TopoDS_Face& F);

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

  bool IsModified(const TopoDS_Edge& E) const;

  const NCollection_Sequence<TopoDS_Shape>& FilletEdges() const;

  int NbFillet() const;

  const NCollection_Sequence<TopoDS_Shape>& ChamferEdges() const;

  int NbChamfer() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;

  Standard_EXPORT int NbCurves() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& NewEdges(const int I);

  bool HasDescendant(const TopoDS_Edge& E) const;

  const TopoDS_Edge& DescendantEdge(const TopoDS_Edge& E) const;

  Standard_EXPORT const TopoDS_Edge& BasisEdge(const TopoDS_Edge& E) const;

  ChFi2d_ConstructionError Status() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

private:
  ChFi2d_Builder myMakeChFi2d;
};

inline bool BRepFilletAPI_MakeFillet2d::IsModified(const TopoDS_Edge& E) const
{
  return myMakeChFi2d.IsModified(E);
}

inline const NCollection_Sequence<TopoDS_Shape>& BRepFilletAPI_MakeFillet2d::FilletEdges() const
{
  return myMakeChFi2d.FilletEdges();
}

inline int BRepFilletAPI_MakeFillet2d::NbFillet() const
{
  return myMakeChFi2d.NbFillet();
}

inline const NCollection_Sequence<TopoDS_Shape>& BRepFilletAPI_MakeFillet2d::ChamferEdges() const
{
  return myMakeChFi2d.ChamferEdges();
}

inline int BRepFilletAPI_MakeFillet2d::NbChamfer() const
{
  return myMakeChFi2d.NbChamfer();
}

inline bool BRepFilletAPI_MakeFillet2d::HasDescendant(const TopoDS_Edge& E) const
{
  return myMakeChFi2d.HasDescendant(E);
}

inline const TopoDS_Edge& BRepFilletAPI_MakeFillet2d::DescendantEdge(const TopoDS_Edge& E) const
{
  return myMakeChFi2d.DescendantEdge(E);
}

inline ChFi2d_ConstructionError BRepFilletAPI_MakeFillet2d::Status() const
{
  return myMakeChFi2d.Status();
}
