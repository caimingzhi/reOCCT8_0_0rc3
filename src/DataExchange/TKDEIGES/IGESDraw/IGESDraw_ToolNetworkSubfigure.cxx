#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDraw_NetworkSubfigure.hpp>
#include <IGESDraw_NetworkSubfigureDef.hpp>
#include <IGESDraw_ToolNetworkSubfigure.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>
#include <TCollection_HAsciiString.hpp>

IGESDraw_ToolNetworkSubfigure::IGESDraw_ToolNetworkSubfigure() = default;

void IGESDraw_ToolNetworkSubfigure::ReadOwnParams(const occ::handle<IGESDraw_NetworkSubfigure>& ent,
                                                  const occ::handle<IGESData_IGESReaderData>&   IR,
                                                  IGESData_ParamReader& PR) const
{
  // bool                           st; //szv#4:S4163:12Mar99 not needed
  int nbval;

  occ::handle<IGESDraw_NetworkSubfigureDef>                            definition;
  gp_XYZ                                                               translation;
  gp_XYZ                                                               scale;
  int                                                                  typeflag;
  occ::handle<TCollection_HAsciiString>                                designator;
  occ::handle<IGESGraph_TextDisplayTemplate>                           textTemplate;
  occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>> connectPoints;

  double scaleX;
  double scaleY;
  double scaleZ;

  // Reading definition(Instance of NetworkSubfigureDef)
  PR.ReadEntity(IR,
                PR.Current(),
                "Instance of NetworkSubfigureDef",
                // clang-format off
		STANDARD_TYPE(IGESDraw_NetworkSubfigureDef), definition); //szv#4:S4163:12Mar99 `st=` not needed

  // Reading translation(XYZ)
  PR.ReadXYZ( PR.CurrentList(1, 3), "Translation data", translation); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on

  // Reading scale(XYZ)
  if (PR.DefinedElseSkip())                                // Reading scale(X)
    PR.ReadReal(PR.Current(), "Scale factors(X)", scaleX); // szv#4:S4163:12Mar99 `st=` not needed
  else
    scaleX = 1.0; // Default Value

  if (PR.DefinedElseSkip())                                // Reading scale(Y)
    PR.ReadReal(PR.Current(), "Scale factors(Y)", scaleY); // szv#4:S4163:12Mar99 `st=` not needed
  else
    scaleY = scaleX; // Default Value

  if (PR.DefinedElseSkip())                                // Reading scale(Z)
    PR.ReadReal(PR.Current(), "Scale factors(Z)", scaleZ); // szv#4:S4163:12Mar99 `st=` not needed
  else
    scaleZ = scaleX; // Default Value

  scale.SetCoord(scaleX, scaleY, scaleZ);

  if (PR.DefinedElseSkip())                              // Reading typeflag(Integer)
    PR.ReadInteger(PR.Current(), "Type flag", typeflag); // szv#4:S4163:12Mar99 `st=` not needed
  else
    typeflag = 0; // Default Value

  // Reading designator(String)
  if (PR.DefinedElseSkip())
    // clang-format off
    PR.ReadText(PR.Current(), "Primary reference designator", designator); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on
  else
    PR.AddWarning("Primary reference designator : Null definition");

  // Reading textTemplate(Instance of TextDisplayTemplate or Null)
  bool st = PR.ReadEntity(IR,
                          PR.Current(),
                          "Instance of TextDisplayTemplate",
                          STANDARD_TYPE(IGESGraph_TextDisplayTemplate),
                          textTemplate,
                          true);

  // Reading nbval(Integer)
  if (PR.DefinedElseSkip())
    // clang-format off
    st = PR.ReadInteger(PR.Current(),"Count of Connect Points", nbval); //szv#4:S4163:12Mar99 `st=` not needed
  // clang-format on
  else
    nbval = 0;
  if (st && nbval > 0)
  {
    // Reading connectPoints(HArray1OfConnectPoint)
    connectPoints = new NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>(1, nbval);
    occ::handle<IGESDraw_ConnectPoint> tempConnectPoint;
    for (int i = 1; i <= nbval; i++)
    {
      // st = PR.ReadEntity(IR, PR.Current(), "ConnectPoint entity",
      // STANDARD_TYPE(IGESDraw_ConnectPoint),tempConnectPoint,
      // true); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadEntity(IR,
                        PR.Current(),
                        "ConnectPoint entity",
                        STANDARD_TYPE(IGESDraw_ConnectPoint),
                        tempConnectPoint,
                        true))
        connectPoints->SetValue(i, tempConnectPoint);
    }
  }
  else if (nbval < 0)
    PR.AddFail("Count of Connect point entities : Less than Zero");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(definition, translation, scale, typeflag, designator, textTemplate, connectPoints);
}

