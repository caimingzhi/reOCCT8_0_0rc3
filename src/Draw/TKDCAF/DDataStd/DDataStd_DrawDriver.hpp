#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Draw_ColorKind.hpp>
class Draw_Drawable3D;
class TDF_Label;
class TDataXtd_Constraint;
class TopoDS_Shape;

//! Root class of drivers to build draw variables from TDF_Label.
//! Priority rule to display standard attributes is :
//! * 1 Constraint
//! * 2 Object
//! * 3 Datum      (Point,Axis,Plane)
//! * 4 Geometry
//! * 5 NamedShape
class DDataStd_DrawDriver : public Standard_Transient
{

public:
  //! access to the current DrawDriver
  //! ================================
  Standard_EXPORT static void Set(const occ::handle<DDataStd_DrawDriver>& DD);

  Standard_EXPORT static occ::handle<DDataStd_DrawDriver> Get();

  //! next method is called by DrawPresentation (may be redefined)
  //! ============================================================
  Standard_EXPORT DDataStd_DrawDriver();

  //! reusable methods (may used when redefined <Drawable>)
  //! =====================================================
  Standard_EXPORT virtual occ::handle<Draw_Drawable3D> Drawable(const TDF_Label& L) const;

  Standard_EXPORT occ::handle<Draw_Drawable3D> DrawableConstraint(
    const occ::handle<TDataXtd_Constraint>& C) const;

  Standard_EXPORT occ::handle<Draw_Drawable3D> DrawableShape(const TDF_Label&     L,
                                                             const Draw_ColorKind color,
                                                             const bool current = true) const;

  //! May be used for temporary display of a shape
  Standard_EXPORT static occ::handle<Draw_Drawable3D> DrawableShape(const TopoDS_Shape&  s,
                                                                    const Draw_ColorKind color);

  DEFINE_STANDARD_RTTIEXT(DDataStd_DrawDriver, Standard_Transient)
};

