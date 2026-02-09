

#include <StepAP214.hpp>

#include <Interface_Statics.hpp>
#include <StepAP214_Protocol.hpp>

StaticHandle(StepAP214_Protocol, proto);

occ::handle<StepAP214_Protocol> StepAP214::Protocol()

{
  InitHandleVoid(StepAP214_Protocol, proto);
  return proto;
}