void IGESDraw_ToolNetworkSubfigure::WriteOwnParams(
  const occ::handle<IGESDraw_NetworkSubfigure>& ent,
  IGESData_IGESWriter&                          IW) const
{
  IW.Send(ent->SubfigureDefinition());
  IW.Send(ent->Translation().X());
  IW.Send(ent->Translation().Y());
  IW.Send(ent->Translation().Z());
  IW.Send(ent->ScaleFactors().X());
  IW.Send(ent->ScaleFactors().Y());
  IW.Send(ent->ScaleFactors().Z());
  IW.Send(ent->TypeFlag());
  IW.Send(ent->ReferenceDesignator());

  IW.Send(ent->DesignatorTemplate());

  IW.Send(ent->NbConnectPoints());

  int Up = ent->NbConnectPoints();
  for (int i = 1; i <= Up; i++)
    IW.Send(ent->ConnectPoint(i));
}

void IGESDraw_ToolNetworkSubfigure::OwnShared(const occ::handle<IGESDraw_NetworkSubfigure>& ent,
                                              Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->SubfigureDefinition());
  iter.GetOneItem(ent->DesignatorTemplate());
  int Up = ent->NbConnectPoints();
  for (int i = 1; i <= Up; i++)
    iter.GetOneItem(ent->ConnectPoint(i));
}

void IGESDraw_ToolNetworkSubfigure::OwnCopy(const occ::handle<IGESDraw_NetworkSubfigure>& another,
                                            const occ::handle<IGESDraw_NetworkSubfigure>& ent,
                                            Interface_CopyTool&                           TC) const
{
  int                                                                  nbval;
  gp_XYZ                                                               translation;
  gp_XYZ                                                               scale;
  int                                                                  typeflag;
  occ::handle<TCollection_HAsciiString>                                designator;
  occ::handle<NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>> connectPoints;

  nbval = another->NbConnectPoints();

  DeclareAndCast(IGESDraw_NetworkSubfigureDef,
                 definition,
                 TC.Transferred(another->SubfigureDefinition()));

  translation = another->Translation();
  scale       = another->ScaleFactors();
  typeflag    = another->TypeFlag();
  if (!another->ReferenceDesignator().IsNull())
    designator = new TCollection_HAsciiString(another->ReferenceDesignator());

  DeclareAndCast(IGESGraph_TextDisplayTemplate,
                 textTemplate,
                 TC.Transferred(another->DesignatorTemplate()));

  if (nbval > 0)
    connectPoints = new NCollection_HArray1<occ::handle<IGESDraw_ConnectPoint>>(1, nbval);
  for (int i = 1; i <= nbval; i++)
  {
    DeclareAndCast(IGESDraw_ConnectPoint,
                   tempconnectPoint,
                   TC.Transferred(another->ConnectPoint(i)));
    connectPoints->SetValue(i, tempconnectPoint);
  }

  ent->Init(definition, translation, scale, typeflag, designator, textTemplate, connectPoints);
}

IGESData_DirChecker IGESDraw_ToolNetworkSubfigure::DirChecker(
  const occ::handle<IGESDraw_NetworkSubfigure>& /*ent*/) const
{
  IGESData_DirChecker DC(420, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  return DC;
}

void IGESDraw_ToolNetworkSubfigure::OwnCheck(const occ::handle<IGESDraw_NetworkSubfigure>& ent,
                                             const Interface_ShareTool&,
                                             occ::handle<Interface_Check>& ach) const
{
  if (ent->TypeFlag() != 0 && ent->TypeFlag() != 1 && ent->TypeFlag() != 2)
    ach->AddFail("Type Flag : Value != 0/1/2");
  if (ent->NbConnectPoints() != ent->SubfigureDefinition()->NbPointEntities())
    ach->AddFail("Count of associated Connect Points inconsistent with Definition");
  if (ent->ReferenceDesignator().IsNull())
    ach->AddFail("Primary Reference Designator : not defined");
}

void IGESDraw_ToolNetworkSubfigure::OwnDump(const occ::handle<IGESDraw_NetworkSubfigure>& ent,
                                            const IGESData_IGESDumper&                    dumper,
                                            Standard_OStream&                             S,
                                            const int level) const
{
  int sublevel = (level <= 4) ? 0 : 1;

  S << "IGESDraw_NetworkSubfigure\n"
    << "Network Subfigure Definition Entity : ";
  dumper.Dump(ent->SubfigureDefinition(), S, sublevel);
  S << "\nTranslation Data : ";
  IGESData_DumpXYZL(S, level, ent->Translation(), ent->Location());
  S << "\nScale Factors    : ";
  IGESData_DumpXYZ(S, ent->ScaleFactors());
  S << "\nType Flag : " << ent->TypeFlag() << "\n"
    << "Primary Reference Designator : ";
  IGESData_DumpString(S, ent->ReferenceDesignator());
  S << "\nText Display Template Entity : ";
  dumper.Dump(ent->DesignatorTemplate(), S, sublevel);
  S << "\nConnect Points  : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbConnectPoints(), ent->ConnectPoint);
  S << std::endl;
}
