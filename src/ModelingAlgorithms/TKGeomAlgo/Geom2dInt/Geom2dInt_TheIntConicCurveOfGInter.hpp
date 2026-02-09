#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntRes2d_Intersection.hpp>
class IntCurve_IConicTool;
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class Geom2dInt_TheProjPCurOfGInter;
class Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter;
class Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter;
class gp_Lin2d;
class IntRes2d_Domain;
class gp_Circ2d;
class gp_Elips2d;
class gp_Parab2d;
class gp_Hypr2d;

class Geom2dInt_TheIntConicCurveOfGInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Geom2dInt_TheIntConicCurveOfGInter();

  Geom2dInt_TheIntConicCurveOfGInter(const gp_Lin2d&          L,
                                     const IntRes2d_Domain&   D1,
                                     const Adaptor2d_Curve2d& PCurve,
                                     const IntRes2d_Domain&   D2,
                                     const double             TolConf,
                                     const double             Tol);

  Standard_EXPORT Geom2dInt_TheIntConicCurveOfGInter(const gp_Circ2d&         C,
                                                     const IntRes2d_Domain&   D1,
                                                     const Adaptor2d_Curve2d& PCurve,
                                                     const IntRes2d_Domain&   D2,
                                                     const double             TolConf,
                                                     const double             Tol);

  Standard_EXPORT Geom2dInt_TheIntConicCurveOfGInter(const gp_Elips2d&        E,
                                                     const IntRes2d_Domain&   D1,
                                                     const Adaptor2d_Curve2d& PCurve,
                                                     const IntRes2d_Domain&   D2,
                                                     const double             TolConf,
                                                     const double             Tol);

  Standard_EXPORT Geom2dInt_TheIntConicCurveOfGInter(const gp_Parab2d&        Prb,
                                                     const IntRes2d_Domain&   D1,
                                                     const Adaptor2d_Curve2d& PCurve,
                                                     const IntRes2d_Domain&   D2,
                                                     const double             TolConf,
                                                     const double             Tol);

  Standard_EXPORT Geom2dInt_TheIntConicCurveOfGInter(const gp_Hypr2d&         H,
                                                     const IntRes2d_Domain&   D1,
                                                     const Adaptor2d_Curve2d& PCurve,
                                                     const IntRes2d_Domain&   D2,
                                                     const double             TolConf,
                                                     const double             Tol);

  void Perform(const gp_Lin2d&          L,
               const IntRes2d_Domain&   D1,
               const Adaptor2d_Curve2d& PCurve,
               const IntRes2d_Domain&   D2,
               const double             TolConf,
               const double             Tol);

  void Perform(const gp_Circ2d&         C,
               const IntRes2d_Domain&   D1,
               const Adaptor2d_Curve2d& PCurve,
               const IntRes2d_Domain&   D2,
               const double             TolConf,
               const double             Tol);

  void Perform(const gp_Elips2d&        E,
               const IntRes2d_Domain&   D1,
               const Adaptor2d_Curve2d& PCurve,
               const IntRes2d_Domain&   D2,
               const double             TolConf,
               const double             Tol);

  void Perform(const gp_Parab2d&        Prb,
               const IntRes2d_Domain&   D1,
               const Adaptor2d_Curve2d& PCurve,
               const IntRes2d_Domain&   D2,
               const double             TolConf,
               const double             Tol);

  void Perform(const gp_Hypr2d&         H,
               const IntRes2d_Domain&   D1,
               const Adaptor2d_Curve2d& PCurve,
               const IntRes2d_Domain&   D2,
               const double             TolConf,
               const double             Tol);

private:
  void Perform(const IntCurve_IConicTool& ICurve,
               const IntRes2d_Domain&     D1,
               const Adaptor2d_Curve2d&   PCurve,
               const IntRes2d_Domain&     D2,
               const double               TolConf,
               const double               Tol);
};

#define TheImpTool IntCurve_IConicTool
#define TheImpTool_hxx <IntCurve_IConicTool.hpp>
#define ThePCurve Adaptor2d_Curve2d
#define ThePCurve_hxx <Adaptor2d_Curve2d.hpp>
#define ThePCurveTool Geom2dInt_Geom2dCurveTool
#define ThePCurveTool_hxx <Geom2dInt_Geom2dCurveTool.hpp>
#define TheProjPCur Geom2dInt_TheProjPCurOfGInter
#define TheProjPCur_hxx <Geom2dInt_TheProjPCurOfGInter.hpp>
#define IntCurve_TheIntersector Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_TheIntersector_hxx <Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_MyImpParToolOfTheIntersector                                                      \
  Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter
#define IntCurve_MyImpParToolOfTheIntersector_hxx                                                  \
  <Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter.hpp>
#define IntCurve_IntConicCurveGen Geom2dInt_TheIntConicCurveOfGInter
#define IntCurve_IntConicCurveGen_hxx <Geom2dInt_TheIntConicCurveOfGInter.hpp>

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
