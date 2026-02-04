#pragma once


#include <Standard_Type.hpp>

//! Base class of the hierarchy of classes describing various situations
//! occurring during execution of some algorithm or procedure.
//!
//! Alert should provide unique text identifier that can be used to distinguish
//! particular type of alerts, e.g. to get text message string describing it.
//! See method GetMessageKey(); by default, dynamic type name is used.
//!
//! Alert can contain some data. To avoid duplication of data, new alert
//! can be merged with another one of the same type. Method SupportsMerge()
//! should return true if merge is supported; method Merge() should do the
//! merge if possible and return true in that case and false otherwise.
class Message_Alert : public Standard_Transient
{
public:
  //! Return a C string to be used as a key for generating text user
  //! messages describing this alert.
  //! The messages are generated with help of Message_Msg class, in
  //! Message_Report::Dump().
  //! Base implementation returns dynamic type name of the instance.
  virtual Standard_EXPORT const char* GetMessageKey() const;

  //! Return true if this type of alert can be merged with other
  //! of the same type to avoid duplication.
  //! Basis implementation returns true.
  virtual Standard_EXPORT bool SupportsMerge() const;

  //! If possible, merge data contained in this alert to theTarget.
  //! @return True if merged.
  //! Base implementation always returns true.
  virtual Standard_EXPORT bool Merge(const occ::handle<Message_Alert>& theTarget);

  //! Dumps the content of me into the stream
  virtual Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  // OCCT RTTI
  DEFINE_STANDARD_RTTIEXT(Message_Alert, Standard_Transient)
};

//! Macro allowing to define simple alert (without data) in single line of code
#define DEFINE_SIMPLE_ALERT(Alert)                                                                 \
  class Alert : public Message_Alert                                                               \
  {                                                                                                \
    DEFINE_STANDARD_RTTI_INLINE(Alert, Message_Alert)                                              \
  };

