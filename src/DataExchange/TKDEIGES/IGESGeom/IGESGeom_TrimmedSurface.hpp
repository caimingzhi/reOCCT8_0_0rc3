#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESGeom_CurveOnSurface.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESGeom_CurveOnSurface;

class IGESGeom_TrimmedSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_TrimmedSurface();

  Standard_EXPORT void Init(
    const occ::handle<IGESData_IGESEntity>&                                       aSurface,
    const int                                                                     aFlag,
    const occ::handle<IGESGeom_CurveOnSurface>&                                   anOuter,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGeom_CurveOnSurface>>>& allInners);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  Standard_EXPORT bool HasOuterContour() const;

  Standard_EXPORT occ::handle<IGESGeom_CurveOnSurface> OuterContour() const;

  Standard_EXPORT int OuterBoundaryType() const;

  Standard_EXPORT int NbInnerContours() const;

  Standard_EXPORT occ::handle<IGESGeom_CurveOnSurface> InnerContour(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_TrimmedSurface, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity>                                       theSurface;
  int                                                                    theFlag;
  occ::handle<IGESGeom_CurveOnSurface>                                   theOuterCurve;
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_CurveOnSurface>>> theInnerCurves;
};
