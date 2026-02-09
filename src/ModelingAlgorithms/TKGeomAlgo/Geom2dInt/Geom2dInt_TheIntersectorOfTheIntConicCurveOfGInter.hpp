#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntRes2d_Intersection.hpp>
#include <NCollection_Array1.hpp>
class Standard_ConstructionError;
class IntCurve_IConicTool;
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class Geom2dInt_TheProjPCurOfGInter;
class Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter;
class IntRes2d_Domain;
class gp_Pnt2d;

class Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter();

  Standard_EXPORT Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter(
    const IntCurve_IConicTool& ITool,
    const IntRes2d_Domain&     Dom1,
    const Adaptor2d_Curve2d&   PCurve,
    const IntRes2d_Domain&     Dom2,
    const double               TolConf,
    const double               Tol);

  Standard_EXPORT void Perform(const IntCurve_IConicTool& ITool,
                               const IntRes2d_Domain&     Dom1,
                               const Adaptor2d_Curve2d&   PCurve,
                               const IntRes2d_Domain&     Dom2,
                               const double               TolConf,
                               const double               Tol);

  Standard_EXPORT double FindU(const double               parameter,
                               gp_Pnt2d&                  point,
                               const Adaptor2d_Curve2d&   TheParCurev,
                               const IntCurve_IConicTool& TheImpTool) const;

  Standard_EXPORT double FindV(const double               parameter,
                               gp_Pnt2d&                  point,
                               const IntCurve_IConicTool& TheImpTool,
                               const Adaptor2d_Curve2d&   ParCurve,
                               const IntRes2d_Domain&     TheParCurveDomain,
                               const double               V0,
                               const double               V1,
                               const double               Tolerance) const;

  Standard_EXPORT void And_Domaine_Objet1_Intersections(
    const IntCurve_IConicTool&  TheImpTool,
    const Adaptor2d_Curve2d&    TheParCurve,
    const IntRes2d_Domain&      TheImpCurveDomain,
    const IntRes2d_Domain&      TheParCurveDomain,
    int&                        NbResultats,
    NCollection_Array1<double>& Inter2_And_Domain2,
    NCollection_Array1<double>& Inter1,
    NCollection_Array1<double>& Resultat1,
    NCollection_Array1<double>& Resultat2,
    const double                EpsNul) const;
};
