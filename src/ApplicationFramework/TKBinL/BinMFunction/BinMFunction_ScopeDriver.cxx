#include <BinMDF_ADriver.hpp>
#include <BinMFunction_ScopeDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TFunction_Scope.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMFunction_ScopeDriver, BinMDF_ADriver)

BinMFunction_ScopeDriver::BinMFunction_ScopeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TFunction_Scope)->Name())
{
}

occ::handle<TDF_Attribute> BinMFunction_ScopeDriver::NewEmpty() const
{
  return new TFunction_Scope();
}

bool BinMFunction_ScopeDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                     const occ::handle<TDF_Attribute>& theTarget,
                                     BinObjMgt_RRelocationTable&) const
{
  occ::handle<TFunction_Scope> S = occ::down_cast<TFunction_Scope>(theTarget);

  int nb;
  if (!(theSource >> nb))
    return false;
  if (!nb)
    return true;

  NCollection_DoubleMap<int, TDF_Label>& map = S->ChangeFunctions();

  NCollection_Array1<int> IDs(1, nb);
  theSource.GetIntArray(&IDs(1), nb);

  int freeID = 0;
  for (int i = 1; i <= nb; i++)
  {
    TCollection_AsciiString entry;
    if (!(theSource >> entry))
      return false;
    TDF_Label L;
    TDF_Tool::Label(S->Label().Data(), entry, L, true);
    if (!L.IsNull())
    {
      map.Bind(IDs.Value(i), L);
      if (IDs.Value(i) > freeID)
        freeID = IDs.Value(i);
    }
  }

  freeID++;
  S->SetFreeID(freeID);

  return true;
}

void BinMFunction_ScopeDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                     BinObjMgt_Persistent&             theTarget,
                                     NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TFunction_Scope>                 S   = occ::down_cast<TFunction_Scope>(theSource);
  const NCollection_DoubleMap<int, TDF_Label>& map = S->GetFunctions();
  const int                                    nb  = map.Extent();

  theTarget << nb;
  if (!nb)
    return;

  {
    NCollection_Array1<int>                         aSourceArray(1, nb);
    NCollection_DoubleMap<int, TDF_Label>::Iterator itr(map);
    for (int i = 1; itr.More(); itr.Next(), i++)
    {
      aSourceArray.SetValue(i, itr.Key1());
    }
    int* aPtr = (int*)&aSourceArray(1);
    theTarget.PutIntArray(aPtr, nb);
  }

  {
    NCollection_DoubleMap<int, TDF_Label>::Iterator itr(map);
    for (; itr.More(); itr.Next())
    {
      TDF_Label L = itr.Key2();
      if (!L.IsNull())
      {
        TCollection_AsciiString entry;
        TDF_Tool::Entry(L, entry);
        theTarget << entry;
      }
    }
  }
}
