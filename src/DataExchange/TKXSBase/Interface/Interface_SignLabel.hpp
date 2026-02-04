#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <MoniTool_SignText.hpp>
class TCollection_AsciiString;
class Standard_Transient;

//! Signature to give the Label from the Model
class Interface_SignLabel : public MoniTool_SignText
{

public:
  Standard_EXPORT Interface_SignLabel();

  //! Returns "Entity Label"
  Standard_EXPORT const char* Name() const override;

  //! Considers context as an InterfaceModel and returns the Label
  //! computed by it
  Standard_EXPORT TCollection_AsciiString
    Text(const occ::handle<Standard_Transient>& ent,
         const occ::handle<Standard_Transient>& context) const override;

  DEFINE_STANDARD_RTTIEXT(Interface_SignLabel, MoniTool_SignText)
};

