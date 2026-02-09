#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ChFi3d_ChBuilder.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <BRepFilletAPI_LocalOperation.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_CircSection.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TopoDS_Shape;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Vertex;
class TopOpeBRepBuild_HBuilder;

class BRepFilletAPI_MakeChamfer : public BRepFilletAPI_LocalOperation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFilletAPI_MakeChamfer(const TopoDS_Shape& S);

  Standard_EXPORT void Add(const TopoDS_Edge& E) override;

  Standard_EXPORT void Add(const double Dis, const TopoDS_Edge& E);

  Standard_EXPORT void SetDist(const double Dis, const int IC, const TopoDS_Face& F);

  Standard_EXPORT void GetDist(const int IC, double& Dis) const;

  Standard_EXPORT void Add(const double       Dis1,
                           const double       Dis2,
                           const TopoDS_Edge& E,
                           const TopoDS_Face& F);

  Standard_EXPORT void SetDists(const double       Dis1,
                                const double       Dis2,
                                const int          IC,
                                const TopoDS_Face& F);

  Standard_EXPORT void Dists(const int IC, double& Dis1, double& Dis2) const;

  Standard_EXPORT void AddDA(const double       Dis,
                             const double       Angle,
                             const TopoDS_Edge& E,
                             const TopoDS_Face& F);

  Standard_EXPORT void SetDistAngle(const double       Dis,
                                    const double       Angle,
                                    const int          IC,
                                    const TopoDS_Face& F);

  Standard_EXPORT void GetDistAngle(const int IC, double& Dis, double& Angle) const;

  Standard_EXPORT void SetMode(const ChFiDS_ChamfMode theMode);

  Standard_EXPORT bool IsSymetric(const int IC) const;

  Standard_EXPORT bool IsTwoDistances(const int IC) const;

  Standard_EXPORT bool IsDistanceAngle(const int IC) const;

  Standard_EXPORT void ResetContour(const int IC) override;

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

  Standard_EXPORT void Simulate(const int IC) override;

  Standard_EXPORT int NbSurf(const int IC) const override;

  Standard_EXPORT occ::handle<NCollection_HArray1<ChFiDS_CircSection>> Sect(
    const int IC,
    const int IS) const override;

private:
  ChFi3d_ChBuilder                                       myBuilder;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};
