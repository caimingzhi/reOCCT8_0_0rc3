#include <BRep_Builder.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TNaming_Iterator.hpp>
#include <TNaming_Localizer.hpp>
#include <TNaming_NamedShape.hpp>
#include <TNaming_Naming.hpp>
#include <TNaming_NewShapeIterator.hpp>
#include <TNaming_OldShapeIterator.hpp>
#include <TNaming_Tool.hpp>
#include <TNaming_UsedShapes.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>

static void LastModif(TNaming_NewShapeIterator&                                      it,
                      const TopoDS_Shape&                                            S,
                      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
                      const NCollection_Map<TDF_Label>&                              Updated,
                      NCollection_List<TDF_Label>&                                   Deleted)
{
  bool YaModif = false;
  for (; it.More(); it.Next())
  {
    const TDF_Label& Lab = it.Label();
    if (!Updated.Contains(Lab))
      continue;

    if (it.IsModification())
    {
      YaModif = true;
      TNaming_NewShapeIterator it2(it);
      if (!it2.More())
      {
        const TopoDS_Shape& S1 = it.Shape();
        if (S1.IsNull())
        {
          Deleted.Append(Lab);
        }
        else
        {
          MS.Add(S1);
        }
      }
      else
        LastModif(it2, it.Shape(), MS, Updated, Deleted);
    }
  }
  if (!YaModif)
    MS.Add(S);
}

static void LastModif(TNaming_NewShapeIterator&                                      it,
                      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
                      const TopoDS_Shape&                                            S,
                      NCollection_List<TDF_Label>&                                   Deleted)
{
  bool YaModif = false;
  for (; it.More(); it.Next())
  {
    const TDF_Label& Lab = it.Label();
    if (it.IsModification())
    {
      YaModif = true;
      TNaming_NewShapeIterator it2(it);
      if (!it2.More())
      {
        const TopoDS_Shape& S1 = it.Shape();
        if (S1.IsNull())
        {
          Deleted.Append(Lab);
        }
        else
        {
          MS.Add(S1);
        }
      }
      else
        LastModif(it2, MS, it.Shape(), Deleted);
    }
  }
  if (!YaModif)
    MS.Add(S);
}

static TopoDS_Shape MakeShape(
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS)
{
  if (!MS.IsEmpty())
  {
    if (MS.Extent() == 1)
    {
      return MS(1);
    }
    else
    {
      TopoDS_Compound C;
      BRep_Builder    B;
      B.MakeCompound(C);
      for (int anItMS = 1; anItMS <= MS.Extent(); ++anItMS)
      {
        B.Add(C, MS(anItMS));
      }
      return C;
    }
  }
  return TopoDS_Shape();
}

TopoDS_Shape TNaming_Tool::GetShape(const occ::handle<TNaming_NamedShape>& NS)
{
  TNaming_Iterator                                              itL(NS);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS;
  if (NS->Evolution() == TNaming_SELECTED)
  {
    for (; itL.More(); itL.Next())
    {
      if (!itL.NewShape().IsNull())
      {
        if (itL.NewShape().ShapeType() != TopAbs_VERTEX)
        {
          occ::handle<TNaming_Naming> aNaming;
          NS->Label().FindAttribute(TNaming_Naming::GetID(), aNaming);
          if (!aNaming.IsNull())
          {
            if (aNaming->GetName().Orientation() == TopAbs_FORWARD
                || aNaming->GetName().Orientation() == TopAbs_REVERSED)
            {
              TopoDS_Shape aS = itL.NewShape();
              if (aNaming->GetName().Type() == TNaming_ORIENTATION)
              {
                aS.Orientation(aNaming->GetName().Orientation());
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
                      aS.Orientation(aNaming2->GetName().Orientation());
                      break;
                    }
                  }
                }
              }
              MS.Add(aS);
            }
            else
              MS.Add(itL.NewShape());
          }
          else
            MS.Add(itL.NewShape());
        }
        else
          MS.Add(itL.NewShape());
      }
    }
  }
  else
    for (; itL.More(); itL.Next())
    {
      if (!itL.NewShape().IsNull())
        MS.Add(itL.NewShape());
    }
  return MakeShape(MS);
}

TopoDS_Shape TNaming_Tool::OriginalShape(const occ::handle<TNaming_NamedShape>& NS)
{
  TNaming_Iterator                                              itL(NS);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS;
  for (; itL.More(); itL.Next())
  {
    MS.Add(itL.OldShape());
  }
  return MakeShape(MS);
}

