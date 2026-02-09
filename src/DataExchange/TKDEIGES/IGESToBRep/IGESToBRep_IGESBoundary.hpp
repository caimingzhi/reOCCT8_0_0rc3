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

class IGESToBRep_IGESBoundary : public Standard_Transient
{

public:
  Standard_EXPORT IGESToBRep_IGESBoundary();

  Standard_EXPORT IGESToBRep_IGESBoundary(const IGESToBRep_CurveAndSurface& CS);

  Standard_EXPORT void Init(const IGESToBRep_CurveAndSurface&       CS,
                            const occ::handle<IGESData_IGESEntity>& entity,
                            const TopoDS_Face&                      face,
                            const gp_Trsf2d&                        trans,
                            const double                            uFact,
                            const int                               filepreference);

  occ::handle<ShapeExtend_WireData> WireData() const;

  occ::handle<ShapeExtend_WireData> WireData3d() const;

  occ::handle<ShapeExtend_WireData> WireData2d() const;

  Standard_EXPORT bool Transfer(
    bool&                                                                     okCurve,
    bool&                                                                     okCurve3d,
    bool&                                                                     okCurve2d,
    const occ::handle<IGESData_IGESEntity>&                                   curve3d,
    const bool                                                                toreverse3d,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& curves2d,
    const int                                                                 number);

  Standard_EXPORT bool Transfer(
    bool&                                                                     okCurve,
    bool&                                                                     okCurve3d,
    bool&                                                                     okCurve2d,
    const occ::handle<ShapeExtend_WireData>&                                  curve3d,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& curves2d,
    const bool                                                                toreverse2d,
    const int                                                                 number,
    occ::handle<ShapeExtend_WireData>&                                        lsewd);

  Standard_EXPORT virtual void Check(const bool result,
                                     const bool checkclosure,
                                     const bool okCurve3d,
                                     const bool okCurve2d);

  DEFINE_STANDARD_RTTIEXT(IGESToBRep_IGESBoundary, Standard_Transient)

protected:
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
