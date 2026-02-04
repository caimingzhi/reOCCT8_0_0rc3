#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <SelectMgr_Filter.hpp>
#include <AIS_KindOfInteractive.hpp>
class SelectMgr_EntityOwner;

//! A framework to reject or to accept only objects of
//! given types and/or signatures.
//! Objects are stored, and the stored objects - along
//! with the flag settings - are used to define the filter.
//! Objects to be filtered are compared with the stored
//! objects added to the filter, and are accepted or
//! rejected according to the exclusion flag setting.
//! -   Exclusion flag on
//! -   the function IsOk answers true for all objects,
//! except those of the types and signatures stored
//! in the filter framework
//! -   Exclusion flag off
//! -   the function IsOk answers true for all objects
//! which have the same type and signature as the stored ones.
class AIS_ExclusionFilter : public SelectMgr_Filter
{

public:
  //! Constructs an empty exclusion filter object defined by
  //! the flag setting ExclusionFlagOn.
  //! By default, the flag is set to true.
  Standard_EXPORT AIS_ExclusionFilter(const bool ExclusionFlagOn = true);

  //! All the AIS objects of <TypeToExclude>
  //! Will be rejected by the IsOk Method.
  Standard_EXPORT AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
                                      const bool                  ExclusionFlagOn = true);

  //! Constructs an exclusion filter object defined by the
  //! enumeration value TypeToExclude, the signature
  //! SignatureInType, and the flag setting ExclusionFlagOn.
  //! By default, the flag is set to true.
  Standard_EXPORT AIS_ExclusionFilter(const AIS_KindOfInteractive TypeToExclude,
                                      const int                   SignatureInType,
                                      const bool                  ExclusionFlagOn = true);

  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anObj) const override;

  //! Adds the type TypeToExclude to the list of types.
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

