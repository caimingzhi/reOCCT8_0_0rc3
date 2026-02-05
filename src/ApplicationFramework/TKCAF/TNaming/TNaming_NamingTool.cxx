#include <TDF_ChildIterator.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Iterator.hpp>
#include <TNaming_Naming.hpp>
#include <TNaming_NamingTool.hpp>
#include <TNaming_NewShapeIterator.hpp>
#include <TNaming_OldShapeIterator.hpp>
#include <TNaming_Tool.hpp>
#include <TopoDS_Shape.hpp>

#ifdef OCCT_DEBUG_DESC
  #include <TCollection_AsciiString.hpp>
  #include <TDF_Tool.hpp>
  #include <BRepTools.hpp>

static void WriteS(const TopoDS_Shape& shape, const char* filename)
{
  char buf[256];
  if (strlen(filename) > 255)
    return;
  #ifdef _MSC_VER
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
#endif

//=======================================================================
// function : IsForbiden
// purpose  : ANaming voir NamingTool
//=======================================================================

static bool IsForbiden(const NCollection_Map<TDF_Label>& Forbiden, const TDF_Label& Lab)
{
  if (Lab.IsRoot())
  {
    return false;
  }
  if (Forbiden.Contains(Lab))
    return true;
  else
  {
    return IsForbiden(Forbiden, Lab.Father());
  }
}

//=================================================================================================

static void LastModif(TNaming_NewShapeIterator&                                      it,
                      const TopoDS_Shape&                                            S,
                      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
                      const NCollection_Map<TDF_Label>&                              Updated,
                      const NCollection_Map<TDF_Label>&                              Forbiden)
{
  bool YaModif = false;
  for (; it.More(); it.Next())
  {
    const TDF_Label& Lab = it.Label();
#ifdef OCCT_DEBUG_DESC
    TCollection_AsciiString entry;
    TDF_Tool::Entry(Lab, entry);
    std::cout << "NamingTool:: LastModif LabelEntry = " << entry << std::endl;
#endif
    if (!Updated.IsEmpty() && !Updated.Contains(Lab))
      continue;
    if (IsForbiden(Forbiden, Lab))
      continue;
    if (it.IsModification())
    {
      YaModif = true;
      TNaming_NewShapeIterator it2(it);
      if (!it2.More())
      {
        const TopoDS_Shape& aS = it.Shape();
        MS.Add(aS); // Modified
      }
      else
        LastModif(it2, it.Shape(), MS, Updated, Forbiden);
    }
  }
  if (!YaModif)
    MS.Add(S);
}

//=======================================================================
static void ApplyOrientation(NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
                             const TopAbs_Orientation OrientationToApply)
{
#ifdef OCCT_DEBUG_APPLY
  if (!MS.IsEmpty())
  {
    std::cout << "OrientationToApply = " << OrientationToApply << std::endl;
    for (int anItMS1 = 1; anItMS1 <= MS.Extent(); ++anItMS1)
    {
      std::cout << "ApplyOrientation: TShape = " << MS(anItMS1).TShape()->This()
                << " OR = " << MS(anItMS1).Orientation() << std::endl;
    }
  }
#endif
  for (int anItMS = 1; anItMS <= MS.Extent(); ++anItMS)
  {
    MS.Substitute(anItMS, MS(anItMS).Oriented(OrientationToApply));
  }
}

//=================================================================================================

void TNaming_NamingTool::CurrentShape(
  const NCollection_Map<TDF_Label>&                              Valid,
  const NCollection_Map<TDF_Label>&                              Forbiden,
  const occ::handle<TNaming_NamedShape>&                         Att,
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS)
{
  TDF_Label Lab = Att->Label();
#ifdef OCCT_DEBUG_DESC
  TCollection_AsciiString entry;
  TDF_Tool::Entry(Lab, entry);
  std::cout << "NamingTool:: LabelEntry = " << entry << std::endl;
#endif
  if (!Valid.IsEmpty() && !Valid.Contains(Lab))
  {
#ifdef OCCT_DEBUG_DESC
    TCollection_AsciiString entry;
    TDF_Tool::Entry(Lab, entry);
    std::cout << "NamingTool:: LabelEntry = " << entry << " is out of Valid map" << std::endl;
#endif
    return;
  }

  TNaming_Iterator itL(Att);
  for (; itL.More(); itL.Next())
  {
    const TopoDS_Shape& S = itL.NewShape();
    if (S.IsNull())
      continue;
#ifdef OCCT_DEBUG_DESC
    WriteS(S, "CS_NewShape.brep");
    if (itL.OldShape().IsNull())
      std::cout << "OldShape is Null" << std::endl;
    else
      WriteS(itL.OldShape(), "CS_OldShape.brep");
#endif
    bool               YaOrientationToApply(false);
    TopAbs_Orientation OrientationToApply(TopAbs_FORWARD);
    if (Att->Evolution() == TNaming_SELECTED)
    {
      if (itL.More() && itL.NewShape().ShapeType() != TopAbs_VERTEX)
      { // OR-N
        occ::handle<TNaming_Naming> aNaming;
        Lab.FindAttribute(TNaming_Naming::GetID(), aNaming);
        if (!aNaming.IsNull())
        {
          if (aNaming->GetName().Type() == TNaming_ORIENTATION)
          {
            OrientationToApply = aNaming->GetName().Orientation();
          }
          else
          {
            occ::handle<TNaming_Naming> aNaming2;
            TDF_ChildIterator           it(aNaming->Label());
            for (; it.More(); it.Next())
            {
              const TDF_Label& aLabel = it.Value();
              aLabel.FindAttribute(TNaming_Naming::GetID(), aNaming2);
              if (!aNaming2.IsNull())
              {
                if (aNaming2->GetName().Type() == TNaming_ORIENTATION)
                {
                  OrientationToApply = aNaming2->GetName().Orientation();
                  break;
                }
              }
            }
          }
          if (OrientationToApply == TopAbs_FORWARD || OrientationToApply == TopAbs_REVERSED)
            YaOrientationToApply = true;
        }
      } //
    }
    TNaming_NewShapeIterator it(itL);
    if (!it.More())
    {
      if (YaOrientationToApply)
        MS.Add(S.Oriented(OrientationToApply));
      else
        MS.Add(S);
    }
    else
    {
      //     LastModif(it, S, MS, Valid, Forbiden);
      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS2;
      LastModif(it, S, MS2, Valid, Forbiden);
      // clang-format off
      if (YaOrientationToApply) ApplyOrientation (MS2, OrientationToApply);//the solution to be refined
      // clang-format on
      for (int anItMS2 = 1; anItMS2 <= MS2.Extent(); ++anItMS2)
        MS.Add(MS2(anItMS2));
    }
  }
}

//=================================================================================================

void TNaming_NamingTool::CurrentShapeFromShape(
  const NCollection_Map<TDF_Label>&                              Valid,
  const NCollection_Map<TDF_Label>&                              Forbiden,
  const TDF_Label&                                               Acces,
  const TopoDS_Shape&                                            S,
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS)
{
  TNaming_NewShapeIterator it(S, Acces);

  occ::handle<TNaming_NamedShape> NS = it.NamedShape();
  if (!NS.IsNull() && NS->Evolution() == TNaming_SELECTED)
    MS.Add(TNaming_Tool::GetShape(NS));
  else
  {
    if (!it.More())
      MS.Add(S);
    else
      LastModif(it, S, MS, Valid, Forbiden);
  }
}

//=================================================================================================

static void MakeDescendants(TNaming_NewShapeIterator& it, NCollection_Map<TDF_Label>& Descendants)
{
  for (; it.More(); it.Next())
  {
    Descendants.Add(it.Label());
#ifdef OCCT_DEBUG_DESC
    TCollection_AsciiString entry;
    TDF_Tool::Entry(it.Label(), entry);
    std::cout << "MakeDescendants: Label = " << entry << std::endl;
#endif
    if (!it.Shape().IsNull())
    {
      TNaming_NewShapeIterator it2(it);
      MakeDescendants(it2, Descendants);
    }
  }
}

//=======================================================================
void BuildDescendants2(const occ::handle<TNaming_NamedShape>& NS,
                       const TDF_Label&                       ForbLab,
                       NCollection_Map<TDF_Label>&            Descendants)
{
  if (NS.IsNull())
    return;
  TNaming_NewShapeIterator it(NS);
  for (; it.More(); it.Next())
  {
    if (!it.NamedShape().IsNull())
    {
#ifdef OCCT_DEBUG_DESC
      TCollection_AsciiString entry;
      TDF_Tool::Entry(it.Label(), entry);
      std::cout << "MakeDescendants2: Label = " << entry << std::endl;
#endif
      if (ForbLab == it.Label())
        continue;
      Descendants.Add(it.Label());
      TNaming_NewShapeIterator it2(it);
      MakeDescendants(it2, Descendants);
    }
  }
}

//=================================================================================================

void TNaming_NamingTool::BuildDescendants(const occ::handle<TNaming_NamedShape>& NS,
                                          NCollection_Map<TDF_Label>&            Descendants)
{
  if (NS.IsNull())
    return;
  Descendants.Add(NS->Label());
  TNaming_NewShapeIterator it(NS);
#ifdef OCCT_DEBUG_DESC
  TCollection_AsciiString entry;
  TDF_Tool::Entry(NS->Label(), entry);
  std::cout << "MakeDescendants: Label = " << entry << std::endl;
#endif
  MakeDescendants(it, Descendants);
  TNaming_OldShapeIterator it2(NS);
  for (; it2.More(); it2.Next())
  {
    if (!it2.Shape().IsNull())
    {
      occ::handle<TNaming_NamedShape> ONS = TNaming_Tool::NamedShape(it2.Shape(), NS->Label());
      if (!ONS.IsNull())
      {
#ifdef OCCT_DEBUG_DESC
        TCollection_AsciiString entry;
        TDF_Tool::Entry(ONS->Label(), entry);
        std::cout << "MakeDescendants_Old: Label = " << entry << std::endl;
#endif
        BuildDescendants2(ONS, NS->Label(), Descendants);
      }
    }
  }
}
