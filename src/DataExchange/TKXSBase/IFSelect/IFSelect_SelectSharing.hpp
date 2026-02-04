#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectSharing selects Entities which directly Share (Level
//! One) the Entities of the Input list
//! Remark : if an Entity of the Input List directly shares
//! another one, it is of course present in the Result List
class IFSelect_SelectSharing : public IFSelect_SelectDeduct
{

public:
  //! Creates a SelectSharing;
  Standard_EXPORT IFSelect_SelectSharing();

  //! Returns the list of selected entities (list of entities
  //! which share (level one) those of input list)
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Sharing (one level)"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectSharing, IFSelect_SelectDeduct)
};

