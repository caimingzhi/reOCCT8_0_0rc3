#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ChFi3d_FilBuilder.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <BRepFilletAPI_LocalOperation.hpp>
#include <ChFi3d_FilletShape.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_CircSection.hpp>
#include <NCollection_HArray1.hpp>
#include <ChFiDS_ErrorStatus.hpp>
class TopoDS_Shape;
class TopoDS_Edge;
class Law_Function;
class TopoDS_Vertex;
class TopOpeBRepBuild_HBuilder;
class Geom_Surface;

class BRepFilletAPI_MakeFillet : public BRepFilletAPI_LocalOperation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFilletAPI_MakeFillet(const TopoDS_Shape&      S,
                                           const ChFi3d_FilletShape FShape = ChFi3d_Rational);

  Standard_EXPORT void SetParams(const double Tang,
                                 const double Tesp,
                                 const double T2d,
                                 const double TApp3d,
                                 const double TolApp2d,
                                 const double Fleche);

  Standard_EXPORT void SetContinuity(const GeomAbs_Shape InternalContinuity,
                                     const double        AngularTolerance);

  Standard_EXPORT void Add(const TopoDS_Edge& E) override;

  Standard_EXPORT void Add(const double Radius, const TopoDS_Edge& E);

  Standard_EXPORT void Add(const double R1, const double R2, const TopoDS_Edge& E);

  Standard_EXPORT void Add(const occ::handle<Law_Function>& L, const TopoDS_Edge& E);

  Standard_EXPORT void Add(const NCollection_Array1<gp_Pnt2d>& UandR, const TopoDS_Edge& E);

  Standard_EXPORT void SetRadius(const double Radius, const int IC, const int IinC);

  Standard_EXPORT void SetRadius(const double R1, const double R2, const int IC, const int IinC);

  Standard_EXPORT void SetRadius(const occ::handle<Law_Function>& L, const int IC, const int IinC);

  Standard_EXPORT void SetRadius(const NCollection_Array1<gp_Pnt2d>& UandR,
                                 const int                           IC,
                                 const int                           IinC);

  Standard_EXPORT void ResetContour(const int IC) override;

  Standard_EXPORT bool IsConstant(const int IC);

  Standard_EXPORT double Radius(const int IC);

  Standard_EXPORT bool IsConstant(const int IC, const TopoDS_Edge& E);

  Standard_EXPORT double Radius(const int IC, const TopoDS_Edge& E);

  Standard_EXPORT void SetRadius(const double Radius, const int IC, const TopoDS_Edge& E);

  Standard_EXPORT void SetRadius(const double Radius, const int IC, const TopoDS_Vertex& V);

  Standard_EXPORT bool GetBounds(const int IC, const TopoDS_Edge& E, double& F, double& L);

  Standard_EXPORT occ::handle<Law_Function> GetLaw(const int IC, const TopoDS_Edge& E);

  Standard_EXPORT void SetLaw(const int                        IC,
                              const TopoDS_Edge&               E,
                              const occ::handle<Law_Function>& L);

  Standard_EXPORT void SetFilletShape(const ChFi3d_FilletShape FShape);

  Standard_EXPORT ChFi3d_FilletShape GetFilletShape() const;

  Standard_EXPORT int NbContours() const override;

  Standard_EXPORT int Contour(const TopoDS_Edge& E) const override;

  Standard_EXPORT int NbEdges(const int I) const override;

  Standard_EXPORT const TopoDS_Edge& Edge(const int I, const int J) const override;

  Standard_EXPORT void Remove(const TopoDS_Edge& E) override;

  Standard_EXPORT double Length(const int IC) const override;

  Standard_EXPORT TopoDS_Vertex FirstVertex(const int IC) const override;

  Standard_EXPORT TopoDS_Vertex LastVertex(const int IC) const override;

  Standard_EXPORT double Abscissa(const int IC, const TopoDS_Vertex& V) const override;

  Standard_EXPORT double RelativeAbscissa(const int IC, const TopoDS_Vertex& V) const override;

  Standard_EXPORT bool ClosedAndTangent(const int IC) const override;

  Standard_EXPORT bool Closed(const int IC) const override;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void Reset() override;

  Standard_EXPORT occ::handle<TopOpeBRepBuild_HBuilder> Builder() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(
    const TopoDS_Shape& EorV) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& F) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& F) override;

  Standard_EXPORT int NbSurfaces() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& NewFaces(const int I);

  Standard_EXPORT void Simulate(const int IC) override;

  Standard_EXPORT int NbSurf(const int IC) const override;

  Standard_EXPORT occ::handle<NCollection_HArray1<ChFiDS_CircSection>> Sect(
    const int IC,
    const int IS) const override;

  Standard_EXPORT int NbFaultyContours() const;

  Standard_EXPORT int FaultyContour(const int I) const;

  Standard_EXPORT int NbComputedSurfaces(const int IC) const;

  Standard_EXPORT occ::handle<Geom_Surface> ComputedSurface(const int IC, const int IS) const;

  Standard_EXPORT int NbFaultyVertices() const;

  Standard_EXPORT TopoDS_Vertex FaultyVertex(const int IV) const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT TopoDS_Shape BadShape() const;

  Standard_EXPORT ChFiDS_ErrorStatus StripeStatus(const int IC) const;

private:
  ChFi3d_FilBuilder                                      myBuilder;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};
