#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Face.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_List.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <TopAbs_State.hpp>
#include <TopAbs_Orientation.hpp>

class Adaptor3d_HVertex;
class gp_Pnt2d;
class gp_Pnt;

class BRepTopAdaptor_TopolTool : public Adaptor3d_TopolTool
{

public:
  Standard_EXPORT BRepTopAdaptor_TopolTool();

  Standard_EXPORT BRepTopAdaptor_TopolTool(const occ::handle<Adaptor3d_Surface>& Surface);

  Standard_EXPORT void Initialize() override;

  Standard_EXPORT void Initialize(const occ::handle<Adaptor3d_Surface>& S) override;

  Standard_EXPORT void Initialize(const occ::handle<Adaptor2d_Curve2d>& Curve) override;

  Standard_EXPORT void Init() override;

  Standard_EXPORT bool More() override;

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> Value() override;

  Standard_EXPORT void Next() override;

  Standard_EXPORT void* Edge() const override;

  Standard_EXPORT void InitVertexIterator() override;

  Standard_EXPORT bool MoreVertex() override;

  Standard_EXPORT occ::handle<Adaptor3d_HVertex> Vertex() override;

  Standard_EXPORT void NextVertex() override;

  Standard_EXPORT TopAbs_State Classify(const gp_Pnt2d& P2d,
                                        const double    Tol,
                                        const bool      RecadreOnPeriodic = true) override;

  Standard_EXPORT bool IsThePointOn(const gp_Pnt2d& P2d,
                                    const double    Tol,
                                    const bool      RecadreOnPeriodic = true) override;

  Standard_EXPORT TopAbs_Orientation Orientation(const occ::handle<Adaptor2d_Curve2d>& C) override;

  Standard_EXPORT TopAbs_Orientation Orientation(const occ::handle<Adaptor3d_HVertex>& C) override;

  Standard_EXPORT void Destroy();

  ~BRepTopAdaptor_TopolTool() override { Destroy(); }

  Standard_EXPORT bool Has3d() const override;

  Standard_EXPORT double Tol3d(const occ::handle<Adaptor2d_Curve2d>& C) const override;

  Standard_EXPORT double Tol3d(const occ::handle<Adaptor3d_HVertex>& V) const override;

  Standard_EXPORT gp_Pnt Pnt(const occ::handle<Adaptor3d_HVertex>& V) const override;

  Standard_EXPORT void ComputeSamplePoints() override;

  Standard_EXPORT int NbSamplesU() override;

  Standard_EXPORT int NbSamplesV() override;

  Standard_EXPORT int NbSamples() override;

  Standard_EXPORT void SamplePoint(const int Index, gp_Pnt2d& P2d, gp_Pnt& P3d) override;

  Standard_EXPORT bool DomainIsInfinite() override;

  DEFINE_STANDARD_RTTIEXT(BRepTopAdaptor_TopolTool, Adaptor3d_TopolTool)

private:
  TopExp_Explorer                                             myVIterator;
  TopoDS_Face                                                 myFace;
  void*                                                       myFClass2d;
  occ::handle<BRepAdaptor_Curve2d>                            myCurve;
  NCollection_List<occ::handle<Standard_Transient>>           myCurves;
  NCollection_List<occ::handle<Standard_Transient>>::Iterator myCIterator;
  double                                                      myU0;
  double                                                      myV0;
  double                                                      myDU;
  double                                                      myDV;
};
