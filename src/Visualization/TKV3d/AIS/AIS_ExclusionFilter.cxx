#include <AIS_ExclusionFilter.hpp>
#include <AIS_InteractiveObject.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_ExclusionFilter, SelectMgr_Filter)

AIS_ExclusionFilter::AIS_ExclusionFilter(const bool ExclusionFlagOn)
    : myIsExclusionFlagOn(ExclusionFlagOn)
{
}

AIS_ExclusionFilter::AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
                                         const bool                  ExclusionFlagOn)
    : myIsExclusionFlagOn(ExclusionFlagOn)
{
  NCollection_List<int> L;
  myStoredTypes.Bind((int)TypeToExclude, L);
}

AIS_ExclusionFilter::AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
                                         const int                   SignatureInType,
                                         const bool                  ExclusionFlagOn)
    : myIsExclusionFlagOn(ExclusionFlagOn)
{
  NCollection_List<int> L;
  L.Append(SignatureInType);
  myStoredTypes.Bind((int)TypeToExclude, L);
}

bool AIS_ExclusionFilter::Add(const AIS_KindOfInteractive TypeToExclude)
{
  if (IsStored(TypeToExclude))
    return false;
  NCollection_List<int> L;
  myStoredTypes.Bind((int)TypeToExclude, L);
  return true;
}

bool AIS_ExclusionFilter::Add(const AIS_KindOfInteractive TypeToExclude, const int SignatureInType)
{
  if (!IsStored(TypeToExclude))
  {
    NCollection_List<int> L;
    L.Append(SignatureInType);
    myStoredTypes.Bind((int)TypeToExclude, L);
    return true;
  }

  myStoredTypes((int)TypeToExclude).Append(SignatureInType);
  return true;
}

bool AIS_ExclusionFilter::Remove(const AIS_KindOfInteractive TypeToExclude)
{
  if (!IsStored(TypeToExclude))
    return false;
  myStoredTypes((int)TypeToExclude).Clear();
  myStoredTypes.UnBind((int)TypeToExclude);
  return true;
}

bool AIS_ExclusionFilter::Remove(const AIS_KindOfInteractive TypeToExclude,
                                 const int                   SignatureInType)
{
  if (!IsStored(TypeToExclude))
    return false;
  NCollection_List<int>& LL = myStoredTypes.ChangeFind((int)TypeToExclude);
  for (NCollection_List<int>::Iterator it(LL); it.More(); it.Next())
  {
    if (it.Value() == SignatureInType)
    {
      LL.Remove(it);
      return true;
    }
  }
  return false;
}

void AIS_ExclusionFilter::Clear()
{
  NCollection_DataMap<int, NCollection_List<int>>::Iterator Mit(myStoredTypes);
  for (; Mit.More(); Mit.Next())
    myStoredTypes.ChangeFind(Mit.Key()).Clear();
  myStoredTypes.Clear();
}

bool AIS_ExclusionFilter::IsStored(const AIS_KindOfInteractive aType) const
{
  return myStoredTypes.IsBound(int(aType));
}

bool AIS_ExclusionFilter::IsSignatureIn(const AIS_KindOfInteractive aType,
                                        const int                   SignatureInType) const
{
  if (!myStoredTypes.IsBound(aType))
    return false;
  for (NCollection_List<int>::Iterator Lit(myStoredTypes((int)aType)); Lit.More(); Lit.Next())
  {
    if (Lit.Value() == SignatureInType)
      return true;
  }
  return false;
}

void AIS_ExclusionFilter::ListOfStoredTypes(NCollection_List<int>& TheList) const
{
  TheList.Clear();
  NCollection_DataMap<int, NCollection_List<int>>::Iterator MIT(myStoredTypes);
  for (; MIT.More(); MIT.Next())
    TheList.Append(MIT.Key());
}

void AIS_ExclusionFilter::ListOfSignature(const AIS_KindOfInteractive aType,
                                          NCollection_List<int>&      TheStoredList) const
{
  TheStoredList.Clear();
  if (IsStored(aType))
    for (NCollection_List<int>::Iterator it(myStoredTypes(aType)); it.More(); it.Next())
      TheStoredList.Append(it.Value());
}

bool AIS_ExclusionFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& EO) const
{
  if (myStoredTypes.IsEmpty())
    return myIsExclusionFlagOn;

  if (EO.IsNull())
    return false;
  occ::handle<AIS_InteractiveObject> IO = occ::down_cast<AIS_InteractiveObject>(EO->Selectable());
  if (IO.IsNull())
    return false;

  if (!myStoredTypes.IsBound(IO->Type()))
    return myIsExclusionFlagOn;

  if (myStoredTypes(IO->Type()).IsEmpty())
    return !myIsExclusionFlagOn;

  if (IsSignatureIn(IO->Type(), IO->Signature()))
    return !myIsExclusionFlagOn;

  return myIsExclusionFlagOn;
}
