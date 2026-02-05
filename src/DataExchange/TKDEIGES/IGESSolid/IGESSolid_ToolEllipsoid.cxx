#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_Ellipsoid.hpp>
#include <IGESSolid_ToolEllipsoid.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>

IGESSolid_ToolEllipsoid::IGESSolid_ToolEllipsoid() = default;

void IGESSolid_ToolEllipsoid::ReadOwnParams(const occ::handle<IGESSolid_Ellipsoid>& ent,
                                            const occ::handle<IGESData_IGESReaderData>& /* IR */,
                                            IGESData_ParamReader& PR) const
{
  gp_XYZ tempSize, tempCenter, tempXAxis, tempZAxis;
  // bool st; //szv#4:S4163:12Mar99 not needed
  double tempreal;

  PR.ReadXYZ(PR.CurrentList(1, 3), "Size", tempSize); // szv#4:S4163:12Mar99 `st=` not needed

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Center Point (X)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Center Point (X)", tempreal))
      tempCenter.SetX(tempreal);
  }
  else
    tempCenter.SetX(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Center Point (Y)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Center Point (Y)", tempreal))
      tempCenter.SetY(tempreal);
  }
  else
    tempCenter.SetY(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Center Point (Z)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Center Point (Z)", tempreal))
      tempCenter.SetZ(tempreal);
  }
  else
    tempCenter.SetZ(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Local X axis (I)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Local X axis (I)", tempreal))
      tempXAxis.SetX(tempreal);
  }
  else
    tempXAxis.SetX(1.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Local X axis (J)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Local X axis (J)", tempreal))
      tempXAxis.SetY(tempreal);
  }
  else
    tempXAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Local X axis (K)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Local X axis (K)", tempreal))
      tempXAxis.SetZ(tempreal);
  }
  else
    tempXAxis.SetZ(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Local Z axis (I)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Local Z axis (I)", tempreal))
      tempZAxis.SetX(tempreal);
  }
  else
    tempZAxis.SetX(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Local Z axis (J)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Local Z axis (J)", tempreal))
      tempZAxis.SetY(tempreal);
  }
  else
    tempZAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
  {
    // st = PR.ReadReal(PR.Current(), "Local Z axis (K)", tempreal); //szv#4:S4163:12Mar99 moved in
    // if
    if (PR.ReadReal(PR.Current(), "Local Z axis (K)", tempreal))
      tempZAxis.SetZ(tempreal);
  }
  else
    tempZAxis.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempSize, tempCenter, tempXAxis, tempZAxis);
  double eps = 1.E-05;
  if (!tempXAxis.IsEqual(ent->XAxis().XYZ(), eps))
    PR.AddWarning("XAxis poorly unitary, normalized");
  if (!tempZAxis.IsEqual(ent->ZAxis().XYZ(), eps))
    PR.AddWarning("ZAxis poorly unitary, normalized");
}

void IGESSolid_ToolEllipsoid::WriteOwnParams(const occ::handle<IGESSolid_Ellipsoid>& ent,
                                             IGESData_IGESWriter&                    IW) const
{
  IW.Send(ent->Size().X());
  IW.Send(ent->Size().Y());
  IW.Send(ent->Size().Z());
  IW.Send(ent->Center().X());
  IW.Send(ent->Center().Y());
  IW.Send(ent->Center().Z());
  IW.Send(ent->XAxis().X());
  IW.Send(ent->XAxis().Y());
  IW.Send(ent->XAxis().Z());
  IW.Send(ent->ZAxis().X());
  IW.Send(ent->ZAxis().Y());
  IW.Send(ent->ZAxis().Z());
}

void IGESSolid_ToolEllipsoid::OwnShared(const occ::handle<IGESSolid_Ellipsoid>& /* ent */,
                                        Interface_EntityIterator& /* iter */) const
{
}

void IGESSolid_ToolEllipsoid::OwnCopy(const occ::handle<IGESSolid_Ellipsoid>& another,
                                      const occ::handle<IGESSolid_Ellipsoid>& ent,
                                      Interface_CopyTool& /* TC */) const
{
  ent->Init(another->Size(),
            another->Center().XYZ(),
            another->XAxis().XYZ(),
            another->ZAxis().XYZ());
}

IGESData_DirChecker IGESSolid_ToolEllipsoid::DirChecker(
  const occ::handle<IGESSolid_Ellipsoid>& /* ent */) const
{
  IGESData_DirChecker DC(168, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired(0);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESSolid_ToolEllipsoid::OwnCheck(const occ::handle<IGESSolid_Ellipsoid>& ent,
                                       const Interface_ShareTool&,
                                       occ::handle<Interface_Check>& ach) const
{
  double eps    = 1.E-04;
  double prosca = ent->XAxis().Dot(ent->ZAxis());
  if (prosca < -eps || prosca > eps)
    ach->AddFail("Local Z axis : Not orthogonal to X axis");
  if (ent->Size().X() < ent->Size().Y() || ent->Size().Y() < ent->Size().Z()
      || ent->Size().Z() <= 0)
    ach->AddFail("Size : The values does not satisfy LX >= LY >= LZ > 0");
}

void IGESSolid_ToolEllipsoid::OwnDump(const occ::handle<IGESSolid_Ellipsoid>& ent,
                                      const IGESData_IGESDumper& /* dumper */,
                                      Standard_OStream& S,
                                      const int         level) const
{
  S << "IGESSolid_Ellipsoid\n"
    << "Size   : ";
  IGESData_DumpXYZ(S, ent->Size());
  S << "\nCenter : ";
  IGESData_DumpXYZL(S, level, ent->Center(), ent->Location());
  S << "\nXAxis  : ";
  IGESData_DumpXYZL(S, level, ent->XAxis(), ent->VectorLocation());
  S << "\nZAxis  : ";
  IGESData_DumpXYZL(S, level, ent->ZAxis(), ent->VectorLocation());
  S << std::endl;
}
