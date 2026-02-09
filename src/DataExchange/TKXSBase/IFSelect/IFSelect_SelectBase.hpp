#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Selection.hpp>
class IFSelect_SelectionIterator;

class IFSelect_SelectBase : public IFSelect_Selection
{

public:
  Standard_EXPORT void FillIterator(IFSelect_SelectionIterator& iter) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectBase, IFSelect_Selection)
};
