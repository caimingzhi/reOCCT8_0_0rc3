

#include <IGESDraw.hpp>

#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESDimen.hpp>
#include <IGESDraw_GeneralModule.hpp>
#include <IGESDraw_Protocol.hpp>
#include <IGESDraw_ReadWriteModule.hpp>
#include <IGESDraw_SpecificModule.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESDraw_Protocol> protocol;

void IGESDraw::Init()
{
  IGESDimen::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESDraw_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESDraw_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESDraw_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESDraw_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESDraw_SpecificModule, protocol);
  }
}

occ::handle<IGESDraw_Protocol> IGESDraw::Protocol()
{
  return protocol;
}
