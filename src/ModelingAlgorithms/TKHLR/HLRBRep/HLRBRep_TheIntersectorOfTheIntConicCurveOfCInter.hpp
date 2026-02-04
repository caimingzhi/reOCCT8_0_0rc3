#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <IntRes2d_Intersection.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
class Standard_ConstructionError;
class IntCurve_IConicTool;
class HLRBRep_CurveTool;
class HLRBRep_TheProjPCurOfCInter;
class HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter;
class IntRes2d_Domain;
class gp_Pnt2d;

class HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter();

  //! Intersection between an implicit curve and
  //! a parametrised curve.
  //! The exception ConstructionError is raised if the domain
  //! of the parametrised curve does not verify HasFirstPoint
  //! and HasLastPoint return True.
  Standard_EXPORT HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter(const IntCurve_IConicTool& ITool,
                                                                   const IntRes2d_Domain&     Dom1,
                                                                   const HLRBRep_CurvePtr& PCurve,
                                                                   const IntRes2d_Domain&  Dom2,
                                                                   const double            TolConf,
                                                                   const double            Tol);

  //! Intersection between an implicit curve and
  //! a parametrised curve.
  //! The exception ConstructionError is raised if the domain
  //! of the parametrised curve does not verify HasFirstPoint
  //! and HasLastPoint return True.
  Standard_EXPORT void Perform(const IntCurve_IConicTool& ITool,
                               const IntRes2d_Domain&     Dom1,
                               const HLRBRep_CurvePtr&    PCurve,
                               const IntRes2d_Domain&     Dom2,
                               const double               TolConf,
                               const double               Tol);

  Standard_EXPORT double FindU(const double               parameter,
                               gp_Pnt2d&                  point,
                               const HLRBRep_CurvePtr&    TheParCurev,
                               const IntCurve_IConicTool& TheImpTool) const;

  Standard_EXPORT double FindV(const double               parameter,
                               gp_Pnt2d&                  point,
                               const IntCurve_IConicTool& TheImpTool,
                               const HLRBRep_CurvePtr&    ParCurve,
                               const IntRes2d_Domain&     TheParCurveDomain,
                               const double               V0,
                               const double               V1,
                               const double               Tolerance) const;

  Standard_EXPORT void And_Domaine_Objet1_Intersections(
    const IntCurve_IConicTool&  TheImpTool,
    const HLRBRep_CurvePtr&     TheParCurve,
    const IntRes2d_Domain&      TheImpCurveDomain,
    const IntRes2d_Domain&      TheParCurveDomain,
    int&                        NbResultats,
    NCollection_Array1<double>& Inter2_And_Domain2,
    NCollection_Array1<double>& Inter1,
    NCollection_Array1<double>& Resultat1,
    NCollection_Array1<double>& Resultat2,
    const double                EpsNul) const;
};

