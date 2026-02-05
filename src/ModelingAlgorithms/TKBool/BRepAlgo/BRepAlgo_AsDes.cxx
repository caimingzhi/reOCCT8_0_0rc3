#include <BRepAlgo_AsDes.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepAlgo_AsDes, Standard_Transient)

//=================================================================================================

BRepAlgo_AsDes::BRepAlgo_AsDes() = default;

//=================================================================================================

void BRepAlgo_AsDes::Add(const TopoDS_Shape& S, const TopoDS_Shape& SS)
{
  if (!down.IsBound(S))
  {
    NCollection_List<TopoDS_Shape> L;
    down.Bind(S, L);
  }
  down(S).Append(SS);

  if (!up.IsBound(SS))
  {
    NCollection_List<TopoDS_Shape> L;
    up.Bind(SS, L);
  }
  up(SS).Append(S);
}

//=================================================================================================

void BRepAlgo_AsDes::Add(const TopoDS_Shape& S, const NCollection_List<TopoDS_Shape>& SS)
{
  NCollection_List<TopoDS_Shape>::Iterator it(SS);
  for (; it.More(); it.Next())
  {
    Add(S, it.Value());
  }
}

//=================================================================================================

void BRepAlgo_AsDes::Clear()
{
  up.Clear();
  down.Clear();
}

//=================================================================================================

bool BRepAlgo_AsDes::HasAscendant(const TopoDS_Shape& S) const
{
  return up.IsBound(S);
}

//=================================================================================================

bool BRepAlgo_AsDes::HasDescendant(const TopoDS_Shape& S) const
{
  return down.IsBound(S);
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepAlgo_AsDes::Ascendant(const TopoDS_Shape& S) const
{
  if (up.IsBound(S))
    return up(S);
  static NCollection_List<TopoDS_Shape> empty;
  return empty;
}

//=================================================================================================

const NCollection_List<TopoDS_Shape>& BRepAlgo_AsDes::Descendant(const TopoDS_Shape& S) const
{
  if (down.IsBound(S))
    return down(S);
  static NCollection_List<TopoDS_Shape> empty;
  return empty;
}

//=================================================================================================

NCollection_List<TopoDS_Shape>& BRepAlgo_AsDes::ChangeDescendant(const TopoDS_Shape& S)
{
  if (down.IsBound(S))
    return down.ChangeFind(S);
  static NCollection_List<TopoDS_Shape> empty;
  return empty;
}

//=================================================================================================

static void ReplaceInList(const TopoDS_Shape&             OldS,
                          const TopoDS_Shape&             NewS,
                          NCollection_List<TopoDS_Shape>& L)
{
  NCollection_Map<TopoDS_Shape>            aMS;
  NCollection_List<TopoDS_Shape>::Iterator it(L);
  for (; it.More(); it.Next())
  {
    aMS.Add(it.Value());
  }
  it.Initialize(L);
  while (it.More())
  {
    if (it.Value().IsSame(OldS))
    {
      TopAbs_Orientation O = it.Value().Orientation();
      if (aMS.Add(NewS.Oriented(O)))
      {
        L.InsertBefore(NewS.Oriented(O), it);
      }
      L.Remove(it);
    }
    else
      it.Next();
  }
}

//=================================================================================================

static void RemoveInList(const TopoDS_Shape& S, NCollection_List<TopoDS_Shape>& L)
{
  NCollection_List<TopoDS_Shape>::Iterator it(L);
  while (it.More())
  {
    if (it.Value().IsSame(S))
    {
      L.Remove(it);
      break;
    }
    it.Next();
  }
}

//=================================================================================================

bool BRepAlgo_AsDes::HasCommonDescendant(const TopoDS_Shape&             S1,
                                         const TopoDS_Shape&             S2,
                                         NCollection_List<TopoDS_Shape>& LC) const
{
  LC.Clear();
  if (HasDescendant(S1) && HasDescendant(S2))
  {
    NCollection_List<TopoDS_Shape>::Iterator it1(Descendant(S1));
    for (; it1.More(); it1.Next())
    {
      const TopoDS_Shape&                      DS1 = it1.Value();
      NCollection_List<TopoDS_Shape>::Iterator it2(Ascendant(DS1));
      for (; it2.More(); it2.Next())
      {
        const TopoDS_Shape& ADS1 = it2.Value();
        if (ADS1.IsSame(S2))
        {
          LC.Append(DS1);
        }
      }
    }
  }
  return (!LC.IsEmpty());
}

//=================================================================================================

void BRepAlgo_AsDes::BackReplace(const TopoDS_Shape&                   OldS,
                                 const TopoDS_Shape&                   NewS,
                                 const NCollection_List<TopoDS_Shape>& L,
                                 const bool                            InUp)
{
  NCollection_List<TopoDS_Shape>::Iterator it(L);
  for (; it.More(); it.Next())
  {
    const TopoDS_Shape& S = it.Value();
    if (InUp)
    {
      if (up.IsBound(S))
      {
        ReplaceInList(OldS, NewS, up.ChangeFind(S));
      }
    }
    else
    {
      if (down.IsBound(S))
      {
        ReplaceInList(OldS, NewS, down.ChangeFind(S));
      }
    }
  }
}

//=================================================================================================

void BRepAlgo_AsDes::Replace(const TopoDS_Shape& OldS, const TopoDS_Shape& NewS)
{
  for (int i = 0; i < 2; ++i)
  {
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                    aMap   = !i ? up : down;
    NCollection_List<TopoDS_Shape>* pLSOld = aMap.ChangeSeek(OldS);
    if (!pLSOld)
    {
      continue;
    }
    //
    bool InUp = i != 0;
    BackReplace(OldS, NewS, *pLSOld, InUp);
    //
    NCollection_List<TopoDS_Shape>* pLSNew = aMap.ChangeSeek(NewS);
    if (!pLSNew)
    {
      // filter the list
      NCollection_Map<TopoDS_Shape>            aMS;
      NCollection_List<TopoDS_Shape>::Iterator aIt(*pLSOld);
      for (; aIt.More();)
      {
        if (!aMS.Add(aIt.Value()))
        {
          pLSOld->Remove(aIt);
        }
        else
        {
          aIt.Next();
        }
      }
      aMap.Bind(NewS, *pLSOld);
    }
    else
    {
      // avoid duplicates
      NCollection_Map<TopoDS_Shape>            aMS;
      NCollection_List<TopoDS_Shape>::Iterator aIt(*pLSNew);
      for (; aIt.More(); aIt.Next())
      {
        aMS.Add(aIt.Value());
      }
      //
      aIt.Initialize(*pLSOld);
      for (; aIt.More(); aIt.Next())
      {
        const TopoDS_Shape& aS = aIt.Value();
        if (aMS.Add(aS))
        {
          pLSNew->Append(aS);
        }
      }
    }
    //
    aMap.UnBind(OldS);
  }
}

//=================================================================================================

void BRepAlgo_AsDes::Remove(const TopoDS_Shape& SS)
{
  if (down.IsBound(SS))
  {
    throw Standard_ConstructionError(" BRepAlgo_AsDes::Remove");
  }
  if (!up.IsBound(SS))
  {
    throw Standard_ConstructionError(" BRepAlgo_AsDes::Remove");
  }
  NCollection_List<TopoDS_Shape>::Iterator it(up(SS));
  for (; it.More(); it.Next())
  {
    RemoveInList(SS, down.ChangeFind((it.Value())));
  }
  up.UnBind(SS);
}
