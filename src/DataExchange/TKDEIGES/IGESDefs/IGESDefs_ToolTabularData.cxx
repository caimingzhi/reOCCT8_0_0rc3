#include <IGESBasic_HArray1OfHArray1OfReal.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDefs_TabularData.hpp>
#include <IGESDefs_ToolTabularData.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESDefs_ToolTabularData::IGESDefs_ToolTabularData() = default;

void IGESDefs_ToolTabularData::ReadOwnParams(const occ::handle<IGESDefs_TabularData>& ent,
                                             const occ::handle<IGESData_IGESReaderData>&,
                                             IGESData_ParamReader& PR) const
{
  int                                           nbProps;
  int                                           propType;
  int                                           nbDeps;
  int                                           nbIndeps;
  occ::handle<NCollection_HArray1<int>>         typesInd;
  occ::handle<NCollection_HArray1<int>>         nbValuesInd;
  occ::handle<IGESBasic_HArray1OfHArray1OfReal> valuesInd;
  occ::handle<IGESBasic_HArray1OfHArray1OfReal> valuesDep;

  int i;

  PR.ReadInteger(PR.Current(), "Number of Property values", nbProps);

  PR.ReadInteger(PR.Current(), "Property type", propType);

  bool st = PR.ReadInteger(PR.Current(), "No. of dependent variables", nbDeps);
  if (st && nbDeps > 0)
    valuesDep = new IGESBasic_HArray1OfHArray1OfReal(1, nbDeps);

  st = PR.ReadInteger(PR.Current(), "No. of Independent variables", nbIndeps);
  if (st && nbIndeps > 0)
  {
    valuesInd   = new IGESBasic_HArray1OfHArray1OfReal(1, nbIndeps);
    typesInd    = new NCollection_HArray1<int>(1, nbIndeps);
    nbValuesInd = new NCollection_HArray1<int>(1, nbIndeps);
  }

  PR.ReadInts(PR.CurrentList(nbIndeps), "Type of independent variables", typesInd);

  PR.ReadInts(PR.CurrentList(nbIndeps),

              "No. of values of independent variables",
              nbValuesInd);

  for (i = 1; i <= nbIndeps; i++)
  {
    occ::handle<NCollection_HArray1<double>> tarr;
    int                                      nb = nbValuesInd->Value(i), j;
    if (nb > 0)
    {
      tarr = new NCollection_HArray1<double>(1, nb);
      for (j = 1; j <= nb; j++)
      {
        double treal;
        PR.ReadReal(PR.Current(), "Value of independent variable", treal);
        tarr->SetValue(j, treal);
      }
    }
    valuesInd->SetValue(i, tarr);
  }

  int curnum = PR.CurrentNumber();
  int nbpars = PR.NbParams();
  int nbd    = 0;
  for (i = curnum; i <= nbpars; i++)
  {
    if (PR.ParamType(i) != Interface_ParamReal)
      break;
    nbd = i - curnum + 1;
  }
  occ::handle<NCollection_HArray1<double>> somedeps;
  if (nbd > 0)
    somedeps = new NCollection_HArray1<double>(1, nbd);
  for (i = 1; i <= nbd; i++)
  {
    double treal;

    PR.ReadReal(PR.Current(), "Value of dependent variable", treal);

    somedeps->SetValue(i, treal);
  }
  if (nbDeps > 0)
    valuesDep->SetValue(1, somedeps);
  else
    PR.AddWarning("Some Real remain while no dependent value is defined");

  nbProps = PR.CurrentNumber() - 2;

  PR.AddWarning("Don't know exactly how to read dependent values ...");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbProps, propType, typesInd, nbValuesInd, valuesInd, valuesDep);
}

