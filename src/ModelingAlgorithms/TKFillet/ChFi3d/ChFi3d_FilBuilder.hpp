#pragma once


#include <BRepAdaptor_Surface.hpp>
#include <BlendFunc_SectionShape.hpp>
#include <ChFi3d_Builder.hpp>
#include <ChFi3d_FilletShape.hpp>
#include <ChFiDS_Stripe.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_ElSpine.hpp>
#include <ChFiDS_CircSection.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <ChFiDS_SurfData.hpp>
#include <NCollection_Sequence.hpp>
#include <math_Vector.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>

class Adaptor3d_TopolTool;
class BRepBlend_Line;
class gp_XY;
class ChFiDS_SurfData;
class ChFiDS_Spine;
class ChFiDS_Stripe;
class Law_Function;
class TopoDS_Edge;
class TopoDS_Shape;
class TopoDS_Vertex;

//! Tool of construction of fillets 3d on edges (on a solid).
class ChFi3d_FilBuilder : public ChFi3d_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFi3d_FilBuilder(const TopoDS_Shape&      S,
                                    const ChFi3d_FilletShape FShape = ChFi3d_Rational,
                                    const double             Ta     = 1.0e-2);

  //! Sets the type of fillet surface.
  Standard_EXPORT void SetFilletShape(const ChFi3d_FilletShape FShape);

  //! Returns the type of fillet surface.
  Standard_EXPORT ChFi3d_FilletShape GetFilletShape() const;

  //! initialisation of a contour with the first edge
  //! (the following are found by propagation).
  //! Attention, you need to start with SetRadius.
  Standard_EXPORT void Add(const TopoDS_Edge& E);

  //! initialisation of the constant vector the corresponding 1st edge.
  Standard_EXPORT void Add(const double Radius, const TopoDS_Edge& E);

  //! Set the radius of the contour of index IC.
  Standard_EXPORT void SetRadius(const occ::handle<Law_Function>& C, const int IC, const int IinC);

  //! Returns true the contour is flagged as edge constant.
  Standard_EXPORT bool IsConstant(const int IC);

  //! Returns the vector if the contour is flagged as edge
  //! constant.
  Standard_EXPORT double Radius(const int IC);

  //! Reset all vectors of contour IC.
  Standard_EXPORT void ResetContour(const int IC);

  //! Set a constant on edge E of the contour of
  //! index IC. Since then E is flagged as constant.
  Standard_EXPORT void SetRadius(const double Radius, const int IC, const TopoDS_Edge& E);

  //! Extracts the flag constant and the vector of edge E.
  Standard_EXPORT void UnSet(const int IC, const TopoDS_Edge& E);

  //! Set a vector on vertex V of the contour of index IC.
  Standard_EXPORT void SetRadius(const double Radius, const int IC, const TopoDS_Vertex& V);

  //! Extracts the vector of the vertex V.
  Standard_EXPORT void UnSet(const int IC, const TopoDS_Vertex& V);

  //! Set a vertex on the point of parameter U in the edge IinC
  //! of the contour of index IC
  Standard_EXPORT void SetRadius(const gp_XY& UandR, const int IC, const int IinC);

  //! Returns true E is flagged as edge constant.
  Standard_EXPORT bool IsConstant(const int IC, const TopoDS_Edge& E);

  //! Returns the vector if E is flagged as edge constant.
  Standard_EXPORT double Radius(const int IC, const TopoDS_Edge& E);

  //! Returns in First and Last extremities of the
  //! part of variable vector framing E, returns
  //! False if E is flagged as edge constant.
  Standard_EXPORT bool GetBounds(const int IC, const TopoDS_Edge& E, double& First, double& Last);

  //! Returns the rule of elementary evolution of the
  //! part to variable vector framing E, returns a
  //! rule zero if E is flagged as edge constant.
  Standard_EXPORT occ::handle<Law_Function> GetLaw(const int IC, const TopoDS_Edge& E);

  //! Sets the rule of elementary evolution of the
  //! part to variable vector framing E.
  Standard_EXPORT void SetLaw(const int                        IC,
                              const TopoDS_Edge&               E,
                              const occ::handle<Law_Function>& L);

  Standard_EXPORT void Simulate(const int IC);

  Standard_EXPORT int NbSurf(const int IC) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<ChFiDS_CircSection>> Sect(const int IC,
                                                                            const int IS) const;

