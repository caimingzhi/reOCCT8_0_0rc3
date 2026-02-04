#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Wedge.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class gp_Ax2;
class TopoDS_Shell;
class TopoDS_Solid;

//! Describes functions to build wedges, i.e. boxes with inclined faces.
//! A MakeWedge object provides a framework for:
//! -   defining the construction of a wedge,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class BRepPrimAPI_MakeWedge : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Make a STEP right angular wedge. (ltx >= 0)
  Standard_EXPORT BRepPrimAPI_MakeWedge(const double dx,
                                        const double dy,
                                        const double dz,
                                        const double ltx);

  //! Make a STEP right angular wedge. (ltx >= 0)
  Standard_EXPORT BRepPrimAPI_MakeWedge(const gp_Ax2& Axes,
                                        const double  dx,
                                        const double  dy,
                                        const double  dz,
                                        const double  ltx);

  //! Make a wedge. The face at dy is xmin,zmin xmax,zmax
  Standard_EXPORT BRepPrimAPI_MakeWedge(const double dx,
                                        const double dy,
                                        const double dz,
                                        const double xmin,
                                        const double zmin,
                                        const double xmax,
                                        const double zmax);

  //! Make a wedge. The face at dy is xmin,zmin xmax,zmax
  Standard_EXPORT BRepPrimAPI_MakeWedge(const gp_Ax2& Axes,
                                        const double  dx,
                                        const double  dy,
                                        const double  dz,
                                        const double  xmin,
                                        const double  zmin,
                                        const double  xmax,
                                        const double  zmax);

  //! Returns the internal algorithm.
  Standard_EXPORT BRepPrim_Wedge& Wedge();

  //! Stores the solid in myShape.
  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  //! Returns the constructed box in the form of a shell.
  Standard_EXPORT const TopoDS_Shell& Shell();
  Standard_EXPORT                     operator TopoDS_Shell();

  //! Returns the constructed box in the form of a solid.
  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();

private:
  BRepPrim_Wedge myWedge;
};

