

#include <IGESAppli.hpp>
#include <IGESAppli_GeneralModule.hpp>
#include <IGESAppli_Protocol.hpp>
#include <IGESAppli_ReadWriteModule.hpp>
#include <IGESAppli_SpecificModule.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESDefs.hpp>
#include <IGESDraw.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESAppli_Protocol> protocol;

void IGESAppli::Init()
{
  IGESDefs::Init();
  IGESDraw::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESAppli_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESAppli_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESAppli_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESAppli_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESAppli_SpecificModule, protocol);
  }
}

occ::handle<IGESAppli_Protocol> IGESAppli::Protocol()
{
  return protocol;
}
