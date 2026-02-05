#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_CopyTool.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Label.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <TDF_RelocationTable.hpp>
#include <Standard_TypeMismatch.hpp>

//=================================================================================================

void TDF_CopyTool::Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                        const occ::handle<TDF_RelocationTable>& aRelocationTable)
{
  TDF_IDFilter privilegeFilter; // Ignore the target attribute's privilege!
  TDF_IDFilter refFilter;       // Will not be used.
  TDF_CopyTool::Copy(aSourceDataSet, aRelocationTable, privilegeFilter, refFilter, false);
}

//=================================================================================================

void TDF_CopyTool::Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                        const occ::handle<TDF_RelocationTable>& aRelocationTable,
                        const TDF_IDFilter&                     aPrivilegeFilter)
{
  TDF_IDFilter refFilter; // Will not be used.
  TDF_CopyTool::Copy(aSourceDataSet, aRelocationTable, aPrivilegeFilter, refFilter, false);
}

//=================================================================================================

void TDF_CopyTool::Copy(const occ::handle<TDF_DataSet>&         aSourceDataSet,
                        const occ::handle<TDF_RelocationTable>& aRelocationTable,
                        const TDF_IDFilter&                     aPrivilegeFilter,
                        const TDF_IDFilter& /* aRefFilter */,
                        const bool /* setSelfContained */)
{
  if (aSourceDataSet->IsEmpty())
    return;

  NCollection_Map<TDF_Label>&                  srcLabs = aSourceDataSet->Labels();
  NCollection_Map<occ::handle<TDF_Attribute>>& srcAtts = aSourceDataSet->Attributes();
  NCollection_List<TDF_Label>&                 rootLst = aSourceDataSet->Roots();

  NCollection_DataMap<TDF_Label, TDF_Label>& theLabMap = aRelocationTable->LabelTable();
  NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>& theAttMap =
    aRelocationTable->AttributeTable();

  // Parallel exploration of the root label structures:
  // * builds the target labels not found;
  // * binds the source attributes with the target ones;
  // * binds the source attributes with new target ones if there is none.

  // Label pre-binding is tested before paste.
  // For it is possible to copy the roots at another place with OTHER TAGS,
  // we first ask <theLabMap> if each source root label is already bound.

  for (NCollection_List<TDF_Label>::Iterator labLItr(rootLst); labLItr.More(); labLItr.Next())
  {
    const TDF_Label& sLab = labLItr.Value();
    if (theLabMap.IsBound(sLab))
    {
      TDF_Label tIns(theLabMap.Find(sLab));
      TDF_CopyTool::CopyLabels(sLab, tIns, theLabMap, theAttMap, srcLabs, srcAtts);
    }
    // if not bound : do nothing!
  }

  // The relocation attribute table is now ready,
  // except for the label unattached attributes,
  // but everybody can update the relocation table...

  // Now: the paste phase!
  NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>::Iterator attItr2(
    theAttMap);
  for (; attItr2.More(); attItr2.Next())
  {
    const occ::handle<TDF_Attribute>& sAtt = attItr2.Key();
    if (!sAtt.IsNull())
    { // This condition looks superfluous; and below also.
      const occ::handle<TDF_Attribute>& tAtt = attItr2.Value();
      // 1 - No copy on itself.
      // 2 - The target attribute is present BUT its privilege over the
      // source one must be ignored. The source attribute can be copied.
      if ((sAtt != tAtt) && aPrivilegeFilter.IsIgnored(tAtt->ID()))
        sAtt->Paste(tAtt, aRelocationTable);
    }
  }
}

//=======================================================================
// function : CopyLabels
// purpose  : Internal root label copy recursive method.
//=======================================================================

void TDF_CopyTool::CopyLabels(
  const TDF_Label&                                                             aSLabel,
  TDF_Label&                                                                   aTargetLabel,
  NCollection_DataMap<TDF_Label, TDF_Label>&                                   aLabMap,
  NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>& aAttMap,
  const NCollection_Map<TDF_Label>&                                            aSrcLabelMap,
  const NCollection_Map<occ::handle<TDF_Attribute>>&                           aSrcAttributeMap)
{
  TDF_CopyTool::CopyAttributes(aSLabel, aTargetLabel, aAttMap, aSrcAttributeMap);

  // Does the same for the children.
  for (TDF_ChildIterator childItr(aSLabel); childItr.More(); childItr.Next())
  {
    const TDF_Label& childSLab = childItr.Value();
    if (aSrcLabelMap.Contains(childSLab))
    {
      TDF_Label childTIns;
      if (aLabMap.IsBound(childSLab))
      {
        childTIns = aLabMap.Find(childSLab);
      }
      else
      {
        childTIns = aTargetLabel.FindChild(childSLab.Tag());
        aLabMap.Bind(childSLab, childTIns);
      }

      TDF_CopyTool::CopyLabels(childSLab,
                               childTIns,
                               aLabMap,
                               aAttMap,
                               aSrcLabelMap,
                               aSrcAttributeMap);
    }
  }
}

//=======================================================================
// function : CopyAttributes
// purpose  : Internal attribute copy method.
//=======================================================================

void TDF_CopyTool::CopyAttributes(
  const TDF_Label&                                                             aSLabel,
  TDF_Label&                                                                   aTargetLabel,
  NCollection_DataMap<occ::handle<TDF_Attribute>, occ::handle<TDF_Attribute>>& aAttMap,
  const NCollection_Map<occ::handle<TDF_Attribute>>&                           aSrcAttributeMap)
{
  occ::handle<TDF_Attribute> tAtt;

  // Finds the target attributes or creates them empty.
  for (TDF_AttributeIterator attItr(aSLabel); attItr.More(); attItr.Next())
  {
    const occ::handle<TDF_Attribute> sAtt = attItr.Value();
    if (aSrcAttributeMap.Contains(sAtt))
    {
      const Standard_GUID& id = sAtt->ID();
      if (!aTargetLabel.FindAttribute(id, tAtt))
      {
        tAtt = sAtt->NewEmpty();
        if (tAtt->ID() != id)
          tAtt->SetID(id); //
        aTargetLabel.AddAttribute(tAtt, true);
        aAttMap.Bind(sAtt, tAtt);
      }
      else
      {
        // Some attributes have the same ID, but are different and
        // exclusive. This obliged to test the dynamic type identity.
        if (tAtt->IsInstance(sAtt->DynamicType()))
          aAttMap.Bind(sAtt, tAtt);
        else
          throw Standard_TypeMismatch("TDF_CopyTool: Cannot paste to a different type attribute.");
      }
    }
  }
}
