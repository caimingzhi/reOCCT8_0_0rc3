#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_SolidAssembly.hpp>
#include <IGESSolid_ToolSolidAssembly.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>

IGESSolid_ToolSolidAssembly::IGESSolid_ToolSolidAssembly() = default;

void IGESSolid_ToolSolidAssembly::ReadOwnParams(const occ::handle<IGESSolid_SolidAssembly>& ent,
                                                const occ::handle<IGESData_IGESReaderData>& IR,
                                                IGESData_ParamReader& PR) const
{

  int nbitems;

  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>           tempItems;
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>> tempMatrices;

  bool st = PR.ReadInteger(PR.Current(), "Number of Items", nbitems);
  if (st && nbitems > 0)
  {
    tempItems    = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nbitems);
    tempMatrices = new NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>(1, nbitems);

    occ::handle<IGESData_IGESEntity> anent;
    int                              i;
    for (i = 1; i <= nbitems; i++)
    {

      if (PR.ReadEntity(IR, PR.Current(), "Solid assembly items", anent))
        tempItems->SetValue(i, anent);
    }

    occ::handle<IGESGeom_TransformationMatrix> amatr;
    for (i = 1; i <= nbitems; i++)
    {

      if (PR.ReadEntity(IR,
                        PR.Current(),
                        "Matrices",
                        STANDARD_TYPE(IGESGeom_TransformationMatrix),
                        amatr,
                        true))
        tempMatrices->SetValue(i, amatr);
    }
  }
  else
    PR.AddFail("Number of Items : Not Positive");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempItems, tempMatrices);
}

void IGESSolid_ToolSolidAssembly::WriteOwnParams(const occ::handle<IGESSolid_SolidAssembly>& ent,
                                                 IGESData_IGESWriter& IW) const
{
  int nbitems = ent->NbItems();
  int i;

  IW.Send(nbitems);
  for (i = 1; i <= nbitems; i++)
    IW.Send(ent->Item(i));
  for (i = 1; i <= nbitems; i++)
    IW.Send(ent->TransfMatrix(i));
}

void IGESSolid_ToolSolidAssembly::OwnShared(const occ::handle<IGESSolid_SolidAssembly>& ent,
                                            Interface_EntityIterator&                   iter) const
{
  int nbitems = ent->NbItems();
  int i;
  for (i = 1; i <= nbitems; i++)
    iter.GetOneItem(ent->Item(i));
  for (i = 1; i <= nbitems; i++)
    iter.GetOneItem(ent->TransfMatrix(i));
}

void IGESSolid_ToolSolidAssembly::OwnCopy(const occ::handle<IGESSolid_SolidAssembly>& another,
                                          const occ::handle<IGESSolid_SolidAssembly>& ent,
                                          Interface_CopyTool&                         TC) const
{
  int                              nbitems, i;
  occ::handle<IGESData_IGESEntity> anent;

  nbitems = another->NbItems();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> tempItems =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nbitems);
  occ::handle<NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>> tempMatrices =
    new NCollection_HArray1<occ::handle<IGESGeom_TransformationMatrix>>(1, nbitems);

  for (i = 1; i <= nbitems; i++)
  {
    DeclareAndCast(IGESData_IGESEntity, localent, TC.Transferred(another->Item(i)));
    tempItems->SetValue(i, localent);
  }
  for (i = 1; i <= nbitems; i++)
  {
    DeclareAndCast(IGESGeom_TransformationMatrix,
                   newlocalent,
                   TC.Transferred(another->TransfMatrix(i)));
    tempMatrices->SetValue(i, newlocalent);
  }

  ent->Init(tempItems, tempMatrices);
}

IGESData_DirChecker IGESSolid_ToolSolidAssembly::DirChecker(
  const occ::handle<IGESSolid_SolidAssembly>&) const
{
  IGESData_DirChecker DC(184, 0, 1);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(2);
  DC.GraphicsIgnored(1);
  return DC;
}

void IGESSolid_ToolSolidAssembly::OwnCheck(const occ::handle<IGESSolid_SolidAssembly>&,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>&) const
{
}

void IGESSolid_ToolSolidAssembly::OwnDump(const occ::handle<IGESSolid_SolidAssembly>& ent,
                                          const IGESData_IGESDumper&                  dumper,
                                          Standard_OStream&                           S,
                                          const int                                   level) const
{

  S << "IGESSolid_SolidAssembly\n"
    << "Items : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbItems(), ent->Item);
  S << "\n"
    << "Matrices : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbItems(), ent->TransfMatrix);
  S << std::endl;
}
