#include <TNaming_Identifier.hpp>
#include <TNaming_Iterator.hpp>
#include <TNaming_NamedShape.hpp>
#include <NCollection_List.hpp>
#include <TNaming_Localizer.hpp>
#include <TNaming_OldShapeIterator.hpp>
#include <TNaming_Tool.hpp>
#include <TNaming_UsedShapes.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

#ifdef OCCT_DEBUG

  #ifdef OCCT_DEBUG_SC
    #include <TDF_Tool.hpp>
    #include <TDF_Label.hpp>
    #include <NCollection_Map.hpp>

    #include <TCollection_AsciiString.hpp>
    #include <BRepTools.hpp>

void LPrintEntry(const TDF_Label& label)
{
  TCollection_AsciiString entry;
  TDF_Tool::Entry(label, entry);
  std::cout << "LabelEntry = " << entry << std::endl;
}

static void LWrite(const TopoDS_Shape& shape, const char* filename)
{
  char buf[256];
  if (strlen(filename) > 256)
    return;
    #if defined _MSC_VER
  strcpy_s(buf, filename);
    #else
  strcpy(buf, filename);
    #endif
  char* p = buf;
  while (*p)
  {
    if (*p == ':')
      *p = '-';
    p++;
  }
  std::ofstream save(buf);
  if (!save)
    std::cout << "File " << buf << " was not created: rdstate = " << save.rdstate() << std::endl;
  save << "DBRep_DrawableShape" << std::endl << std::endl;
  if (!shape.IsNull())
    BRepTools::Write(shape, save);
  save.close();
}

static void LWriteNSOnLabel(const occ::handle<TNaming_NamedShape>& NS, const char* filename)
{
  if (!NS.IsNull() && !NS->IsEmpty())
  {
    TCollection_AsciiString aNam(filename);
    TCollection_AsciiString oldS("_Old");
    TCollection_AsciiString newS("_New_");
    int                     i(0);
    TNaming_Iterator        it(NS);
    for (; it.More(); it.Next(), i++)
    {
      TCollection_AsciiString aName1   = aNam + oldS + i + ".brep";
      TCollection_AsciiString aName2   = aNam + newS + i + ".brep";
      const TopoDS_Shape&     oldShape = it.OldShape();
      const TopoDS_Shape&     newShape = it.NewShape();
      if (!oldShape.IsNull())
        LWrite(oldShape, aName1.ToCString());
      if (!newShape.IsNull())
        LWrite(newShape, aName2.ToCString());
    }
  }
}
  #endif
#endif

void TNaming_Localizer::FindFeaturesInAncestors(
  const TopoDS_Shape&                                     S,
  const TopoDS_Shape&                                     Context,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& AncInFeature)
{
#ifdef OCCT_DEBUG_SC
  LWrite(S, "Localizer_S.brep");
  LWrite(Context, "Localizer_Context.brep");
#endif

  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& Anc =
    Ancestors(Context, S.ShapeType());

  if (Anc.Contains(S))
  {
#ifdef OCCT_DEBUG_SC
    std::cout << "Localizer: S in ancestor" << std::endl;
#endif
    const NCollection_List<TopoDS_Shape>&    L = Anc.FindFromKey(S);
    NCollection_List<TopoDS_Shape>::Iterator itL(L);
    for (; itL.More(); itL.Next())
    {
      const TopoDS_Shape& AS = itL.Value();
#ifdef OCCT_DEBUG_SC
      LWrite(AS, "Localizer_AS.brep");
#endif
      occ::handle<TNaming_NamedShape> NS = TNaming_Tool::NamedShape(AS, myUS->Label());
      if (!NS.IsNull())
      {

        AncInFeature.Add(AS);
      }
      else if (AS.ShapeType() > TopAbs_FACE)
      {
        FindFeaturesInAncestors(AS, Context, AncInFeature);
      }
      else
      {
#ifdef OCCT_DEBUG
        std::cout << " TNaming_Localization : Failure in the research of ancetres in TDF"
                  << std::endl;
#endif
      }
    }
  }
  else
  {
#ifdef OCCT_DEBUG

    std::cout << " TNaming_Localization : S n est pas dans le solide" << std::endl;

#endif
  }
}

