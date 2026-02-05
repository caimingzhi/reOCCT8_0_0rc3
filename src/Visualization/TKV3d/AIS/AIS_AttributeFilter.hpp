#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Quantity_NameOfColor.hpp>
#include <Standard_Real.hpp>
#include <SelectMgr_Filter.hpp>
class SelectMgr_EntityOwner;

//! Selects Interactive Objects, which have the desired width or color.
//! The filter questions each Interactive Object in local
//! context to determine whether it has an non-null
//! owner, and if so, whether it has the required color
//! and width attributes. If the object returns true in each
//! case, it is kept. If not, it is rejected.
//! This filter is used only in an open local context.
//! In the Collector viewer, you can only locate
//! Interactive Objects, which answer positively to the
//! filters, which are in position when a local context is open.
class AIS_AttributeFilter : public SelectMgr_Filter
{
public:
  //! Constructs an empty attribute filter object.
  //! This filter object determines whether selectable
  //! interactive objects have a non-null owner.
  Standard_EXPORT AIS_AttributeFilter();

  //! Constructs an attribute filter object defined by the
  //! color attribute aCol.
  Standard_EXPORT AIS_AttributeFilter(const Quantity_NameOfColor aCol);

  //! Constructs an attribute filter object defined by the line
  //! width attribute aWidth.
  Standard_EXPORT AIS_AttributeFilter(const double aWidth);

  //! Indicates that the Interactive Object has the color
  //! setting specified by the argument aCol at construction time.
  bool HasColor() const { return hasC; }

  //! Indicates that the Interactive Object has the width
  //! setting specified by the argument aWidth at
  //! construction time.
  bool HasWidth() const { return hasW; }

  //! Sets the color.
  void SetColor(const Quantity_NameOfColor theCol)
  {
    myCol = theCol;
    hasC  = true;
  }

  //! Sets the line width.
  void SetWidth(const double theWidth)
  {
    myWid = theWidth;
    hasW  = true;
  }

  //! Removes the setting for color from the filter.
  void UnsetColor() { hasC = false; }

  //! Removes the setting for width from the filter.
  void UnsetWidth() { hasW = false; }

  //! Indicates that the selected Interactive Object passes
  //! the filter. The owner, anObj, can be either direct or
  //! user. A direct owner is the corresponding
  //! construction element, whereas a user is the
  //! compound shape of which the entity forms a part.
  //! If the Interactive Object returns true
  //! when detected by the Local Context selector through
  //! the mouse, the object is kept; if not, it is rejected.
  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const override;

  DEFINE_STANDARD_RTTIEXT(AIS_AttributeFilter, SelectMgr_Filter)

private:
  Quantity_NameOfColor myCol;
  double               myWid;
  bool                 hasC;
  bool                 hasW;
};
