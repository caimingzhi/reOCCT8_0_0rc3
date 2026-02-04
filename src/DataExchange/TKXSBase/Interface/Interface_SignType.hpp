#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <MoniTool_SignText.hpp>
class TCollection_AsciiString;
class Standard_Transient;
class Interface_InterfaceModel;

//! Provides the basic service to get a type name, according
//! to a norm
//! It can be used for other classes (general signatures ...)
class Interface_SignType : public MoniTool_SignText
{

public:
  //! Returns an identification of the Signature (a word), given at
  //! initialization time
  //! Specialised to consider context as an InterfaceModel
  Standard_EXPORT TCollection_AsciiString
    Text(const occ::handle<Standard_Transient>& ent,
         const occ::handle<Standard_Transient>& context) const override;

  //! Returns the Signature for a Transient object. It is specific
  //! of each sub-class of Signature. For a Null Handle, it should
  //! provide ""
  //! It can work with the model which contains the entity
  Standard_EXPORT virtual const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const = 0;

  //! From a CDL Type Name, returns the Class part (package dropped)
  //! WARNING : buffered, to be immediately copied or printed
  Standard_EXPORT static const char* ClassName(const char* typnam);

  DEFINE_STANDARD_RTTIEXT(Interface_SignType, MoniTool_SignText)
};

