#pragma once

//! Indicates the outcome of a construction, i.e.
//! whether it is successful or not, as explained below.
//! gce_Done: Construction was successful.
//! gce_ConfusedPoints: Two points are coincident.
//! gce_NegativeRadius: Radius value is negative.
//! gce_ColinearPoints: Three points are collinear.
//! gce_IntersectionError: Intersection cannot be computed.
//! gce_NullAxis: Axis is undefined.
//! gce_NullAngle: Angle value is invalid (usually null).
//! gce_NullRadius: Radius is null.
//! gce_InvertAxis: Axis value is invalid.
//! gce_BadAngle: Angle value is invalid.
//! gce_InvertRadius: Radius value is incorrect
//! (usually with respect to another radius).
//! gce_NullFocusLength: Focal distance is null.
//! gce_NullVector: Vector is null.
//! gce_BadEquation: Coefficients are
//! incorrect (applies to the equation of a geometric object).
enum gce_ErrorType
{
  gce_Done,
  gce_ConfusedPoints,
  gce_NegativeRadius,
  gce_ColinearPoints,
  gce_IntersectionError,
  gce_NullAxis,
  gce_NullAngle,
  gce_NullRadius,
  gce_InvertAxis,
  gce_BadAngle,
  gce_InvertRadius,
  gce_NullFocusLength,
  gce_NullVector,
  gce_BadEquation
};
