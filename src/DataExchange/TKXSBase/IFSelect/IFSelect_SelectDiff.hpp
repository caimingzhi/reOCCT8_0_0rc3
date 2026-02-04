#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectControl.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectDiff keeps the entities from a Selection, the Main
//! Input, which are not listed by the Second Input
class IFSelect_SelectDiff : public IFSelect_SelectControl
{

public:
  //! Creates an empty SelectDiff
  Standard_EXPORT IFSelect_SelectDiff();

  //! Returns the list of selected entities : they are the Entities
  //! gotten from the Main Input but not from the Diff Input
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Difference"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectDiff, IFSelect_SelectControl)

protected:
  //! Returns always True, because RootResult gives a Unique list
  Standard_EXPORT bool HasUniqueResult() const override;
};

