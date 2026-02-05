#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_ParamType.hpp>
#include <Standard_PCharacter.hpp>
class TCollection_AsciiString;

//! Auxiliary class to store a literal parameter in a file
//! intermediate directory or in an UndefinedContent : a reference
//! type Parameter detains an Integer which is used to address a
//! record in the directory.
//! FileParameter is intended to be stored in a ParamSet : hence
//! memory management is performed by ParamSet, which calls Clear
//! to work, while the Destructor (see Destroy) does nothing.
//! Also a FileParameter can be read for consultation only, not to
//! be read from a Structure to be included into another one.
class Interface_FileParameter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_FileParameter();

  //! Fills fields (with Entity Number set to zero)
  Standard_EXPORT void Init(const TCollection_AsciiString& val, const Interface_ParamType typ);

  //! Same as above, but builds the Value from a CString
  Standard_EXPORT void Init(const char* val, const Interface_ParamType typ);

  //! Same as above, but as a CString (for immediate exploitation)
  //! was C++ : return const
  Standard_EXPORT const char* CValue() const;

  //! Returns the type of the parameter
  Standard_EXPORT Interface_ParamType ParamType() const;

  //! Allows to set a reference to an Entity in a numbered list
  Standard_EXPORT void SetEntityNumber(const int num);

  //! Returns value set by SetEntityNumber
  Standard_EXPORT int EntityNumber() const;

  //! Clears stored data : frees memory taken for the String Value
  Standard_EXPORT void Clear();

  //! Destructor. Does nothing because Memory is managed by ParamSet
  Standard_EXPORT void Destroy();

  ~Interface_FileParameter() { Destroy(); }

private:
  Interface_ParamType thetype;
  Standard_PCharacter theval;
  int                 thenum;
};
