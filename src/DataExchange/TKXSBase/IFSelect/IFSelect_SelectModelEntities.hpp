#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectBase.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectModelEntities gets all the Entities of an
//! InterfaceModel.
class IFSelect_SelectModelEntities : public IFSelect_SelectBase
{

public:
  //! Creates a SelectModelRoot
  Standard_EXPORT IFSelect_SelectModelEntities();

  //! Returns the list of selected entities : the Entities of the
  //! Model (note that this result assures naturally uniqueness)
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! The complete list of Entities (including shared ones) ...
  //! is exactly identical to RootResults in this case
  Standard_EXPORT Interface_EntityIterator CompleteResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Model Entities"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectModelEntities, IFSelect_SelectBase)
};

