#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <SelectMgr_Filter.hpp>
#include <AIS_KindOfInteractive.hpp>
class SelectMgr_EntityOwner;

class AIS_ExclusionFilter : public SelectMgr_Filter
{

public:
  Standard_EXPORT AIS_ExclusionFilter(const bool ExclusionFlagOn = true);

  Standard_EXPORT AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
                                      const bool                  ExclusionFlagOn = true);

  Standard_EXPORT AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
                                      const int                   SignatureInType,
                                      const bool                  ExclusionFlagOn = true);

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const override;

  Standard_EXPORT bool Add(const AIS_KindOfInteractive TypeToExclude);

  Standard_EXPORT bool Add(const AIS_KindOfInteractive TypeToExclude, const int SignatureInType);

  Standard_EXPORT bool Remove(const AIS_KindOfInteractive TypeToExclude);

  Standard_EXPORT bool Remove(const AIS_KindOfInteractive TypeToExclude, const int SignatureInType);

  Standard_EXPORT void Clear();

  bool IsExclusionFlagOn() const { return myIsExclusionFlagOn; }

  void SetExclusionFlag(const bool theStatus) { myIsExclusionFlagOn = theStatus; }

  Standard_EXPORT bool IsStored(const AIS_KindOfInteractive aType) const;

  Standard_EXPORT void ListOfStoredTypes(NCollection_List<int>& TheList) const;

  Standard_EXPORT void ListOfSignature(const AIS_KindOfInteractive aType,
                                       NCollection_List<int>&      TheStoredList) const;

  DEFINE_STANDARD_RTTIEXT(AIS_ExclusionFilter, SelectMgr_Filter)

private:
  Standard_EXPORT bool IsSignatureIn(const AIS_KindOfInteractive aType, const int aSignature) const;

  bool                                            myIsExclusionFlagOn;
  NCollection_DataMap<int, NCollection_List<int>> myStoredTypes;
};
