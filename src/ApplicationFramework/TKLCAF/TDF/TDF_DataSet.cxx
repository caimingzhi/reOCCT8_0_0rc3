#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <Standard_Handle.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_DataSet, Standard_Transient)

//=================================================================================================

TDF_DataSet::TDF_DataSet() = default;

//=================================================================================================

void TDF_DataSet::Clear()
{
  myRootLabels.Clear();
  myLabelMap.Clear();
  myAttributeMap.Clear();
}

//=================================================================================================

Standard_OStream& TDF_DataSet::Dump(Standard_OStream& anOS) const
{
  anOS << "\t\t=====< TDF_DataSet dump >=====" << std::endl;
  anOS << "Root Labels :" << std::endl << "=============" << std::endl;
  for (NCollection_List<TDF_Label>::Iterator itr1(myRootLabels); itr1.More(); itr1.Next())
  {
    itr1.Value().EntryDump(anOS);
    anOS << " | ";
  }
  anOS << std::endl << "Labels :" << std::endl << "========" << std::endl;
  for (NCollection_Map<TDF_Label>::Iterator itr2(myLabelMap); itr2.More(); itr2.Next())
  {
    itr2.Key().EntryDump(anOS);
    anOS << " | ";
  }
  anOS << std::endl << "Attributes :" << std::endl << "============" << std::endl << std::endl;
  for (NCollection_Map<occ::handle<TDF_Attribute>>::Iterator itr3(myAttributeMap); itr3.More();
       itr3.Next())
  {
    itr3.Key()->Label().EntryDump(anOS);
    anOS << " \t";
    itr3.Key()->Dump(anOS);
    anOS << std::endl;
  }
  anOS << std::endl;
  return anOS;
}
