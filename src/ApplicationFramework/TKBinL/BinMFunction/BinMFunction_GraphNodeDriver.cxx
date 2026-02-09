#include <BinMDF_ADriver.hpp>
#include <BinMFunction_GraphNodeDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <TDF_Attribute.hpp>
#include <TFunction_GraphNode.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMFunction_GraphNodeDriver, BinMDF_ADriver)

BinMFunction_GraphNodeDriver::BinMFunction_GraphNodeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TFunction_GraphNode)->Name())
{
}

occ::handle<TDF_Attribute> BinMFunction_GraphNodeDriver::NewEmpty() const
{
  return new TFunction_GraphNode();
}

bool BinMFunction_GraphNodeDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         BinObjMgt_RRelocationTable&) const
{
  occ::handle<TFunction_GraphNode> GN = occ::down_cast<TFunction_GraphNode>(theTarget);

  int intStatus, nb_previous, nb_next;
  if (!(theSource >> intStatus >> nb_previous >> nb_next))
    return false;

  GN->SetStatus((TFunction_ExecutionStatus)intStatus);

  if (nb_previous)
  {
    NCollection_Array1<int> aTargetArray(1, nb_previous);
    theSource.GetIntArray(&aTargetArray(1), nb_previous);

    for (int i = 1; i <= nb_previous; i++)
    {
      GN->AddPrevious(aTargetArray.Value(i));
    }
  }

  if (nb_next)
  {
    NCollection_Array1<int> aTargetArray(1, nb_next);
    theSource.GetIntArray(&aTargetArray(1), nb_next);

    for (int i = 1; i <= nb_next; i++)
    {
      GN->AddNext(aTargetArray.Value(i));
    }
  }

  return true;
}

void BinMFunction_GraphNodeDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TFunction_GraphNode> GN = occ::down_cast<TFunction_GraphNode>(theSource);

  theTarget << (int)GN->GetStatus();

  theTarget << GN->GetPrevious().Extent();

  theTarget << GN->GetNext().Extent();

  int nb = GN->GetPrevious().Extent();
  if (nb)
  {
    NCollection_Array1<int>        aSourceArray(1, nb);
    NCollection_Map<int>::Iterator itr(GN->GetPrevious());
    for (int i = 1; itr.More(); itr.Next(), i++)
    {
      aSourceArray.SetValue(i, itr.Key());
    }
    int* aPtr = (int*)&aSourceArray(1);
    theTarget.PutIntArray(aPtr, nb);
  }

  nb = GN->GetNext().Extent();
  if (nb)
  {
    NCollection_Array1<int>        aSourceArray(1, nb);
    NCollection_Map<int>::Iterator itr(GN->GetNext());
    for (int i = 1; itr.More(); itr.Next(), i++)
    {
      aSourceArray.SetValue(i, itr.Key());
    }
    int* aPtr = (int*)&aSourceArray(1);
    theTarget.PutIntArray(aPtr, nb);
  }
}
