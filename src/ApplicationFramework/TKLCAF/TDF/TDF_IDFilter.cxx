#include <TDF_IDFilter.hpp>
#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>

#define TDF_IDFilterMapSize 23

TDF_IDFilter::TDF_IDFilter(const bool ignoreMode)
    : myIgnore(ignoreMode)
{
}

void TDF_IDFilter::IgnoreAll(const bool ignore)
{
  myIgnore = ignore;
  myIDMap.Clear();
  myIDMap.ReSize(TDF_IDFilterMapSize);
}

void TDF_IDFilter::Keep(const Standard_GUID& anID)
{
  if (myIgnore)
    myIDMap.Add(anID);
  else
    myIDMap.Remove(anID);
}

void TDF_IDFilter::Keep(const NCollection_List<Standard_GUID>& anIDList)
{
  if (!anIDList.IsEmpty())
  {
    NCollection_List<Standard_GUID>::Iterator itr(anIDList);
    if (myIgnore)
    {
      int n = anIDList.Extent() + myIDMap.NbBuckets() + 1;
      myIDMap.ReSize(n);
      for (; itr.More(); itr.Next())
        myIDMap.Add(itr.Value());
    }
    else
    {
      for (; itr.More(); itr.Next())
        myIDMap.Remove(itr.Value());
    }
  }
}

void TDF_IDFilter::Ignore(const Standard_GUID& anID)
{
  if (myIgnore)
    myIDMap.Remove(anID);
  else
    myIDMap.Add(anID);
}

void TDF_IDFilter::Ignore(const NCollection_List<Standard_GUID>& anIDList)
{
  if (!anIDList.IsEmpty())
  {
    NCollection_List<Standard_GUID>::Iterator itr(anIDList);
    if (myIgnore)
    {
      for (; itr.More(); itr.Next())
        myIDMap.Remove(itr.Value());
    }
    else
    {
      int n = anIDList.Extent() + myIDMap.NbBuckets() + 1;
      myIDMap.ReSize(n);
      for (; itr.More(); itr.Next())
        myIDMap.Add(itr.Value());
    }
  }
}

void TDF_IDFilter::IDList(NCollection_List<Standard_GUID>& anIDList) const
{
  anIDList.Clear();
  for (NCollection_Map<Standard_GUID>::Iterator itr(myIDMap); itr.More(); itr.Next())
    anIDList.Append(itr.Key());
}

void TDF_IDFilter::Copy(const TDF_IDFilter& fromFilter)
{
  myIgnore = fromFilter.IgnoreAll();
  NCollection_List<Standard_GUID> idl;
  fromFilter.IDList(idl);
  if (myIgnore)
    Keep(idl);
  else
    Ignore(idl);
}

void TDF_IDFilter::Dump(Standard_OStream& anOS) const
{
  if (myIgnore)
    anOS << "EX";
  else
    anOS << "IN";
  anOS << "CLUSIVE filter: ";
  if (myIgnore)
    anOS << "ignores";
  else
    anOS << "keeps  ";
  anOS << " all IDs";
  NCollection_Map<Standard_GUID>::Iterator itr(myIDMap);
  if (itr.More())
  {
    anOS << " BUT:" << std::endl;
    for (; itr.More(); itr.Next())
    {
      const Standard_GUID& guid = itr.Key();
      guid.ShallowDump(anOS);
      anOS << std::endl;
    }
  }
}