static void ApplyOrientation(NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
                             const TopAbs_Orientation OrientationToApply)
{
  for (int anItMS = 1; anItMS <= MS.Extent(); ++anItMS)
  {
    MS.Substitute(anItMS, MS(anItMS).Oriented(OrientationToApply));
  }
}

TopoDS_Shape TNaming_Tool::CurrentShape(const occ::handle<TNaming_NamedShape>& Att)
{
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS;
  NCollection_List<TDF_Label>                                   Deleted;

  TNaming_Iterator itL(Att);
  for (; itL.More(); itL.Next())
  {
    const TopoDS_Shape& S = itL.NewShape();
    if (S.IsNull())
      continue;

    bool               YaOrientationToApply(false);
    TopAbs_Orientation OrientationToApply(TopAbs_FORWARD);
    if (Att->Evolution() == TNaming_SELECTED)
    {
      if (itL.More() && itL.NewShape().ShapeType() != TopAbs_VERTEX)
      {
        occ::handle<TNaming_Naming> aNaming;
        Att->Label().FindAttribute(TNaming_Naming::GetID(), aNaming);
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
      }
    }
    TNaming_NewShapeIterator it(itL);
    if (!it.More())
    {
      MS.Add(S);
    }
    else
    {

      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS2;
      LastModif(it, MS2, S, Deleted);
      if (YaOrientationToApply)
        ApplyOrientation(MS2, OrientationToApply);
      for (int anItMS2 = 1; anItMS2 <= MS2.Extent(); ++anItMS2)
        MS.Add(MS2(anItMS2));
    }
  }
  return MakeShape(MS);
}

TopoDS_Shape TNaming_Tool::CurrentShape(const occ::handle<TNaming_NamedShape>& Att,
                                        const NCollection_Map<TDF_Label>&      Updated)
{
  TDF_Label Lab = Att->Label();

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS;
  NCollection_List<TDF_Label>                                   Deleted;

  if (!Updated.Contains(Lab))
  {
    return TopoDS_Shape();
  }

  TNaming_Iterator itL(Att);
  for (; itL.More(); itL.Next())
  {
    const TopoDS_Shape& S = itL.NewShape();
    if (S.IsNull())
      continue;

    bool               YaOrientationToApply(false);
    TopAbs_Orientation OrientationToApply(TopAbs_FORWARD);
    if (Att->Evolution() == TNaming_SELECTED)
    {
      if (itL.More() && itL.NewShape().ShapeType() != TopAbs_VERTEX)
      {
        occ::handle<TNaming_Naming> aNaming;
        Att->Label().FindAttribute(TNaming_Naming::GetID(), aNaming);
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
      }
    }
    TNaming_NewShapeIterator it(itL);
    if (!it.More())
    {
      MS.Add(S);
    }
    else
    {

      NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS2;
      LastModif(it, S, MS2, Updated, Deleted);
      if (YaOrientationToApply)
        ApplyOrientation(MS2, OrientationToApply);
      for (int anItMS2 = 1; anItMS2 <= MS2.Extent(); ++anItMS2)
        MS.Add(MS2(anItMS2));
    }
  }
  return MakeShape(MS);
}

occ::handle<TNaming_NamedShape> TNaming_Tool::CurrentNamedShape(
  const occ::handle<TNaming_NamedShape>& Att,
  const NCollection_Map<TDF_Label>&      Updated)
{
  TopoDS_Shape CS = CurrentShape(Att, Updated);
  if (CS.IsNull())
  {
    occ::handle<TNaming_NamedShape> NS;
    return NS;
  }
  return NamedShape(CS, Att->Label());
}

occ::handle<TNaming_NamedShape> TNaming_Tool::CurrentNamedShape(
  const occ::handle<TNaming_NamedShape>& Att)

{
  TopoDS_Shape CS = CurrentShape(Att);
  if (CS.IsNull())
  {
    occ::handle<TNaming_NamedShape> NS;
    return NS;
  }
  return NamedShape(CS, Att->Label());
}

static void FindModifUntil(TNaming_NewShapeIterator&                                      it,
                           NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
                           const occ::handle<TNaming_NamedShape>&                         Context)
{
  for (; it.More(); it.Next())
  {
    if (!it.Shape().IsNull())
    {
      if (it.NamedShape() == Context)
      {
        MS.Add(it.Shape());
      }
      else
      {
        TNaming_NewShapeIterator it2(it);
        FindModifUntil(it2, MS, Context);
      }
    }
  }
}

