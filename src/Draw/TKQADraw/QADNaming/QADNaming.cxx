#include <BRep_Tool.hpp>
#include <DBRep.hpp>
#include <DDF.hpp>
#include <gp_Pnt.hpp>
#include <QADNaming.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TNaming_Iterator.hpp>
#include <TNaming_Tool.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

#include <cstdio>

void QADNaming::GetShape(const char*                     LabelName,
                         const occ::handle<TDF_Data>&    DF,
                         NCollection_List<TopoDS_Shape>& L)
{
  L.Clear();
  TDF_Label Label;
  bool      Found = DDF::AddLabel(DF, LabelName, Label);
  if (Found)
  {
    TNaming_Iterator it(Label, DF->Transaction());
    for (; it.More(); it.Next())
    {
      L.Append(it.NewShape());
    }
  }
}

void QADNaming_BuildMap(NCollection_Map<TDF_Label>& Updated, const TDF_Label& Lab)
{
  TDF_ChildIterator it(Lab);
  for (; it.More(); it.Next())
  {
    Updated.Add(it.Value());
    QADNaming_BuildMap(Updated, it.Value());
  }
}

TopoDS_Shape QADNaming::CurrentShape(const char* LabelName, const occ::handle<TDF_Data>& DF)
{
  TopoDS_Shape S;
  TDF_Label    Label;
  bool         Found = DDF::AddLabel(DF, LabelName, Label);
  if (!Found)
  {
    std::cout << "no labels" << std::endl;
    return S;
  }
  if (Found)
  {
    occ::handle<TNaming_NamedShape> NS;
    Label.FindAttribute(TNaming_NamedShape::GetID(), NS);
    S = TNaming_Tool::CurrentShape(NS);
    if (S.IsNull())
      std::cout << "current shape from " << LabelName << " is deleted" << std::endl;
    return S;
  }
  return S;
}

TCollection_AsciiString QADNaming::GetEntry(const TopoDS_Shape&          Shape,
                                            const occ::handle<TDF_Data>& DF,
                                            int&                         theStatus)
{
  theStatus = 0;

  if (!TNaming_Tool::HasLabel(DF->Root(), Shape))
  {
    return TCollection_AsciiString();
  }
  int                     Transdef;
  TDF_Label               Lab = TNaming_Tool::Label(DF->Root(), Shape, Transdef);
  TCollection_AsciiString entry;
  TDF_Tool::Entry(Lab, entry);

  TNaming_Iterator it(Lab, DF->Transaction());
  for (; it.More(); it.Next())
  {
    theStatus++;
    if (theStatus == 2)
      break;
  }
  return entry;
}

bool QADNaming::Entry(void* const theArguments, TDF_Label& theLabel)
{
  const char**          arg = (const char**)theArguments;
  occ::handle<TDF_Data> DF;
  if (!DDF::GetDF(arg[1], DF))
  {
    std::cout << "Wrong df" << std::endl;
    return false;
  }
  DDF::AddLabel(DF, arg[2], theLabel);
  if (!theLabel.IsNull())
    return true;
  std::cout << "Wrong entry" << std::endl;
  return false;
}

static int QADNaming_IsSameShapes(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3)
  {
    TopoDS_Shape aShape1 = DBRep::Get(arg[1]);
    TopoDS_Shape aShape2 = DBRep::Get(arg[2]);
    if (aShape1.IsNull() || aShape2.IsNull())
      return 0;
    if (aShape1.IsSame(aShape2))
      di << "1";
    return 0;
  }
  return 1;
}

static int QADNaming_CenterOfShape(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 2)
  {
    TopoDS_Shape aShape = DBRep::Get(arg[1]);
    if (aShape.IsNull())
      return 1;
    double          x = 0, y = 0, z = 0;
    float           all = 0;
    TopExp_Explorer anExp(aShape, TopAbs_VERTEX);
    for (; anExp.More(); anExp.Next(), all++)
    {
      TopoDS_Vertex aVertex = TopoDS::Vertex(anExp.Current());
      gp_Pnt        aPoint  = BRep_Tool::Pnt(aVertex);
      x += aPoint.X();
      y += aPoint.Y();
      z += aPoint.Z();
    }
    if (all != 0)
    {
      char s[100];
      Sprintf(s, "%f %f %f", (float)x / all, (float)y / all, (float)z / all);
      di << s;
      return 0;
    }
  }
  return 1;
}

void QADNaming::AllCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  QADNaming::BasicCommands(theCommands);
  QADNaming::BuilderCommands(theCommands);
  QADNaming::IteratorsCommands(theCommands);
  QADNaming::ToolsCommands(theCommands);
  QADNaming::SelectionCommands(theCommands);

  theCommands.Add("IsSameShapes",
                  "IsSameShapes DrawShape1 DrawShape2",
                  __FILE__,
                  QADNaming_IsSameShapes,
                  "Auxiliary methods");
  theCommands.Add("CenterOfShape",
                  "CenterOfShape DrawShape",
                  __FILE__,
                  QADNaming_CenterOfShape,
                  "Auxiliary methods");

  const char* com = "set Draw_NamingData 1";
  theCommands.Eval(com);
}
