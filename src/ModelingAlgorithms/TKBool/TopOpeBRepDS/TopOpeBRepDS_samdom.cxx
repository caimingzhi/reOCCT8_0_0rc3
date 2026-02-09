#include <TopOpeBRepDS_samdom.hpp>

#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopOpeBRepDS_define.hpp>

static NCollection_IndexedDataMap<TopoDS_Shape,
                                  NCollection_List<TopoDS_Shape>,
                                  TopTools_ShapeMapHasher>* Gps1 = nullptr;
static NCollection_IndexedDataMap<TopoDS_Shape,
                                  NCollection_List<TopoDS_Shape>,
                                  TopTools_ShapeMapHasher>* Gps2 = nullptr;

static occ::handle<TopOpeBRepDS_HDataStructure>* Ghds;

void FDSSDM_Close()
{
  if (Gps1)
  {
    delete Gps1;
    Gps1 = nullptr;
  }

  if (Gps2)
  {
    delete Gps2;
    Gps2 = nullptr;
  }
}

Standard_EXPORT void FDSSDM_prepare(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  if (Gps1 == nullptr)
  {
    Gps1 = (NCollection_IndexedDataMap<
            TopoDS_Shape,
            NCollection_List<TopoDS_Shape>,
            TopTools_ShapeMapHasher>*)new NCollection_IndexedDataMap<TopoDS_Shape,
                                                                     NCollection_List<TopoDS_Shape>,
                                                                     TopTools_ShapeMapHasher>();
  }
  if (Gps2 == nullptr)
  {
    Gps2 = (NCollection_IndexedDataMap<
            TopoDS_Shape,
            NCollection_List<TopoDS_Shape>,
            TopTools_ShapeMapHasher>*)new NCollection_IndexedDataMap<TopoDS_Shape,
                                                                     NCollection_List<TopoDS_Shape>,
                                                                     TopTools_ShapeMapHasher>();
  }

  void* anAddr = (void*)&HDS;
  Ghds         = (occ::handle<TopOpeBRepDS_HDataStructure>*)anAddr;

  Gps1->Clear();
  Gps2->Clear();
  int i, n = HDS->NbShapes();
  for (i = 1; i <= n; i++)
  {
    const TopoDS_Shape& s   = HDS->Shape(i);
    bool                hsd = HDS->HasSameDomain(s);
    if (!hsd)
      continue;
    NCollection_List<TopoDS_Shape> thelist, thelist1;
    if (!Gps1->Contains(s))
      Gps1->Add(s, thelist);
    if (!Gps2->Contains(s))
      Gps2->Add(s, thelist1);
    NCollection_List<TopoDS_Shape>& LS1 = Gps1->ChangeFromKey(s);
    NCollection_List<TopoDS_Shape>& LS2 = Gps2->ChangeFromKey(s);
    FDSSDM_makes1s2(s, LS1, LS2);
  }
}

Standard_EXPORT void FDSSDM_makes1s2(const TopoDS_Shape&             S,
                                     NCollection_List<TopoDS_Shape>& L1,
                                     NCollection_List<TopoDS_Shape>& L2)

{

  const occ::handle<TopOpeBRepDS_HDataStructure>& HDS = *Ghds;

  L1.Append(S);

  int i;
  int nl1 = L1.Extent(), nl2 = L2.Extent();

  while (nl1 > 0 || nl2 > 0)
  {

    NCollection_List<TopoDS_Shape>::Iterator it1(L1);
    for (i = 1; i <= nl1; i++)
    {
      const TopoDS_Shape& S1 = it1.Value();

      NCollection_List<TopoDS_Shape>::Iterator itsd(HDS->SameDomain(S1));
      for (; itsd.More(); itsd.Next())
      {
        const TopoDS_Shape& S2 = itsd.Value();

        bool found = FDSSDM_contains(S2, L2);
        if (!found)
        {
          L2.Prepend(S2);
          nl2++;
        }
      }
      it1.Next();
    }
    nl1 = 0;

    NCollection_List<TopoDS_Shape>::Iterator it2(L2);
    for (i = 1; i <= nl2; i++)
    {
      const TopoDS_Shape& S2 = it2.Value();

      NCollection_List<TopoDS_Shape>::Iterator itsd(HDS->SameDomain(S2));
      for (; itsd.More(); itsd.Next())
      {
        const TopoDS_Shape& S1 = itsd.Value();

        bool found = FDSSDM_contains(S1, L1);
        if (!found)
        {
          L1.Prepend(S1);
          nl1++;
        }
      }
      it2.Next();
    }

    nl2 = 0;
  }
}

