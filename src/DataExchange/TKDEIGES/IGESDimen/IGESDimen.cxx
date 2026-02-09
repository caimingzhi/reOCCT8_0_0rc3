

#include <IGESDimen.hpp>

#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESDimen_GeneralModule.hpp>
#include <IGESDimen_Protocol.hpp>
#include <IGESDimen_ReadWriteModule.hpp>
#include <IGESDimen_SpecificModule.hpp>
#include <IGESGeom.hpp>
#include <IGESGraph.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESDimen_Protocol> protocol;

void IGESDimen::Init()
{
  IGESGeom::Init();
  IGESGraph::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESDimen_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESDimen_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESDimen_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESDimen_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESDimen_SpecificModule, protocol);
  }
}

occ::handle<IGESDimen_Protocol> IGESDimen::Protocol()
{
  return protocol;
}