TopoDS_Shape TNaming_Tool::GeneratedShape(const TopoDS_Shape&                    S,
                                          const occ::handle<TNaming_NamedShape>& Generation)

{
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS;
  occ::handle<TNaming_UsedShapes>                               US;
  Generation->Label().Root().FindAttribute(TNaming_UsedShapes::GetID(), US);

  for (TNaming_NewShapeIterator it(S, US); it.More(); it.Next())
  {
    if (!it.Shape().IsNull() && it.NamedShape() == Generation)
    {
      MS.Add(it.Shape());
    }
  }
  if (MS.IsEmpty())
  {
    TNaming_NewShapeIterator it2(S, US);
    FindModifUntil(it2, MS, Generation);
  }
  return MakeShape(MS);
}

void TNaming_Tool::FirstOlds(const occ::handle<TNaming_UsedShapes>&                         US,
                             const TopoDS_Shape&                                            S,
                             TNaming_OldShapeIterator&                                      it,
                             NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& MS,
                             NCollection_List<TDF_Label>&                                   Labels)
{
  int  TransDef;
  bool YaModif = false;

  for (; it.More(); it.Next())
  {
    if (it.IsModification())
    {
      YaModif = true;
      TNaming_OldShapeIterator it2(it);
      if (!it2.More())
      {
        Labels.Append(TNaming_Tool::Label(US, it.Shape(), TransDef));
        MS.Add(it.Shape());
      }
      else
      {
        FirstOlds(US, it.Shape(), it2, MS, Labels);
      }
    }
  }
  if (!YaModif)
    MS.Add(S);
}

TopoDS_Shape TNaming_Tool::InitialShape(const TopoDS_Shape&          S,
                                        const TDF_Label&             Acces,
                                        NCollection_List<TDF_Label>& Labels)
{
  occ::handle<TNaming_UsedShapes> US;
  Acces.Root().FindAttribute(TNaming_UsedShapes::GetID(), US);
  TopoDS_Shape Res;

  if (!TNaming_Tool::HasLabel(US, S))
    return Res;

  int Transdef;
  Label(US, S, Transdef);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> MS;
  TNaming_OldShapeIterator                                      it(S, Transdef, US);
  if (!it.More())
  {
    return S;
  }
  else
  {
    FirstOlds(US, S, it, MS, Labels);
  }
  return MakeShape(MS);
}

static void Back(const occ::handle<TNaming_NamedShape>&            NS,
                 NCollection_Map<occ::handle<TNaming_NamedShape>>& MNS)
{
  for (TNaming_Iterator it(NS); it.More(); it.Next())
  {
    if (it.NewShape().IsNull())
      continue;
    for (TNaming_OldShapeIterator Oldit(it); Oldit.More(); Oldit.Next())
    {
      const TopoDS_Shape& OS = Oldit.Shape();
      if (!OS.IsNull())
      {
        occ::handle<TNaming_NamedShape> NOS = TNaming_Tool::NamedShape(OS, NS->Label());

        if (!NOS.IsNull())
        {
          if (MNS.Add(NOS))
            Back(NOS, MNS);
        }
      }
    }
  }
}

void TNaming_Tool::Collect(const occ::handle<TNaming_NamedShape>&            NS,
                           NCollection_Map<occ::handle<TNaming_NamedShape>>& MNS,
                           const bool                                        OnlyModif)
{
  MNS.Add(NS);
  Back(NS, MNS);

  for (TNaming_Iterator it(NS); it.More(); it.Next())
  {
    if (it.NewShape().IsNull())
      continue;
    for (TNaming_NewShapeIterator NewIt(it); NewIt.More(); NewIt.Next())
    {
      if (!OnlyModif || NewIt.IsModification())
      {

        Collect(NewIt.NamedShape(), MNS, OnlyModif);
      }
    }
  }
}

#ifdef OCCT_DEBUG

void TNamingTool_DumpLabel(const TopoDS_Shape& S, const TDF_Label& Acces)
{
  occ::handle<TNaming_NamedShape> NS = TNaming_Tool::NamedShape(S, Acces);
  NS->Label().EntryDump(std::cout);
  std::cout << std::endl;
}

  #include <BRepTools.hpp>

