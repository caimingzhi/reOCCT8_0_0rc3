

#include <ShapePersistent_Geom2d.hpp>
#include <ShapePersistent_Geom2d_Curve.hpp>

#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2d_OffsetCurve.hpp>

template <>
const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::Direction, Geom2d_Direction, gp_Dir2d>::PName() const
{
  return "PGeom2d_Direction";
}

template <>
void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::Direction, Geom2d_Direction, gp_Dir2d>::
  Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom2d_Direction> aMyGeom = occ::down_cast<Geom2d_Direction>(myTransient);
  theWriteData << aMyGeom->Dir2d();
}

template <>
const char* ShapePersistent_Geom::instance<ShapePersistent_Geom2d::VectorWithMagnitude,
                                           Geom2d_VectorWithMagnitude,
                                           gp_Vec2d>::PName() const
{
  return "PGeom2d_VectorWithMagnitude";
}

template <>
void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::VectorWithMagnitude,
                                    Geom2d_VectorWithMagnitude,
                                    gp_Vec2d>::Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom2d_VectorWithMagnitude> aMyGeom =
    occ::down_cast<Geom2d_VectorWithMagnitude>(myTransient);
  theWriteData << aMyGeom->Vec2d();
}

template <>
const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::AxisPlacement, Geom2d_AxisPlacement, gp_Ax2d>::PName() const
{
  return "PGeom2d_AxisPlacement";
}

template <>
void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::AxisPlacement,
                                    Geom2d_AxisPlacement,
                                    gp_Ax2d>::Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom2d_AxisPlacement> aMyGeom = occ::down_cast<Geom2d_AxisPlacement>(myTransient);
  write(theWriteData, aMyGeom->Ax2d());
}

template <>
const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::Transformation, Geom2d_Transformation, gp_Trsf2d>::PName() const
{
  return "PGeom2d_Transformation";
}

template <>
void ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::Transformation, Geom2d_Transformation, gp_Trsf2d>::PChildren(
    StdObjMgt_Persistent::SequenceOfPersistent&) const
{
}

template <>
void ShapePersistent_Geom2d::instance<ShapePersistent_Geom2d::Transformation,
                                      Geom2d_Transformation,
                                      gp_Trsf2d>::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myTransient->Trsf2d();
}

Handle(ShapePersistent_Geom2d::Curve) ShapePersistent_Geom2d::Translate(
  const occ::handle<Geom2d_Curve>&                                                         theCurve,
  NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap)
{
  Handle(ShapePersistent_Geom2d::Curve) aPC;
  if (!theCurve.IsNull())
  {
    if (theMap.IsBound(theCurve))
      aPC = Handle(ShapePersistent_Geom2d::Curve)::DownCast(theMap.Find(theCurve));
    else
    {
      occ::handle<Standard_Type> aCT = theCurve->DynamicType();
      if (aCT == STANDARD_TYPE(Geom2d_Line))
      {
        aPC =
          ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_Line>(theCurve), theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_Circle))
      {
        aPC =
          ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_Circle>(theCurve), theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_Ellipse))
      {
        aPC =
          ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_Ellipse>(theCurve), theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_Hyperbola))
      {
        aPC = ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_Hyperbola>(theCurve),
                                                      theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_Parabola))
      {
        aPC = ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_Parabola>(theCurve),
                                                      theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_BezierCurve))
      {
        aPC = ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_BezierCurve>(theCurve),
                                                      theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_BSplineCurve))
      {
        aPC = ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_BSplineCurve>(theCurve),
                                                      theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_TrimmedCurve))
      {
        aPC = ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_TrimmedCurve>(theCurve),
                                                      theMap);
      }
      else if (aCT == STANDARD_TYPE(Geom2d_OffsetCurve))
      {
        aPC = ShapePersistent_Geom2d_Curve::Translate(occ::down_cast<Geom2d_OffsetCurve>(theCurve),
                                                      theMap);
      }
      else
      {
        throw Standard_NullObject("No mapping for the current Transient Curve");
      }
      theMap.Bind(theCurve, aPC);
    }
  }
  return aPC;
}
