#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt2d;
class gp_Pnt;
class gp_Dir;

//! defines IGESCircularArc, Type <100> Form <0>
//! in package IGESGeom
//! A circular arc is a connected portion of a parent circle
//! which consists of more than one point. The definition space
//! coordinate system is always chosen so that the circular arc
//! remains in a plane either coincident with or parallel to
//! the XT, YT plane.
class IGESGeom_CircularArc : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_CircularArc();

  //! This method is used to set the fields of the class
  //! CircularArc
  //! - aZT     : Shift above the Z plane
  //! - aCenter : Center of the circle of which the arc forms a part
  //! - aStart  : Starting point of the circular arc
  //! - anEnd   : Ending point of the circular arc
  Standard_EXPORT void Init(const double aZT,
                            const gp_XY& aCenter,
                            const gp_XY& aStart,
                            const gp_XY& anEnd);

  //! returns the center of the circle of which arc forms a part
  Standard_EXPORT gp_Pnt2d Center() const;

  //! returns the center of the circle of which arc forms a part
  //! after applying Transf. Matrix
  Standard_EXPORT gp_Pnt TransformedCenter() const;

  //! returns the start point of the arc
  Standard_EXPORT gp_Pnt2d StartPoint() const;

  //! returns the start point of the arc after applying Transf. Matrix
  Standard_EXPORT gp_Pnt TransformedStartPoint() const;

  //! returns the parallel displacement of the plane containing the
  //! arc from the XT, YT plane
  Standard_EXPORT double ZPlane() const;

  //! returns the end point of the arc
  Standard_EXPORT gp_Pnt2d EndPoint() const;

  //! returns the end point of the arc after applying Transf. Matrix
  Standard_EXPORT gp_Pnt TransformedEndPoint() const;

  //! returns the radius of the circle of which arc forms a part
  Standard_EXPORT double Radius() const;

  //! returns the angle subtended by the arc at the center in radians
  Standard_EXPORT double Angle() const;

  //! Z-Axis of circle (i.e. [0,0,1])
  Standard_EXPORT gp_Dir Axis() const;

  //! Z-Axis after applying Trans. Matrix
  Standard_EXPORT gp_Dir TransformedAxis() const;

  //! True if StartPoint = EndPoint
  Standard_EXPORT bool IsClosed() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_CircularArc, IGESData_IGESEntity)

private:
  double theZT;
  gp_XY  theCenter;
  gp_XY  theStart;
  gp_XY  theEnd;
};

