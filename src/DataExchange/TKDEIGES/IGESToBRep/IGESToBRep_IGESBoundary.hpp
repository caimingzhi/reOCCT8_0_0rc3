#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESToBRep_CurveAndSurface.hpp>
#include <TopoDS_Face.hpp>
#include <gp_Trsf2d.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class IGESData_IGESEntity;
class ShapeExtend_WireData;

//! This class is intended to translate IGES boundary entity
//! (142-CurveOnSurface, 141-Boundary or 508-Loop) into the wire.
//! Methods Transfer are virtual and are redefined in Advanced
//! Data Exchange to optimize the translation and take into
//! account advanced parameters.
class IGESToBRep_IGESBoundary : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT IGESToBRep_IGESBoundary();

  //! Empty constructor
  Standard_EXPORT IGESToBRep_IGESBoundary(const IGESToBRep_CurveAndSurface& CS);

  //! Inits the object with parameters common for all
  //! types of IGES boundaries.
  //! <CS>: object to be used for retrieving translation parameters
  //! and sending messages,
  //! <entity>: boundary entity to be processed,
  //! <face>, <trans>, <uFact>: as for IGESToBRep_TopoCurve
  //! <filepreference>: preferred representation (2 or 3) given
  //! in the IGES file
  Standard_EXPORT void Init(const IGESToBRep_CurveAndSurface&       CS,
                            const occ::handle<IGESData_IGESEntity>& entity,
                            const TopoDS_Face&                      face,
                            const gp_Trsf2d&                        trans,
                            const double                            uFact,
                            const int                               filepreference);

  //! Returns the resulting wire
  occ::handle<ShapeExtend_WireData> WireData() const;

  //! Returns the wire from 3D curves (edges contain 3D curves
  //! and may contain pcurves)
  occ::handle<ShapeExtend_WireData> WireData3d() const;

  //! Returns the wire from 2D curves (edges contain pcurves
  //! only)
  occ::handle<ShapeExtend_WireData> WireData2d() const;

  //! Translates 141 and 142 entities.
  //! Returns True if the curve has been successfully translated,
  //! otherwise returns False.
  //! <okCurve..>: flags that indicate whether corresponding
  //! representation has been successfully translated
  //! (must be set to True before first call),
  //! <curve3d>: model space curve for 142 and current model space
  //! curve for 141,
  //! <toreverse3d>: False for 142 and current orientation flag
  //! for 141,
  //! <curves2d>: 1 parameter space curve for 142 or list of
  //! them for current model space curves for 141,
  //! <number>: 1 for 142 and rank number of model space curve for 141.
  Standard_EXPORT bool Transfer(
    bool&                                                                     okCurve,
    bool&                                                                     okCurve3d,
    bool&                                                                     okCurve2d,
    const occ::handle<IGESData_IGESEntity>&                                   curve3d,
    const bool                                                                toreverse3d,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& curves2d,
    const int                                                                 number);

  //! Translates 508 entity.
  //! Returns True if the curve has been successfully translated,
  //! otherwise returns False.
  //! Input object IGESBoundary must be created and initialized
  //! before.
  //! <okCurve..>: flags that indicate whether corresponding
  //! representation has been successfully translated
  //! (must be set to True before first call),
  //! <curve3d>: result of translation of current edge,
  //! <curves2d>: list of parameter space curves for edge,
  //! <toreverse2d>: orientation flag of current edge in respect
  //! to its model space curve,
  //! <number>: rank number of edge,
  //! <lsewd>: returns the result of translation of current edge.
  Standard_EXPORT bool Transfer(
    bool&                                                                     okCurve,
    bool&                                                                     okCurve3d,
    bool&                                                                     okCurve2d,
    const occ::handle<ShapeExtend_WireData>&                                  curve3d,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& curves2d,
    const bool                                                                toreverse2d,
    const int                                                                 number,
    occ::handle<ShapeExtend_WireData>&                                        lsewd);

  //! Checks result of translation of IGES boundary entities
  //! (types 141, 142 or 508).
  //! Checks consistency of 2D and 3D representations and keeps
  //! only one if they are inconsistent.
  //! <result>: result of translation (returned by Transfer),
  //! <checkclosure>: False for 142 without parent 144 entity,
  //! otherwise True,
  //! <okCurve3d>, <okCurve2d>: those returned by Transfer.
  Standard_EXPORT virtual void Check(const bool result,
                                     const bool checkclosure,
                                     const bool okCurve3d,
                                     const bool okCurve2d);

  DEFINE_STANDARD_RTTIEXT(IGESToBRep_IGESBoundary, Standard_Transient)

protected:
  //! Methods called by both Transfer methods.
  Standard_EXPORT virtual bool Transfer(
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
    occ::handle<ShapeExtend_WireData>&                                        lsewd);

  Standard_EXPORT static void ReverseCurves3d(const occ::handle<ShapeExtend_WireData>& sewd);

  Standard_EXPORT static void ReverseCurves2d(const occ::handle<ShapeExtend_WireData>& sewd,
                                              const TopoDS_Face&                       face);

  IGESToBRep_CurveAndSurface        myCS;
  occ::handle<IGESData_IGESEntity>  myentity;
  occ::handle<ShapeExtend_WireData> mysewd;
  occ::handle<ShapeExtend_WireData> mysewd3d;
  occ::handle<ShapeExtend_WireData> mysewd2d;
  TopoDS_Face                       myface;
  gp_Trsf2d                         mytrsf;
  double                            myuFact;
  int                               myfilepreference;
};

inline occ::handle<ShapeExtend_WireData> IGESToBRep_IGESBoundary::WireData() const
{
  return mysewd;
}

inline occ::handle<ShapeExtend_WireData> IGESToBRep_IGESBoundary::WireData3d() const
{
  return mysewd3d;
}

inline occ::handle<ShapeExtend_WireData> IGESToBRep_IGESBoundary::WireData2d() const
{
  return mysewd2d;
}
