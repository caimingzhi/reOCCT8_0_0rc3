#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <IntRes2d_Intersection.hpp>
class IntCurve_IConicTool;
class HLRBRep_CurveTool;
class HLRBRep_TheProjPCurOfCInter;
class HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter;
class HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter;
class gp_Lin2d;
class IntRes2d_Domain;
class gp_Circ2d;
class gp_Elips2d;
class gp_Parab2d;
class gp_Hypr2d;

class HLRBRep_TheIntConicCurveOfCInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  HLRBRep_TheIntConicCurveOfCInter();

  //! Intersection between a line and a parametric curve.
  HLRBRep_TheIntConicCurveOfCInter(const gp_Lin2d&         L,
                                   const IntRes2d_Domain&  D1,
                                   const HLRBRep_CurvePtr& PCurve,
                                   const IntRes2d_Domain&  D2,
                                   const double            TolConf,
                                   const double            Tol);

  //! Intersection between a line and a parametric curve.
  Standard_EXPORT HLRBRep_TheIntConicCurveOfCInter(const gp_Circ2d&        C,
                                                   const IntRes2d_Domain&  D1,
                                                   const HLRBRep_CurvePtr& PCurve,
                                                   const IntRes2d_Domain&  D2,
                                                   const double            TolConf,
                                                   const double            Tol);

  //! Intersection between an ellipse and a parametric curve.
  Standard_EXPORT HLRBRep_TheIntConicCurveOfCInter(const gp_Elips2d&       E,
                                                   const IntRes2d_Domain&  D1,
                                                   const HLRBRep_CurvePtr& PCurve,
                                                   const IntRes2d_Domain&  D2,
                                                   const double            TolConf,
                                                   const double            Tol);

  //! Intersection between a parabola and a parametric curve.
  Standard_EXPORT HLRBRep_TheIntConicCurveOfCInter(const gp_Parab2d&       Prb,
                                                   const IntRes2d_Domain&  D1,
                                                   const HLRBRep_CurvePtr& PCurve,
                                                   const IntRes2d_Domain&  D2,
                                                   const double            TolConf,
                                                   const double            Tol);

  //! Intersection between the main branch of an hyperbola
  //! and a parametric curve.
  Standard_EXPORT HLRBRep_TheIntConicCurveOfCInter(const gp_Hypr2d&        H,
                                                   const IntRes2d_Domain&  D1,
                                                   const HLRBRep_CurvePtr& PCurve,
                                                   const IntRes2d_Domain&  D2,
                                                   const double            TolConf,
                                                   const double            Tol);

  //! Intersection between a line and a parametric curve.
  void Perform(const gp_Lin2d&         L,
               const IntRes2d_Domain&  D1,
               const HLRBRep_CurvePtr& PCurve,
               const IntRes2d_Domain&  D2,
               const double            TolConf,
               const double            Tol);

  //! Intersection between a line and a parametric curve.
  void Perform(const gp_Circ2d&        C,
               const IntRes2d_Domain&  D1,
               const HLRBRep_CurvePtr& PCurve,
               const IntRes2d_Domain&  D2,
               const double            TolConf,
               const double            Tol);

  //! Intersection between an ellipse and a parametric curve.
  void Perform(const gp_Elips2d&       E,
               const IntRes2d_Domain&  D1,
               const HLRBRep_CurvePtr& PCurve,
               const IntRes2d_Domain&  D2,
               const double            TolConf,
               const double            Tol);

  //! Intersection between a parabola and a parametric curve.
  void Perform(const gp_Parab2d&       Prb,
               const IntRes2d_Domain&  D1,
               const HLRBRep_CurvePtr& PCurve,
               const IntRes2d_Domain&  D2,
               const double            TolConf,
               const double            Tol);

  //! Intersection between the main branch of an hyperbola
  //! and a parametric curve.
  void Perform(const gp_Hypr2d&        H,
               const IntRes2d_Domain&  D1,
               const HLRBRep_CurvePtr& PCurve,
               const IntRes2d_Domain&  D2,
               const double            TolConf,
               const double            Tol);

private:
  //! Intersection between a conic fom gp
  //! and a parametric curve.
  void Perform(const IntCurve_IConicTool& ICurve,
               const IntRes2d_Domain&     D1,
               const HLRBRep_CurvePtr&    PCurve,
               const IntRes2d_Domain&     D2,
               const double               TolConf,
               const double               Tol);
};

#define TheImpTool IntCurve_IConicTool
#define TheImpTool_hxx <IntCurve_IConicTool.hpp>
#define ThePCurve HLRBRep_CurvePtr
#define ThePCurve_hxx <HLRBRep_CurvePtr.hxx>
#define ThePCurveTool HLRBRep_CurveTool
#define ThePCurveTool_hxx <HLRBRep_CurveTool.hpp>
#define TheProjPCur HLRBRep_TheProjPCurOfCInter
#define TheProjPCur_hxx <HLRBRep_TheProjPCurOfCInter.hpp>
#define IntCurve_TheIntersector HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_TheIntersector_hxx <HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter.hpp>
#define IntCurve_IntConicCurveGen HLRBRep_TheIntConicCurveOfCInter
#define IntCurve_IntConicCurveGen_hxx <HLRBRep_TheIntConicCurveOfCInter.hpp>

#include <IntCurve_IntConicCurveGen_1.hpp>

#undef TheImpTool
#undef TheImpTool_hxx
#undef ThePCurve
#undef ThePCurve_hxx
#undef ThePCurveTool
#undef ThePCurveTool_hxx
#undef TheProjPCur
#undef TheProjPCur_hxx
#undef IntCurve_TheIntersector
#undef IntCurve_TheIntersector_hxx
#undef IntCurve_MyImpParToolOfTheIntersector
#undef IntCurve_MyImpParToolOfTheIntersector_hxx
#undef IntCurve_MyImpParToolOfTheIntersector
#undef IntCurve_MyImpParToolOfTheIntersector_hxx
#undef IntCurve_IntConicCurveGen
#undef IntCurve_IntConicCurveGen_hxx
