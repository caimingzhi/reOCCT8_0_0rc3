#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectShared selects Entities which are directly Shared
//! by the Entities of the Input list
class IFSelect_SelectShared : public IFSelect_SelectDeduct
{

public:
  //! Creates a SelectShared;
  Standard_EXPORT IFSelect_SelectShared();

  //! Returns the list of selected entities (list of entities
  //! shared by those of input list)
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Shared (one level)"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectShared, IFSelect_SelectDeduct)
};
