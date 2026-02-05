#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class Geom_Curve;
class gp_Ax2;

//! Describes functions to build revolved shapes.
//! A MakeRevolution object provides a framework for:
//! -   defining the construction of a revolved shape,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class BRepPrimAPI_MakeRevolution : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make a revolution body by rotating a curve around Z.
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian);

  //! Make a revolution body by rotating a curve around Z.
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                             const double                   angle);

  //! Make a revolution body by rotating a curve around Z.
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax);

  //! Make a revolution body by rotating a curve around Z.
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax,
                                             const double                   angle);

  //! Make a revolution body by rotating a curve around Z.
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian);

  //! Make a revolution body by rotating a curve around Z.
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian,
                                             const double                   angle);

  //! Make a revolution body by rotating a curve around Z.
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax);

  //! Make a revolution body by rotating a curve around Z.
  //! For all algorithms the resulting shape is composed of
  //! -   a lateral revolved face,
  //! -   two planar faces in planes parallel to the plane z =
  //! 0, and passing by the extremities of the revolved
  //! portion of Meridian, if these points are not on the Z
  //! axis (in case of a complete revolved shape, these faces are circles),
  //! -   and in the case of a portion of a revolved shape, two
  //! planar faces to close the shape (in the planes u = 0 and u = angle).
  Standard_EXPORT BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                             const occ::handle<Geom_Curve>& Meridian,
                                             const double                   VMin,
                                             const double                   VMax,
                                             const double                   angle);

  //! Returns the algorithm.
  Standard_EXPORT void* OneAxis() override;

  //! Returns the algorithm.
  Standard_EXPORT BRepPrim_Revolution& Revolution();

private:
  BRepPrim_Revolution myRevolution;
};
