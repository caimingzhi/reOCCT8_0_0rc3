#pragma once

#include <BRepAdaptor_Curve2d.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <ChFiDS_ErrorStatus.hpp>
#include <ChFiDS_Map.hpp>
#include <ChFiDS_Regul.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_SurfData.hpp>
#include <NCollection_Sequence.hpp>
#include <ChFiDS_StripeMap.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <math_Vector.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>

class TopOpeBRepDS_HDataStructure;
class TopOpeBRepBuild_HBuilder;
class TopoDS_Edge;
class ChFiDS_Spine;
class TopoDS_Vertex;
class Geom_Surface;
class ChFiDS_SurfData;
class Adaptor3d_TopolTool;
class BRepBlend_Line;
class Blend_Function;
class Blend_FuncInv;
class Blend_SurfRstFunction;
class Blend_SurfPointFuncInv;
class Blend_SurfCurvFuncInv;
class Blend_RstRstFunction;
class Blend_CurvPointFuncInv;
class ChFiDS_Stripe;
class BRepTopAdaptor_TopolTool;
class gp_Pnt2d;
class ChFiDS_CommonPoint;
class TopoDS_Face;
class AppBlend_Approx;
class Geom2d_Curve;

class ChFi3d_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual ~ChFi3d_Builder();

  Standard_EXPORT void SetParams(const double Tang,
                                 const double Tesp,
                                 const double T2d,
                                 const double TApp3d,
                                 const double TolApp2d,
                                 const double Fleche);

  Standard_EXPORT void SetContinuity(const GeomAbs_Shape InternalContinuity,
                                     const double        AngularTolerance);

  Standard_EXPORT void Remove(const TopoDS_Edge& E);

  Standard_EXPORT int Contains(const TopoDS_Edge& E) const;

  Standard_EXPORT int Contains(const TopoDS_Edge& E, int& IndexInSpine) const;

  Standard_EXPORT int NbElements() const;

  Standard_EXPORT occ::handle<ChFiDS_Spine> Value(const int I) const;

  Standard_EXPORT double Length(const int IC) const;

  Standard_EXPORT TopoDS_Vertex FirstVertex(const int IC) const;

  Standard_EXPORT TopoDS_Vertex LastVertex(const int IC) const;

  Standard_EXPORT double Abscissa(const int IC, const TopoDS_Vertex& V) const;

  Standard_EXPORT double RelativeAbscissa(const int IC, const TopoDS_Vertex& V) const;

  Standard_EXPORT bool ClosedAndTangent(const int IC) const;

  Standard_EXPORT bool Closed(const int IC) const;

  Standard_EXPORT void Compute();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT TopoDS_Shape Shape() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& EouV);

  Standard_EXPORT int NbFaultyContours() const;

  Standard_EXPORT int FaultyContour(const int I) const;

  Standard_EXPORT int NbComputedSurfaces(const int IC) const;

  Standard_EXPORT occ::handle<Geom_Surface> ComputedSurface(const int IC, const int IS) const;

  Standard_EXPORT int NbFaultyVertices() const;

  Standard_EXPORT TopoDS_Vertex FaultyVertex(const int IV) const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT TopoDS_Shape BadShape() const;

  Standard_EXPORT ChFiDS_ErrorStatus StripeStatus(const int IC) const;

  Standard_EXPORT void Reset();

  Standard_EXPORT occ::handle<TopOpeBRepBuild_HBuilder> Builder() const;

  Standard_EXPORT bool SplitKPart(const occ::handle<ChFiDS_SurfData>&                 Data,
                                  NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SetData,
                                  const occ::handle<ChFiDS_Spine>&                    Spine,
                                  const int                                           Iedge,
                                  const occ::handle<Adaptor3d_Surface>&               S1,
                                  const occ::handle<Adaptor3d_TopolTool>&             I1,
                                  const occ::handle<Adaptor3d_Surface>&               S2,
                                  const occ::handle<Adaptor3d_TopolTool>&             I2,
                                  bool&                                               Intf,
                                  bool&                                               Intl);

  Standard_EXPORT bool PerformTwoCornerbyInter(const int Index);

