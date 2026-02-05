#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! This selection gets the Single Views attached to its input
//! IGES entities. Single Views themselves or Drawings as passed
//! as such (Drawings, for their Annotations)
class IGESSelect_SelectSingleViewFrom : public IFSelect_SelectDeduct
{

public:
  //! Creates a SelectSingleViewFrom
  Standard_EXPORT IGESSelect_SelectSingleViewFrom();

  //! Selects the Single Views attached (in Directory Part) to
  //! input entities
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns the label, with is "Single Views attached"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectSingleViewFrom, IFSelect_SelectDeduct)

protected:
  //! Returns True, because selection works with a ViewSorter which
  //! gives a unique result
  Standard_EXPORT bool HasUniqueResult() const override;
};
