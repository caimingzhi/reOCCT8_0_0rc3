#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_GWedge.hpp>
class gp_Ax2;

//! Provides constructors without Builders.
class BRepPrim_Wedge : public BRepPrim_GWedge
{
public:
  DEFINE_STANDARD_ALLOC

  //! Default constructor
  BRepPrim_Wedge() = default;

  //! Creates a Wedge algorithm. <Axes> is the axis
  //! system for the primitive.
  //!
  //! XMin, YMin, ZMin are set to 0
  //! XMax, YMax, ZMax are set to dx, dy, dz
  //! Z2Min = ZMin
  //! Z2Max = ZMax
  //! X2Min = XMin
  //! X2Max = XMax
  //! The result is a box
  //! dx,dy,dz should be positive
  Standard_EXPORT BRepPrim_Wedge(const gp_Ax2& Axes,
                                 const double  dx,
                                 const double  dy,
                                 const double  dz);

  //! Creates a Wedge primitive. <Axes> is the axis
  //! system for the primitive.
  //!
  //! XMin, YMin, ZMin are set to 0
  //! XMax, YMax, ZMax are set to dx, dy, dz
  //! Z2Min = ZMin
  //! Z2Max = ZMax
  //! X2Min = ltx
  //! X2Max = ltx
  //! The result is a STEP right angular wedge
  //! dx,dy,dz should be positive
  //! ltx should not be negative
  Standard_EXPORT BRepPrim_Wedge(const gp_Ax2& Axes,
                                 const double  dx,
                                 const double  dy,
                                 const double  dz,
                                 const double  ltx);

  //! Create a Wedge primitive. <Axes> is the axis
  //! system for the primitive.
  //!
  //! all the fields are set to the corresponding value
  //! XYZMax - XYZMin should be positive
  //! ZX2Max - ZX2Min should not be negative
  Standard_EXPORT BRepPrim_Wedge(const gp_Ax2& Axes,
                                 const double  xmin,
                                 const double  ymin,
                                 const double  zmin,
                                 const double  z2min,
                                 const double  x2min,
                                 const double  xmax,
                                 const double  ymax,
                                 const double  zmax,
                                 const double  z2max,
                                 const double  x2max);
};

