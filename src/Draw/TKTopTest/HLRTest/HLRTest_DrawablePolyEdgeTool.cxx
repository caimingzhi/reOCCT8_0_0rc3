#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <HLRAlgo_EdgeIterator.hpp>
#include <HLRAlgo_EdgeStatus.hpp>
#include <HLRBRep_PolyAlgo.hpp>
#include <HLRTest_DrawablePolyEdgeTool.hpp>
#include <OSD_Chronometer.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRTest_DrawablePolyEdgeTool, Draw_Drawable3D)

#define PntX1 ((double*)Coordinates)[0]
#define PntY1 ((double*)Coordinates)[1]
#define PntZ1 ((double*)Coordinates)[2]
#define PntX2 ((double*)Coordinates)[3]
#define PntY2 ((double*)Coordinates)[4]
#define PntZ2 ((double*)Coordinates)[5]

//=================================================================================================

HLRTest_DrawablePolyEdgeTool::HLRTest_DrawablePolyEdgeTool(const occ::handle<HLRBRep_PolyAlgo>& Alg,
                                                           const int  ViewId,
                                                           const bool Debug)
    : myAlgo(Alg),
      myDispRg1(false),
      myDispRgN(false),
      myDispHid(false),
      myViewId(ViewId),
      myDebug(Debug),
      myHideMode(true)
{
  OSD_Chronometer ChronHide;
  if (myDebug)
  {
    ChronHide.Reset();
    ChronHide.Start();
  }
  double               sta, end, dx, dy, dz;
  float                tolsta, tolend;
  HLRAlgo_EdgeIterator It;
  myBiPntVis.Clear();
  myBiPntHid.Clear();
  void*              Coordinates;
  HLRAlgo_EdgeStatus status;
  TopoDS_Shape       S;
  bool               reg1, regn, outl, intl;

  for (myAlgo->InitHide(); myAlgo->MoreHide(); myAlgo->NextHide())
  {
    Coordinates = &myAlgo->Hide(status, S, reg1, regn, outl, intl);
    dx          = PntX2 - PntX1;
    dy          = PntY2 - PntY1;
    dz          = PntZ2 - PntZ1;

    for (It.InitVisible(status); It.MoreVisible(); It.NextVisible())
    {
      It.Visible(sta, tolsta, end, tolend);
      myBiPntVis.Append(HLRBRep_BiPoint(PntX1 + sta * dx,
                                        PntY1 + sta * dy,
                                        PntZ1 + sta * dz,
                                        PntX1 + end * dx,
                                        PntY1 + end * dy,
                                        PntZ1 + end * dz,
                                        S,
                                        reg1,
                                        regn,
                                        outl,
                                        intl));
    }

    for (It.InitHidden(status); It.MoreHidden(); It.NextHidden())
    {
      It.Hidden(sta, tolsta, end, tolend);
      myBiPntHid.Append(HLRBRep_BiPoint(PntX1 + sta * dx,
                                        PntY1 + sta * dy,
                                        PntZ1 + sta * dz,
                                        PntX1 + end * dx,
                                        PntY1 + end * dy,
                                        PntZ1 + end * dz,
                                        S,
                                        reg1,
                                        regn,
                                        outl,
                                        intl));
    }
  }
  if (myDebug)
  {
    ChronHide.Stop();
    std::cout << " Temps Hide   :";
    ChronHide.Show();
  }
}

//=================================================================================================

void HLRTest_DrawablePolyEdgeTool::DrawOn(Draw_Display& D) const
{
  if (myViewId == D.ViewId())
  {
    if (myHideMode)
    {
      NCollection_List<HLRBRep_BiPoint>::Iterator It;
      if (myDispHid)
      {
        D.SetColor(Draw_bleu);

        for (It.Initialize(myBiPntHid); It.More(); It.Next())
        {
          const HLRBRep_BiPoint& BP     = It.Value();
          bool                   todraw = true;
          if ((!myDispRg1 && BP.Rg1Line() && !BP.OutLine())
              || (!myDispRgN && BP.RgNLine() && !BP.OutLine()))
            todraw = false;
          if (todraw)
          {
            D.MoveTo(BP.P1());
            D.DrawTo(BP.P2());
          }
        }
      }
      D.SetColor(Draw_vert);

      for (It.Initialize(myBiPntVis); It.More(); It.Next())
      {
        const HLRBRep_BiPoint& BP     = It.Value();
        bool                   todraw = true;
        if ((!myDispRg1 && BP.Rg1Line() && !BP.OutLine())
            || (!myDispRgN && BP.RgNLine() && !BP.OutLine()))
          todraw = false;
        if (todraw)
        {
          D.MoveTo(BP.P1());
          D.DrawTo(BP.P2());
        }
      }
    }
    else
    {
      void*        Coordinates;
      TopoDS_Shape S;
      bool         reg1, regn, outl, intl;
      D.SetColor(Draw_vert);

      for (myAlgo->InitShow(); myAlgo->MoreShow(); myAlgo->NextShow())
      {
        Coordinates = &myAlgo->Show(S, reg1, regn, outl, intl);
        bool todraw = true;
        if ((!myDispRg1 && reg1 && !outl) || (!myDispRgN && regn && !outl))
          todraw = false;
        if (todraw)
        {
          D.MoveTo(gp_Pnt(PntX1, PntY1, PntZ1));
          D.DrawTo(gp_Pnt(PntX2, PntY2, PntZ2));
        }
      }
    }
  }
}
