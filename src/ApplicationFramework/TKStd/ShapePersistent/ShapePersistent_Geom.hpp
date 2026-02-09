#pragma once

#include <Standard_NotImplemented.hpp>
#include <Standard_NullObject.hpp>

#include <StdObjMgt_SharedObject.hpp>
#include <NCollection_DataMap.hpp>

#include <StdObject_gp_Curves.hpp>

#include <StdObject_gp_Axes.hpp>

#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Cone& theCone)
{
  gp_Ax3 anAx;
  double aRadius, aSemiAngle;

  theReadData >> anAx >> aRadius >> aSemiAngle;

  theCone.SetPosition(anAx);
  theCone.SetRadius(aRadius);
  theCone.SetSemiAngle(aSemiAngle);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Cone& theCone)
{
  const gp_Ax3& anAx       = theCone.Position();
  double        aRadius    = theCone.RefRadius();
  double        aSemiAngle = theCone.SemiAngle();
  theWriteData << anAx << aRadius << aSemiAngle;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Cylinder& theCyl)
{
  gp_Ax3 anAx;
  double aRadius;

  theReadData >> anAx >> aRadius;

  theCyl.SetPosition(anAx);
  theCyl.SetRadius(aRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Cylinder& theCyl)
{
  const gp_Ax3& anAx    = theCyl.Position();
  double        aRadius = theCyl.Radius();
  theWriteData << anAx << aRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Sphere& theSph)
{
  gp_Ax3 anAx;
  double aRadius;

  theReadData >> anAx >> aRadius;

  theSph.SetPosition(anAx);
  theSph.SetRadius(aRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Sphere& theSph)
{
  const gp_Ax3& anAx    = theSph.Position();
  double        aRadius = theSph.Radius();
  theWriteData << anAx << aRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Torus& theTorus)
{
  gp_Ax3 anAx;
  double aMajorRadius, aMinorRadius;

  theReadData >> anAx >> aMajorRadius >> aMinorRadius;

  theTorus.SetPosition(anAx);
  theTorus.SetMajorRadius(aMajorRadius);
  theTorus.SetMinorRadius(aMinorRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Torus& theTorus)
{
  const gp_Ax3& anAx         = theTorus.Position();
  double        aMajorRadius = theTorus.MajorRadius();
  double        aMinorRadius = theTorus.MinorRadius();
  theWriteData << anAx << aMajorRadius << aMinorRadius;
  return theWriteData;
}

#include <StdObject_gp_Trsfs.hpp>

#include <Geom_CartesianPoint.hpp>
#include <Geom_Direction.hpp>
#include <Geom_VectorWithMagnitude.hpp>
#include <Geom_Axis1Placement.hpp>
#include <Geom_Axis2Placement.hpp>
#include <Geom_Transformation.hpp>
#include <Geom_Surface.hpp>
class Standard_Transient;
class StdObjMgt_Persistent;

class ShapePersistent_Geom : public StdObjMgt_SharedObject
{
public:
  class Geometry : public StdObjMgt_Persistent
  {
  public:
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    Standard_EXPORT void PChildren(SequenceOfPersistent& theChildren) const override;

    const char* PName() const override { return "PGeom_Geometry"; }
  };

protected:
  template <class Transient>
  struct geometryBase : public DelayedBase<Geometry, Transient>
  {

    void Write(StdObjMgt_WriteData&) const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::geometryBase::Write - not implemented");
    }

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    const char* PName() const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::geometryBase::PName - not implemented");
    }
  };

  template <class Base, class PData>
  class subBase : public Base
  {
  public:
    void Read(StdObjMgt_ReadData& theReadData) override { PData().Read(theReadData); }

    void Write(StdObjMgt_WriteData& theWriteData) const override { PData().Write(theWriteData); }

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::subBase::PChildren - not implemented");
    }

    const char* PName() const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::subBase::PName - not implemented");
    }
  };

  template <class Base, class GpData>
  struct subBase_gp : public Base
  {
  public:
    void Read(StdObjMgt_ReadData&) override {}

    void Write(StdObjMgt_WriteData&) const override {}

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    const char* PName() const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::subBase_gp::PName - not implemented");
    }
  };

  template <class Base>
  struct subBase_empty : Base
  {

    const char* PName() const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::subBase_empty::PName - not implemented");
    }
  };

  template <class Base, class Target, class Data = void>
  class instance : public Base
  {
  public:
    void Read(StdObjMgt_ReadData& theReadData) override
    {
      Data aData;
      theReadData >> aData;
      this->myTransient = new Target(aData);
    }

    void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    void Write(StdObjMgt_WriteData&) const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::instance::Write - not implemented");
    }

    const char* PName() const override
    {
      throw Standard_NotImplemented("ShapePersistent_Geom::instance::PName - not implemented");
    }
  };

private:
  typedef geometryBase<Geom_Geometry> basic;

