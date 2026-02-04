#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectBase.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectModelRoots gets all the Root Entities of an
//! InterfaceModel. Remember that a "Root Entity" is defined as
//! having no Sharing Entity (if there is a Loop between Entities,
//! none of them can be a "Root").
class IFSelect_SelectModelRoots : public IFSelect_SelectBase
{

public:
  //! Creates a SelectModelRoot
  Standard_EXPORT IFSelect_SelectModelRoots();

  //! Returns the list of selected entities : the Roots of the Model
  //! (note that this result assures naturally uniqueness)
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Model Roots"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectModelRoots, IFSelect_SelectBase)
};

