#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! This selection gets the Drawings attached to its input IGES
//! entities. They are read through the Single Views, referenced
//! in Directory Parts of the entities
class IGESSelect_SelectDrawingFrom : public IFSelect_SelectDeduct
{

public:
  //! Creates a SelectDrawingFrom
  Standard_EXPORT IGESSelect_SelectDrawingFrom();

  //! Selects the Drawings attached (through Single Views in
  //! Directory Part) to input entities
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns the label, with its "Drawings attached"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectDrawingFrom, IFSelect_SelectDeduct)

protected:
  //! Returns True, because selection works with a ViewSorter which
  //! gives a unique result
  Standard_EXPORT bool HasUniqueResult() const override;
};

