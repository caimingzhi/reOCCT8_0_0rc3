#include <TopOpeBRepTool.hpp>
#include <TopOpeBRepTool_CLASSI.hpp>
#include <TopOpeBRepTool_REGUW.hpp>
#include <TopOpeBRepTool_TOOL.hpp>
#include <TopExp_Explorer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <BRep_Tool.hpp>
#include <TopoDS.hpp>

#define SAME (-1)
#define DIFF (-2)
#define UNKNOWN (0)
#define oneINtwo (1)
#define twoINone (2)

#define M_FORWARD(sta) (sta == TopAbs_FORWARD)
#define M_REVERSED(sta) (sta == TopAbs_REVERSED)
#define M_INTERNAL(sta) (sta == TopAbs_INTERNAL)
#define M_EXTERNAL(sta) (sta == TopAbs_EXTERNAL)

#ifdef OCCT_DEBUG
extern bool TopOpeBRepTool_GettraceREGUFA();
static NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> STATIC_mapw, STATIC_mapf;

static int FUN_adds(const TopoDS_Shape& s)
{
  TopAbs_ShapeEnum        typ = s.ShapeType();
  TCollection_AsciiString aa;
  int                     is = 0;
  if (typ == TopAbs_WIRE)
  {
    aa = TCollection_AsciiString("wi");
    is = STATIC_mapw.Add(s);
  }
  if (typ == TopAbs_FACE)
  {
    aa = TCollection_AsciiString("fa");
    is = STATIC_mapf.Add(s);
  }
  return is;
}

Standard_EXPORT void FUN_tool_coutsta(const int& sta, const int& i1, const int& i2)
{
  switch (sta)
  {
    case SAME:
      std::cout << i1 << " gives SAME bnd with " << i2 << std::endl;
      break;
    case DIFF:
      std::cout << i1 << " gives  OUT bnd with " << i2 << std::endl;
      break;
    case oneINtwo:
      std::cout << i1 << " is IN " << i2 << std::endl;
      break;
    case twoINone:
      std::cout << i2 << " is IN " << i1 << std::endl;
      break;
  }
}
#endif

Standard_EXPORT void FUN_addOwlw(const TopoDS_Shape&                   Ow,
                                 const NCollection_List<TopoDS_Shape>& lw,
                                 NCollection_List<TopoDS_Shape>&       lresu);

bool TopOpeBRepTool::RegularizeWires(
  const TopoDS_Face& theFace,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    mapoldWnewW,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    ESplits)
{
  if (theFace.IsNull())
    return false;
  TopoDS_Shape aLocalShape = theFace.Oriented(TopAbs_FORWARD);
  TopoDS_Face  aFace       = TopoDS::Face(aLocalShape);

  TopOpeBRepTool_REGUW REGUW(aFace);
  REGUW.SetOwNw(mapoldWnewW);
  REGUW.SetEsplits(ESplits);

  TopExp_Explorer exw(aFace, TopAbs_WIRE);
  for (; exw.More(); exw.Next())
  {
    const TopoDS_Shape& W = exw.Current();
    REGUW.Init(W);
    bool ok = REGUW.MapS();
    if (!ok)
      return false;
    ok = REGUW.SplitEds();
    if (!ok)
      return false;
    ok = REGUW.REGU();
    if (!ok)
      return false;
  }

  REGUW.GetEsplits(ESplits);
  REGUW.GetOwNw(mapoldWnewW);
  return true;
}

bool TopOpeBRepTool::Regularize(
  const TopoDS_Face&              theFace,
  NCollection_List<TopoDS_Shape>& aListOfFaces,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    ESplits)
{
  TopOpeBRepTool_REGUW REGUW(theFace);
  aListOfFaces.Clear();
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
       mapoldWnewW;
  bool regu = TopOpeBRepTool::RegularizeWires(theFace, mapoldWnewW, ESplits);
  if (regu)
  {
    regu = TopOpeBRepTool::RegularizeFace(theFace, mapoldWnewW, aListOfFaces);
  }
  return regu;
}

