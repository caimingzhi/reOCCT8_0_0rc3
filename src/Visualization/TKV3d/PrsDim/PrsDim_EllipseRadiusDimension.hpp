#pragma once


#include <gp_Elips.hpp>
#include <PrsDim_Relation.hpp>
#include <PrsDim_KindOfSurface.hpp>

class Geom_OffsetCurve;
class TopoDS_Shape;
class TCollection_ExtendedString;
class Geom_Surface;

//! Computes geometry (basis curve and plane of dimension)
//! for input shape aShape from TopoDS
//! Root class for MinRadiusDimension and MaxRadiusDimension
class PrsDim_EllipseRadiusDimension : public PrsDim_Relation
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_EllipseRadiusDimension, PrsDim_Relation)
public:
  PrsDim_KindOfDimension KindOfDimension() const override { return PrsDim_KOD_ELLIPSERADIUS; }

  bool IsMovable() const override { return true; }

  Standard_EXPORT void ComputeGeometry();

protected:
  Standard_EXPORT PrsDim_EllipseRadiusDimension(const TopoDS_Shape&               aShape,
                                                const TCollection_ExtendedString& aText);

protected:
  gp_Elips                      myEllipse;
  double                        myFirstPar;
  double                        myLastPar;
  bool                          myIsAnArc;
  occ::handle<Geom_OffsetCurve> myOffsetCurve;
  double                        myOffset;
  bool                          myIsOffset;

private:
  Standard_EXPORT void ComputeFaceGeometry();

  Standard_EXPORT void ComputeCylFaceGeometry(const PrsDim_KindOfSurface       aSurfType,
                                              const occ::handle<Geom_Surface>& aSurf,
                                              const double                     Offset);

  Standard_EXPORT void ComputePlanarFaceGeometry();

  Standard_EXPORT void ComputeEdgeGeometry();
};

