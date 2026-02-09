#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <Standard_CString.hpp>
#include <TDF_Label.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TDF_IDFilter;
class TCollection_AsciiString;
class TDF_Data;

class TDF_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int NbLabels(const TDF_Label& aLabel);

  Standard_EXPORT static int NbAttributes(const TDF_Label& aLabel);

  Standard_EXPORT static int NbAttributes(const TDF_Label& aLabel, const TDF_IDFilter& aFilter);

  Standard_EXPORT static bool IsSelfContained(const TDF_Label& aLabel);

  Standard_EXPORT static bool IsSelfContained(const TDF_Label& aLabel, const TDF_IDFilter& aFilter);

  Standard_EXPORT static void OutReferers(const TDF_Label&                             theLabel,
                                          NCollection_Map<occ::handle<TDF_Attribute>>& theAtts);

  Standard_EXPORT static void OutReferers(const TDF_Label&    aLabel,
                                          const TDF_IDFilter& aFilterForReferers,
                                          const TDF_IDFilter& aFilterForReferences,
                                          NCollection_Map<occ::handle<TDF_Attribute>>& atts);

  Standard_EXPORT static void OutReferences(const TDF_Label&                             aLabel,
                                            NCollection_Map<occ::handle<TDF_Attribute>>& atts);

  Standard_EXPORT static void OutReferences(const TDF_Label&    aLabel,
                                            const TDF_IDFilter& aFilterForReferers,
                                            const TDF_IDFilter& aFilterForReferences,
                                            NCollection_Map<occ::handle<TDF_Attribute>>& atts);

  Standard_EXPORT static void RelocateLabel(const TDF_Label& aSourceLabel,
                                            const TDF_Label& fromRoot,
                                            const TDF_Label& toRoot,
                                            TDF_Label&       aTargetLabel,
                                            const bool       create = false);

  Standard_EXPORT static void Entry(const TDF_Label& aLabel, TCollection_AsciiString& anEntry);

  Standard_EXPORT static void TagList(const TDF_Label& aLabel, NCollection_List<int>& aTagList);

  Standard_EXPORT static void TagList(const TCollection_AsciiString& anEntry,
                                      NCollection_List<int>&         aTagList);

  Standard_EXPORT static void Label(const occ::handle<TDF_Data>&   aDF,
                                    const TCollection_AsciiString& anEntry,
                                    TDF_Label&                     aLabel,
                                    const bool                     create = false);

  Standard_EXPORT static void Label(const occ::handle<TDF_Data>& aDF,
                                    const char*                  anEntry,
                                    TDF_Label&                   aLabel,
                                    const bool                   create = false);

  Standard_EXPORT static void Label(const occ::handle<TDF_Data>& aDF,
                                    const NCollection_List<int>& aTagList,
                                    TDF_Label&                   aLabel,
                                    const bool                   create = false);

  Standard_EXPORT static void CountLabels(NCollection_List<TDF_Label>&         aLabelList,
                                          NCollection_DataMap<TDF_Label, int>& aLabelMap);

  Standard_EXPORT static void DeductLabels(NCollection_List<TDF_Label>&         aLabelList,
                                           NCollection_DataMap<TDF_Label, int>& aLabelMap);

  Standard_EXPORT static void DeepDump(Standard_OStream& anOS, const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT static void ExtendedDeepDump(Standard_OStream&            anOS,
                                               const occ::handle<TDF_Data>& aDF,
                                               const TDF_IDFilter&          aFilter);

  Standard_EXPORT static void DeepDump(Standard_OStream& anOS, const TDF_Label& aLabel);

  Standard_EXPORT static void ExtendedDeepDump(Standard_OStream&   anOS,
                                               const TDF_Label&    aLabel,
                                               const TDF_IDFilter& aFilter);
};
