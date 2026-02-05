#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;
class IntSurf_LineOn2S;
class IntSurf_PntOn2S;

class BRepApprox_ApproxLine : public Standard_Transient
{

public:
  Standard_EXPORT BRepApprox_ApproxLine(const occ::handle<Geom_BSplineCurve>&   CurveXYZ,
                                        const occ::handle<Geom2d_BSplineCurve>& CurveUV1,
                                        const occ::handle<Geom2d_BSplineCurve>& CurveUV2);

  //! theTang variable has been entered only for compatibility with
  //! the alias IntPatch_WLine. They are not used in this class.
  Standard_EXPORT BRepApprox_ApproxLine(const occ::handle<IntSurf_LineOn2S>& lin,
                                        const bool                           theTang = false);

  Standard_EXPORT int NbPnts() const;

  Standard_EXPORT IntSurf_PntOn2S Point(const int Index);

  DEFINE_STANDARD_RTTIEXT(BRepApprox_ApproxLine, Standard_Transient)

private:
  occ::handle<Geom_BSplineCurve>   myCurveXYZ;
  occ::handle<Geom2d_BSplineCurve> myCurveUV1;
  occ::handle<Geom2d_BSplineCurve> myCurveUV2;
  occ::handle<IntSurf_LineOn2S>    myLineOn2S;
};