Standard_EXPORT void FDSSDM_s1s2makesordor(const NCollection_List<TopoDS_Shape>& LS1,
                                           const NCollection_List<TopoDS_Shape>& LS2,
                                           NCollection_List<TopoDS_Shape>&       LSO,
                                           NCollection_List<TopoDS_Shape>&       LDO)
{

  const occ::handle<TopOpeBRepDS_HDataStructure>& HDS = *Ghds;

  NCollection_List<TopoDS_Shape>::Iterator it(LS1);
  if (!it.More())
    return;
  const TopoDS_Shape& sref = it.Value();
  HDS->SameDomainReference(sref);
  TopOpeBRepDS_Config oref = HDS->SameDomainOrientation(sref);

  for (it.Initialize(LS1); it.More(); it.Next())
  {
    const TopoDS_Shape& s = it.Value();
    TopOpeBRepDS_Config o = HDS->SameDomainOrientation(s);

    if (o == oref && !FDSSDM_contains(s, LSO))
      LSO.Append(s);
    else if (o != oref && !FDSSDM_contains(s, LDO))
      LDO.Append(s);
  }

  for (it.Initialize(LS2); it.More(); it.Next())
  {
    const TopoDS_Shape& s = it.Value();
    TopOpeBRepDS_Config o = HDS->SameDomainOrientation(s);

    if (o == oref && !FDSSDM_contains(s, LSO))
      LSO.Append(s);
    else if (o != oref && !FDSSDM_contains(s, LDO))
      LDO.Append(s);
  }
}

Standard_EXPORT bool FDSSDM_hass1s2(const TopoDS_Shape& S)
{
  bool b1 = Gps1->Contains(S);
  bool b2 = Gps2->Contains(S);
  bool b  = (b1 && b2);
  return b;
}

Standard_EXPORT void FDSSDM_s1s2(const TopoDS_Shape&             S,
                                 NCollection_List<TopoDS_Shape>& LS1,
                                 NCollection_List<TopoDS_Shape>& LS2)
{
  LS1.Clear();
  LS2.Clear();
  bool b = FDSSDM_hass1s2(S);
  if (!b)
  {
    FDSSDM_makes1s2(S, LS1, LS2);
    return;
  }
  const NCollection_List<TopoDS_Shape>& L1 = Gps1->FindFromKey(S);
  const NCollection_List<TopoDS_Shape>& L2 = Gps2->FindFromKey(S);
  FDSSDM_copylist(L1, LS1);
  FDSSDM_copylist(L2, LS2);
}

Standard_EXPORT void FDSSDM_sordor(const TopoDS_Shape&             S,
                                   NCollection_List<TopoDS_Shape>& LSO,
                                   NCollection_List<TopoDS_Shape>& LDO)
{
  LSO.Clear();
  LDO.Clear();
  NCollection_List<TopoDS_Shape> LS1, LS2;
  FDSSDM_s1s2(S, LS1, LS2);
  FDSSDM_s1s2makesordor(LS1, LS2, LSO, LDO);
}

Standard_EXPORT bool FDSSDM_contains(const TopoDS_Shape& S, const NCollection_List<TopoDS_Shape>& L)

{
  for (NCollection_List<TopoDS_Shape>::Iterator it(L); it.More(); it.Next())
  {
    const TopoDS_Shape& SL     = it.Value();
    bool                issame = SL.IsSame(S);
    if (issame)
      return true;
  }
  return false;
}

Standard_EXPORT void FDSSDM_copylist(const NCollection_List<TopoDS_Shape>& Lin,
                                     const int                             I1,
                                     const int                             I2,
                                     NCollection_List<TopoDS_Shape>&       Lou)

{
  NCollection_List<TopoDS_Shape>::Iterator it(Lin);
  for (int i = 1; it.More(); it.Next(), i++)
  {
    const TopoDS_Shape& EL = it.Value();
    if (i >= I1 && i <= I2)
    {
      Lou.Append(EL);
    }
  }
}

Standard_EXPORT void FDSSDM_copylist(const NCollection_List<TopoDS_Shape>& Lin,
                                     NCollection_List<TopoDS_Shape>&       Lou)

{
  const int I1 = 1;
  const int I2 = Lin.Extent();
  FDSSDM_copylist(Lin, I1, I2, Lou);
}
