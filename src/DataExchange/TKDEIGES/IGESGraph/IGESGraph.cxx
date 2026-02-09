

#include <IGESGraph.hpp>

#include <IGESBasic.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESGraph_GeneralModule.hpp>
#include <IGESGraph_Protocol.hpp>
#include <IGESGraph_ReadWriteModule.hpp>
#include <IGESGraph_SpecificModule.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>

static occ::handle<IGESGraph_Protocol> protocol;

void IGESGraph::Init()
{
  IGESBasic::Init();
  if (protocol.IsNull())
  {
    protocol = new IGESGraph_Protocol;
    Interface_GeneralLib::SetGlobal(new IGESGraph_GeneralModule, protocol);
    Interface_ReaderLib::SetGlobal(new IGESGraph_ReadWriteModule, protocol);
    IGESData_WriterLib::SetGlobal(new IGESGraph_ReadWriteModule, protocol);
    IGESData_SpecificLib::SetGlobal(new IGESGraph_SpecificModule, protocol);
  }
}

occ::handle<IGESGraph_Protocol> IGESGraph::Protocol()
{
  return protocol;
}
