#include <BinMXCAFDoc.hpp>

#include <BinMDF_ADriverTable.hpp>
#include <BinMXCAFDoc_AssemblyItemRefDriver.hpp>
#include <BinMXCAFDoc_CentroidDriver.hpp>
#include <BinMXCAFDoc_ColorDriver.hpp>
#include <BinMXCAFDoc_DatumDriver.hpp>
#include <BinMXCAFDoc_DimTolDriver.hpp>
#include <BinMXCAFDoc_GraphNodeDriver.hpp>
#include <BinMXCAFDoc_LengthUnitDriver.hpp>
#include <BinMXCAFDoc_LocationDriver.hpp>
#include <BinMXCAFDoc_MaterialDriver.hpp>
#include <BinMXCAFDoc_NoteBinDataDriver.hpp>
#include <BinMXCAFDoc_NoteCommentDriver.hpp>
#include <BinMXCAFDoc_VisMaterialDriver.hpp>
#include <BinMXCAFDoc_VisMaterialToolDriver.hpp>
#include <Message_Messenger.hpp>
#include <TNaming_NamedShape.hpp>

void BinMXCAFDoc::AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                             const occ::handle<Message_Messenger>&   theMsgDrv)
{
  theDriverTable->AddDriver(new BinMXCAFDoc_CentroidDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_ColorDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_GraphNodeDriver(theMsgDrv));

  occ::handle<BinMDF_ADriver> aNSDriver;
  theDriverTable->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aNSDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aNamedShapeDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aNSDriver);

  occ::handle<BinMXCAFDoc_LocationDriver> aLocationDriver =
    new BinMXCAFDoc_LocationDriver(theMsgDrv);
  if (!aNamedShapeDriver.IsNull())
  {
    aLocationDriver->SetNSDriver(aNamedShapeDriver);
  }

  theDriverTable->AddDriver(aLocationDriver);
  theDriverTable->AddDriver(new BinMXCAFDoc_LengthUnitDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_AssemblyItemRefDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_DatumDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_DimTolDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_MaterialDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_VisMaterialDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_NoteBinDataDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_NoteCommentDriver(theMsgDrv));
  theDriverTable->AddDriver(new BinMXCAFDoc_VisMaterialToolDriver(theMsgDrv));
}
