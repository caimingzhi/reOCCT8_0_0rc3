#include <BinMDF_ReferenceDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Reference.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDF_ReferenceDriver, BinMDF_ADriver)

BinMDF_ReferenceDriver::BinMDF_ReferenceDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDF_Reference)->Name())
{
}

occ::handle<TDF_Attribute> BinMDF_ReferenceDriver::NewEmpty() const
{
  return new TDF_Reference();
}

bool BinMDF_ReferenceDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   BinObjMgt_RRelocationTable&) const
{
  occ::handle<TDF_Reference> aRef = occ::down_cast<TDF_Reference>(theTarget);

  TDF_Label tLab;
  if (!theSource.GetLabel(aRef->Label().Data(), tLab))
    return false;

  aRef->Set(tLab);
  return true;
}

void BinMDF_ReferenceDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   BinObjMgt_Persistent&             theTarget,
                                   NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDF_Reference> aRef = occ::down_cast<TDF_Reference>(theSource);
  if (!aRef.IsNull())
  {
    const TDF_Label& lab    = aRef->Label();
    const TDF_Label& refLab = aRef->Get();
    if (!lab.IsNull() && !refLab.IsNull())
    {
      if (lab.IsDescendant(refLab.Root()))
      {
        theTarget << refLab;
      }
    }
  }
}
