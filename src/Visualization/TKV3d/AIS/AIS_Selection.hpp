#pragma once

#include <NCollection_Array1.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <NCollection_List.hpp>
#include <AIS_SelectionScheme.hpp>

enum AIS_SelectStatus
{
  AIS_SS_Added,
  AIS_SS_Removed,
  AIS_SS_NotDone
};

#include <Standard.hpp>
#include <Standard_Type.hpp>

class SelectMgr_Filter;

class AIS_Selection : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AIS_Selection, Standard_Transient)
public:
  Standard_EXPORT AIS_Selection();

  Standard_EXPORT virtual void Clear();

  Standard_EXPORT virtual AIS_SelectStatus Select(
    const occ::handle<SelectMgr_EntityOwner>& theOwner,
    const occ::handle<SelectMgr_Filter>&      theFilter,
    const AIS_SelectionScheme                 theSelScheme,
    const bool                                theIsDetected);

  Standard_EXPORT virtual AIS_SelectStatus AddSelect(
    const occ::handle<SelectMgr_EntityOwner>& theObject);

  virtual void ClearAndSelect(const occ::handle<SelectMgr_EntityOwner>& theObject,
                              const occ::handle<SelectMgr_Filter>&      theFilter,
                              const bool                                theIsDetected)
  {
    Clear();
    Select(theObject, theFilter, AIS_SelectionScheme_Add, theIsDetected);
  }

  bool IsSelected(const occ::handle<SelectMgr_EntityOwner>& theObject) const
  {
    return myResultMap.IsBound(theObject);
  }

  const NCollection_List<occ::handle<SelectMgr_EntityOwner>>& Objects() const { return myresult; }

  int Extent() const { return myresult.Size(); }

  bool IsEmpty() const { return myresult.IsEmpty(); }

public:
  void Init()
  {
    myIterator = NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator(myresult);
  }

  bool More() const { return myIterator.More(); }

  void Next() { myIterator.Next(); }

  const occ::handle<SelectMgr_EntityOwner>& Value() const { return myIterator.Value(); }

  Standard_EXPORT virtual void SelectOwners(
    const NCollection_Array1<occ::handle<SelectMgr_EntityOwner>>& thePickedOwners,
    const AIS_SelectionScheme                                     theSelScheme,
    const bool                                                    theToAllowSelOverlap,
    const occ::handle<SelectMgr_Filter>&                          theFilter);

protected:
  Standard_EXPORT virtual AIS_SelectStatus appendOwner(
    const occ::handle<SelectMgr_EntityOwner>& theOwner,
    const occ::handle<SelectMgr_Filter>&      theFilter);

protected:
  NCollection_List<occ::handle<SelectMgr_EntityOwner>>           myresult;
  NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator myIterator;
  NCollection_DataMap<occ::handle<SelectMgr_EntityOwner>,
                      NCollection_List<occ::handle<SelectMgr_EntityOwner>>::Iterator>
    myResultMap;
};
