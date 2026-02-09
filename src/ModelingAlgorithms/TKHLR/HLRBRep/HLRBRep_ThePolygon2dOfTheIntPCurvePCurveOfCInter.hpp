#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Intf_Polygon2d.hpp>
class Standard_OutOfRange;
class HLRBRep_CurveTool;
class IntRes2d_Domain;
class Bnd_Box2d;
class gp_Pnt2d;

class HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter : public Intf_Polygon2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter(const HLRBRep_CurvePtr& Curve,
                                                                   const int               NbPnt,
                                                                   const IntRes2d_Domain&  Domain,
                                                                   const double            Tol);

  Standard_EXPORT void ComputeWithBox(const HLRBRep_CurvePtr& Curve, const Bnd_Box2d& OtherBox);

  double DeflectionOverEstimation() const override;

  void SetDeflectionOverEstimation(const double x);

  void Closed(const bool clos);

  bool Closed() const override { return ClosedPolygon; }

  int NbSegments() const override;

  Standard_EXPORT void Segment(const int theIndex,
                               gp_Pnt2d& theBegin,
                               gp_Pnt2d& theEnd) const override;

  double InfParameter() const;

  double SupParameter() const;

  Standard_EXPORT bool AutoIntersectionIsPossible() const;

  Standard_EXPORT double ApproxParamOnCurve(const int Index, const double ParamOnLine) const;

  int CalculRegion(const double x,
                   const double y,
                   const double x1,
                   const double x2,
                   const double y1,
                   const double y2) const;

  Standard_EXPORT void Dump() const;

private:
  double                       TheDeflection;
  int                          NbPntIn;
  int                          TheMaxNbPoints;
  NCollection_Array1<gp_Pnt2d> ThePnts;
  NCollection_Array1<double>   TheParams;
  NCollection_Array1<int>      TheIndex;
  bool                         ClosedPolygon;
  double                       Binf;
  double                       Bsup;
};

#define TheCurve HLRBRep_CurvePtr
#define TheCurve_hxx <HLRBRep_CurvePtr.hxx>
#define TheCurveTool HLRBRep_CurveTool
#define TheCurveTool_hxx <HLRBRep_CurveTool.hpp>
#define IntCurve_Polygon2dGen HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter
#define IntCurve_Polygon2dGen_hxx <HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter.hpp>

#include <IntCurve_Polygon2dGen_1.hpp>

#undef TheCurve
#undef TheCurve_hxx
#undef TheCurveTool
#undef TheCurveTool_hxx
#undef IntCurve_Polygon2dGen
#undef IntCurve_Polygon2dGen_hxx
