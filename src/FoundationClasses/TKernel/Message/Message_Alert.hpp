#pragma once

#include <Standard_Type.hpp>

namespace System { namespace log {
class Message_Alert : public Standard_Transient
{
public:
  virtual Standard_EXPORT const char* GetMessageKey() const;

  virtual Standard_EXPORT bool SupportsMerge() const;

  virtual Standard_EXPORT bool Merge(const occ::handle<Message_Alert>& theTarget);

  virtual Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(Message_Alert, Standard_Transient)
};
}} // namespace System::log


#define DEFINE_SIMPLE_ALERT(Alert)                                                                 \
  class Alert : public System::log::Message_Alert                                                               \
  {                                                                                                \
    DEFINE_STANDARD_RTTI_INLINE(Alert, System::log::Message_Alert)                                              \
  };
