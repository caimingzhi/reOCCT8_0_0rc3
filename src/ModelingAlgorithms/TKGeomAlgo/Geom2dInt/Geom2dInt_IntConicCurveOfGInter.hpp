#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntCurve_IntConicConic.hpp>
#include <Geom2dInt_TheIntConicCurveOfGInter.hpp>
#include <IntRes2d_Intersection.hpp>
class Standard_ConstructionError;
class IntCurve_IConicTool;
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class Geom2dInt_TheIntConicCurveOfGInter;
class gp_Lin2d;
class IntRes2d_Domain;
class gp_Circ2d;
class gp_Elips2d;
class gp_Parab2d;
class gp_Hypr2d;

class Geom2dInt_IntConicCurveOfGInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dInt_IntConicCurveOfGInter();

  Standard_EXPORT Geom2dInt_IntConicCurveOfGInter(const gp_Lin2d&          L,
                                                  const IntRes2d_Domain&   D1,
                                                  const Adaptor2d_Curve2d& PCurve,
                                                  const IntRes2d_Domain&   D2,
                                                  const double             TolConf,
                                                  const double             Tol);

  Standard_EXPORT Geom2dInt_IntConicCurveOfGInter(const gp_Circ2d&         C,
                                                  const IntRes2d_Domain&   D1,
                                                  const Adaptor2d_Curve2d& PCurve,
                                                  const IntRes2d_Domain&   D2,
                                                  const double             TolConf,
                                                  const double             Tol);

  Standard_EXPORT Geom2dInt_IntConicCurveOfGInter(const gp_Elips2d&        E,
                                                  const IntRes2d_Domain&   D1,
                                                  const Adaptor2d_Curve2d& PCurve,
                                                  const IntRes2d_Domain&   D2,
                                                  const double             TolConf,
                                                  const double             Tol);

  Standard_EXPORT Geom2dInt_IntConicCurveOfGInter(const gp_Parab2d&        Prb,
                                                  const IntRes2d_Domain&   D1,
                                                  const Adaptor2d_Curve2d& PCurve,
                                                  const IntRes2d_Domain&   D2,
                                                  const double             TolConf,
                                                  const double             Tol);

  Standard_EXPORT Geom2dInt_IntConicCurveOfGInter(const gp_Hypr2d&         H,
                                                  const IntRes2d_Domain&   D1,
                                                  const Adaptor2d_Curve2d& PCurve,
                                                  const IntRes2d_Domain&   D2,
                                                  const double             TolConf,
                                                  const double             Tol);

  Standard_EXPORT void Perform(const gp_Lin2d&          L,
                               const IntRes2d_Domain&   D1,
                               const Adaptor2d_Curve2d& PCurve,
                               const IntRes2d_Domain&   D2,
                               const double             TolConf,
                               const double             Tol);

  Standard_EXPORT void Perform(const gp_Circ2d&         C,
                               const IntRes2d_Domain&   D1,
                               const Adaptor2d_Curve2d& PCurve,
                               const IntRes2d_Domain&   D2,
                               const double             TolConf,
                               const double             Tol);

  Standard_EXPORT void Perform(const gp_Elips2d&        E,
                               const IntRes2d_Domain&   D1,
                               const Adaptor2d_Curve2d& PCurve,
                               const IntRes2d_Domain&   D2,
                               const double             TolConf,
                               const double             Tol);

  Standard_EXPORT void Perform(const gp_Parab2d&        Prb,
                               const IntRes2d_Domain&   D1,
                               const Adaptor2d_Curve2d& PCurve,
                               const IntRes2d_Domain&   D2,
                               const double             TolConf,
                               const double             Tol);

  Standard_EXPORT void Perform(const gp_Hypr2d&         H,
                               const IntRes2d_Domain&   D1,
                               const Adaptor2d_Curve2d& PCurve,
                               const IntRes2d_Domain&   D2,
                               const double             TolConf,
                               const double             Tol);

private:
  Standard_EXPORT void InternalPerform(const gp_Lin2d&          Lin1,
                                       const IntRes2d_Domain&   D1,
                                       const Adaptor2d_Curve2d& PCurve,
                                       const IntRes2d_Domain&   D2,
                                       const double             TolConf,
                                       const double             Tol,
                                       const bool               Composite);

  Standard_EXPORT void InternalPerform(const gp_Circ2d&         Circ1,
                                       const IntRes2d_Domain&   D1,
                                       const Adaptor2d_Curve2d& PCurve,
                                       const IntRes2d_Domain&   D2,
                                       const double             TolConf,
                                       const double             Tol,
                                       const bool               Composite);

  Standard_EXPORT void InternalPerform(const gp_Elips2d&        Eli1,
                                       const IntRes2d_Domain&   D1,
                                       const Adaptor2d_Curve2d& PCurve,
                                       const IntRes2d_Domain&   D2,
                                       const double             TolConf,
                                       const double             Tol,
                                       const bool               Composite);

  Standard_EXPORT void InternalPerform(const gp_Parab2d&        Prb1,
                                       const IntRes2d_Domain&   D1,
                                       const Adaptor2d_Curve2d& PCurve,
                                       const IntRes2d_Domain&   D2,
                                       const double             TolConf,
                                       const double             Tol,
                                       const bool               Composite);

  Standard_EXPORT void InternalPerform(const gp_Hypr2d&         Hpr1,
                                       const IntRes2d_Domain&   D1,
                                       const Adaptor2d_Curve2d& PCurve,
                                       const IntRes2d_Domain&   D2,
                                       const double             TolConf,
                                       const double             Tol,
                                       const bool               Composite);

  double                             param1inf;
  double                             param1sup;
  double                             param2inf;
  double                             param2sup;
  IntCurve_IntConicConic             intconiconi;
  Geom2dInt_TheIntConicCurveOfGInter intconicurv;
};
