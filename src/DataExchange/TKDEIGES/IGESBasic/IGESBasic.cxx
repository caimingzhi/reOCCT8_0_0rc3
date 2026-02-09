

#include <IGESBasic.hpp>
#include <IGESBasic_GeneralModule.hpp>
#include <IGESBasic_Protocol.hpp>
#include <IGESBasic_ReadWriteModule.hpp>
#include <IGESBasic_SpecificModule.hpp>
#include <IGESData.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESBasic_Protocol> protocol;

void IGESBasic::Init()
{
  IGESData::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESBasic_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESBasic_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESBasic_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESBasic_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESBasic_SpecificModule, protocol);
  }
}

occ::handle<IGESBasic_Protocol> IGESBasic::Protocol()
{
  return protocol;
}
