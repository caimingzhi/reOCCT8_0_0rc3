#ifndef No_Exception
  #define No_Exception
#endif

#include <HLRAlgo_BiPoint.hpp>

HLRAlgo_BiPoint::HLRAlgo_BiPoint(const double X1,
                                 const double Y1,
                                 const double Z1,
                                 const double X2,
                                 const double Y2,
                                 const double Z2,
                                 const double XT1,
                                 const double YT1,
                                 const double ZT1,
                                 const double XT2,
                                 const double YT2,
                                 const double ZT2,
                                 const int    Index,
                                 const bool   reg1,
                                 const bool   regn,
                                 const bool   outl,
                                 const bool   intl)
{
  myPoints.Pnt1.SetCoord(X1, Y1, Z1);
  myPoints.Pnt2.SetCoord(X2, Y2, Z2);
  myPoints.PntP1.SetCoord(XT1, YT1, ZT1);
  myPoints.PntP2.SetCoord(XT2, YT2, ZT2);
  myIndices.ShapeIndex = Index;
  myIndices.FaceConex1 = myIndices.Face1Pt1 = myIndices.Face1Pt2 = myIndices.FaceConex2 =
    myIndices.Face2Pt1 = myIndices.Face2Pt2 = 0;
  myIndices.SegFlags                        = 0;
  Rg1Line(reg1);
  RgNLine(regn);
  OutLine(outl);
  IntLine(intl);
  Hidden(false);
}

HLRAlgo_BiPoint::HLRAlgo_BiPoint(const double X1,
                                 const double Y1,
                                 const double Z1,
                                 const double X2,
                                 const double Y2,
                                 const double Z2,
                                 const double XT1,
                                 const double YT1,
                                 const double ZT1,
                                 const double XT2,
                                 const double YT2,
                                 const double ZT2,
                                 const int    Index,
                                 const int    flag)
{
  myPoints.Pnt1        = gp_XYZ(X1, Y1, Z1);
  myPoints.Pnt2        = gp_XYZ(X2, Y2, Z2);
  myPoints.PntP1       = gp_XYZ(XT1, YT1, ZT1);
  myPoints.PntP2       = gp_XYZ(XT2, YT2, ZT2);
  myIndices.ShapeIndex = Index;
  myIndices.FaceConex1 = myIndices.Face1Pt1 = myIndices.Face1Pt2 = myIndices.FaceConex2 =
    myIndices.Face2Pt1 = myIndices.Face2Pt2 = 0;
  myIndices.SegFlags                        = flag;
  Hidden(false);
}

HLRAlgo_BiPoint::HLRAlgo_BiPoint(const double X1,
                                 const double Y1,
                                 const double Z1,
                                 const double X2,
                                 const double Y2,
                                 const double Z2,
                                 const double XT1,
                                 const double YT1,
                                 const double ZT1,
                                 const double XT2,
                                 const double YT2,
                                 const double ZT2,
                                 const int    Index,
                                 const int    i1,
                                 const int    i1p1,
                                 const int    i1p2,
                                 const bool   reg1,
                                 const bool   regn,
                                 const bool   outl,
                                 const bool   intl)
{
  myPoints.Pnt1.SetCoord(X1, Y1, Z1);
  myPoints.Pnt2.SetCoord(X2, Y2, Z2);
  myPoints.PntP1.SetCoord(XT1, YT1, ZT1);
  myPoints.PntP2.SetCoord(XT2, YT2, ZT2);
  myIndices.ShapeIndex = Index;
  myIndices.FaceConex1 = i1;
  myIndices.Face1Pt1   = i1p1;
  myIndices.Face1Pt2   = i1p2;
  myIndices.FaceConex2 = myIndices.Face2Pt1 = myIndices.Face2Pt2 = 0;
  myIndices.SegFlags                                             = 0;
  Rg1Line(reg1);
  RgNLine(regn);
  OutLine(outl);
  IntLine(intl);
  Hidden(false);
}

