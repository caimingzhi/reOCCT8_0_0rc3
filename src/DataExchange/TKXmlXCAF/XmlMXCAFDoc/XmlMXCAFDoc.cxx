#include <XmlMXCAFDoc.hpp>

#include <Message_Messenger.hpp>
#include <TNaming_NamedShape.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMNaming_NamedShapeDriver.hpp>
#include <XmlMXCAFDoc_AssemblyItemRefDriver.hpp>
#include <XmlMXCAFDoc_CentroidDriver.hpp>
#include <XmlMXCAFDoc_ColorDriver.hpp>
#include <XmlMXCAFDoc_DatumDriver.hpp>
#include <XmlMXCAFDoc_DimTolDriver.hpp>
#include <XmlMXCAFDoc_GraphNodeDriver.hpp>
#include <XmlMXCAFDoc_LengthUnitDriver.hpp>
#include <XmlMXCAFDoc_LocationDriver.hpp>
#include <XmlMXCAFDoc_MaterialDriver.hpp>
#include <XmlMXCAFDoc_VisMaterialDriver.hpp>
#include <XmlMXCAFDoc_NoteCommentDriver.hpp>
#include <XmlMXCAFDoc_NoteBinDataDriver.hpp>
#include <XmlMXCAFDoc_VisMaterialToolDriver.hpp>

//=================================================================================================

void XmlMXCAFDoc::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                             const occ::handle<Message_Messenger>&   anMsgDrv)
{
  aDriverTable->AddDriver(new XmlMXCAFDoc_CentroidDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_ColorDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_GraphNodeDriver(anMsgDrv));

  // oan: changes for sharing locations map
  occ::handle<XmlMDF_ADriver> aDriver;
  aDriverTable->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<XmlMNaming_NamedShapeDriver> aNamedShapeDriver =
    occ::down_cast<XmlMNaming_NamedShapeDriver>(aDriver);

  occ::handle<XmlMXCAFDoc_LocationDriver> aLocationDriver =
    new XmlMXCAFDoc_LocationDriver(anMsgDrv);
  if (!aNamedShapeDriver.IsNull())
  {
    aLocationDriver->SetSharedLocations(&(aNamedShapeDriver->GetShapesLocations()));
  }

  aDriverTable->AddDriver(aLocationDriver);
  aDriverTable->AddDriver(new XmlMXCAFDoc_LengthUnitDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_AssemblyItemRefDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_DatumDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_DimTolDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_MaterialDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_VisMaterialDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_NoteCommentDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_NoteBinDataDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlMXCAFDoc_VisMaterialToolDriver(anMsgDrv));
}
