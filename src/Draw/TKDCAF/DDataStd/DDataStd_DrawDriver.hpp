#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Draw_ColorKind.hpp>
class Draw_Drawable3D;
class TDF_Label;
class TDataXtd_Constraint;
class TopoDS_Shape;

class DDataStd_DrawDriver : public Standard_Transient
{

public:
  Standard_EXPORT static void Set(const occ::handle<DDataStd_DrawDriver>& DD);

  Standard_EXPORT static occ::handle<DDataStd_DrawDriver> Get();

  Standard_EXPORT DDataStd_DrawDriver();

  Standard_EXPORT virtual occ::handle<Draw_Drawable3D> Drawable(const TDF_Label& L) const;

  Standard_EXPORT occ::handle<Draw_Drawable3D> DrawableConstraint(
    const occ::handle<TDataXtd_Constraint>& C) const;

  Standard_EXPORT occ::handle<Draw_Drawable3D> DrawableShape(const TDF_Label&     L,
                                                             const Draw_ColorKind color,
                                                             const bool current = true) const;

  Standard_EXPORT static occ::handle<Draw_Drawable3D> DrawableShape(const TopoDS_Shape&  s,
                                                                    const Draw_ColorKind color);

  DEFINE_STANDARD_RTTIEXT(DDataStd_DrawDriver, Standard_Transient)
};
