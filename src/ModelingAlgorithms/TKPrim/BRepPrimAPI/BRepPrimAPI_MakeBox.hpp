#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepPrim_Wedge.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class gp_Pnt;
class gp_Ax2;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_Face;

//! Describes functions to build parallelepiped boxes.
//! A MakeBox object provides a framework for:
//! -   defining the construction of a box,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
//! Constructs a box such that its sides are parallel to the axes of
//! -   the global coordinate system, or
//! -   the local coordinate system Axis. and
//! -   with a corner at (0, 0, 0) and of size (dx, dy, dz), or
//! -   with a corner at point P and of size (dx, dy, dz), or
//! -   with corners at points P1 and P2.
//! Exceptions
//! Standard_DomainError if: dx, dy, dz are less than or equal to
//! Precision::Confusion(), or
//! -   the vector joining the points P1 and P2 has a
//! component projected onto the global coordinate
//! system less than or equal to Precision::Confusion().
//! In these cases, the box would be flat.

class BRepPrimAPI_MakeBox : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Default constructor
  BRepPrimAPI_MakeBox() = default;

  //! Make a box with a corner at 0,0,0 and the other dx,dy,dz
  Standard_EXPORT BRepPrimAPI_MakeBox(const double dx, const double dy, const double dz);

  //! Make a box with a corner at P and size dx, dy, dz.
  Standard_EXPORT BRepPrimAPI_MakeBox(const gp_Pnt& P,
                                      const double  dx,
                                      const double  dy,
                                      const double  dz);

  //! Make a box with corners P1,P2.
  Standard_EXPORT BRepPrimAPI_MakeBox(const gp_Pnt& P1, const gp_Pnt& P2);

  //! Make a box with Ax2 (the left corner and the axis) and size dx, dy, dz.
  Standard_EXPORT BRepPrimAPI_MakeBox(const gp_Ax2& Axes,
                                      const double  dx,
                                      const double  dy,
                                      const double  dz);

  //! Init a box with a corner at 0,0,0 and the other theDX, theDY, theDZ
  Standard_EXPORT void Init(const double theDX, const double theDY, const double theDZ);

  //! Init a box with a corner at thePnt and size theDX, theDY, theDZ.
  Standard_EXPORT void Init(const gp_Pnt& thePnt,
                            const double  theDX,
                            const double  theDY,
                            const double  theDZ);

  //! Init a box with corners thePnt1, thePnt2.
  Standard_EXPORT void Init(const gp_Pnt& thePnt1, const gp_Pnt& thePnt2);

  //! Init a box with Ax2 (the left corner and the theAxes) and size theDX, theDY, theDZ.
  Standard_EXPORT void Init(const gp_Ax2& theAxes,
                            const double  theDX,
                            const double  theDY,
                            const double  theDZ);

  //! Returns the internal algorithm.
  Standard_EXPORT BRepPrim_Wedge& Wedge();

  //! Stores the solid in myShape.
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  //! Returns the constructed box as a shell.
  Standard_EXPORT const TopoDS_Shell& Shell();
  Standard_EXPORT                     operator TopoDS_Shell();

  //! Returns the constructed box as a solid.
  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();

  //! Returns ZMin face
  Standard_EXPORT const TopoDS_Face& BottomFace();

  //! Returns XMin face
  Standard_EXPORT const TopoDS_Face& BackFace();

  //! Returns XMax face
  Standard_EXPORT const TopoDS_Face& FrontFace();

  //! Returns YMin face
  Standard_EXPORT const TopoDS_Face& LeftFace();

  //! Returns YMax face
  Standard_EXPORT const TopoDS_Face& RightFace();

  //! Returns ZMax face
  Standard_EXPORT const TopoDS_Face& TopFace();

protected:
  BRepPrim_Wedge myWedge;
};