void TNamingTool_Write(const TopoDS_Shape& S, const char* File)
{
  BRepTools::Write(S, File);
}

#endif

void TNaming_Tool::FindShape(const NCollection_Map<TDF_Label>& Valid,
                             const NCollection_Map<TDF_Label>&,
                             const occ::handle<TNaming_NamedShape>& Arg,
                             TopoDS_Shape&                          S)
{
  if (!Valid.IsEmpty() && !Valid.Contains(Arg->Label()))
    return;
  if (Arg.IsNull() || Arg->IsEmpty())
    return;

  occ::handle<TNaming_Naming> aNaming;
  if (!Arg->FindAttribute(TNaming_Naming::GetID(), aNaming))
  {
#ifdef OCCT_DEBUG

#endif
    return;
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> subShapes;
  TopExp_Explorer anExpl(Arg->Get(), (TopAbs_ShapeEnum)((int)(aNaming->GetName().ShapeType()) + 1));
  for (; anExpl.More(); anExpl.Next())
    subShapes.Add(anExpl.Current());
#ifdef OCCT_DEBUG

#endif

  NCollection_List<occ::handle<TNaming_NamedShape>> extArgs;
  NCollection_Map<occ::handle<TDF_Attribute>>       outRefs;
  TDF_Tool::OutReferences(Arg->Label(), outRefs);
  if (outRefs.IsEmpty())
  {
#ifdef OCCT_DEBUG

#endif
    return;
  }
  for (NCollection_Map<occ::handle<TDF_Attribute>>::Iterator itr(outRefs); itr.More(); itr.Next())
  {
    if (itr.Key()->DynamicType() == STANDARD_TYPE(TNaming_NamedShape))
    {
#ifdef OCCT_DEBUG

#endif
      occ::handle<TNaming_NamedShape> anExtArg(occ::down_cast<TNaming_NamedShape>(itr.Key()));
      const occ::handle<TNaming_NamedShape>& aCurrentExtArg =
        TNaming_Tool::CurrentNamedShape(anExtArg);
      if (!aCurrentExtArg.IsNull() && !aCurrentExtArg->IsEmpty())
        extArgs.Append(aCurrentExtArg);
#ifdef OCCT_DEBUG

#endif
    }
  }

  NCollection_List<occ::handle<TNaming_NamedShape>>::Iterator extArgsIterator(extArgs);
  for (; extArgsIterator.More(); extArgsIterator.Next())
  {
    occ::handle<TNaming_NamedShape> anExtArg = extArgsIterator.Value();

    occ::handle<TNaming_NamedShape> aContextNS;
    if (anExtArg->Label().Father().IsNull()
        || !anExtArg->Label().Father().FindAttribute(TNaming_NamedShape::GetID(), aContextNS))
    {
      aContextNS = anExtArg;
    }

#ifdef OCCT_DEBUG

#endif

    TopExp_Explorer explC(aContextNS->Get(), aNaming->GetName().ShapeType()), explSubC;
    for (; explC.More(); explC.Next())
    {
      int                                                    DoesCoincide   = 0;
      const TopoDS_Shape&                                    possibleResult = explC.Current();
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> subShapesOfResult;
      for (explSubC.Init(possibleResult,
                         (TopAbs_ShapeEnum)((int)(aNaming->GetName().ShapeType()) + 1));
           explSubC.More();
           explSubC.Next())
      {
        subShapesOfResult.Add(explSubC.Current());
      }
      if (subShapesOfResult.Extent() != subShapes.Extent())
        continue;
      for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itrR(subShapesOfResult);
           itrR.More();
           itrR.Next())
      {
        for (NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itr1(subShapes);
             itr1.More();
             itr1.Next())
        {
          if (itrR.Key().IsSame(itr1.Key()))
          {
            DoesCoincide++;
            break;
          }
        }
      }
      if (DoesCoincide == subShapes.Extent())
      {
#ifdef OCCT_DEBUG

#endif
        S = possibleResult;
        break;
      }
    }

    if (!S.IsNull())
      break;
#ifdef OCCT_DEBUG

#endif
  }

#ifdef OCCT_DEBUG
  if (S.IsNull())
  {
    std::cout << "TNaming_Tool::FindShape(): There hasn't been found a sub shape of the context "
                 "shape coinciding with the sub shapes of naming"
              << std::endl;
  }
#endif
}
