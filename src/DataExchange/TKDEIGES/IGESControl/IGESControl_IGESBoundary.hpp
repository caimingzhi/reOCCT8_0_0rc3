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

//! Translates IGES boundary entity (types 141, 142 and 508)
//! in Advanced Data Exchange.
//! Redefines translation and treatment methods from inherited
//! open class IGESToBRep_IGESBoundary.
class IGESControl_IGESBoundary : public IGESToBRep_IGESBoundary
{

public:
  //! Creates an object and calls inherited constructor.
  Standard_EXPORT IGESControl_IGESBoundary();

  //! Creates an object and calls inherited constructor.
  Standard_EXPORT IGESControl_IGESBoundary(const IGESToBRep_CurveAndSurface& CS);

  //! Checks result of translation of IGES boundary entities
  //! (types 141, 142 or 508).
  //! Checks consistency of 2D and 3D representations and keeps
  //! only one if they are inconsistent.
  //! Checks the closure of resulting wire and if it is not closed,
  //! checks 2D and 3D representation and updates the resulting
  //! wire to contain only closed representation.
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