const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& TNaming_Localizer::SubShapes(
  const TopoDS_Shape&    In,
  const TopAbs_ShapeEnum TS)
{

  NCollection_List<TopoDS_Shape>::Iterator itS(myShapeWithSubShapes);
  NCollection_List<NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>>::Iterator itSS(
    mySubShapes);

  for (; itS.More(); itS.Next(), itSS.Next())
  {
    if (In.IsSame(itS.Value()))
    {
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& SubShapes = itSS.ChangeValue();
      for (TopExp_Explorer exp(In, TS); exp.More(); exp.Next())
      {
        const TopoDS_Shape& SS = exp.Current();
        if (SubShapes.Contains(SS))
        {
          break;
        }
        SubShapes.Add(SS);
      }
      return SubShapes;
    }
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> emptyMap;
  mySubShapes.Prepend(emptyMap);
  myShapeWithSubShapes.Prepend(In);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& SubShapes = mySubShapes.First();
  for (TopExp_Explorer exp(In, TS); exp.More(); exp.Next())
  {
    const TopoDS_Shape& SS = exp.Current();
    if (SubShapes.Contains(SS))
    {
      break;
    }
    SubShapes.Add(SS);
  }
  return SubShapes;
}

const NCollection_IndexedDataMap<TopoDS_Shape,
                                 NCollection_List<TopoDS_Shape>,
                                 TopTools_ShapeMapHasher>&
  TNaming_Localizer::Ancestors(const TopoDS_Shape& In, const TopAbs_ShapeEnum TS)
{
  NCollection_List<TopoDS_Shape>::Iterator itS(myShapeWithAncestors);
  NCollection_List<NCollection_IndexedDataMap<TopoDS_Shape,
                                              NCollection_List<TopoDS_Shape>,
                                              TopTools_ShapeMapHasher>>::Iterator itA(myAncestors);

  for (; itS.More(); itS.Next(), itA.Next())
  {
    if (In.IsSame(itS.Value()))
    {

      NCollection_IndexedDataMap<TopoDS_Shape,
                                 NCollection_List<TopoDS_Shape>,
                                 TopTools_ShapeMapHasher>& Anc = itA.ChangeValue();

      TopExp_Explorer exp(In, TS);
#ifdef OCCT_DEBUG
      if (!exp.More())
        std::cout << " TNaming_Localization : Construction ancetres impossible" << std::endl;
#endif
      const TopoDS_Shape& SS = exp.Current();

      if (Anc.Contains(SS))
      {
        return Anc;
      }
      else
      {

        TopAbs_ShapeEnum TA = TopAbs_FACE;
        if (TS == TopAbs_EDGE)
          TA = TopAbs_FACE;
        if (TS == TopAbs_VERTEX)
          TA = TopAbs_EDGE;
        if (TA >= In.ShapeType())
        {
          TopExp::MapShapesAndAncestors(In, TS, TA, Anc);
        }
        else
        {
#ifdef OCCT_DEBUG
          std::cout << " TNaming_Localization : Construction ancetres impossible" << std::endl;
#endif
        }
      }
      return Anc;
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    emptyAnc;
  myShapeWithAncestors.Prepend(In);
  myAncestors.Prepend(emptyAnc);

  TopAbs_ShapeEnum TA = TopAbs_COMPOUND;

  if (TS == TopAbs_VERTEX)
    TA = TopAbs_EDGE;
  else if (TS == TopAbs_EDGE)
    TA = TopAbs_FACE;
  else if (TS == TopAbs_FACE)
    TA = TopAbs_SOLID;
  if ((TS == TopAbs_EDGE || TS == TopAbs_VERTEX || TS == TopAbs_FACE) && TA >= In.ShapeType())
  {
    TopExp::MapShapesAndAncestors(In, TS, TA, myAncestors.First());
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << " TNaming_Localization : Construction ancetres impossible" << std::endl;
#endif
  }
  return myAncestors.First();
}

bool TNaming_Localizer::IsNew(const TopoDS_Shape& S, const occ::handle<TNaming_NamedShape>& NS)
{
  TNaming_Iterator itLab(NS);
  for (; itLab.More(); itLab.Next())
  {
    if (itLab.OldShape().IsSame(S))
    {
      return false;
    }
    if (itLab.NewShape().IsSame(S))
    {
      return true;
    }
  }
#ifdef OCCT_DEBUG
  std::cout << "TNaming_Localizer:IsNewInLab : Shape n est pas dans le Label." << std::endl;
#endif
  return false;
}

void TNaming_Localizer::GoBack(const TopoDS_Shape&                                S,
                               const TDF_Label&                                   Lab,
                               const TNaming_Evolution                            Evol,
                               NCollection_List<TopoDS_Shape>&                    LBS,
                               NCollection_List<occ::handle<TNaming_NamedShape>>& LBNS)
{

  TNaming_OldShapeIterator it(S, myCurTrans, myUS);
  TopoDS_Shape             Sol;
  if (!it.More())
  {

    const TDF_Label& Father = Lab.Father();
    TNaming_Iterator itLab(Father);
    if (itLab.More())
      Sol = itLab.OldShape();

    if (!Sol.IsNull())
    {
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> AncInFeature;
      FindFeaturesInAncestors(S, Sol, AncInFeature);
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itF(AncInFeature);
      for (; itF.More(); itF.Next())
      {
        const TopoDS_Shape& AncOfS = itF.Key();
        LBS.Append(AncOfS);
        LBNS.Append(TNaming_Tool::NamedShape(AncOfS, Lab));
      }
    }
  }
  else
  {
    for (; it.More(); it.Next())
    {

      if (it.NamedShape()->Evolution() == Evol)
      {
        occ::handle<TNaming_NamedShape> NS = TNaming_Tool::NamedShape(it.Shape(), Lab);
        if (!NS.IsNull())
        {
          LBS.Append(it.Shape());
          LBNS.Append(TNaming_Tool::NamedShape(it.Shape(), Lab));
        }
        else
        {
#ifdef OCCT_DEBUG
          std::cout << "TNaming_Localizer: Shape modifie sans avoir ete cree" << std::endl;
#endif
        }
      }
    }
  }
}

occ::handle<TNaming_NamedShape> NamedShape(const TDF_Label& Lab)
{
  occ::handle<TNaming_NamedShape> NS;
  Lab.FindAttribute(TNaming_NamedShape::GetID(), NS);
  return NS;
}

void TNaming_Localizer::Backward(const occ::handle<TNaming_NamedShape>&                  NS,
                                 const TopoDS_Shape&                                     S,
                                 NCollection_Map<occ::handle<TNaming_NamedShape>>&       Primitives,
                                 NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& Shapes)
{
  TNaming_Evolution Evol  = NS->Evolution();
  TDF_Label         LabNS = NS->Label();

  NCollection_List<TopoDS_Shape>                    LBS;
  NCollection_List<occ::handle<TNaming_NamedShape>> LBNS;

  GoBack(S, LabNS, Evol, LBS, LBNS);

  NCollection_List<TopoDS_Shape>::Iterator                    itLBS(LBS);
  NCollection_List<occ::handle<TNaming_NamedShape>>::Iterator itLBNS(LBNS);

  if (LBS.IsEmpty())
  {
    Primitives.Add(NS);
  }
  for (; itLBS.More(); itLBS.Next(), itLBNS.Next())
  {
    const TopoDS_Shape&             OS  = itLBS.Value();
    occ::handle<TNaming_NamedShape> NOS = itLBNS.Value();
    Evol                                = NOS->Evolution();
    if (Evol == TNaming_PRIMITIVE)
    {
      Primitives.Add(NOS);
    }
    else if (Evol == TNaming_GENERATED)
    {
      Shapes.Add(OS);
    }
    else
    {
      Backward(NOS, itLBS.Value(), Primitives, Shapes);
    }
  }
}

#ifdef OCCT_DEBUG

#endif

void TNaming_Localizer::FindNeighbourg(
  const TopoDS_Shape&                                     Sol,
  const TopoDS_Shape&                                     S,
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& Neighbourg)
{
  if (Sol.IsNull() || S.IsNull())
    return;
  TopAbs_ShapeEnum TA = S.ShapeType();
  TopAbs_ShapeEnum TS = TopAbs_COMPOUND;

  if (TA == TopAbs_FACE)
    TS = TopAbs_EDGE;
  if (TA == TopAbs_EDGE)
    TS = TopAbs_VERTEX;
  if (TA == TopAbs_VERTEX)
    TS = TopAbs_VERTEX;
  const NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>& Anc = Ancestors(Sol, TS);

  for (TopExp_Explorer Exp(S, TS); Exp.More(); Exp.Next())
  {
    const TopoDS_Shape& SS = Exp.Current();
    if (!Anc.Contains(SS))
    {

      break;
    }
    else
    {
      NCollection_List<TopoDS_Shape>::Iterator itL(Anc.FindFromKey(SS));
      for (; itL.More(); itL.Next())
      {
        if (!itL.Value().IsSame(S))
        {
          Neighbourg.Add(itL.Value());
        }
      }
    }
  }
}

TNaming_Localizer::TNaming_Localizer() = default;

void TNaming_Localizer::Init(const occ::handle<TNaming_UsedShapes>& US, const int CurTrans)
{
  myUS       = US;
  myCurTrans = CurTrans;
}

#ifdef OCCT_DEBUG

#endif

void TNaming_Localizer::FindGenerator(const occ::handle<TNaming_NamedShape>& NS,
                                      const TopoDS_Shape&                    S,
                                      NCollection_List<TopoDS_Shape>&        theListOfGenerators)

{
  occ::handle<TNaming_UsedShapes> US;
  TDF_Label                       LabNS = NS->Label();
  (LabNS.Root()).FindAttribute(TNaming_UsedShapes::GetID(), US);

  for (TNaming_OldShapeIterator it(S, US); it.More(); it.Next())
  {
    if (it.Label() == LabNS)
    {
      theListOfGenerators.Append(it.Shape());
    }
  }
}

void TNaming_Localizer::FindShapeContext(const occ::handle<TNaming_NamedShape>& NS,
                                         const TopoDS_Shape&                    S,
                                         TopoDS_Shape&                          SC)

{
#ifdef OCCT_DEBUG_SC
  LWrite(S, "FSC_Sel.brep");
  LPrintEntry(NS->Label());
#endif
  NCollection_List<TopoDS_Shape> aList;
  TDF_Label                      Father = NS->Label().Father();
  TNaming_Iterator               itLab(Father);
  for (; itLab.More(); itLab.Next())
  {
    aList.Append(itLab.OldShape());
  }

  NCollection_List<TopoDS_Shape>::Iterator it(aList);
  bool                                     found = false;
  for (; it.More(); it.Next())
  {
    SC = it.Value();
#ifdef OCCT_DEBUG_SC
    LWrite(SC, "FSC_OldShape.brep");
#endif
    if (SC.IsNull())
      continue;
    else
    {
      if (SC.ShapeType() < S.ShapeType())
      {
        for (TopExp_Explorer exp(SC, S.ShapeType()); exp.More(); exp.Next())
        {
          if (exp.Current().IsSame(S))
          {
            found = true;
#ifdef OCCT_DEBUG_SC
            std::cout << "Find Context shape = " << SC.TShape() << "ShapeType = " << SC.ShapeType()
                      << std::endl;
#endif
            break;
          }
        }
        if (found)
          break;
      }
    }
  }

  if (!SC.IsNull())
  {
    occ::handle<TNaming_NamedShape> aNS = TNaming_Tool::NamedShape(SC, Father);
    if (!aNS.IsNull())
    {
#ifdef OCCT_DEBUG_SC
      std::cout << "FindShapeContext: ";
      LPrintEntry(aNS->Label());
#endif
      if (aNS->Label().Father().FindAttribute(TNaming_NamedShape::GetID(), aNS))
      {
        TopoDS_Shape aShape;
#ifdef OCCT_DEBUG_SC
        LWriteNSOnLabel(aNS, "FSC");
#endif
        TNaming_Iterator anIter(aNS->Label());
        for (; anIter.More(); anIter.Next())
        {
          aShape = anIter.NewShape();
          if (!aShape.IsNull())
            break;
        }
        if (!aShape.IsNull())
          SC = aShape;
      }
    }
  }
}
