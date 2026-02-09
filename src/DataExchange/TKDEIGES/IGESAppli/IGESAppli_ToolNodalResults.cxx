#include <IGESAppli_Node.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESAppli_NodalResults.hpp>
#include <IGESAppli_ToolNodalResults.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

IGESAppli_ToolNodalResults::IGESAppli_ToolNodalResults() = default;

void IGESAppli_ToolNodalResults::ReadOwnParams(const occ::handle<IGESAppli_NodalResults>&  ent,
                                               const occ::handle<IGESData_IGESReaderData>& IR,
                                               IGESData_ParamReader&                       PR) const
{
  int    tempSubCaseNum = 0;
  double tempTime;
  int    nbval   = 0;
  int    nbnodes = 0;

  occ::handle<IGESDimen_GeneralNote>                            tempNote;
  occ::handle<NCollection_HArray2<double>>                      tempData;
  occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>> tempNodes;
  occ::handle<NCollection_HArray1<int>>                         tempNodeIdentifiers;

  PR.ReadEntity(IR,
                PR.Current(),
                "General Note describing the analysis case",
                STANDARD_TYPE(IGESDimen_GeneralNote),
                tempNote);
  PR.ReadInteger(PR.Current(), "Subcase number", tempSubCaseNum);
  PR.ReadReal(PR.Current(), "Analysis time used", tempTime);
  bool tempFlag = PR.ReadInteger(PR.Current(), "No. of values", nbval);

  if (PR.ReadInteger(PR.Current(), "No. of nodes", nbnodes))
  {
    tempData            = new NCollection_HArray2<double>(1, nbnodes, 1, nbval);
    tempNodes           = new NCollection_HArray1<occ::handle<IGESAppli_Node>>(1, nbnodes);
    tempNodeIdentifiers = new NCollection_HArray1<int>(1, nbnodes);
    for (int i = 1; i <= nbnodes; i++)
    {
      int aitem;

      occ::handle<IGESAppli_Node> aNode;

      if (PR.ReadInteger(PR.Current(), "Node no. identifier", aitem))
        tempNodeIdentifiers->SetValue(i, aitem);
      if (PR.ReadEntity(IR, PR.Current(), "FEM Node", STANDARD_TYPE(IGESAppli_Node), aNode))
        tempNodes->SetValue(i, aNode);
      if (tempFlag)

        for (int j = 1; j <= nbval; j++)
        {
          double aval;
          if (PR.ReadReal(PR.Current(), "Value", aval))
            tempData->SetValue(i, j, aval);
        }
    }
  }
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNote, tempSubCaseNum, tempTime, tempNodeIdentifiers, tempNodes, tempData);
}

void IGESAppli_ToolNodalResults::WriteOwnParams(const occ::handle<IGESAppli_NodalResults>& ent,
                                                IGESData_IGESWriter&                       IW) const
{
  int nbnodes = ent->NbNodes();
  int nbdata  = ent->NbData();
  IW.Send(ent->Note());
  IW.Send(ent->SubCaseNumber());
  IW.Send(ent->Time());
  IW.Send(nbdata);
  IW.Send(nbnodes);
  for (int i = 1; i <= nbnodes; i++)
  {
    IW.Send(ent->NodeIdentifier(i));
    IW.Send(ent->Node(i));
    for (int j = 1; j <= nbdata; j++)
      IW.Send(ent->Data(i, j));
  }
}

void IGESAppli_ToolNodalResults::OwnShared(const occ::handle<IGESAppli_NodalResults>& ent,
                                           Interface_EntityIterator&                  iter) const
{
  int nbnodes = ent->NbNodes();
  iter.GetOneItem(ent->Note());
  for (int i = 1; i <= nbnodes; i++)
    iter.GetOneItem(ent->Node(i));
}

void IGESAppli_ToolNodalResults::OwnCopy(const occ::handle<IGESAppli_NodalResults>& another,
                                         const occ::handle<IGESAppli_NodalResults>& ent,
                                         Interface_CopyTool&                        TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, aNote, TC.Transferred(another->Note()));
  int                                   aSubCaseNum      = another->SubCaseNumber();
  double                                aTime            = another->Time();
  int                                   nbnodes          = another->NbNodes();
  int                                   nbval            = another->NbData();
  occ::handle<NCollection_HArray1<int>> aNodeIdentifiers = new NCollection_HArray1<int>(1, nbnodes);
  occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>> aNodes =
    new NCollection_HArray1<occ::handle<IGESAppli_Node>>(1, nbnodes);
  occ::handle<NCollection_HArray2<double>> aData =
    new NCollection_HArray2<double>(1, nbnodes, 1, nbval);

  for (int i = 1; i <= nbnodes; i++)
  {
    int aItem = another->NodeIdentifier(i);
    aNodeIdentifiers->SetValue(i, aItem);
    DeclareAndCast(IGESAppli_Node, anentity, TC.Transferred(another->Node(i)));
    aNodes->SetValue(i, anentity);
    for (int j = 1; j <= nbval; j++)
      aData->SetValue(i, j, another->Data(i, j));
  }

  ent->Init(aNote, aSubCaseNum, aTime, aNodeIdentifiers, aNodes, aData);
  ent->SetFormNumber(another->FormNumber());
}

