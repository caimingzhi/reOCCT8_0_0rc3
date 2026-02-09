#pragma once

#include <gp_XYZ.hpp>
#include <STEPControl_Controller.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Circle.hpp>
#include <StepGeom_Direction.hpp>
#include <StepGeom_Line.hpp>
#include <StepGeom_Plane.hpp>
#include <StepGeom_Vector.hpp>
#include <XSControl_WorkSession.hpp>

#include <gtest/gtest.h>

class StepTidy_BaseTestFixture : public testing::Test
{
protected:
  StepTidy_BaseTestFixture()
      : myWS()
  {
    STEPControl_Controller::Init();
    myWS = new XSControl_WorkSession;
    myWS->SelectNorm("STEP");
    myWS->SetModel(myWS->NormAdaptor()->NewModel());
  }

  occ::handle<StepGeom_CartesianPoint> addCartesianPoint(const char*   theName  = nullptr,
                                                         const gp_XYZ& thePoint = gp_XYZ(0.,
                                                                                         0.,
                                                                                         0.)) const
  {
    const occ::handle<StepGeom_CartesianPoint>  aCartesianPoint = new StepGeom_CartesianPoint;
    const occ::handle<TCollection_HAsciiString> aName =
      theName ? new TCollection_HAsciiString(theName) : new TCollection_HAsciiString();
    aCartesianPoint->Init3D(aName, thePoint.X(), thePoint.Y(), thePoint.Z());
    myWS->Model()->AddWithRefs(aCartesianPoint);
    return aCartesianPoint;
  }

  occ::handle<StepGeom_Direction> addDirection(const char*   theName      = nullptr,
                                               const gp_XYZ& theDirection = gp_XYZ(0.,
                                                                                   0.,
                                                                                   1.)) const
  {
    const occ::handle<StepGeom_Direction>       aDirection = new StepGeom_Direction;
    const occ::handle<TCollection_HAsciiString> aName =
      theName ? new TCollection_HAsciiString(theName) : new TCollection_HAsciiString();
    occ::handle<NCollection_HArray1<double>> aDirectionRatios =
      new NCollection_HArray1<double>(1, 3);
    aDirectionRatios->SetValue(1, theDirection.X());
    aDirectionRatios->SetValue(2, theDirection.Y());
    aDirectionRatios->SetValue(3, theDirection.Z());
    aDirection->Init(aName, aDirectionRatios);
    myWS->Model()->AddWithRefs(aDirection);
    return aDirection;
  }

  occ::handle<StepGeom_Vector> addVector(const char*   theName        = nullptr,
                                         const gp_XYZ& theOrientation = gp_XYZ(0., 0., 1.),
                                         const double  aMagnitude     = 1.) const
  {
    const occ::handle<StepGeom_Vector>          aVector = new StepGeom_Vector;
    const occ::handle<TCollection_HAsciiString> aName =
      theName ? new TCollection_HAsciiString(theName) : new TCollection_HAsciiString();
    aVector->Init(aName, addDirection(nullptr, theOrientation), aMagnitude);
    myWS->Model()->AddWithRefs(aVector);
    return aVector;
  }

  occ::handle<StepGeom_Axis2Placement3d> addAxis2Placement3d(
    const char*   theName         = nullptr,
    const gp_XYZ& theLocation     = gp_XYZ(0., 0., 0.),
    const gp_XYZ& theAxis         = gp_XYZ(0., 0., 1.),
    const gp_XYZ& theRefDirection = gp_XYZ(0., 1., 0.)) const
  {
    const occ::handle<StepGeom_Axis2Placement3d> aAxis2Placement3d = new StepGeom_Axis2Placement3d;
    const occ::handle<TCollection_HAsciiString>  aName =
      theName ? new TCollection_HAsciiString(theName) : new TCollection_HAsciiString();
    aAxis2Placement3d->Init(aName,
                            addCartesianPoint(nullptr, theLocation),
                            true,
                            addDirection(nullptr, theAxis),
                            true,
                            addDirection(nullptr, theRefDirection));
    myWS->Model()->AddWithRefs(aAxis2Placement3d);
    return aAxis2Placement3d;
  }

  occ::handle<StepGeom_Line> addLine(const char*   theName        = nullptr,
                                     const gp_XYZ& theLocation    = gp_XYZ(0., 0., 0.),
                                     const gp_XYZ& theOrientation = gp_XYZ(0., 0., 1.),
                                     const double  aMagnitude     = 1.) const
  {
    const occ::handle<StepGeom_Line>            aLine = new StepGeom_Line;
    const occ::handle<TCollection_HAsciiString> aName =
      theName ? new TCollection_HAsciiString(theName) : new TCollection_HAsciiString();
    aLine->Init(aName,
                addCartesianPoint(nullptr, theLocation),
                addVector(nullptr, theOrientation, aMagnitude));
    myWS->Model()->AddWithRefs(aLine);
    return aLine;
  }

  occ::handle<StepGeom_Circle> addCircle(const char*   theName         = nullptr,
                                         const gp_XYZ& theLocation     = gp_XYZ(0., 0., 0.),
                                         const gp_XYZ& theAxis         = gp_XYZ(0., 0., 1.),
                                         const gp_XYZ& theRefDirection = gp_XYZ(0., 1., 0.),
                                         const double  theRadius       = 1.) const
  {
    const occ::handle<StepGeom_Circle>          aCircle = new StepGeom_Circle;
    const occ::handle<TCollection_HAsciiString> aName =
      theName ? new TCollection_HAsciiString(theName) : new TCollection_HAsciiString();
    StepGeom_Axis2Placement aSelector;
    aSelector.SetValue(addAxis2Placement3d(nullptr, theLocation, theAxis, theRefDirection));
    aCircle->Init(aName, aSelector, theRadius);
    myWS->Model()->AddWithRefs(aCircle);
    return aCircle;
  }

  occ::handle<StepGeom_Plane> addPlane(const char*   theName         = nullptr,
                                       const gp_XYZ& theLocation     = gp_XYZ(0., 0., 0.),
                                       const gp_XYZ& theAxis         = gp_XYZ(0., 0., 1.),
                                       const gp_XYZ& theRefDirection = gp_XYZ(0., 1., 0.)) const
  {
    const occ::handle<StepGeom_Plane>           aPlane = new StepGeom_Plane;
    const occ::handle<TCollection_HAsciiString> aName =
      theName ? new TCollection_HAsciiString(theName) : new TCollection_HAsciiString();
    aPlane->Init(aName, addAxis2Placement3d(nullptr, theLocation, theAxis, theRefDirection));
    myWS->Model()->AddWithRefs(aPlane);
    return aPlane;
  }

  void addToModel(const occ::handle<Standard_Transient>& theEntity) const
  {
    myWS->Model()->AddWithRefs(theEntity);
  }

protected:
  occ::handle<XSControl_WorkSession> myWS;
};
