#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Selection.hpp>
class IFSelect_SelectionIterator;

class IFSelect_SelectControl : public IFSelect_Selection
{

public:
  Standard_EXPORT occ::handle<IFSelect_Selection> MainInput() const;

  Standard_EXPORT bool HasSecondInput() const;

  Standard_EXPORT occ::handle<IFSelect_Selection> SecondInput() const;

  Standard_EXPORT void SetMainInput(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT void SetSecondInput(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT void FillIterator(IFSelect_SelectionIterator& iter) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectControl, IFSelect_Selection)

private:
  occ::handle<IFSelect_Selection> themain;
  occ::handle<IFSelect_Selection> thesecond;
};
