#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_JoinType.hpp>
#include <Standard_Integer.hpp>
#include <Bisector_Bisec.hpp>
#include <NCollection_DataMap.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <NCollection_Sequence.hpp>
#include <MAT_Side.hpp>
class MAT2d_Circuit;
class MAT_Bisector;
class Bisector_Bisec;
class Geom2d_Geometry;
class gp_Pnt2d;
class gp_Vec2d;

class MAT2d_Tool2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MAT2d_Tool2d();

  Standard_EXPORT void Sense(const MAT_Side aside);

  Standard_EXPORT void SetJoinType(const GeomAbs_JoinType aJoinType);

  Standard_EXPORT void InitItems(const occ::handle<MAT2d_Circuit>& aCircuit);

  Standard_EXPORT int NumberOfItems() const;

  Standard_EXPORT double ToleranceOfConfusion() const;

  Standard_EXPORT int FirstPoint(const int anitem, double& dist);

  Standard_EXPORT int TangentBefore(const int anitem, const bool IsOpenResult);

  Standard_EXPORT int TangentAfter(const int anitem, const bool IsOpenResult);

  Standard_EXPORT int Tangent(const int bisector);

  Standard_EXPORT void CreateBisector(const occ::handle<MAT_Bisector>& abisector);

  Standard_EXPORT bool TrimBisector(const occ::handle<MAT_Bisector>& abisector);

  Standard_EXPORT bool TrimBisector(const occ::handle<MAT_Bisector>& abisector, const int apoint);

  Standard_EXPORT double IntersectBisector(const occ::handle<MAT_Bisector>& bisectorone,
                                           const occ::handle<MAT_Bisector>& bisectortwo,
                                           int&                             intpnt);

  Standard_EXPORT double Distance(const occ::handle<MAT_Bisector>& abisector,
                                  const double                     param1,
                                  const double                     param2) const;

  Standard_EXPORT void Dump(const int bisector, const int erease) const;

  Standard_EXPORT const Bisector_Bisec& GeomBis(const int Index) const;

  Standard_EXPORT occ::handle<Geom2d_Geometry> GeomElt(const int Index) const;

  Standard_EXPORT const gp_Pnt2d& GeomPnt(const int Index) const;

  Standard_EXPORT const gp_Vec2d& GeomVec(const int Index) const;

  Standard_EXPORT occ::handle<MAT2d_Circuit> Circuit() const;

  Standard_EXPORT void BisecFusion(const int Index1, const int Index2);

  Standard_EXPORT Bisector_Bisec& ChangeGeomBis(const int Index);

private:
  Standard_EXPORT bool IsSameDistance(const occ::handle<MAT_Bisector>& bisectorone,
                                      const occ::handle<MAT_Bisector>& bisectortwo,
                                      const gp_Pnt2d&                  apoint,
                                      double&                          adistance) const;

  Standard_EXPORT bool Projection(const int       IndexElt,
                                  const gp_Pnt2d& Point,
                                  double&         Distance) const;

  Standard_EXPORT void TrimBisec(Bisector_Bisec& Bis,
                                 const int       IndexEdge,
                                 const bool      OnLine,
                                 const int       StartOrEnd) const;

  double                                   theDirection;
  GeomAbs_JoinType                         theJoinType;
  int                                      theNumberOfBisectors;
  int                                      theNumberOfPnts;
  int                                      theNumberOfVecs;
  occ::handle<MAT2d_Circuit>               theCircuit;
  NCollection_DataMap<int, Bisector_Bisec> theGeomBisectors;
  NCollection_DataMap<int, gp_Pnt2d>       theGeomPnts;
  NCollection_DataMap<int, gp_Vec2d>       theGeomVecs;
  NCollection_Sequence<int>                theLinesLength;
};
