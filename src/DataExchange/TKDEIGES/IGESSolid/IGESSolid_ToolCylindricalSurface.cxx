#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_ToolCylindricalSurface.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESSolid_ToolCylindricalSurface::IGESSolid_ToolCylindricalSurface() = default;

void IGESSolid_ToolCylindricalSurface::ReadOwnParams(
  const occ::handle<IGESSolid_CylindricalSurface>& ent,
  const occ::handle<IGESData_IGESReaderData>&      IR,
  IGESData_ParamReader&                            PR) const
{
  occ::handle<IGESGeom_Point>     tempLocation;
  occ::handle<IGESGeom_Direction> tempAxis;
  occ::handle<IGESGeom_Direction> tempRefdir;
  double                          tempRadius;

  PR.ReadEntity(IR, PR.Current(), "Point on axis", STANDARD_TYPE(IGESGeom_Point), tempLocation);

  PR.ReadEntity(IR, PR.Current(), "Axis direction", STANDARD_TYPE(IGESGeom_Direction), tempAxis);

  PR.ReadReal(PR.Current(), "Radius", tempRadius);

  if (ent->FormNumber() == 1)
    PR.ReadEntity(IR,
                  PR.Current(),
                  "Reference direction",
                  STANDARD_TYPE(IGESGeom_Direction),
                  tempRefdir);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempLocation, tempAxis, tempRadius, tempRefdir);
}

void IGESSolid_ToolCylindricalSurface::WriteOwnParams(
  const occ::handle<IGESSolid_CylindricalSurface>& ent,
  IGESData_IGESWriter&                             IW) const
{
  IW.Send(ent->LocationPoint());
  IW.Send(ent->Axis());
  IW.Send(ent->Radius());
  if (ent->IsParametrised())
    IW.Send(ent->ReferenceDir());
}

void IGESSolid_ToolCylindricalSurface::OwnShared(
  const occ::handle<IGESSolid_CylindricalSurface>& ent,
  Interface_EntityIterator&                        iter) const
{
  iter.GetOneItem(ent->LocationPoint());
  iter.GetOneItem(ent->Axis());
  iter.GetOneItem(ent->ReferenceDir());
}

void IGESSolid_ToolCylindricalSurface::OwnCopy(
  const occ::handle<IGESSolid_CylindricalSurface>& another,
  const occ::handle<IGESSolid_CylindricalSurface>& ent,
  Interface_CopyTool&                              TC) const
{
  double tempRadius;

  DeclareAndCast(IGESGeom_Point, tempLocation, TC.Transferred(another->LocationPoint()));
  DeclareAndCast(IGESGeom_Direction, tempAxis, TC.Transferred(another->Axis()));
  tempRadius = another->Radius();
  if (another->IsParametrised())
  {
    DeclareAndCast(IGESGeom_Direction, tempRefdir, TC.Transferred(another->ReferenceDir()));
    ent->Init(tempLocation, tempAxis, tempRadius, tempRefdir);
  }
  else
  {
    occ::handle<IGESGeom_Direction> tempRefdir;
    ent->Init(tempLocation, tempAxis, tempRadius, tempRefdir);
  }
}

IGESData_DirChecker IGESSolid_ToolCylindricalSurface::DirChecker(
  const occ::handle<IGESSolid_CylindricalSurface>&) const
{
  IGESData_DirChecker DC(192, 0, 1);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolCylindricalSurface::OwnCheck(
  const occ::handle<IGESSolid_CylindricalSurface>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->Radius() <= 0.0)
    ach->AddFail("Radius : Value <= 0.0");
  int fn = 0;
  if (ent->IsParametrised())
    fn = 1;
  if (fn != ent->FormNumber())
    ach->AddFail("Parametrised Status Mismatches with Form Number");
}

void IGESSolid_ToolCylindricalSurface::OwnDump(const occ::handle<IGESSolid_CylindricalSurface>& ent,
                                               const IGESData_IGESDumper& dumper,
                                               Standard_OStream&          S,
                                               const int                  level) const
{
  S << "IGESSolid_CylindricalSurface\n";

  int sublevel = (level <= 4) ? 0 : 1;
  S << "Point on axis  : ";
  dumper.Dump(ent->LocationPoint(), S, sublevel);
  S << "\n"
    << "Axis direction : ";
  dumper.Dump(ent->Axis(), S, sublevel);
  S << "\n"
    << "Radius         : " << ent->Radius() << "\n";
  if (ent->IsParametrised())
  {
    S << "Surface is Parametrised  -  Reference direction : ";
    dumper.Dump(ent->ReferenceDir(), S, sublevel);
    S << std::endl;
  }
  else
    S << "Surface is UnParametrised" << std::endl;
}
