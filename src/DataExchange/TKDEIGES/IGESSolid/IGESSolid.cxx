

#include <IGESSolid.hpp>

#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESGeom.hpp>
#include <IGESSolid_GeneralModule.hpp>
#include <IGESSolid_Protocol.hpp>
#include <IGESSolid_ReadWriteModule.hpp>
#include <IGESSolid_SpecificModule.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESSolid_Protocol> protocol;

void IGESSolid::Init()
{
  IGESGeom::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESSolid_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESSolid_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESSolid_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESSolid_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESSolid_SpecificModule, protocol);
  }
}

occ::handle<IGESSolid_Protocol> IGESSolid::Protocol()
{
  return protocol;
}
