#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! This selection gets in all the model, the entities which are
//! attached to the views given as input. Only Single Views are
//! considered. This information is kept from Directory Part
//! (View Item).
class IGESSelect_SelectFromSingleView : public IFSelect_SelectDeduct
{

public:
  //! Creates a SelectFromSingleView
  Standard_EXPORT IGESSelect_SelectFromSingleView();

  //! Selects the Entities which are attached to the Single View(s)
  //! present in the Input
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns the label, with is "Entities attached to single View"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectFromSingleView, IFSelect_SelectDeduct)
};

