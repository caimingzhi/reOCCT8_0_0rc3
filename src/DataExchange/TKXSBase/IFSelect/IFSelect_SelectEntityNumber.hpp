#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectBase.hpp>
class IFSelect_IntParam;
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

//! A SelectEntityNumber gets in an InterfaceModel (through a
//! Graph), the Entity which has a specified Number (its rank of
//! adding into the Model) : there can be zero (if none) or one.
//! The Number is not directly defined as an Integer, but as a
//! Parameter, which can be externally controlled
class IFSelect_SelectEntityNumber : public IFSelect_SelectBase
{

public:
  //! Creates a SelectEntityNumber, initially with no specified Number
  Standard_EXPORT IFSelect_SelectEntityNumber();

  //! Sets Entity Number to be taken (initially, none is set : 0)
  Standard_EXPORT void SetNumber(const occ::handle<IFSelect_IntParam>& num);

  //! Returns specified Number (as a Parameter)
  Standard_EXPORT occ::handle<IFSelect_IntParam> Number() const;

  //! Returns the list of selected entities : the Entity having the
  //! specified Number (this result assures naturally uniqueness)
  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  //! Returns a text defining the criterium : "Entity Number ..."
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectEntityNumber, IFSelect_SelectBase)

private:
  occ::handle<IFSelect_IntParam> thenum;
};