protected:
  Standard_EXPORT ChFi3d_Builder(const TopoDS_Shape& S, const double Ta);

  Standard_EXPORT virtual void SimulKPart(const occ::handle<ChFiDS_SurfData>& SD) const = 0;

  Standard_EXPORT virtual bool SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
                                         const occ::handle<ChFiDS_ElSpine>&      Guide,
                                         const occ::handle<ChFiDS_Spine>&        Spine,
                                         const int                               Choix,
                                         const occ::handle<BRepAdaptor_Surface>& S1,
                                         const occ::handle<Adaptor3d_TopolTool>& I1,
                                         const occ::handle<BRepAdaptor_Surface>& S2,
                                         const occ::handle<Adaptor3d_TopolTool>& I2,
                                         const double                            TolGuide,
                                         double&                                 First,
                                         double&                                 Last,
                                         const bool                              Inside,
                                         const bool                              Appro,
                                         const bool                              Forward,
                                         const bool                              RecOnS1,
                                         const bool                              RecOnS2,
                                         const math_Vector&                      Soldep,
                                         int&                                    Intf,
                                         int&                                    Intl) = 0;

  Standard_EXPORT virtual void SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
                                         const occ::handle<ChFiDS_ElSpine>&      Guide,
                                         const occ::handle<ChFiDS_Spine>&        Spine,
                                         const int                               Choix,
                                         const occ::handle<BRepAdaptor_Surface>& S1,
                                         const occ::handle<Adaptor3d_TopolTool>& I1,
                                         const occ::handle<BRepAdaptor_Curve2d>& PC1,
                                         const occ::handle<BRepAdaptor_Surface>& Sref1,
                                         const occ::handle<BRepAdaptor_Curve2d>& PCref1,
                                         bool&                                   Decroch1,
                                         const occ::handle<BRepAdaptor_Surface>& S2,
                                         const occ::handle<Adaptor3d_TopolTool>& I2,
                                         const TopAbs_Orientation                Or2,
                                         const double                            Fleche,
                                         const double                            TolGuide,
                                         double&                                 First,
                                         double&                                 Last,
                                         const bool                              Inside,
                                         const bool                              Appro,
                                         const bool                              Forward,
                                         const bool                              RecP,
                                         const bool                              RecS,
                                         const bool                              RecRst,
                                         const math_Vector&                      Soldep);

  Standard_EXPORT virtual void SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
                                         const occ::handle<ChFiDS_ElSpine>&      Guide,
                                         const occ::handle<ChFiDS_Spine>&        Spine,
                                         const int                               Choix,
                                         const occ::handle<BRepAdaptor_Surface>& S1,
                                         const occ::handle<Adaptor3d_TopolTool>& I1,
                                         const TopAbs_Orientation                Or1,
                                         const occ::handle<BRepAdaptor_Surface>& S2,
                                         const occ::handle<Adaptor3d_TopolTool>& I2,
                                         const occ::handle<BRepAdaptor_Curve2d>& PC2,
                                         const occ::handle<BRepAdaptor_Surface>& Sref2,
                                         const occ::handle<BRepAdaptor_Curve2d>& PCref2,
                                         bool&                                   Decroch2,
                                         const double                            Fleche,
                                         const double                            TolGuide,
                                         double&                                 First,
                                         double&                                 Last,
                                         const bool                              Inside,
                                         const bool                              Appro,
                                         const bool                              Forward,
                                         const bool                              RecP,
                                         const bool                              RecS,
                                         const bool                              RecRst,
                                         const math_Vector&                      Soldep);

  Standard_EXPORT virtual void SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
                                         const occ::handle<ChFiDS_ElSpine>&      Guide,
                                         const occ::handle<ChFiDS_Spine>&        Spine,
                                         const int                               Choix,
                                         const occ::handle<BRepAdaptor_Surface>& S1,
                                         const occ::handle<Adaptor3d_TopolTool>& I1,
                                         const occ::handle<BRepAdaptor_Curve2d>& PC1,
                                         const occ::handle<BRepAdaptor_Surface>& Sref1,
                                         const occ::handle<BRepAdaptor_Curve2d>& PCref1,
                                         bool&                                   Decroch1,
                                         const TopAbs_Orientation                Or1,
                                         const occ::handle<BRepAdaptor_Surface>& S2,
                                         const occ::handle<Adaptor3d_TopolTool>& I2,
                                         const occ::handle<BRepAdaptor_Curve2d>& PC2,
                                         const occ::handle<BRepAdaptor_Surface>& Sref2,
                                         const occ::handle<BRepAdaptor_Curve2d>& PCref2,
                                         bool&                                   Decroch2,
                                         const TopAbs_Orientation                Or2,
                                         const double                            Fleche,
                                         const double                            TolGuide,
                                         double&                                 First,
                                         double&                                 Last,
                                         const bool                              Inside,
                                         const bool                              Appro,
                                         const bool                              Forward,
                                         const bool                              RecP1,
                                         const bool                              RecRst1,
                                         const bool                              RecP2,
                                         const bool                              RecRst2,
                                         const math_Vector&                      Soldep);

  Standard_EXPORT bool SimulData(occ::handle<ChFiDS_SurfData>&           Data,
                                 const occ::handle<ChFiDS_ElSpine>&      Guide,
                                 const occ::handle<ChFiDS_ElSpine>&      AdditionalGuide,
                                 occ::handle<BRepBlend_Line>&            Lin,
                                 const occ::handle<Adaptor3d_Surface>&   S1,
                                 const occ::handle<Adaptor3d_TopolTool>& I1,
                                 const occ::handle<Adaptor3d_Surface>&   S2,
                                 const occ::handle<Adaptor3d_TopolTool>& I2,
                                 Blend_Function&                         Func,
                                 Blend_FuncInv&                          FInv,
                                 const double                            PFirst,
                                 const double                            MaxStep,
                                 const double                            Fleche,
                                 const double                            TolGuide,
                                 double&                                 First,
                                 double&                                 Last,
                                 const bool                              Inside,
                                 const bool                              Appro,
                                 const bool                              Forward,
                                 const math_Vector&                      Soldep,
                                 const int                               NbSecMin,
                                 const bool                              RecOnS1 = false,
                                 const bool                              RecOnS2 = false);

  Standard_EXPORT bool SimulData(occ::handle<ChFiDS_SurfData>&           Data,
                                 const occ::handle<ChFiDS_ElSpine>&      HGuide,
                                 occ::handle<BRepBlend_Line>&            Lin,
                                 const occ::handle<Adaptor3d_Surface>&   S1,
                                 const occ::handle<Adaptor3d_TopolTool>& I1,
                                 const occ::handle<Adaptor3d_Surface>&   S2,
                                 const occ::handle<Adaptor2d_Curve2d>&   PC2,
                                 const occ::handle<Adaptor3d_TopolTool>& I2,
                                 bool&                                   Decroch,
                                 Blend_SurfRstFunction&                  Func,
                                 Blend_FuncInv&                          FInv,
                                 Blend_SurfPointFuncInv&                 FInvP,
                                 Blend_SurfCurvFuncInv&                  FInvC,
                                 const double                            PFirst,
                                 const double                            MaxStep,
                                 const double                            Fleche,
                                 const double                            TolGuide,
                                 double&                                 First,
                                 double&                                 Last,
                                 const math_Vector&                      Soldep,
                                 const int                               NbSecMin,
                                 const bool                              Inside,
                                 const bool                              Appro,
                                 const bool                              Forward,
                                 const bool                              RecP,
                                 const bool                              RecS,
                                 const bool                              RecRst);

  Standard_EXPORT bool SimulData(occ::handle<ChFiDS_SurfData>&           Data,
                                 const occ::handle<ChFiDS_ElSpine>&      HGuide,
                                 occ::handle<BRepBlend_Line>&            Lin,
                                 const occ::handle<Adaptor3d_Surface>&   S1,
                                 const occ::handle<Adaptor2d_Curve2d>&   PC1,
                                 const occ::handle<Adaptor3d_TopolTool>& I1,
                                 bool&                                   Decroch1,
                                 const occ::handle<Adaptor3d_Surface>&   S2,
                                 const occ::handle<Adaptor2d_Curve2d>&   PC2,
                                 const occ::handle<Adaptor3d_TopolTool>& I2,
                                 bool&                                   Decroch2,
                                 Blend_RstRstFunction&                   Func,
                                 Blend_SurfCurvFuncInv&                  FInv1,
                                 Blend_CurvPointFuncInv&                 FInvP1,
                                 Blend_SurfCurvFuncInv&                  FInv2,
                                 Blend_CurvPointFuncInv&                 FInvP2,
                                 const double                            PFirst,
                                 const double                            MaxStep,
                                 const double                            Fleche,
                                 const double                            TolGuide,
                                 double&                                 First,
                                 double&                                 Last,
                                 const math_Vector&                      Soldep,
                                 const int                               NbSecMin,
                                 const bool                              Inside,
                                 const bool                              Appro,
                                 const bool                              Forward,
                                 const bool                              RecP1,
                                 const bool                              RecRst1,
                                 const bool                              RecP2,
                                 const bool                              RecRst2);

  Standard_EXPORT virtual void SetRegul() = 0;

  Standard_EXPORT bool PerformElement(const occ::handle<ChFiDS_Spine>& CElement,
                                      const double                     Offset,
                                      const TopoDS_Face&               theFirstFace);

  Standard_EXPORT void PerformExtremity(const occ::handle<ChFiDS_Spine>& CElement);

  Standard_EXPORT void PerformSetOfSurf(occ::handle<ChFiDS_Stripe>& S, const bool Simul = false);

  Standard_EXPORT void PerformSetOfKPart(occ::handle<ChFiDS_Stripe>& S, const bool Simul = false);

  Standard_EXPORT void PerformSetOfKGen(occ::handle<ChFiDS_Stripe>& S, const bool Simul = false);

  Standard_EXPORT void Trunc(const occ::handle<ChFiDS_SurfData>&   SD,
                             const occ::handle<ChFiDS_Spine>&      Spine,
                             const occ::handle<Adaptor3d_Surface>& S1,
                             const occ::handle<Adaptor3d_Surface>& S2,
                             const int                             iedge,
                             const bool                            isfirst,
                             const int                             cntlFiOnS);

  Standard_EXPORT void CallPerformSurf(occ::handle<ChFiDS_Stripe>&                         Stripe,
                                       const bool                                          Simul,
                                       NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqSD,
                                       occ::handle<ChFiDS_SurfData>&                       SD,
                                       const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                       const occ::handle<ChFiDS_Spine>&                    Spine,
                                       const occ::handle<BRepAdaptor_Surface>&             HS1,
                                       const occ::handle<BRepAdaptor_Surface>&             HS3,
                                       const gp_Pnt2d&                                     P1,
                                       const gp_Pnt2d&                                     P3,
                                       const occ::handle<Adaptor3d_TopolTool>&             I1,
                                       const occ::handle<BRepAdaptor_Surface>&             HS2,
                                       const occ::handle<BRepAdaptor_Surface>&             HS4,
                                       const gp_Pnt2d&                                     P2,
                                       const gp_Pnt2d&                                     P4,
                                       const occ::handle<Adaptor3d_TopolTool>&             I2,
                                       const double                                        MaxStep,
                                       const double                                        Fleche,
                                       const double                                        TolGuide,
                                       double&                                             First,
                                       double&                                             Last,
                                       const bool                                          Inside,
                                       const bool                                          Appro,
                                       const bool                                          Forward,
                                       const bool                                          RecOnS1,
                                       const bool                                          RecOnS2,
                                       math_Vector&                                        Soldep,
                                       int&                                                Intf,
                                       int&                                                Intl,
                                       occ::handle<BRepAdaptor_Surface>&                   Surf1,
                                       occ::handle<BRepAdaptor_Surface>&                   Surf2);

  Standard_EXPORT virtual bool PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Data,
                                           const occ::handle<ChFiDS_ElSpine>&      Guide,
                                           const occ::handle<ChFiDS_Spine>&        Spine,
                                           const int                               Choix,
                                           const occ::handle<BRepAdaptor_Surface>& S1,
                                           const occ::handle<Adaptor3d_TopolTool>& I1,
                                           const occ::handle<BRepAdaptor_Surface>& S2,
                                           const occ::handle<Adaptor3d_TopolTool>& I2,
                                           const double                            MaxStep,
                                           const double                            Fleche,
                                           const double                            TolGuide,
                                           double&                                 First,
                                           double&                                 Last,
                                           const bool                              Inside,
                                           const bool                              Appro,
                                           const bool                              Forward,
                                           const bool                              RecOnS1,
                                           const bool                              RecOnS2,
                                           const math_Vector&                      Soldep,
                                           int&                                    Intf,
                                           int&                                    Intl) = 0;

  Standard_EXPORT virtual void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Data,
                                           const occ::handle<ChFiDS_ElSpine>&      Guide,
                                           const occ::handle<ChFiDS_Spine>&        Spine,
                                           const int                               Choix,
                                           const occ::handle<BRepAdaptor_Surface>& S1,
                                           const occ::handle<Adaptor3d_TopolTool>& I1,
                                           const occ::handle<BRepAdaptor_Curve2d>& PC1,
                                           const occ::handle<BRepAdaptor_Surface>& Sref1,
                                           const occ::handle<BRepAdaptor_Curve2d>& PCref1,
                                           bool&                                   Decroch1,
                                           const occ::handle<BRepAdaptor_Surface>& S2,
                                           const occ::handle<Adaptor3d_TopolTool>& I2,
                                           const TopAbs_Orientation                Or2,
                                           const double                            MaxStep,
                                           const double                            Fleche,
                                           const double                            TolGuide,
                                           double&                                 First,
                                           double&                                 Last,
                                           const bool                              Inside,
                                           const bool                              Appro,
                                           const bool                              Forward,
                                           const bool                              RecP,
                                           const bool                              RecS,
                                           const bool                              RecRst,
                                           const math_Vector&                      Soldep);

  Standard_EXPORT virtual void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Data,
                                           const occ::handle<ChFiDS_ElSpine>&      Guide,
                                           const occ::handle<ChFiDS_Spine>&        Spine,
                                           const int                               Choix,
                                           const occ::handle<BRepAdaptor_Surface>& S1,
                                           const occ::handle<Adaptor3d_TopolTool>& I1,
                                           const TopAbs_Orientation                Or1,
                                           const occ::handle<BRepAdaptor_Surface>& S2,
                                           const occ::handle<Adaptor3d_TopolTool>& I2,
                                           const occ::handle<BRepAdaptor_Curve2d>& PC2,
                                           const occ::handle<BRepAdaptor_Surface>& Sref2,
                                           const occ::handle<BRepAdaptor_Curve2d>& PCref2,
                                           bool&                                   Decroch2,
                                           const double                            MaxStep,
                                           const double                            Fleche,
                                           const double                            TolGuide,
                                           double&                                 First,
                                           double&                                 Last,
                                           const bool                              Inside,
                                           const bool                              Appro,
                                           const bool                              Forward,
                                           const bool                              RecP,
                                           const bool                              RecS,
                                           const bool                              RecRst,
                                           const math_Vector&                      Soldep);

  Standard_EXPORT virtual void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Data,
                                           const occ::handle<ChFiDS_ElSpine>&      Guide,
                                           const occ::handle<ChFiDS_Spine>&        Spine,
                                           const int                               Choix,
                                           const occ::handle<BRepAdaptor_Surface>& S1,
                                           const occ::handle<Adaptor3d_TopolTool>& I1,
                                           const occ::handle<BRepAdaptor_Curve2d>& PC1,
                                           const occ::handle<BRepAdaptor_Surface>& Sref1,
                                           const occ::handle<BRepAdaptor_Curve2d>& PCref1,
                                           bool&                                   Decroch1,
                                           const TopAbs_Orientation                Or1,
                                           const occ::handle<BRepAdaptor_Surface>& S2,
                                           const occ::handle<Adaptor3d_TopolTool>& I2,
                                           const occ::handle<BRepAdaptor_Curve2d>& PC2,
                                           const occ::handle<BRepAdaptor_Surface>& Sref2,
                                           const occ::handle<BRepAdaptor_Curve2d>& PCref2,
                                           bool&                                   Decroch2,
                                           const TopAbs_Orientation                Or2,
                                           const double                            MaxStep,
                                           const double                            Fleche,
                                           const double                            TolGuide,
                                           double&                                 First,
                                           double&                                 Last,
                                           const bool                              Inside,
                                           const bool                              Appro,
                                           const bool                              Forward,
                                           const bool                              RecP1,
                                           const bool                              RecRst1,
                                           const bool                              RecP2,
                                           const bool                              RecRst2,
                                           const math_Vector&                      Soldep);

  Standard_EXPORT virtual void PerformTwoCorner(const int Index) = 0;

  Standard_EXPORT virtual void PerformThreeCorner(const int Index) = 0;

  Standard_EXPORT void PerformMoreThreeCorner(const int Index, const int nbcourb);

  Standard_EXPORT virtual void ExtentOneCorner(const TopoDS_Vertex&              V,
                                               const occ::handle<ChFiDS_Stripe>& S) = 0;

  Standard_EXPORT virtual void ExtentTwoCorner(
    const TopoDS_Vertex&                                V,
    const NCollection_List<occ::handle<ChFiDS_Stripe>>& LS) = 0;

  Standard_EXPORT virtual void ExtentThreeCorner(
    const TopoDS_Vertex&                                V,
    const NCollection_List<occ::handle<ChFiDS_Stripe>>& LS) = 0;

  Standard_EXPORT virtual bool PerformFirstSection(const occ::handle<ChFiDS_Spine>&        S,
                                                   const occ::handle<ChFiDS_ElSpine>&      HGuide,
                                                   const int                               Choix,
                                                   occ::handle<BRepAdaptor_Surface>&       S1,
                                                   occ::handle<BRepAdaptor_Surface>&       S2,
                                                   const occ::handle<Adaptor3d_TopolTool>& I1,
                                                   const occ::handle<Adaptor3d_TopolTool>& I2,
                                                   const double                            Par,
                                                   math_Vector&                            SolDep,
                                                   TopAbs_State&                           Pos1,
                                                   TopAbs_State& Pos2) const = 0;

  Standard_EXPORT bool SearchFace(const occ::handle<ChFiDS_Spine>& Sp,
                                  const ChFiDS_CommonPoint&        Pc,
                                  const TopoDS_Face&               FRef,
                                  TopoDS_Face&                     FVoi) const;

  Standard_EXPORT bool StripeOrientations(const occ::handle<ChFiDS_Spine>& Sp,
                                          TopAbs_Orientation&              Or1,
                                          TopAbs_Orientation&              Or2,
                                          int&                             ChoixConge) const;

  Standard_EXPORT bool ComputeData(occ::handle<ChFiDS_SurfData>&           Data,
                                   const occ::handle<ChFiDS_ElSpine>&      Guide,
                                   const occ::handle<ChFiDS_Spine>&        Spine,
                                   occ::handle<BRepBlend_Line>&            Lin,
                                   const occ::handle<Adaptor3d_Surface>&   S1,
                                   const occ::handle<Adaptor3d_TopolTool>& I1,
                                   const occ::handle<Adaptor3d_Surface>&   S2,
                                   const occ::handle<Adaptor3d_TopolTool>& I2,
                                   Blend_Function&                         Func,
                                   Blend_FuncInv&                          FInv,
                                   const double                            PFirst,
                                   const double                            MaxStep,
                                   const double                            Fleche,
                                   const double                            TolGuide,
                                   double&                                 First,
                                   double&                                 Last,
                                   const bool                              Inside,
                                   const bool                              Appro,
                                   const bool                              Forward,
                                   const math_Vector&                      Soldep,
                                   int&                                    Intf,
                                   int&                                    Intl,
                                   bool&                                   Gd1,
                                   bool&                                   Gd2,
                                   bool&                                   Gf1,
                                   bool&                                   Gf2,
                                   const bool                              RecOnS1 = false,
                                   const bool                              RecOnS2 = false);

  Standard_EXPORT bool ComputeData(occ::handle<ChFiDS_SurfData>&           Data,
                                   const occ::handle<ChFiDS_ElSpine>&      HGuide,
                                   occ::handle<BRepBlend_Line>&            Lin,
                                   const occ::handle<Adaptor3d_Surface>&   S1,
                                   const occ::handle<Adaptor3d_TopolTool>& I1,
                                   const occ::handle<Adaptor3d_Surface>&   S2,
                                   const occ::handle<Adaptor2d_Curve2d>&   PC2,
                                   const occ::handle<Adaptor3d_TopolTool>& I2,
                                   bool&                                   Decroch,
                                   Blend_SurfRstFunction&                  Func,
                                   Blend_FuncInv&                          FInv,
                                   Blend_SurfPointFuncInv&                 FInvP,
                                   Blend_SurfCurvFuncInv&                  FInvC,
                                   const double                            PFirst,
                                   const double                            MaxStep,
                                   const double                            Fleche,
                                   const double                            TolGuide,
                                   double&                                 First,
                                   double&                                 Last,
                                   const math_Vector&                      Soldep,
                                   const bool                              Inside,
                                   const bool                              Appro,
                                   const bool                              Forward,
                                   const bool                              RecP,
                                   const bool                              RecS,
                                   const bool                              RecRst);

  Standard_EXPORT bool ComputeData(occ::handle<ChFiDS_SurfData>&           Data,
                                   const occ::handle<ChFiDS_ElSpine>&      HGuide,
                                   occ::handle<BRepBlend_Line>&            Lin,
                                   const occ::handle<Adaptor3d_Surface>&   S1,
                                   const occ::handle<Adaptor2d_Curve2d>&   PC1,
                                   const occ::handle<Adaptor3d_TopolTool>& I1,
                                   bool&                                   Decroch1,
                                   const occ::handle<Adaptor3d_Surface>&   S2,
                                   const occ::handle<Adaptor2d_Curve2d>&   PC2,
                                   const occ::handle<Adaptor3d_TopolTool>& I2,
                                   bool&                                   Decroch2,
                                   Blend_RstRstFunction&                   Func,
                                   Blend_SurfCurvFuncInv&                  FInv1,
                                   Blend_CurvPointFuncInv&                 FInvP1,
                                   Blend_SurfCurvFuncInv&                  FInv2,
                                   Blend_CurvPointFuncInv&                 FInvP2,
                                   const double                            PFirst,
                                   const double                            MaxStep,
                                   const double                            Fleche,
                                   const double                            TolGuide,
                                   double&                                 First,
                                   double&                                 Last,
                                   const math_Vector&                      Soldep,
                                   const bool                              Inside,
                                   const bool                              Appro,
                                   const bool                              Forward,
                                   const bool                              RecP1,
                                   const bool                              RecRst1,
                                   const bool                              RecP2,
                                   const bool                              RecRst2);

  Standard_EXPORT bool CompleteData(occ::handle<ChFiDS_SurfData>&         Data,
                                    Blend_Function&                       Func,
                                    occ::handle<BRepBlend_Line>&          Lin,
                                    const occ::handle<Adaptor3d_Surface>& S1,
                                    const occ::handle<Adaptor3d_Surface>& S2,
                                    const TopAbs_Orientation              Or1,
                                    const bool                            Gd1,
                                    const bool                            Gd2,
                                    const bool                            Gf1,
                                    const bool                            Gf2,
                                    const bool                            Reversed = false);

  Standard_EXPORT bool CompleteData(occ::handle<ChFiDS_SurfData>&         Data,
                                    Blend_SurfRstFunction&                Func,
                                    occ::handle<BRepBlend_Line>&          Lin,
                                    const occ::handle<Adaptor3d_Surface>& S1,
                                    const occ::handle<Adaptor3d_Surface>& S2,
                                    const TopAbs_Orientation              Or,
                                    const bool                            Reversed);

  Standard_EXPORT bool CompleteData(occ::handle<ChFiDS_SurfData>&         Data,
                                    Blend_RstRstFunction&                 Func,
                                    occ::handle<BRepBlend_Line>&          Lin,
                                    const occ::handle<Adaptor3d_Surface>& S1,
                                    const occ::handle<Adaptor3d_Surface>& S2,
                                    const TopAbs_Orientation              Or);

  Standard_EXPORT bool StoreData(occ::handle<ChFiDS_SurfData>&         Data,
                                 const AppBlend_Approx&                Approx,
                                 const occ::handle<BRepBlend_Line>&    Lin,
                                 const occ::handle<Adaptor3d_Surface>& S1,
                                 const occ::handle<Adaptor3d_Surface>& S2,
                                 const TopAbs_Orientation              Or1,
                                 const bool                            Gd1,
                                 const bool                            Gd2,
                                 const bool                            Gf1,
                                 const bool                            Gf2,
                                 const bool                            Reversed = false);

  Standard_EXPORT bool CompleteData(occ::handle<ChFiDS_SurfData>&         Data,
                                    const occ::handle<Geom_Surface>&      Surfcoin,
                                    const occ::handle<Adaptor3d_Surface>& S1,
                                    const occ::handle<Geom2d_Curve>&      PC1,
                                    const occ::handle<Adaptor3d_Surface>& S2,
                                    const occ::handle<Geom2d_Curve>&      PC2,
                                    const TopAbs_Orientation              Or,
                                    const bool                            On1,
                                    const bool                            Gd1,
                                    const bool                            Gd2,
                                    const bool                            Gf1,
                                    const bool                            Gf2);

  double                                                                            tolappangle;
  double                                                                            tolesp;
  double                                                                            tol2d;
  double                                                                            tolapp3d;
  double                                                                            tolapp2d;
  double                                                                            fleche;
  GeomAbs_Shape                                                                     myConti;
  ChFiDS_Map                                                                        myEFMap;
  ChFiDS_Map                                                                        myESoMap;
  ChFiDS_Map                                                                        myEShMap;
  ChFiDS_Map                                                                        myVFMap;
  ChFiDS_Map                                                                        myVEMap;
  occ::handle<TopOpeBRepDS_HDataStructure>                                          myDS;
  occ::handle<TopOpeBRepBuild_HBuilder>                                             myCoup;
  NCollection_List<occ::handle<ChFiDS_Stripe>>                                      myListStripe;
  ChFiDS_StripeMap                                                                  myVDataMap;
  NCollection_List<ChFiDS_Regul>                                                    myRegul;
  NCollection_List<occ::handle<ChFiDS_Stripe>>                                      badstripes;
  NCollection_List<TopoDS_Shape>                                                    badvertices;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<int>, TopTools_ShapeMapHasher> myEVIMap;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>          myEdgeFirstFace;
  bool                                                                              done;
  bool                                                                              hasresult;

