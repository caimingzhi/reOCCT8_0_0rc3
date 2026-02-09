#include <IGESAppli_NodalResults.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_NodalResults, IGESData_IGESEntity)

IGESAppli_NodalResults::IGESAppli_NodalResults() = default;

void IGESAppli_NodalResults::Init(
  const occ::handle<IGESDimen_GeneralNote>&                            aNote,
  const int                                                            aNumber,
  const double                                                         aTime,
  const occ::handle<NCollection_HArray1<int>>&                         allNodeIdentifiers,
  const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>& allNodes,
  const occ::handle<NCollection_HArray2<double>>&                      allData)
{
  if (allNodes->Lower() != 1 || allNodeIdentifiers->Lower() != 1
      || allNodes->Length() != allNodeIdentifiers->Length() || allData->LowerCol() != 1
      || allData->LowerRow() != 1 || allNodes->Length() != allData->UpperRow())
    throw Standard_DimensionMismatch("IGESAppli_NodalResults : Init");
  theNote            = aNote;
  theSubCaseNum      = aNumber;
  theTime            = aTime;
  theNodeIdentifiers = allNodeIdentifiers;
  theNodes           = allNodes;
  theData            = allData;
  InitTypeAndForm(146, FormNumber());
}

void IGESAppli_NodalResults::SetFormNumber(const int form)
{
  if (form < 0 || form > 34)
    throw Standard_OutOfRange("IGESAppli_NodalResults : SetFormNumber");
  InitTypeAndForm(146, form);
}

occ::handle<IGESDimen_GeneralNote> IGESAppli_NodalResults::Note() const
{
  return theNote;
}

occ::handle<IGESAppli_Node> IGESAppli_NodalResults::Node(const int Index) const
{
  return theNodes->Value(Index);
}

int IGESAppli_NodalResults::NbNodes() const
{
  return theNodes->Length();
}

int IGESAppli_NodalResults::SubCaseNumber() const
{
  return theSubCaseNum;
}

double IGESAppli_NodalResults::Time() const
{
  return theTime;
}

int IGESAppli_NodalResults::NbData() const
{
  return theData->RowLength();
}

int IGESAppli_NodalResults::NodeIdentifier(const int Index) const
{
  return theNodeIdentifiers->Value(Index);
}

double IGESAppli_NodalResults::Data(const int NodeNum, const int DataNum) const
{
  return theData->Value(NodeNum, DataNum);
}