protected:
  Standard_EXPORT void SimulKPart(const occ::handle<ChFiDS_SurfData>& SD) const override;

  Standard_EXPORT bool SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
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
                                 int&                                    Intl) override;

  Standard_EXPORT void SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
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
                                 const math_Vector&                      Soldep) override;

  Standard_EXPORT void SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
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
                                 const math_Vector&                      Soldep) override;

  Standard_EXPORT void SimulSurf(occ::handle<ChFiDS_SurfData>&           Data,
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
                                 const math_Vector&                      Soldep) override;

  Standard_EXPORT bool PerformFirstSection(const occ::handle<ChFiDS_Spine>&        S,
                                           const occ::handle<ChFiDS_ElSpine>&      HGuide,
                                           const int                               Choix,
                                           occ::handle<BRepAdaptor_Surface>&       S1,
                                           occ::handle<BRepAdaptor_Surface>&       S2,
                                           const occ::handle<Adaptor3d_TopolTool>& I1,
                                           const occ::handle<Adaptor3d_TopolTool>& I2,
                                           const double                            Par,
                                           math_Vector&                            SolDep,
                                           TopAbs_State&                           Pos1,
                                           TopAbs_State& Pos2) const override;

  //! Method calculates the elements of construction of the
  //! fillet (constant or evolutive).
  Standard_EXPORT bool PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
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
                                   const math_Vector&                                  Soldep,
                                   int&                                                Intf,
                                   int& Intl) override;

  Standard_EXPORT void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC1,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref1,
                                   bool&                                               Decroch1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
                                   const occ::handle<Adaptor3d_TopolTool>&             I2,
                                   const TopAbs_Orientation                            Or2,
                                   const double                                        MaxStep,
                                   const double                                        Fleche,
                                   const double                                        TolGuide,
                                   double&                                             First,
                                   double&                                             Last,
                                   const bool                                          Inside,
                                   const bool                                          Appro,
                                   const bool                                          Forward,
                                   const bool                                          RecP,
                                   const bool                                          RecS,
                                   const bool                                          RecRst,
                                   const math_Vector& Soldep) override;

  Standard_EXPORT void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const TopAbs_Orientation                            Or1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
                                   const occ::handle<Adaptor3d_TopolTool>&             I2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC2,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref2,
                                   bool&                                               Decroch2,
                                   const double                                        MaxStep,
                                   const double                                        Fleche,
                                   const double                                        TolGuide,
                                   double&                                             First,
                                   double&                                             Last,
                                   const bool                                          Inside,
                                   const bool                                          Appro,
                                   const bool                                          Forward,
                                   const bool                                          RecP,
                                   const bool                                          RecS,
                                   const bool                                          RecRst,
                                   const math_Vector& Soldep) override;

  Standard_EXPORT void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Data,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC1,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref1,
                                   bool&                                               Decroch1,
                                   const TopAbs_Orientation                            Or1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
                                   const occ::handle<Adaptor3d_TopolTool>&             I2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC2,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref2,
                                   bool&                                               Decroch2,
                                   const TopAbs_Orientation                            Or2,
                                   const double                                        MaxStep,
                                   const double                                        Fleche,
                                   const double                                        TolGuide,
                                   double&                                             First,
                                   double&                                             Last,
                                   const bool                                          Inside,
                                   const bool                                          Appro,
                                   const bool                                          Forward,
                                   const bool                                          RecP1,
                                   const bool                                          RecRst1,
                                   const bool                                          RecP2,
                                   const bool                                          RecRst2,
                                   const math_Vector& Soldep) override;

  //! Method to split an singular SurfData in several non
  //! singular SurfData..
  Standard_EXPORT void SplitSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
                                 const occ::handle<BRepBlend_Line>&                  line);

  Standard_EXPORT void PerformTwoCorner(const int Index) override;

  Standard_EXPORT void PerformThreeCorner(const int Index) override;

  Standard_EXPORT void ExtentOneCorner(const TopoDS_Vertex&              V,
                                       const occ::handle<ChFiDS_Stripe>& S) override;

  Standard_EXPORT void ExtentTwoCorner(
    const TopoDS_Vertex&                                V,
    const NCollection_List<occ::handle<ChFiDS_Stripe>>& LS) override;

  Standard_EXPORT void ExtentThreeCorner(
    const TopoDS_Vertex&                                V,
    const NCollection_List<occ::handle<ChFiDS_Stripe>>& LS) override;

  Standard_EXPORT void SetRegul() override;

private:
  BlendFunc_SectionShape myShape;
};