void IGESDefs_ToolTabularData::WriteOwnParams(const occ::handle<IGESDefs_TabularData>& ent,
                                              IGESData_IGESWriter&                     IW) const
{
  int i, nbIndeps = ent->NbIndependents();
  int j, nbDeps   = ent->NbDependents();
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->PropertyType());
  IW.Send(nbDeps);
  IW.Send(nbIndeps);
  for (i = 1; i <= nbIndeps; i++)
    IW.Send(ent->TypeOfIndependents(i));
  for (i = 1; i <= nbIndeps; i++)
    IW.Send(ent->NbValues(i));
  for (i = 1; i <= nbIndeps; i++)
    for (j = 1; j <= ent->NbValues(i); j++)
      IW.Send(ent->IndependentValue(i, j));

  if (nbDeps == 0)
    return;
  occ::handle<NCollection_HArray1<double>> deps = ent->DependentValues(1);
  for (i = 1; i <= deps->Length(); i++)
    IW.Send(deps->Value(i));
}

void IGESDefs_ToolTabularData::OwnShared(const occ::handle<IGESDefs_TabularData>&,
                                         Interface_EntityIterator&) const
{
}

void IGESDefs_ToolTabularData::OwnCopy(const occ::handle<IGESDefs_TabularData>& another,
                                       const occ::handle<IGESDefs_TabularData>& ent,
                                       Interface_CopyTool&) const
{
  int                                   nbProps     = another->NbPropertyValues();
  int                                   propType    = another->PropertyType();
  int                                   nbDeps      = another->NbDependents();
  int                                   nbIndeps    = another->NbIndependents();
  occ::handle<NCollection_HArray1<int>> typesInd    = new NCollection_HArray1<int>(1, nbIndeps);
  occ::handle<NCollection_HArray1<int>> nbValuesInd = new NCollection_HArray1<int>(1, nbIndeps);
  occ::handle<IGESBasic_HArray1OfHArray1OfReal> valuesInd =
    new IGESBasic_HArray1OfHArray1OfReal(1, nbIndeps);
  occ::handle<IGESBasic_HArray1OfHArray1OfReal> valuesDep =
    new IGESBasic_HArray1OfHArray1OfReal(1, nbDeps);
  int i;
  for (i = 1; i <= nbIndeps; i++)
  {
    int j, nval;
    typesInd->SetValue(i, another->TypeOfIndependents(i));
    nval = another->NbValues(i);
    nbValuesInd->SetValue(i, nval);
    occ::handle<NCollection_HArray1<double>> tmparr = new NCollection_HArray1<double>(1, nval);
    for (j = 1; j <= nval; j++)
      tmparr->SetValue(j, another->IndependentValue(i, j));
    valuesInd->SetValue(i, tmparr);
  }

  ent->Init(nbProps, propType, typesInd, nbValuesInd, valuesInd, valuesDep);
}

IGESData_DirChecker IGESDefs_ToolTabularData::DirChecker(
  const occ::handle<IGESDefs_TabularData>&) const
{
  IGESData_DirChecker DC(406, 11);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);

  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDefs_ToolTabularData::OwnCheck(const occ::handle<IGESDefs_TabularData>&,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>&) const
{
}

void IGESDefs_ToolTabularData::OwnDump(const occ::handle<IGESDefs_TabularData>& ent,
                                       const IGESData_IGESDumper&,
                                       Standard_OStream& S,
                                       const int         level) const
{
  int nbIndeps = ent->NbIndependents();
  int nbDeps   = ent->NbDependents();

  S << "IGESDefs_TabularData\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "Property type : " << ent->PropertyType() << "\n"
    << "No. of Dependent variables    : " << nbDeps << "\n"
    << "No. of Independent variables  : " << nbIndeps << "\n"
    << "Type of independent variables : ";
  IGESData_DumpVals(S, level, 1, nbIndeps, ent->TypeOfIndependents);
  S << "\nNumber of values of independent variables : ";
  IGESData_DumpVals(S, level, 1, nbIndeps, ent->NbValues);

  S << std::endl << "Values of the independent variable : ";
  if (level < 5)
    S << " [ask level > 4]";
  else
  {
    for (int ind = 1; ind <= nbIndeps; ind++)
    {
      S << std::endl << "[" << ind << "]:";
      int nbi = ent->NbValues(ind);
      for (int iv = 1; iv <= nbi; iv++)
        S << " " << ent->IndependentValue(ind, iv);
    }
  }

  S << std::endl << "Values of the dependent variable : ";

  S << "  TO BE DONE" << std::endl;
}
