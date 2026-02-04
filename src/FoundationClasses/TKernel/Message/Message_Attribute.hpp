#pragma once


#include <Standard_Transient.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <TCollection_AsciiString.hpp>

//! Additional information of extended alert attribute
//! To provide other custom attribute container, it might be redefined.
class Message_Attribute : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Message_Attribute, Standard_Transient)
public:
  //! Empty constructor
  Standard_EXPORT Message_Attribute(
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  //! Return a C string to be used as a key for generating text user messages describing this alert.
  //! The messages are generated with help of Message_Msg class, in Message_Report::Dump().
  //! Base implementation returns dynamic type name of the instance.
  Standard_EXPORT virtual const char* GetMessageKey() const;

  //! Returns custom name of alert if it is set
  //! @return alert name
  const TCollection_AsciiString& GetName() const { return myName; }

  //! Sets the custom name of alert
  //! @param theName a name for the alert
  void SetName(const TCollection_AsciiString& theName) { myName = theName; }

  //! Dumps the content of me into the stream
  virtual Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  TCollection_AsciiString myName; //!< alert name, if defined is used in GetMessageKey
};

