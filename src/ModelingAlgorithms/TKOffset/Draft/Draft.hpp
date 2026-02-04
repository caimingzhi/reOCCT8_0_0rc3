#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class TopoDS_Face;
class gp_Dir;

class Draft
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the draft angle of the face <F> using the
  //! direction <Direction>. The method is valid for :
  //! - Plane faces,
  //! - Cylindrical or conical faces, when the direction
  //! of the axis of the surface is colinear with the
  //! direction.
  //! Otherwise, the exception DomainError is raised.
  Standard_EXPORT static double Angle(const TopoDS_Face& F, const gp_Dir& Direction);
};