Standard_EXPORT bool FUN_tool_ClassifW(
  const TopoDS_Face& F,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    mapOwNw,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    mapWlow)
{
#ifdef OCCT_DEBUG
  bool trc = TopOpeBRepTool_GettraceREGUFA();
  if (trc)
    std::cout << "** ClassifW :" << std::endl;
#endif
  double       tolF        = BRep_Tool::Tolerance(F);
  double       toluv       = TopOpeBRepTool_TOOL::TolUV(F, tolF);
  TopoDS_Shape aLocalShape = F.Oriented(TopAbs_FORWARD);
  TopoDS_Face  FFOR        = TopoDS::Face(aLocalShape);

  TopOpeBRepTool_CLASSI CLASSI;
  CLASSI.Init2d(FFOR);

  NCollection_List<TopoDS_Shape> null;
  NCollection_List<TopoDS_Shape> oldW;
  int                            noldW = mapOwNw.Extent();
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itm(mapOwNw);

  if (noldW == 1)
  {
    const NCollection_List<TopoDS_Shape>& low = itm.Value();
    bool                                  ok  = CLASSI.Classilist(low, mapWlow);
    return ok;
  }

  NCollection_List<TopoDS_Shape> lOws;
  for (; itm.More(); itm.Next())
  {
    const TopoDS_Shape& owi = itm.Key();
    lOws.Append(owi);
    const NCollection_List<TopoDS_Shape>& low = itm.Value();
    NCollection_List<TopoDS_Shape>        lwresu;
    FUN_addOwlw(owi, low, lwresu);
    NCollection_List<TopoDS_Shape>::Iterator itw(lwresu);
    for (; itw.More(); itw.Next())
      mapWlow.Bind(itw.Value(), null);
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapdone;
  int                                                    nOw = noldW;
  int nite = 0, nitemax = int(nOw * (nOw - 1) / 2);
  while (nite <= nitemax)
  {
    nOw = lOws.Extent();
    if (nOw == 0)
      break;

    NCollection_List<TopoDS_Shape>::Iterator itOw(lOws);
    const TopoDS_Shape&                      Ow1  = itOw.Value();
    bool                                     isb1 = mapWlow.IsBound(Ow1);
    isb1                                          = isb1 || !mapdone.Contains(Ow1);
    if (!isb1)
      continue;

    const NCollection_List<TopoDS_Shape>& lw1 = mapOwNw.Find(Ow1);

    if (nOw == 1)
    {

      break;
    }

    itOw.Next();
    bool         OUTall = false;
    TopoDS_Shape Ow2;
    int          sta12 = UNKNOWN;
    for (; itOw.More(); itOw.Next())
    {
      Ow2       = itOw.Value();
      bool isb2 = mapWlow.IsBound(Ow2);
      isb2      = isb2 || !mapdone.Contains(Ow2);
      if (!isb2)
        continue;
      int stabnd2d12 = CLASSI.ClassiBnd2d(Ow1, Ow2, toluv, true);
      sta12          = CLASSI.Classip2d(Ow1, Ow2, stabnd2d12);
      if (sta12 == DIFF)
      {
        OUTall = true;
        continue;
      }
      else if ((sta12 == UNKNOWN) || (sta12 == SAME))
        return false;
      break;
    }
    if (OUTall)
    {

      NCollection_List<TopoDS_Shape> ldone;
      FUN_addOwlw(Ow1, lw1, ldone);
      NCollection_List<TopoDS_Shape>::Iterator itw(ldone);
      for (; itw.More(); itw.Next())
        mapdone.Add(itw.Value());
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << "old wires :wi" << FUN_adds(Ow1) << " is OUT all old wires" << std::endl;
#endif
      lOws.RemoveFirst();
    }
    else
    {
#ifdef OCCT_DEBUG
      if (trc)
      {
        std::cout << "old wires :wi -> ";
        FUN_tool_coutsta(sta12, FUN_adds(Ow1), FUN_adds(Ow2));
        std::cout << std::endl;
      }
#endif
      const NCollection_List<TopoDS_Shape>& lw2 = mapOwNw.Find(Ow2);

      NCollection_List<TopoDS_Shape> lw1r;
      FUN_addOwlw(Ow1, lw1, lw1r);
      NCollection_List<TopoDS_Shape> lw2r;
      FUN_addOwlw(Ow2, lw2, lw2r);
      NCollection_List<TopoDS_Shape> lgre, lsma;
      if (sta12 == oneINtwo)
      {
        lgre.Append(lw2r);
        lsma.Append(lw1r);
      }
      if (sta12 == twoINone)
      {
        lgre.Append(lw1r);
        lsma.Append(lw2r);
      }

      NCollection_List<TopoDS_Shape>::Iterator itsma(lsma);
      for (; itsma.More(); itsma.Next())
      {
        const TopoDS_Shape& wsma   = itsma.Value();
        bool                isbsma = mapWlow.IsBound(wsma);
        isbsma                     = isbsma || !mapdone.Contains(wsma);
        if (!isbsma)
          continue;

        NCollection_List<TopoDS_Shape>::Iterator itgre(lgre);
        for (; itgre.More(); itgre.Next())
        {
          const TopoDS_Shape& wgre   = itgre.Value();
          bool                isbgre = mapWlow.IsBound(wgre);
          isbgre                     = isbgre || !mapdone.Contains(wgre);
          if (!isbgre)
            continue;

          int stabnd2d = CLASSI.ClassiBnd2d(wsma, wgre, toluv, true);
          int sta      = CLASSI.Classip2d(wsma, wgre, stabnd2d);
#ifdef OCCT_DEBUG
          if (trc)
          {
            std::cout << " wires :wi -> ";
            FUN_tool_coutsta(sta, FUN_adds(wsma), FUN_adds(wgre));
            std::cout << std::endl;
          }
#endif

          if (sta == DIFF)
            continue;
          else if (sta == oneINtwo)
          {
            mapWlow.ChangeFind(wgre).Append(mapWlow.ChangeFind(wsma));
            mapWlow.UnBind(wsma);
          }
          else if (sta == twoINone)
          {
            mapWlow.ChangeFind(wsma).Append(mapWlow.ChangeFind(wgre));
            mapWlow.UnBind(wgre);
          }
          else
            return false;
        }
      }
      lOws.RemoveFirst();
    }
  }
  return true;
}

bool TopOpeBRepTool::RegularizeFace(
  const TopoDS_Face& theFace,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                  mapoldWnewW,
  NCollection_List<TopoDS_Shape>& newFaces)
{

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    mapWlow;

  TopoDS_Shape aLocalShape = theFace.Oriented(TopAbs_FORWARD);
  TopoDS_Face  aFace       = TopoDS::Face(aLocalShape);

  bool classifok = FUN_tool_ClassifW(aFace, mapoldWnewW, mapWlow);
  if (!classifok)
    return false;

  bool facesbuilt = TopOpeBRepTool_TOOL::WireToFace(theFace, mapWlow, newFaces);
  return facesbuilt;
}
