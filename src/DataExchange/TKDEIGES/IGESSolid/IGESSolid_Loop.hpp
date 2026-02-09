#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_HArray1OfHArray1OfInteger;
class IGESBasic_HArray1OfHArray1OfIGESEntity;

class IGESSolid_Loop : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Loop();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<int>>&                              types,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& edges,
    const occ::handle<NCollection_HArray1<int>>&                              index,
    const occ::handle<NCollection_HArray1<int>>&                              orient,
    const occ::handle<NCollection_HArray1<int>>&                              nbParameterCurves,
    const occ::handle<IGESBasic_HArray1OfHArray1OfInteger>&                   isoparametricFlags,
    const occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity>&                curves);

  Standard_EXPORT bool IsBound() const;

  Standard_EXPORT void SetBound(const bool bound);

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT int EdgeType(const int Index) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Edge(const int Index) const;

  Standard_EXPORT bool Orientation(const int Index) const;

  Standard_EXPORT int NbParameterCurves(const int Index) const;

  Standard_EXPORT bool IsIsoparametric(const int EdgeIndex, const int CurveIndex) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ParametricCurve(const int EdgeIndex,
                                                                   const int CurveIndex) const;

  Standard_EXPORT int ListIndex(const int num) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Loop, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<int>>                              theTypes;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> theEdges;
  occ::handle<NCollection_HArray1<int>>                              theIndex;
  occ::handle<NCollection_HArray1<int>>                              theOrientationFlags;
  occ::handle<NCollection_HArray1<int>>                              theNbParameterCurves;
  occ::handle<IGESBasic_HArray1OfHArray1OfInteger>                   theIsoparametricFlags;
  occ::handle<IGESBasic_HArray1OfHArray1OfIGESEntity>                theCurves;
};
