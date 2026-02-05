#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_DimensionedGeometry.hpp>
#include <IGESDimen_ToolDimensionedGeometry.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESDimen_ToolDimensionedGeometry::IGESDimen_ToolDimensionedGeometry() = default;

void IGESDimen_ToolDimensionedGeometry::ReadOwnParams(
  const occ::handle<IGESDimen_DimensionedGeometry>& ent,
  const occ::handle<IGESData_IGESReaderData>&       IR,
  IGESData_ParamReader&                             PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed
  int                                                                tempNbDimen;
  occ::handle<IGESData_IGESEntity>                                   aDimEntity;
  int                                                                nbgeom = 0;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> GeomEntities;

  // clang-format off
  PR.ReadInteger(PR.Current(),"Number of Dimensions",tempNbDimen); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadInteger(PR.Current(),"number of entities",nbgeom); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadEntity(IR,PR.Current(),"Dimension Entity",aDimEntity); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  if (nbgeom > 0)
    PR.ReadEnts(IR,
                PR.CurrentList(nbgeom),
                "Geometry Entities",
                GeomEntities); // szv#4:S4163:12Mar99 `st=` not needed
  /*
      {
        GeomEntities = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1,nbgeom);
        for (int i = 1; i <= nbgeom; i++)
      {
            occ::handle<IGESData_IGESEntity> anentity;
            st = PR.ReadEntity(IR,PR.Current(),"Geometry Entity",anentity);
        if (st) GeomEntities->SetValue(i,anentity);
      }
      }
  */
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbDimen, aDimEntity, GeomEntities);
}

void IGESDimen_ToolDimensionedGeometry::WriteOwnParams(
  const occ::handle<IGESDimen_DimensionedGeometry>& ent,
  IGESData_IGESWriter&                              IW) const
{
  IW.Send(ent->NbDimensions());
  IW.Send(ent->NbGeometryEntities());
  IW.Send(ent->DimensionEntity());
  for (int upper = ent->NbGeometryEntities(), i = 1; i <= upper; i++)
    IW.Send(ent->GeometryEntity(i));
}

void IGESDimen_ToolDimensionedGeometry::OwnShared(
  const occ::handle<IGESDimen_DimensionedGeometry>& ent,
  Interface_EntityIterator&                         iter) const
{
  iter.GetOneItem(ent->DimensionEntity());
  for (int upper = ent->NbGeometryEntities(), i = 1; i <= upper; i++)
    iter.GetOneItem(ent->GeometryEntity(i));
}

void IGESDimen_ToolDimensionedGeometry::OwnCopy(
  const occ::handle<IGESDimen_DimensionedGeometry>& another,
  const occ::handle<IGESDimen_DimensionedGeometry>& ent,
  Interface_CopyTool&                               TC) const
{
  int nbDim = another->NbDimensions();
  DeclareAndCast(IGESData_IGESEntity, anentity, TC.Transferred(another->DimensionEntity()));
  int upper = another->NbGeometryEntities();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> EntArray =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, upper);
  for (int i = 1; i <= upper; i++)
  {
    DeclareAndCast(IGESData_IGESEntity, myentity, TC.Transferred(another->GeometryEntity(i)));
    EntArray->SetValue(i, myentity);
  }
  ent->Init(nbDim, anentity, EntArray);
}

bool IGESDimen_ToolDimensionedGeometry::OwnCorrect(
  const occ::handle<IGESDimen_DimensionedGeometry>& ent) const
{
  if (ent->NbDimensions() == 1)
    return false;
  //  force NbDimensions to 1 -> reconstruct
  int                                                                nb = ent->NbGeometryEntities();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> EntArray =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nb);
  for (int i = 1; i <= nb; i++)
    EntArray->SetValue(i, ent->GeometryEntity(i));
  ent->Init(1, ent->DimensionEntity(), EntArray);
  return true;
}

IGESData_DirChecker IGESDimen_ToolDimensionedGeometry::DirChecker(
  const occ::handle<IGESDimen_DimensionedGeometry>& /* ent */) const
{
  IGESData_DirChecker DC(402, 13); // type no = 402; form no. = 13
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDimen_ToolDimensionedGeometry::OwnCheck(
  const occ::handle<IGESDimen_DimensionedGeometry>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->NbDimensions() != 1)
    ach->AddFail("NbDimensions != 1");
  if (ent->UseFlag() > 3)
    ach->AddFail("Incorrect UseFlag");
}

void IGESDimen_ToolDimensionedGeometry::OwnDump(
  const occ::handle<IGESDimen_DimensionedGeometry>& ent,
  const IGESData_IGESDumper&                        dumper,
  Standard_OStream&                                 S,
  const int                                         level) const
{
  S << "IGESDimen_DimensionedGeometry\n";

  // int lower = 1; //szv#4:S4163:12Mar99 unused
  //  int upper = ent->NbGeometryEntities();

  S << "Number of Dimensions : " << ent->NbDimensions() << "\n"
    << "Dimension Entity : ";
  dumper.Dump(ent->DimensionEntity(), S, (level <= 4) ? 0 : 1);
  S << "\n"
    << "Geometry Entities : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbGeometryEntities(), ent->GeometryEntity);
  S << std::endl;
}
