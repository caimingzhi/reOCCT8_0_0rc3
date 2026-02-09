#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_ToolVertexList.hpp>
#include <IGESSolid_VertexList.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESSolid_ToolVertexList::IGESSolid_ToolVertexList() = default;

void IGESSolid_ToolVertexList::ReadOwnParams(const occ::handle<IGESSolid_VertexList>& ent,
                                             const occ::handle<IGESData_IGESReaderData>&,
                                             IGESData_ParamReader& PR) const
{

  int nbitems = 0;

  occ::handle<NCollection_HArray1<gp_XYZ>> tempVertices;

  bool sb = PR.ReadInteger(PR.Current(), nbitems);
  if (sb && (nbitems > 0))
  {

    Message_Msg Msg183("XSTEP_183");

    tempVertices = new NCollection_HArray1<gp_XYZ>(1, nbitems);

    gp_XYZ anXYZ;
    for (int i = 1; i <= nbitems; i++)
    {

      if (PR.ReadXYZ(PR.CurrentList(1, 3), Msg183, anXYZ))
        tempVertices->SetValue(i, anXYZ);
    }
  }
  else
  {
    Message_Msg Msg182("XSTEP_182");
    PR.SendFail(Msg182);
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  if (nbitems > 0)
    ent->Init(tempVertices);
}

void IGESSolid_ToolVertexList::WriteOwnParams(const occ::handle<IGESSolid_VertexList>& ent,
                                              IGESData_IGESWriter&                     IW) const
{
  int nbitems = ent->NbVertices();
  int i;

  IW.Send(nbitems);
  for (i = 1; i <= nbitems; i++)
  {
    IW.Send(ent->Vertex(i).X());
    IW.Send(ent->Vertex(i).Y());
    IW.Send(ent->Vertex(i).Z());
  }
}

void IGESSolid_ToolVertexList::OwnShared(const occ::handle<IGESSolid_VertexList>&,
                                         Interface_EntityIterator&) const
{
}

void IGESSolid_ToolVertexList::OwnCopy(const occ::handle<IGESSolid_VertexList>& another,
                                       const occ::handle<IGESSolid_VertexList>& ent,
                                       Interface_CopyTool&) const
{
  int nbitems, i;

  nbitems = another->NbVertices();
  occ::handle<NCollection_HArray1<gp_XYZ>> tempVertices =
    new NCollection_HArray1<gp_XYZ>(1, nbitems);

  for (i = 1; i <= nbitems; i++)
  {
    tempVertices->SetValue(i, another->Vertex(i).XYZ());
  }
  ent->Init(tempVertices);
}

IGESData_DirChecker IGESSolid_ToolVertexList::DirChecker(
  const occ::handle<IGESSolid_VertexList>&) const
{
  IGESData_DirChecker DC(502, 1);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);

  DC.SubordinateStatusRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolVertexList::OwnCheck(const occ::handle<IGESSolid_VertexList>& ent,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>& ach) const
{

  if (ent->NbVertices() <= 0)
  {
    Message_Msg Msg182("XSTEP_182");
    ach->SendFail(Msg182);
  }
}

void IGESSolid_ToolVertexList::OwnDump(const occ::handle<IGESSolid_VertexList>& ent,
                                       const IGESData_IGESDumper&,
                                       Standard_OStream& S,
                                       const int         level) const
{
  S << "IGESSolid_VertexList\n"
    << "Vertices : ";
  IGESData_DumpListXYZL(S, level, 1, ent->NbVertices(), ent->Vertex, ent->Location());
  S << std::endl;
}