private:
  Standard_EXPORT bool FaceTangency(const TopoDS_Edge&   E0,
                                    const TopoDS_Edge&   E1,
                                    const TopoDS_Vertex& V) const;

  Standard_EXPORT void PerformSetOfSurfOnElSpine(const occ::handle<ChFiDS_ElSpine>&     ES,
                                                 occ::handle<ChFiDS_Stripe>&            St,
                                                 occ::handle<BRepTopAdaptor_TopolTool>& It1,
                                                 occ::handle<BRepTopAdaptor_TopolTool>& It2,
                                                 const bool Simul = false);

  Standard_EXPORT void PerformFilletOnVertex(const int Index);

  Standard_EXPORT void PerformSingularCorner(const int Index);

  Standard_EXPORT void PerformOneCorner(const int Index, const bool PrepareOnSame = false);

  Standard_EXPORT void IntersectMoreCorner(const int Index);

  Standard_EXPORT void PerformMoreSurfdata(const int Index);

  Standard_EXPORT void PerformIntersectionAtEnd(const int Index);

  Standard_EXPORT void ExtentAnalyse();

  Standard_EXPORT bool FindFace(const TopoDS_Vertex&      V,
                                const ChFiDS_CommonPoint& P1,
                                const ChFiDS_CommonPoint& P2,
                                TopoDS_Face&              Fv) const;

  Standard_EXPORT bool FindFace(const TopoDS_Vertex&      V,
                                const ChFiDS_CommonPoint& P1,
                                const ChFiDS_CommonPoint& P2,
                                TopoDS_Face&              Fv,
                                const TopoDS_Face&        Favoid) const;

  Standard_EXPORT bool MoreSurfdata(const int Index) const;

  Standard_EXPORT bool StartSol(const occ::handle<ChFiDS_Spine>&    Spine,
                                occ::handle<BRepAdaptor_Surface>&   HS,
                                gp_Pnt2d&                           P,
                                occ::handle<BRepAdaptor_Curve2d>&   HC,
                                double&                             W,
                                const occ::handle<ChFiDS_SurfData>& SD,
                                const bool                          isFirst,
                                const int                           OnS,
                                occ::handle<BRepAdaptor_Surface>&   HSref,
                                occ::handle<BRepAdaptor_Curve2d>&   HCref,
                                bool&                               RecP,
                                bool&                               RecS,
                                bool&                               RecRst,
                                bool&                               C1Obst,
                                occ::handle<BRepAdaptor_Surface>&   HSbis,
                                gp_Pnt2d&                           Pbis,
                                const bool                          Decroch,
                                const TopoDS_Vertex&                Vref) const;

  Standard_EXPORT void StartSol(const occ::handle<ChFiDS_Stripe>&      S,
                                const occ::handle<ChFiDS_ElSpine>&     HGuide,
                                occ::handle<BRepAdaptor_Surface>&      HS1,
                                occ::handle<BRepAdaptor_Surface>&      HS2,
                                occ::handle<BRepTopAdaptor_TopolTool>& I1,
                                occ::handle<BRepTopAdaptor_TopolTool>& I2,
                                gp_Pnt2d&                              P1,
                                gp_Pnt2d&                              P2,
                                double&                                First) const;

  Standard_EXPORT void ConexFaces(const occ::handle<ChFiDS_Spine>&  Sp,
                                  const int                         IEdge,
                                  occ::handle<BRepAdaptor_Surface>& HS1,
                                  occ::handle<BRepAdaptor_Surface>& HS2) const;

  Standard_EXPORT void UpdateTolesp();

  TopoDS_Shape                   myShape;
  double                         angular;
  NCollection_List<TopoDS_Shape> myGenerated;
  TopoDS_Shape                   myShapeResult;
  TopoDS_Shape                   badShape;
};
