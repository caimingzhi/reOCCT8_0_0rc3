#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_Cylinder.hpp>
#include <IGESSolid_ToolCylinder.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESSolid_ToolCylinder::IGESSolid_ToolCylinder() = default;

void IGESSolid_ToolCylinder::ReadOwnParams(const occ::handle<IGESSolid_Cylinder>& ent,
                                           const occ::handle<IGESData_IGESReaderData>&,
                                           IGESData_ParamReader& PR) const
{
  double tempHeight, tempRadius, tempreal;
  gp_XYZ tempCenter, tempAxis;

  PR.ReadReal(PR.Current(), "Height", tempHeight);

  PR.ReadReal(PR.Current(), "Radius", tempRadius);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Face center (X)", tempreal))
      tempCenter.SetX(tempreal);
  }
  else
    tempCenter.SetX(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Face center (Y)", tempreal))
      tempCenter.SetY(tempreal);
  }
  else
    tempCenter.SetY(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Face center (Z)", tempreal))
      tempCenter.SetZ(tempreal);
  }
  else
    tempCenter.SetZ(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Axis direction (I)", tempreal))
      tempAxis.SetX(tempreal);
  }
  else
    tempAxis.SetX(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Axis direction (J)", tempreal))
      tempAxis.SetY(tempreal);
  }
  else
    tempAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
  {

    if (PR.ReadReal(PR.Current(), "Axis direction (K)", tempreal))
      tempAxis.SetZ(tempreal);
  }
  else
    tempAxis.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempHeight, tempRadius, tempCenter, tempAxis);
  double eps = 1.E-05;
  if (!tempAxis.IsEqual(ent->Axis().XYZ(), eps))
    PR.AddWarning("Axis poorly unitary, normalized");
}

void IGESSolid_ToolCylinder::WriteOwnParams(const occ::handle<IGESSolid_Cylinder>& ent,
                                            IGESData_IGESWriter&                   IW) const
{
  IW.Send(ent->Height());
  IW.Send(ent->Radius());
  IW.Send(ent->FaceCenter().X());
  IW.Send(ent->FaceCenter().Y());
  IW.Send(ent->FaceCenter().Z());
  IW.Send(ent->Axis().X());
  IW.Send(ent->Axis().Y());
  IW.Send(ent->Axis().Z());
}

void IGESSolid_ToolCylinder::OwnShared(const occ::handle<IGESSolid_Cylinder>&,
                                       Interface_EntityIterator&) const
{
}

void IGESSolid_ToolCylinder::OwnCopy(const occ::handle<IGESSolid_Cylinder>& another,
                                     const occ::handle<IGESSolid_Cylinder>& ent,
                                     Interface_CopyTool&) const
{
  ent->Init(another->Height(),
            another->Radius(),
            another->FaceCenter().XYZ(),
            another->Axis().XYZ());
}

IGESData_DirChecker IGESSolid_ToolCylinder::DirChecker(const occ::handle<IGESSolid_Cylinder>&) const
{
  IGESData_DirChecker DC(154, 0);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(0);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolCylinder::OwnCheck(const occ::handle<IGESSolid_Cylinder>& ent,
                                      const Interface_ShareTool&,
                                      occ::handle<Interface_Check>& ach) const
{
  if (ent->Height() <= 0.0)
    ach->AddFail("Height : Value < 0");
  if (ent->Radius() <= 0.0)
    ach->AddFail("Radius : Value < 0");
}

void IGESSolid_ToolCylinder::OwnDump(const occ::handle<IGESSolid_Cylinder>& ent,
                                     const IGESData_IGESDumper&,
                                     Standard_OStream& S,
                                     const int         level) const
{

  S << "IGESSolid_Cylinder\n"
    << "Height : " << ent->Height() << "  "
    << "Radius : " << ent->Radius() << "\n"
    << "Center : ";
  IGESData_DumpXYZL(S, level, ent->FaceCenter(), ent->Location());
  S << "\nAxis : ";
  IGESData_DumpXYZL(S, level, ent->Axis(), ent->VectorLocation());
  S << std::endl;
}
