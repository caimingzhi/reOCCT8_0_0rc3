#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bisector_PointOnBis.hpp>
#include <Standard_Boolean.hpp>
class gp_Trsf2d;

//! Polygon of PointOnBis
class Bisector_PolyBis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bisector_PolyBis();

  Standard_EXPORT void Append(const Bisector_PointOnBis& Point);

  Standard_EXPORT int Length() const;

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT const Bisector_PointOnBis& Value(const int Index) const;

  Standard_EXPORT const Bisector_PointOnBis& First() const;

  Standard_EXPORT const Bisector_PointOnBis& Last() const;

  Standard_EXPORT int Interval(const double U) const;

  Standard_EXPORT void Transform(const gp_Trsf2d& T);

private:
  Bisector_PointOnBis thePoints[30];
  int                 nbPoints;
};
