

#include <RWHeaderSection.hpp>

#include <HeaderSection.hpp>
#include <HeaderSection_Protocol.hpp>
#include <RWHeaderSection_GeneralModule.hpp>
#include <RWHeaderSection_ReadWriteModule.hpp>
#include <StepData.hpp>

static occ::handle<RWHeaderSection_ReadWriteModule> rwm;
static occ::handle<RWHeaderSection_GeneralModule>   rwg;

void RWHeaderSection::Init()
{

  occ::handle<HeaderSection_Protocol> proto = HeaderSection::Protocol();
  StepData::AddHeaderProtocol(proto);
  if (rwm.IsNull())
    rwm = new RWHeaderSection_ReadWriteModule;
  if (rwg.IsNull())
    rwg = new RWHeaderSection_GeneralModule;
}
