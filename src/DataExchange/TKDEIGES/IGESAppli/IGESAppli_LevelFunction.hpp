#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines LevelFunction, Type <406> Form <3>
//! in package IGESAppli
//! Used to transfer the meaning or intended use of a level
//! in the sending system
class IGESAppli_LevelFunction : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_LevelFunction();

  //! This method is used to set the fields of the class
  //! LevelFunction
  //! - nbPropVal    : Number of Properties, always = 2
  //! - aCode        : Function Description code
  //! default = 0
  //! - aFuncDescrip : Function Description
  //! default = null string
  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const int                                    aCode,
                            const occ::handle<TCollection_HAsciiString>& aFuncDescrip);

  //! is always 2
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the function description code. Default = 0
  Standard_EXPORT int FuncDescriptionCode() const;

  //! returns the function description
  //! Default = null string
  Standard_EXPORT occ::handle<TCollection_HAsciiString> FuncDescription() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_LevelFunction, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  int                                   theFuncDescripCode;
  occ::handle<TCollection_HAsciiString> theFuncDescrip;
};

