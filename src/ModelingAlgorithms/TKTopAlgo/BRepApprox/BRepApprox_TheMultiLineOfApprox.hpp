#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <Approx_Status.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
class BRepApprox_ApproxLine;
class ApproxInt_SvSurfaces;

class BRepApprox_TheMultiLineOfApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepApprox_TheMultiLineOfApprox();

  Standard_EXPORT BRepApprox_TheMultiLineOfApprox(const occ::handle<BRepApprox_ApproxLine>& line,
                                                  void* const  PtrSvSurfaces,
                                                  const int    NbP3d,
                                                  const int    NbP2d,
                                                  const bool   ApproxU1V1,
                                                  const bool   ApproxU2V2,
                                                  const double xo,
                                                  const double yo,
                                                  const double zo,
                                                  const double u1o,
                                                  const double v1o,
                                                  const double u2o,
                                                  const double v2o,
                                                  const bool   P2DOnFirst,
                                                  const int    IndMin = 0,
                                                  const int    IndMax = 0);

  Standard_EXPORT BRepApprox_TheMultiLineOfApprox(const occ::handle<BRepApprox_ApproxLine>& line,
                                                  const int                                 NbP3d,
                                                  const int                                 NbP2d,
                                                  const bool   ApproxU1V1,
                                                  const bool   ApproxU2V2,
                                                  const double xo,
                                                  const double yo,
                                                  const double zo,
                                                  const double u1o,
                                                  const double v1o,
                                                  const double u2o,
                                                  const double v2o,
                                                  const bool   P2DOnFirst,
                                                  const int    IndMin = 0,
                                                  const int    IndMax = 0);

  Standard_EXPORT int FirstPoint() const;

  Standard_EXPORT int LastPoint() const;

  Standard_EXPORT int NbP2d() const;

  Standard_EXPORT int NbP3d() const;

  Standard_EXPORT Approx_Status WhatStatus() const;

  Standard_EXPORT void Value(const int MPointIndex, NCollection_Array1<gp_Pnt>& tabPt) const;

  Standard_EXPORT void Value(const int MPointIndex, NCollection_Array1<gp_Pnt2d>& tabPt2d) const;

  Standard_EXPORT void Value(const int                     MPointIndex,
                             NCollection_Array1<gp_Pnt>&   tabPt,
                             NCollection_Array1<gp_Pnt2d>& tabPt2d) const;

  Standard_EXPORT bool Tangency(const int MPointIndex, NCollection_Array1<gp_Vec>& tabV) const;

  Standard_EXPORT bool Tangency(const int MPointIndex, NCollection_Array1<gp_Vec2d>& tabV2d) const;

  Standard_EXPORT bool Tangency(const int                     MPointIndex,
                                NCollection_Array1<gp_Vec>&   tabV,
                                NCollection_Array1<gp_Vec2d>& tabV2d) const;

  Standard_EXPORT BRepApprox_TheMultiLineOfApprox MakeMLBetween(const int Low,
                                                                const int High,
                                                                const int NbPointsToInsert) const;

  Standard_EXPORT bool MakeMLOneMorePoint(const int                        Low,
                                          const int                        High,
                                          const int                        indbad,
                                          BRepApprox_TheMultiLineOfApprox& OtherLine) const;

  Standard_EXPORT void Dump() const;

private:
  void*                              PtrOnmySvSurfaces;
  occ::handle<BRepApprox_ApproxLine> myLine;
  int                                indicemin;
  int                                indicemax;
  int                                nbp3d;
  int                                nbp2d;
  bool                               myApproxU1V1;
  bool                               myApproxU2V2;
  bool                               p2donfirst;
  double                             Xo;
  double                             Yo;
  double                             Zo;
  double                             U1o;
  double                             V1o;
  double                             U2o;
  double                             V2o;
};