public:
  typedef subBase_empty<basic>                         Point;
  typedef instance<Point, Geom_CartesianPoint, gp_Pnt> CartesianPoint;

  typedef subBase_gp<basic, gp_Vec>                          Vector;
  typedef instance<Vector, Geom_Direction, gp_Dir>           Direction;
  typedef instance<Vector, Geom_VectorWithMagnitude, gp_Vec> VectorWithMagnitude;

  typedef subBase_gp<basic, gp_Ax1>                            AxisPlacement;
  typedef instance<AxisPlacement, Geom_Axis1Placement, gp_Ax1> Axis1Placement;
  typedef instance<AxisPlacement, Geom_Axis2Placement>         Axis2Placement;

  typedef instance<SharedBase<Geom_Transformation>, Geom_Transformation, gp_Trsf> Transformation;

  typedef geometryBase<Geom_Curve>   Curve;
  typedef geometryBase<Geom_Surface> Surface;

public:
  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom_Curve>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_Surface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);
};

template <>
inline const char* ShapePersistent_Geom::subBase_empty<ShapePersistent_Geom::basic>::PName() const
{
  return "PGeom_Point";
}

template <>
inline const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom::Point, Geom_CartesianPoint, gp_Pnt>::PName() const
{
  return "PGeom_CartesianPoint";
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom::Point,
                                           Geom_CartesianPoint,
                                           gp_Pnt>::Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom_CartesianPoint> aMyGeom = occ::down_cast<Geom_CartesianPoint>(myTransient);
  theWriteData << aMyGeom->Pnt();
}

template <>
inline const char* ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::basic, gp_Vec>::PName()
  const
{
  return "PGeom_Vector";
}

template <>
inline const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom::Direction, Geom_Direction, gp_Dir>::PName() const
{
  return "PGeom_Direction";
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom::Direction,
                                           Geom_Direction,
                                           gp_Dir>::Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom_Direction> aMyGeom = occ::down_cast<Geom_Direction>(myTransient);
  theWriteData << aMyGeom->Dir();
}

template <>
inline const char* ShapePersistent_Geom::instance<ShapePersistent_Geom::VectorWithMagnitude,
                                                  Geom_VectorWithMagnitude,
                                                  gp_Vec>::PName() const
{
  return "PGeom_VectorWithMagnitude";
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom::VectorWithMagnitude,
                                           Geom_VectorWithMagnitude,
                                           gp_Vec>::Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom_VectorWithMagnitude> aMyGeom =
    occ::down_cast<Geom_VectorWithMagnitude>(myTransient);
  theWriteData << aMyGeom->Vec();
}

template <>
inline const char* ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::basic, gp_Ax1>::PName()
  const
{
  return "PGeom_AxisPlacement";
}

template <>
inline const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom::Axis1Placement, Geom_Axis1Placement, gp_Ax1>::PName() const
{
  return "PGeom_Axis1Placement";
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom::Axis1Placement,
                                           Geom_Axis1Placement,
                                           gp_Ax1>::Write(StdObjMgt_WriteData& theWriteData) const
{
  occ::handle<Geom_Axis1Placement> aMyGeom = occ::down_cast<Geom_Axis1Placement>(myTransient);
  write(theWriteData, aMyGeom->Ax1());
}

template <>
inline const char* ShapePersistent_Geom::instance<ShapePersistent_Geom::AxisPlacement,
                                                  Geom_Axis2Placement>::PName() const
{
  return "PGeom_Axis2Placement";
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom::AxisPlacement,
                                           Geom_Axis2Placement>::Read(StdObjMgt_ReadData&
                                                                        theReadData)
{
  gp_Ax1 anAxis;
  gp_Dir anXDirection;

  theReadData >> anAxis >> anXDirection;

  myTransient = new Geom_Axis2Placement(anAxis.Location(), anAxis.Direction(), anXDirection);
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom::AxisPlacement,
                                           Geom_Axis2Placement>::Write(StdObjMgt_WriteData&
                                                                         theWriteData) const
{
  occ::handle<Geom_Axis2Placement> aMyGeom      = occ::down_cast<Geom_Axis2Placement>(myTransient);
  const gp_Ax1&                    anAxis       = aMyGeom->Axis();
  const gp_Dir&                    anXDirection = aMyGeom->Direction();
  write(theWriteData, anAxis) << anXDirection;
}

template <>
inline const char* ShapePersistent_Geom::
  instance<ShapePersistent_Geom::Transformation, Geom_Transformation, gp_Trsf>::PName() const
{
  return "PGeom_Transformation";
}

template <>
inline void ShapePersistent_Geom::instance<ShapePersistent_Geom::Transformation,
                                           Geom_Transformation,
                                           gp_Trsf>::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myTransient->Trsf();
}

template <>
inline const char* ShapePersistent_Geom::geometryBase<Geom_Geometry>::PName() const
{
  return "PGeom_Geometry";
}

template <>
inline const char* ShapePersistent_Geom::geometryBase<Geom_Curve>::PName() const
{
  return "PGeom_Curve";
}

template <>
inline const char* ShapePersistent_Geom::geometryBase<Geom_Surface>::PName() const
{
  return "PGeom_Surface";
}
