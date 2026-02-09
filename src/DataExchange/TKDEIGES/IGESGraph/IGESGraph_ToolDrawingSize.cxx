#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_DrawingSize.hpp>
#include <IGESGraph_ToolDrawingSize.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESGraph_ToolDrawingSize::IGESGraph_ToolDrawingSize() = default;

void IGESGraph_ToolDrawingSize::ReadOwnParams(const occ::handle<IGESGraph_DrawingSize>& ent,
                                              const occ::handle<IGESData_IGESReaderData>&,
                                              IGESData_ParamReader& PR) const
{

  int    nbPropertyValues;
  double xSize;
  double ySize;

  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues);
  if (nbPropertyValues != 2)
    PR.AddFail("No. of Property values : Value is not 2");

  PR.ReadReal(PR.Current(), "Drawing extent along +ve XD axis", xSize);

  PR.ReadReal(PR.Current(), "Drawing extent along +ve YD axis", ySize);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbPropertyValues, xSize, ySize);
}

void IGESGraph_ToolDrawingSize::WriteOwnParams(const occ::handle<IGESGraph_DrawingSize>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->XSize());
  IW.Send(ent->YSize());
}

void IGESGraph_ToolDrawingSize::OwnShared(const occ::handle<IGESGraph_DrawingSize>&,
                                          Interface_EntityIterator&) const
{
}

void IGESGraph_ToolDrawingSize::OwnCopy(const occ::handle<IGESGraph_DrawingSize>& another,
                                        const occ::handle<IGESGraph_DrawingSize>& ent,
                                        Interface_CopyTool&) const
{
  ent->Init(2, another->XSize(), another->YSize());
}

bool IGESGraph_ToolDrawingSize::OwnCorrect(const occ::handle<IGESGraph_DrawingSize>& ent) const
{
  bool res = (ent->NbPropertyValues() != 2);
  if (res)
    ent->Init(2, ent->XSize(), ent->YSize());
  return res;
}

IGESData_DirChecker IGESGraph_ToolDrawingSize::DirChecker(
  const occ::handle<IGESGraph_DrawingSize>&) const
{
  IGESData_DirChecker DC(406, 16);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolDrawingSize::OwnCheck(const occ::handle<IGESGraph_DrawingSize>& ent,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 2)
    ach->AddFail("No. of Property values : Value != 2");
}

void IGESGraph_ToolDrawingSize::OwnDump(const occ::handle<IGESGraph_DrawingSize>& ent,
                                        const IGESData_IGESDumper&,
                                        Standard_OStream& S,
                                        const int) const
{
  S << "IGESGraph_DrawingSize\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "Drawing extent along positive X-axis : " << ent->XSize() << "\n"
    << "Drawing extent along positive Y-axis : " << ent->YSize() << "\n"
    << std::endl;
}
