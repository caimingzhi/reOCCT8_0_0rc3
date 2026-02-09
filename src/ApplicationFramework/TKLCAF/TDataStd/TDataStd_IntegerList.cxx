#include <TDataStd_IntegerList.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_IntegerList, TDF_Attribute)

const Standard_GUID& TDataStd_IntegerList::GetID()
{
  static Standard_GUID TDataStd_IntegerListID("E406AA18-FF3F-483b-9A78-1A5EA5D1AA52");
  return TDataStd_IntegerListID;
}

static occ::handle<TDataStd_IntegerList> SetAttr(const TDF_Label&     label,
                                                 const Standard_GUID& theGuid)
{
  occ::handle<TDataStd_IntegerList> A;
  if (!label.FindAttribute(theGuid, A))
  {
    A = new TDataStd_IntegerList;
    A->SetID(theGuid);
    label.AddAttribute(A);
  }
  return A;
}

TDataStd_IntegerList::TDataStd_IntegerList()
    : myID(GetID())
{
}

occ::handle<TDataStd_IntegerList> TDataStd_IntegerList::Set(const TDF_Label& label)
{
  return SetAttr(label, GetID());
}

occ::handle<TDataStd_IntegerList> TDataStd_IntegerList::Set(const TDF_Label&     label,
                                                            const Standard_GUID& theGuid)
{
  return SetAttr(label, theGuid);
}

bool TDataStd_IntegerList::IsEmpty() const
{
  return myList.IsEmpty();
}

int TDataStd_IntegerList::Extent() const
{
  return myList.Extent();
}

void TDataStd_IntegerList::Prepend(const int value)
{
  Backup();
  myList.Prepend(value);
}

void TDataStd_IntegerList::Append(const int value)
{
  Backup();
  myList.Append(value);
}

bool TDataStd_IntegerList::InsertBefore(const int value, const int before_value)
{
  NCollection_List<int>::Iterator itr(myList);
  for (; itr.More(); itr.Next())
  {
    if (itr.Value() == before_value)
    {
      Backup();
      myList.InsertBefore(value, itr);
      return true;
    }
  }
  return false;
}

bool TDataStd_IntegerList::InsertBeforeByIndex(const int index, const int before_value)
{
  int                             i(1);
  bool                            found(false);
  NCollection_List<int>::Iterator itr(myList);
  for (; itr.More(); itr.Next(), ++i)
  {
    if (i == index)
    {
      Backup();
      myList.InsertBefore(before_value, itr);
      found = true;
      break;
    }
  }
  return found;
}

bool TDataStd_IntegerList::InsertAfter(const int value, const int after_value)
{
  NCollection_List<int>::Iterator itr(myList);
  for (; itr.More(); itr.Next())
  {
    if (itr.Value() == after_value)
    {
      Backup();
      myList.InsertAfter(value, itr);
      return true;
    }
  }
  return false;
}

bool TDataStd_IntegerList::InsertAfterByIndex(const int index, const int after_value)
{
  int                             i(1);
  bool                            found(false);
  NCollection_List<int>::Iterator itr(myList);
  for (; itr.More(); itr.Next(), ++i)
  {
    if (i == index)
    {
      Backup();
      myList.InsertAfter(after_value, itr);
      found = true;
      break;
    }
  }
  return found;
}

bool TDataStd_IntegerList::Remove(const int value)
{
  NCollection_List<int>::Iterator itr(myList);
  for (; itr.More(); itr.Next())
  {
    if (itr.Value() == value)
    {
      Backup();
      myList.Remove(itr);
      return true;
    }
  }
  return false;
}

bool TDataStd_IntegerList::RemoveByIndex(const int index)
{
  int                             i(1);
  bool                            found(false);
  NCollection_List<int>::Iterator itr(myList);
  for (; itr.More(); itr.Next(), ++i)
  {
    if (i == index)
    {
      Backup();
      myList.Remove(itr);
      found = true;
      break;
    }
  }
  return found;
}

void TDataStd_IntegerList::Clear()
{
  Backup();
  myList.Clear();
}

int TDataStd_IntegerList::First() const
{
  return myList.First();
}

int TDataStd_IntegerList::Last() const
{
  return myList.Last();
}

const NCollection_List<int>& TDataStd_IntegerList::List() const
{
  return myList;
}

const Standard_GUID& TDataStd_IntegerList::ID() const
{
  return myID;
}

void TDataStd_IntegerList::SetID(const Standard_GUID& theGuid)
{
  if (myID == theGuid)
    return;
  Backup();
  myID = theGuid;
}

void TDataStd_IntegerList::SetID()
{
  Backup();
  myID = GetID();
}

occ::handle<TDF_Attribute> TDataStd_IntegerList::NewEmpty() const
{
  return new TDataStd_IntegerList();
}

void TDataStd_IntegerList::Restore(const occ::handle<TDF_Attribute>& With)
{
  myList.Clear();
  occ::handle<TDataStd_IntegerList> aList = occ::down_cast<TDataStd_IntegerList>(With);
  NCollection_List<int>::Iterator   itr(aList->List());
  for (; itr.More(); itr.Next())
  {
    myList.Append(itr.Value());
  }
  myID = aList->ID();
}

void TDataStd_IntegerList::Paste(const occ::handle<TDF_Attribute>& Into,
                                 const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TDataStd_IntegerList> aList = occ::down_cast<TDataStd_IntegerList>(Into);
  aList->Clear();
  NCollection_List<int>::Iterator itr(myList);
  for (; itr.More(); itr.Next())
  {
    aList->Append(itr.Value());
  }
  aList->SetID(myID);
}

Standard_OStream& TDataStd_IntegerList::Dump(Standard_OStream& anOS) const
{
  anOS << "\nIntegerList: ";
  char sguid[Standard_GUID_SIZE_ALLOC];
  myID.ToCString(sguid);
  anOS << sguid;
  anOS << std::endl;
  return anOS;
}

void TDataStd_IntegerList::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  for (NCollection_List<int>::Iterator aListIt(myList); aListIt.More(); aListIt.Next())
  {
    const int& aValue = aListIt.Value();
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, aValue)
  }
}
