

#include <IGESGeom.hpp>

#include <IGESBasic.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESGeom_GeneralModule.hpp>
#include <IGESGeom_Protocol.hpp>
#include <IGESGeom_ReadWriteModule.hpp>
#include <IGESGeom_SpecificModule.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESGeom_Protocol> protocol;

void IGESGeom::Init()
{
  IGESBasic::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESGeom_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESGeom_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESGeom_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESGeom_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESGeom_SpecificModule, protocol);
  }
}

occ::handle<IGESGeom_Protocol> IGESGeom::Protocol()
{
  return protocol;
}
