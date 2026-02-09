

#include "RWStepAP214.hpp"

#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>
#include <RWHeaderSection.hpp>
#include "RWStepAP214_GeneralModule.hpp"
#include "RWStepAP214_ReadWriteModule.hpp"
#include <StepAP214.hpp>
#include <StepAP214_Protocol.hpp>
#include <StepData_WriterLib.hpp>

static int THE_RWStepAP214_init = 0;

void RWStepAP214::Init()
{
  if (THE_RWStepAP214_init)
  {
    return;
  }
  THE_RWStepAP214_init = 1;
  RWHeaderSection::Init();
  occ::handle<StepAP214_Protocol> proto = StepAP214::Protocol();
  Interface_GeneralLib::SetGlobal(new RWStepAP214_GeneralModule, proto);
  Interface_ReaderLib::SetGlobal(new RWStepAP214_ReadWriteModule, proto);
  StepData_WriterLib::SetGlobal(new RWStepAP214_ReadWriteModule, proto);
}
