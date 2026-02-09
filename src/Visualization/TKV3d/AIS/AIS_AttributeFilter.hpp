#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Quantity_NameOfColor.hpp>
#include <Standard_Real.hpp>
#include <SelectMgr_Filter.hpp>
class SelectMgr_EntityOwner;

class AIS_AttributeFilter : public SelectMgr_Filter
{
public:
  Standard_EXPORT AIS_AttributeFilter();

  Standard_EXPORT AIS_AttributeFilter(const Quantity_NameOfColor aCol);

  Standard_EXPORT AIS_AttributeFilter(const double aWidth);

  bool HasColor() const { return hasC; }

  bool HasWidth() const { return hasW; }

  void SetColor(const Quantity_NameOfColor theCol)
  {
    myCol = theCol;
    hasC  = true;
  }

  void SetWidth(const double theWidth)
  {
    myWid = theWidth;
    hasW  = true;
  }

  void UnsetColor() { hasC = false; }

  void UnsetWidth() { hasW = false; }

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const override;

  DEFINE_STANDARD_RTTIEXT(AIS_AttributeFilter, SelectMgr_Filter)

private:
  Quantity_NameOfColor myCol;
  double               myWid;
  bool                 hasC;
  bool                 hasW;
};
