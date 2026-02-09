

#include <HeaderSection.hpp>
#include <HeaderSection_Protocol.hpp>
#include <Interface_Statics.hpp>

StaticHandle(HeaderSection_Protocol, proto);

occ::handle<HeaderSection_Protocol> HeaderSection::Protocol()

{
  InitHandleVoid(HeaderSection_Protocol, proto);
  return proto;
}
