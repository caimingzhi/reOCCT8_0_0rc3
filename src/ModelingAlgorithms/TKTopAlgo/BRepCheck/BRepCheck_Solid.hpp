#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepCheck_Result.hpp>
class TopoDS_Solid;
class TopoDS_Shape;

//! The class is to check a solid.
class BRepCheck_Solid : public BRepCheck_Result
{

public:
  //! Constructor
  //! <theS> is the solid to check
  Standard_EXPORT BRepCheck_Solid(const TopoDS_Solid& theS);

  //! Checks the solid in context of
  //! the shape <theContextShape>
  Standard_EXPORT void InContext(const TopoDS_Shape& theContextShape) override;

  //! Checks the solid per se.
  //!
  //! The scan area is:
  //! 1.  Shells that overlaps each other
  //! Status:  BRepCheck_InvalidImbricationOfShells
  //!
  //! 2.  Detached parts of the solid (vertices, edges)
  //! that have non-internal orientation
  //! Status:  BRepCheck_BadOrientationOfSubshape
  //!
  //! 3.  For closed, non-internal shells:
  //! 3.1 Shells containing entities of the solid that
  //! are outside towards the shells
  //! Status:  BRepCheck_SubshapeNotInShape
  //!
  //! 3.2 Shells that encloses other Shells
  //! (for non-holes)
  //! Status:  BRepCheck_EnclosedRegion
  Standard_EXPORT void Minimum() override;

  //! see the parent class for more details
  Standard_EXPORT void Blind() override;

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Solid, BRepCheck_Result)
};