HLRAlgo_BiPoint::HLRAlgo_BiPoint(const double X1,
                                 const double Y1,
                                 const double Z1,
                                 const double X2,
                                 const double Y2,
                                 const double Z2,
                                 const double XT1,
                                 const double YT1,
                                 const double ZT1,
                                 const double XT2,
                                 const double YT2,
                                 const double ZT2,
                                 const int    Index,
                                 const int    i1,
                                 const int    i1p1,
                                 const int    i1p2,
                                 const int    flag)
{
  myPoints.Pnt1.SetCoord(X1, Y1, Z1);
  myPoints.Pnt2.SetCoord(X2, Y2, Z2);
  myPoints.PntP1.SetCoord(XT1, YT1, ZT1);
  myPoints.PntP2.SetCoord(XT2, YT2, ZT2);
  myIndices.ShapeIndex = Index;
  myIndices.FaceConex1 = i1;
  myIndices.Face1Pt1   = i1p1;
  myIndices.Face1Pt2   = i1p2;
  myIndices.FaceConex2 = myIndices.Face2Pt1 = myIndices.Face2Pt2 = 0;
  myIndices.SegFlags                                             = flag;
  Hidden(false);
}

HLRAlgo_BiPoint::HLRAlgo_BiPoint(const double X1,
                                 const double Y1,
                                 const double Z1,
                                 const double X2,
                                 const double Y2,
                                 const double Z2,
                                 const double XT1,
                                 const double YT1,
                                 const double ZT1,
                                 const double XT2,
                                 const double YT2,
                                 const double ZT2,
                                 const int    Index,
                                 const int    i1,
                                 const int    i1p1,
                                 const int    i1p2,
                                 const int    i2,
                                 const int    i2p1,
                                 const int    i2p2,
                                 const bool   reg1,
                                 const bool   regn,
                                 const bool   outl,
                                 const bool   intl)
{
  myPoints.Pnt1.SetCoord(X1, Y1, Z1);
  myPoints.Pnt2.SetCoord(X2, Y2, Z2);
  myPoints.PntP1.SetCoord(XT1, YT1, ZT1);
  myPoints.PntP2.SetCoord(XT2, YT2, ZT2);
  myIndices.ShapeIndex = Index;
  myIndices.FaceConex1 = i1;
  myIndices.Face1Pt1   = i1p1;
  myIndices.Face1Pt2   = i1p2;
  myIndices.FaceConex2 = i2;
  myIndices.Face2Pt1   = i2p1;
  myIndices.Face2Pt2   = i2p2;
  myIndices.SegFlags   = 0;
  Rg1Line(reg1);
  RgNLine(regn);
  OutLine(outl);
  IntLine(intl);
  Hidden(false);
}

HLRAlgo_BiPoint::HLRAlgo_BiPoint(const double X1,
                                 const double Y1,
                                 const double Z1,
                                 const double X2,
                                 const double Y2,
                                 const double Z2,
                                 const double XT1,
                                 const double YT1,
                                 const double ZT1,
                                 const double XT2,
                                 const double YT2,
                                 const double ZT2,
                                 const int    Index,
                                 const int    i1,
                                 const int    i1p1,
                                 const int    i1p2,
                                 const int    i2,
                                 const int    i2p1,
                                 const int    i2p2,
                                 const int    flag)
{
  myPoints.Pnt1.SetCoord(X1, Y1, Z1);
  myPoints.Pnt2.SetCoord(X2, Y2, Z2);
  myPoints.PntP1.SetCoord(XT1, YT1, ZT1);
  myPoints.PntP2.SetCoord(XT2, YT2, ZT2);
  myIndices.ShapeIndex = Index;
  myIndices.FaceConex1 = i1;
  myIndices.Face1Pt1   = i1p1;
  myIndices.Face1Pt2   = i1p2;
  myIndices.FaceConex2 = i2;
  myIndices.Face2Pt1   = i2p1;
  myIndices.Face2Pt2   = i2p2;
  myIndices.SegFlags   = flag;
  Hidden(false);
}
