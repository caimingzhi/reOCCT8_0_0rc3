#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_MultiPoint.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Vec2d.hpp>

class gp_Vec;
class gp_Vec2d;

class AppDef_MultiPointConstraint : public AppParCurves_MultiPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_MultiPointConstraint();

  Standard_EXPORT AppDef_MultiPointConstraint(const int NbPoints, const int NbPoints2d);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>& tabP);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt2d>& tabP);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>&   tabP,
                                              const NCollection_Array1<gp_Pnt2d>& tabP2d);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>&   tabP,
                                              const NCollection_Array1<gp_Pnt2d>& tabP2d,
                                              const NCollection_Array1<gp_Vec>&   tabVec,
                                              const NCollection_Array1<gp_Vec2d>& tabVec2d,
                                              const NCollection_Array1<gp_Vec>&   tabCur,
                                              const NCollection_Array1<gp_Vec2d>& tabCur2d);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>&   tabP,
                                              const NCollection_Array1<gp_Pnt2d>& tabP2d,
                                              const NCollection_Array1<gp_Vec>&   tabVec,
                                              const NCollection_Array1<gp_Vec2d>& tabVec2d);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>& tabP,
                                              const NCollection_Array1<gp_Vec>& tabVec,
                                              const NCollection_Array1<gp_Vec>& tabCur);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt>& tabP,
                                              const NCollection_Array1<gp_Vec>& tabVec);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt2d>& tabP2d,
                                              const NCollection_Array1<gp_Vec2d>& tabVec2d);

  Standard_EXPORT AppDef_MultiPointConstraint(const NCollection_Array1<gp_Pnt2d>& tabP2d,
                                              const NCollection_Array1<gp_Vec2d>& tabVec2d,
                                              const NCollection_Array1<gp_Vec2d>& tabCur2d);

  Standard_EXPORT void SetTang(const int Index, const gp_Vec& Tang);

  Standard_EXPORT gp_Vec Tang(const int Index) const;

  Standard_EXPORT void SetTang2d(const int Index, const gp_Vec2d& Tang2d);

  Standard_EXPORT gp_Vec2d Tang2d(const int Index) const;

  Standard_EXPORT void SetCurv(const int Index, const gp_Vec& Curv);

  Standard_EXPORT gp_Vec Curv(const int Index) const;

  Standard_EXPORT void SetCurv2d(const int Index, const gp_Vec2d& Curv2d);

  Standard_EXPORT gp_Vec2d Curv2d(const int Index) const;

  Standard_EXPORT bool IsTangencyPoint() const;

  Standard_EXPORT bool IsCurvaturePoint() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const override;

private:
  occ::handle<NCollection_HArray1<gp_Vec>>   tabTang;
  occ::handle<NCollection_HArray1<gp_Vec>>   tabCurv;
  occ::handle<NCollection_HArray1<gp_Vec2d>> tabTang2d;
  occ::handle<NCollection_HArray1<gp_Vec2d>> tabCurv2d;
};
