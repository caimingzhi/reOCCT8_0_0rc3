#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESAppli_ToolNode.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>

IGESAppli_ToolNode::IGESAppli_ToolNode() = default;

void IGESAppli_ToolNode::ReadOwnParams(const occ::handle<IGESAppli_Node>&          ent,
                                       const occ::handle<IGESData_IGESReaderData>& IR,
                                       IGESData_ParamReader&                       PR) const
{
  gp_XYZ                                     tempCoordinates;
  occ::handle<IGESGeom_TransformationMatrix> tempSystem;

  PR.ReadXYZ(PR.CurrentList(1, 3), "Coordinates of Node (XYZ)", tempCoordinates);

  if (PR.DefinedElseSkip())
    PR.ReadEntity(IR,
                  PR.Current(),
                  "Transformation Matrix",
                  STANDARD_TYPE(IGESGeom_TransformationMatrix),
                  tempSystem,
                  true);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempCoordinates, tempSystem);
}

void IGESAppli_ToolNode::WriteOwnParams(const occ::handle<IGESAppli_Node>& ent,
                                        IGESData_IGESWriter&               IW) const
{
  IW.Send(ent->Coord().X());
  IW.Send(ent->Coord().Y());
  IW.Send(ent->Coord().Z());
  IW.Send(ent->System());
}

void IGESAppli_ToolNode::OwnShared(const occ::handle<IGESAppli_Node>& ent,
                                   Interface_EntityIterator&          iter) const
{
  iter.GetOneItem(ent->System());
}

void IGESAppli_ToolNode::OwnCopy(const occ::handle<IGESAppli_Node>& another,
                                 const occ::handle<IGESAppli_Node>& ent,
                                 Interface_CopyTool&                TC) const
{
  gp_XYZ aCoord = (another->Coord()).XYZ();
  DeclareAndCast(IGESGeom_TransformationMatrix, aSystem, TC.Transferred(another->System()));

  ent->Init(aCoord, aSystem);
}

IGESData_DirChecker IGESAppli_ToolNode::DirChecker(const occ::handle<IGESAppli_Node>&) const
{
  IGESData_DirChecker DC(134, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(04);
  return DC;
}

void IGESAppli_ToolNode::OwnCheck(const occ::handle<IGESAppli_Node>& ent,
                                  const Interface_ShareTool&,
                                  occ::handle<Interface_Check>& ach) const
{
  if (!ent->HasSubScriptNumber())
    ach->AddFail("SubScript Number expected (for Node Number) not present");
  if (!ent->HasTransf())
    ach->AddFail("Transformation Matrix expected, not present");
  if (!ent->System().IsNull())
    if (ent->System()->FormNumber() < 10)
      ach->AddFail("System : Incorrect FormNumber (not 10-11-12)");
}

void IGESAppli_ToolNode::OwnDump(const occ::handle<IGESAppli_Node>& ent,
                                 const IGESData_IGESDumper&         dumper,
                                 Standard_OStream&                  S,
                                 const int                          level) const
{
  S << "IGESAppli_Node\n";
  S << " Nodal Coords : 1st " << ent->Coord().X() << "  2nd : " << ent->Coord().Y()
    << "  3rd : " << ent->Coord().Z() << "\n";
  S << "Nodal Displacement Coordinate System : ";
  if (!ent->System().IsNull())
    dumper.Dump(ent->System(), S, level);
  else
    S << "Global Cartesian Coordinate System (default)";
  S << std::endl;
}