IGESData_DirChecker IGESAppli_ToolNodalResults::DirChecker(
  const occ::handle<IGESAppli_NodalResults>&) const
{
  IGESData_DirChecker DC(146, 0, 34);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);
  DC.BlankStatusIgnored();
  DC.UseFlagRequired(03);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESAppli_ToolNodalResults::OwnCheck(const occ::handle<IGESAppli_NodalResults>& ent,
                                          const Interface_ShareTool&,
                                          occ::handle<Interface_Check>& ach) const
{
  int  FormNum = ent->FormNumber();
  int  nv      = ent->NbData();
  bool OK      = true;
  switch (FormNum)
  {
    case 0:
      if (nv < 0)
        OK = false;
      break;
    case 1:
      if (nv != 1)
        OK = false;
      break;
    case 2:
      if (nv != 1)
        OK = false;
      break;
    case 3:
      if (nv != 3)
        OK = false;
      break;
    case 4:
      if (nv != 6)
        OK = false;
      break;
    case 5:
      if (nv != 3)
        OK = false;
      break;
    case 6:
      if (nv != 3)
        OK = false;
      break;
    case 7:
      if (nv != 3)
        OK = false;
      break;
    case 8:
      if (nv != 3)
        OK = false;
      break;
    case 9:
      if (nv != 3)
        OK = false;
      break;
    case 10:
      if (nv != 1)
        OK = false;
      break;
    case 11:
      if (nv != 1)
        OK = false;
      break;
    case 12:
      if (nv != 3)
        OK = false;
      break;
    case 13:
      if (nv != 1)
        OK = false;
      break;
    case 14:
      if (nv != 1)
        OK = false;
      break;
    case 15:
      if (nv != 3)
        OK = false;
      break;
    case 16:
      if (nv != 1)
        OK = false;
      break;
    case 17:
      if (nv != 3)
        OK = false;
      break;
    case 18:
      if (nv != 3)
        OK = false;
      break;
    case 19:
      if (nv != 3)
        OK = false;
      break;
    case 20:
      if (nv != 3)
        OK = false;
      break;
    case 21:
      if (nv != 3)
        OK = false;
      break;
    case 22:
      if (nv != 3)
        OK = false;
      break;
    case 23:
      if (nv != 6)
        OK = false;
      break;
    case 24:
      if (nv != 6)
        OK = false;
      break;
    case 25:
      if (nv != 6)
        OK = false;
      break;
    case 26:
      if (nv != 6)
        OK = false;
      break;
    case 27:
      if (nv != 6)
        OK = false;
      break;
    case 28:
      if (nv != 6)
        OK = false;
      break;
    case 29:
      if (nv != 9)
        OK = false;
      break;
    case 30:
      if (nv != 9)
        OK = false;
      break;
    case 31:
      if (nv != 9)
        OK = false;
      break;
    case 32:
      if (nv != 9)
        OK = false;
      break;
    case 33:
      if (nv != 9)
        OK = false;
      break;
    case 34:
      if (nv != 9)
        OK = false;
      break;
    default:
      ach->AddFail("Incorrect Form Number");
      break;
  }
  if (!OK)
    ach->AddFail("Incorrect count of real values in array V for FEM node");
}

void IGESAppli_ToolNodalResults::OwnDump(const occ::handle<IGESAppli_NodalResults>& ent,
                                         const IGESData_IGESDumper&                 dumper,
                                         Standard_OStream&                          S,
                                         const int                                  level) const
{

  S << "IGESAppli_NodalResults\n";

  S << "General Note : ";
  dumper.Dump(ent->Note(), S, (level <= 4) ? 0 : 1);
  S << "\n";
  S << "Analysis subcase number : " << ent->SubCaseNumber() << "  ";
  S << "Time used : " << ent->Time() << "\n";
  S << "No. of nodes : " << ent->NbNodes() << "  ";
  S << "No. of values for a node : " << ent->NbData() << "\n";
  S << "Node Identifiers :\n";
  S << "Nodes :\n";
  S << "Data : ";
  if (level < 6)
    S << " [ask level > 5]";

  S << "\n";
  if (level > 4)
  {
    for (int i = 1; i <= ent->NbNodes(); i++)
    {
      S << "[" << i << "]: ";
      S << "NodeIdentifier : " << ent->NodeIdentifier(i) << "  ";
      S << "Node : ";
      dumper.Dump(ent->Node(i), S, 1);
      S << "\n";
      if (level < 6)
        continue;
      S << "Data : [ ";
      for (int j = 1; j <= ent->NbData(); j++)
        S << "  " << ent->Data(i, j);
      S << " ]\n";
    }
  }
}
