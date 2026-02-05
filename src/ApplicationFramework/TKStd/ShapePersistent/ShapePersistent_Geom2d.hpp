#pragma once

#include <ShapePersistent_Geom.hpp>

#include <Geom2d_CartesianPoint.hpp>
#include <Geom2d_Direction.hpp>
#include <Geom2d_VectorWithMagnitude.hpp>
#include <Geom2d_AxisPlacement.hpp>
#include <Geom2d_Transformation.hpp>
#include <Geom2d_Curve.hpp>

class ShapePersistent_Geom2d : public ShapePersistent_Geom
{
  typedef geometryBase<Geom2d_Geometry> basic;

public:
  typedef ShapePersistent_Geom::Geometry Geometry;

  typedef subBase_empty<basic>                             Point;
  typedef instance<Point, Geom2d_CartesianPoint, gp_Pnt2d> CartesianPoint;

  typedef subBase_gp<basic, gp_Vec2d>                            Vector;
  typedef instance<Vector, Geom2d_Direction, gp_Dir2d>           Direction;
  typedef instance<Vector, Geom2d_VectorWithMagnitude, gp_Vec2d> VectorWithMagnitude;

  typedef instance<basic, Geom2d_AxisPlacement, gp_Ax2d> AxisPlacement;

  typedef instance<SharedBase<Geom2d_Transformation>, Geom2d_Transformation, gp_Trsf2d>
    Transformation;

  typedef geometryBase<Geom2d_Curve> Curve;

public:
  //! Create a persistent object for a curve
  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_Curve>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);
};

//=======================================================================
// Geometry
//=======================================================================
template <>
inline const char* ShapePersistent_Geom::geometryBase<Geom2d_Geometry>::PName() const
{
  return "PGeom2d_Geometry";
}

//=======================================================================
// Point
//=======================================================================
template <>
inline const char* ShapePersistent_Geom::subBase_empty<
  ShapePersistent_Geom2d::geometryBase<Geom2d_Geometry>>::PName() const
{
  return "PGeom2d_Point";
}

//=======================================================================
// CartesianPoint
//=======================================================================
template <>
inline const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::Point, Geom2d_CartesianPoint, gp_Pnt2d>::PName() const
{
  return "PGeom2d_CartesianPoint";
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::Point,
                                           Geom2d_CartesianPoint,
                                           gp_Pnt2d>::Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom2d_CartesianPoint> aMyGeom = occ::down_cast<Geom2d_CartesianPoint>(myTransient);
  theWriteData << aMyGeom->Pnt2d();
}

//=======================================================================
// Direction
//=======================================================================
template <>
const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::Direction, Geom2d_Direction, gp_Dir2d>::PName() const;

template <>
void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::Direction, Geom2d_Direction, gp_Dir2d>::
  Write(StdObjMgt_WriteData& theWriteData) const;

//=======================================================================
// VectorWithMagnitude
//=======================================================================
template <>
const char* ShapePersistent_Geom::instance<ShapePersistent_Geom2d::VectorWithMagnitude,
                                           Geom2d_VectorWithMagnitude,
                                           gp_Vec2d>::PName() const;

template <>
void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::VectorWithMagnitude,
                                    Geom2d_VectorWithMagnitude,
                                    gp_Vec2d>::Write(StdObjMgt_WriteData& theWriteData) const;

//=======================================================================
// AxisPlacement
//=======================================================================
template <>
const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::AxisPlacement, Geom2d_AxisPlacement, gp_Ax2d>::PName() const;

template <>
void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::AxisPlacement,
                                    Geom2d_AxisPlacement,
                                    gp_Ax2d>::Write(StdObjMgt_WriteData& theWriteData) const;

//=======================================================================
// Transformation
//=======================================================================
template <>
const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::Transformation, Geom2d_Transformation, gp_Trsf2d>::PName() const;

template <>
void ShapePersistent_Geom::
  instance<ShapePersistent_Geom2d::Transformation, Geom2d_Transformation, gp_Trsf2d>::PChildren(
    StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

template <>
void ShapePersistent_Geom::instance<ShapePersistent_Geom2d::Transformation,
                                    Geom2d_Transformation,
                                    gp_Trsf2d>::Write(StdObjMgt_WriteData& theWriteData) const;

//=======================================================================
// Curve
//=======================================================================
template <>
inline const char* ShapePersistent_Geom::geometryBase<Geom2d_Curve>::PName() const
{
  return "PGeom2d_Curve";
}
