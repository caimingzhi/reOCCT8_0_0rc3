#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESToBRep_IGESBoundary.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class IGESToBRep_CurveAndSurface;
class IGESData_IGESEntity;
class ShapeExtend_WireData;

class IGESControl_IGESBoundary : public IGESToBRep_IGESBoundary
{

public:
  Standard_EXPORT IGESControl_IGESBoundary();

  Standard_EXPORT IGESControl_IGESBoundary(const IGESToBRep_CurveAndSurface& CS);

  Standard_EXPORT void Check(const bool result,
                             const bool checkclosure,
                             const bool okCurve3d,
                             const bool okCurve2d) override;

  DEFINE_STANDARD_RTTIEXT(IGESControl_IGESBoundary, IGESToBRep_IGESBoundary)

protected:
  Standard_EXPORT bool Transfer(
    bool&                                                                     okCurve,
    bool&                                                                     okCurve3d,
    bool&                                                                     okCurve2d,
    const occ::handle<IGESData_IGESEntity>&                                   icurve3d,
    const occ::handle<ShapeExtend_WireData>&                                  scurve3d,
    const bool                                                                usescurve,
    const bool                                                                toreverse3d,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& curves2d,
    const bool                                                                toreverse2d,
    const int                                                                 number,
    occ::handle<ShapeExtend_WireData>&                                        lsewd) override;
};
