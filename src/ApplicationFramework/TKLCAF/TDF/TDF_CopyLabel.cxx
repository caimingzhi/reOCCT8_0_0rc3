#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_ClosureMode.hpp>
#include <TDF_ClosureTool.hpp>
#include <TDF_CopyLabel.hpp>
#include <TDF_CopyTool.hpp>
#include <TDF_Data.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_IDFilter.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_Tool.hpp>

// The bug concerns the COPY operation of some attributes of a non-self-contained label.
// The attributes making the label non-self-contained are not involved by the operation.
// Therefore, these attributes shouldn't be considered by the COPY mechanism and
// the label should be considered as a self-contained.
// Correction of the bug consists of ignoring the attributes not involved by the COPY operation.
//=================================================================================================

TDF_CopyLabel::TDF_CopyLabel()
    : myFilter(false),
      myIsDone(false)
{
  mySL.Nullify();
  myTL.Nullify();
}

//=================================================================================================

TDF_CopyLabel::TDF_CopyLabel(const TDF_Label& aSource, const TDF_Label& aTarget)
    : myFilter(false),
      myIsDone(false)
{
  mySL = aSource;
  myTL = aTarget;
}

//=================================================================================================

void TDF_CopyLabel::Load(const TDF_Label& aSource, const TDF_Label& aTarget)
{
  mySL = aSource;
  myTL = aTarget;
}

//=================================================================================================

void TDF_CopyLabel::ExternalReferences(const TDF_Label&                             aRefLabel,
                                       const TDF_Label&                             aLabel,
                                       NCollection_Map<occ::handle<TDF_Attribute>>& aExternals,
                                       const TDF_IDFilter&                          aFilter,
                                       occ::handle<TDF_DataSet>&                    ds)
{
  //  TCollection_AsciiString entr1,entr2; //d
  for (TDF_AttributeIterator itr(aLabel); itr.More(); itr.Next())
  {
    itr.Value()->References(ds);
    const NCollection_Map<occ::handle<TDF_Attribute>>& attMap = ds->Attributes(); // attMap
    //     TDF_Tool::Entry(itr.Value()->Label(), entr1);  //d
    //     std::cout<<"\tSource Attribute dynamic type = "<<itr.Value()->DynamicType()<<" Label =
    //     "<<entr1 <<std::endl;
    for (NCollection_Map<occ::handle<TDF_Attribute>>::Iterator attMItr(attMap); attMItr.More();
         attMItr.Next())
    {
      const occ::handle<TDF_Attribute>& att = attMItr.Key();

      //       TDF_Tool::Entry(att->Label(), entr1);
      //       std::cout<<"\t\tReferences attribute dynamic type = "<<att->DynamicType()<<" Label =
      //       "<<entr1 <<std::endl;
      if (!att.IsNull() && !att->Label().IsNull())
      {
        if (aFilter.IsKept(att) && att->Label().IsDifferent(aRefLabel)
            && !att->Label().IsDescendant(aRefLabel))
        {
          aExternals.Add(att);
        }
      }
    }

    //     const NCollection_Map<TDF_Label>& labMap = ds->Labels();
    //     for (NCollection_Map<TDF_Label>::Iterator labMItr(labMap);labMItr.More(); labMItr.Next())
    //     {
    //       TDF_Tool::Entry(labMItr.Key(), entr1);
    // 	std::cout<<"\t\tLABELS from DS of Attr:: Lab = "<<entr1<<std::endl;
    //       if (!labMItr.Key().IsDescendant(aRefLabel) && labMItr.Key().IsDifferent(aRefLabel)) {
    // //	aExternals.Add(itr.Value()); // ??? LabelMap of Attribute has label which don't
    // 	// belongs to source hierarchy. So, what we should do ?
    // 	// Add this Attribute to the aExternals or add all attributes
    // 	// from this label ?
    // 	TCollection_AsciiString entr1, entr2;
    // 	TDF_Tool::Entry(labMItr.Key(), entr1);
    // 	TDF_Tool::Entry(aRefLabel, entr2);
    // 	std::cout<<"\t\t\tNot descendant label:: Lab1 = "<<entr1<<" and RefLab =
    // "<<entr2<<std::endl;
    //       }
    //     }

    ds->Clear();
  }
}

//=================================================================================================

bool TDF_CopyLabel::ExternalReferences(const TDF_Label&                             L,
                                       NCollection_Map<occ::handle<TDF_Attribute>>& aExternals,
                                       const TDF_IDFilter&                          aFilter)
{
  occ::handle<TDF_DataSet> ds = new TDF_DataSet();
  ExternalReferences(L, L, aExternals, aFilter, ds);
  for (TDF_ChildIterator itr(L, true); itr.More(); itr.Next())
  {
    ExternalReferences(L, itr.Value(), aExternals, aFilter, ds);
  }
  return aExternals.Extent() != 0;
}

//=======================================================================
#ifdef OCCT_DEBUG
static void PrintEntry(const TDF_Label& label, const bool allLevels)
{
  TCollection_AsciiString entry;
  TDF_Tool::Entry(label, entry);
  std::cout << "\tShareable attribute on the label = " << entry << std::endl;
  TDF_ChildIterator it(label, allLevels);
  for (; it.More(); it.Next())
  {
    TDF_Tool::Entry(it.Value(), entry);
    std::cout << "\tChildLabelEntry = " << entry << std::endl;
  }
}
#endif
//=================================================================================================

void TDF_CopyLabel::Perform()
{
  myIsDone = false;
  if (mySL.Data()->Root().IsDifferent(myTL.Data()->Root()) && // TDF_Data is not the same
                                                              // clang-format off
     !TDF_Tool::IsSelfContained(mySL, myFilter)) return;               //source label isn't self-contained
  // clang-format on

  bool extReferers = ExternalReferences(mySL, myMapOfExt, myFilter);

  myRT                        = new TDF_RelocationTable(true);
  occ::handle<TDF_DataSet> ds = new TDF_DataSet();
  TDF_ClosureMode          mode(true); // descendant plus reference
  ds->AddLabel(mySL);
  myRT->SetRelocation(mySL, myTL);
  TDF_ClosureTool::Closure(ds, myFilter, mode);
  if (extReferers)
  {
    for (NCollection_Map<occ::handle<TDF_Attribute>>::Iterator attMItr(myMapOfExt); attMItr.More();
         attMItr.Next())
    {
      const occ::handle<TDF_Attribute>& att = attMItr.Key();
      myRT->SetRelocation(att, att);
#ifdef OCCT_DEBUG
      PrintEntry(att->Label(), true);
#endif
    }
  }

  TDF_CopyTool::Copy(ds, myRT);
  myIsDone = true;
}

//=================================================================================================

const occ::handle<TDF_RelocationTable>& TDF_CopyLabel::RelocationTable() const
{
  return myRT;
}

//=================================================================================================

void TDF_CopyLabel::UseFilter(const TDF_IDFilter& aFilter)
{
  myFilter.Assign(aFilter);
}
