#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntRes2d_Intersection.hpp>
#include <NCollection_Array1.hpp>
class Standard_ConstructionError;
class IntCurve_IConicTool;
class IntCurve_PConic;
class IntCurve_PConicTool;
class IntCurve_ProjectOnPConicTool;
class IntCurve_MyImpParToolOfIntImpConicParConic;
class IntRes2d_Domain;
class gp_Pnt2d;

class IntCurve_IntImpConicParConic : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurve_IntImpConicParConic();

  Standard_EXPORT IntCurve_IntImpConicParConic(const IntCurve_IConicTool& ITool,
                                               const IntRes2d_Domain&     Dom1,
                                               const IntCurve_PConic&     PCurve,
                                               const IntRes2d_Domain&     Dom2,
                                               const double               TolConf,
                                               const double               Tol);

  Standard_EXPORT void Perform(const IntCurve_IConicTool& ITool,
                               const IntRes2d_Domain&     Dom1,
                               const IntCurve_PConic&     PCurve,
                               const IntRes2d_Domain&     Dom2,
                               const double               TolConf,
                               const double               Tol);

  Standard_EXPORT double FindU(const double               parameter,
                               gp_Pnt2d&                  point,
                               const IntCurve_PConic&     TheParCurev,
                               const IntCurve_IConicTool& TheImpTool) const;

  Standard_EXPORT double FindV(const double               parameter,
                               gp_Pnt2d&                  point,
                               const IntCurve_IConicTool& TheImpTool,
                               const IntCurve_PConic&     ParCurve,
                               const IntRes2d_Domain&     TheParCurveDomain,
                               const double               V0,
                               const double               V1,
                               const double               Tolerance) const;

  Standard_EXPORT void And_Domaine_Objet1_Intersections(
    const IntCurve_IConicTool&  TheImpTool,
    const IntCurve_PConic&      TheParCurve,
    const IntRes2d_Domain&      TheImpCurveDomain,
    const IntRes2d_Domain&      TheParCurveDomain,
    int&                        NbResultats,
    NCollection_Array1<double>& Inter2_And_Domain2,
    NCollection_Array1<double>& Inter1,
    NCollection_Array1<double>& Resultat1,
    NCollection_Array1<double>& Resultat2,
    const double                EpsNul) const;
};
