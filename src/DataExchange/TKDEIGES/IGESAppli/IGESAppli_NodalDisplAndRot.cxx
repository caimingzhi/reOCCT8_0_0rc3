#include <IGESAppli_NodalDisplAndRot.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESBasic_HArray1OfHArray1OfXYZ.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_NodalDisplAndRot, IGESData_IGESEntity)

IGESAppli_NodalDisplAndRot::IGESAppli_NodalDisplAndRot() = default;

void IGESAppli_NodalDisplAndRot::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_GeneralNote>>>& allNotes,
  const occ::handle<NCollection_HArray1<int>>&                                allIdentifiers,
  const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>&        allNodes,
  const occ::handle<IGESBasic_HArray1OfHArray1OfXYZ>&                         allRotParams,
  const occ::handle<IGESBasic_HArray1OfHArray1OfXYZ>&                         allTransParams)
{
  if (allNodes->Lower() != 1
      || (allIdentifiers->Lower() != 1 || allIdentifiers->Length() != allNodes->Length())
      || (allTransParams->Lower() != 1 || allTransParams->Length() != allNodes->Length())
      || (allRotParams->Lower() != 1 || allRotParams->Length() != allNodes->Length()))
    throw Standard_DimensionMismatch(
      "IGESAppli_NodalDisplAndRot : Init(Lengths of arrays inconsistent)");

  for (int i = 1; i <= allNodes->Length(); i++)
  {
    occ::handle<NCollection_HArray1<gp_XYZ>> temp1 = allTransParams->Value(i);
    occ::handle<NCollection_HArray1<gp_XYZ>> temp2 = allRotParams->Value(i);
    if ((temp1->Lower() != 1 || temp1->Length() != allNotes->Length())
        || (temp2->Lower() != 1 || temp2->Length() != allNotes->Length()))
      throw Standard_DimensionMismatch(
        "IGESAppli_NodalDisplAndRot: Init(No. of Param per Node != Nbcases)");
  }

  theNotes           = allNotes;
  theNodes           = allNodes;
  theNodeIdentifiers = allIdentifiers;
  theTransParam      = allTransParams;
  theRotParam        = allRotParams;
  InitTypeAndForm(138, 0);
}

int IGESAppli_NodalDisplAndRot::NbCases() const
{
  return theNotes->Length();
}

int IGESAppli_NodalDisplAndRot::NbNodes() const
{
  return theNodes->Length();
}

occ::handle<IGESDimen_GeneralNote> IGESAppli_NodalDisplAndRot::Note(const int Index) const
{
  return theNotes->Value(Index);
}

int IGESAppli_NodalDisplAndRot::NodeIdentifier(const int Index) const
{
  return theNodeIdentifiers->Value(Index);
}

occ::handle<IGESAppli_Node> IGESAppli_NodalDisplAndRot::Node(const int Index) const
{
  return theNodes->Value(Index);
}

gp_XYZ IGESAppli_NodalDisplAndRot::TranslationParameter(const int NodeNum, const int CaseNum) const
{
  return theTransParam->Value(NodeNum)->Value(CaseNum);
}

gp_XYZ IGESAppli_NodalDisplAndRot::RotationalParameter(const int NodeNum, const int CaseNum) const
{
  return theRotParam->Value(NodeNum)->Value(CaseNum);
}
