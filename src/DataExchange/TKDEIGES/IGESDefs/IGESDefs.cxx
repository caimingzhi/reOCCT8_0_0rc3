

#include <IGESDefs.hpp>

#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESDefs_GeneralModule.hpp>
#include <IGESDefs_Protocol.hpp>
#include <IGESDefs_ReadWriteModule.hpp>
#include <IGESDefs_SpecificModule.hpp>
#include <IGESGraph.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESDefs_Protocol> protocol;

void IGESDefs::Init()
{
  IGESGraph::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESDefs_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESDefs_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESDefs_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESDefs_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESDefs_SpecificModule, protocol);
  }
}

occ::handle<IGESDefs_Protocol> IGESDefs::Protocol()
{
  return protocol;
}
