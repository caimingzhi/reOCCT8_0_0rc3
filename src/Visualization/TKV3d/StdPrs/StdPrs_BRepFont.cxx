#include <StdPrs_BRepFont.hpp>

#include <BRep_Tool.hpp>
#include <BRepTopAdaptor_FClass2d.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <Font_FTLibrary.hpp>
#include <Font_FontMgr.hpp>
#include <GCE2d_MakeSegment.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom_Plane.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Line.hpp>
#include <GeomAPI.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomLib.hpp>
#include <gp_Pln.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>

#ifdef HAVE_FREETYPE
  #include <ft2build.h>
  #include FT_FREETYPE_H
#endif

IMPLEMENT_STANDARD_RTTIEXT(StdPrs_BRepFont, Standard_Transient)

namespace
{

  static const unsigned int      THE_FONT_SIZE      = 72;
  static const unsigned int      THE_RESOLUTION_DPI = 4800;
  static const Font_FTFontParams THE_FONT_PARAMS(THE_FONT_SIZE, THE_RESOLUTION_DPI);

  inline double getScale(const double theSize)
  {
    return theSize / double(THE_FONT_SIZE) * 72.0 / double(THE_RESOLUTION_DPI);
  }

#ifdef HAVE_FREETYPE

  static gp_XY readFTVec(const FT_Vector& theVec,
                         const double     theScaleUnits,
                         const double     theWidthScaling = 1.0)
  {
    return gp_XY(theScaleUnits * double(theVec.x) * theWidthScaling / 64.0,
                 theScaleUnits * double(theVec.y) / 64.0);
  }

  static TopAbs_State classifyWW(const TopoDS_Wire& theW1,
                                 const TopoDS_Wire& theW2,
                                 const TopoDS_Face& theF)
  {
    TopAbs_State aRes = TopAbs_UNKNOWN;

    TopoDS_Face aF = TopoDS::Face(theF.EmptyCopied());
    aF.Orientation(TopAbs_FORWARD);
    BRep_Builder aB;
    aB.Add(aF, theW1);
    BRepTopAdaptor_FClass2d aClass2d(aF, ::Precision::PConfusion());
    for (TopoDS_Iterator anEdgeIter(theW2); anEdgeIter.More(); anEdgeIter.Next())
    {
      const TopoDS_Edge&        anEdge  = TopoDS::Edge(anEdgeIter.Value());
      double                    aPFirst = 0.0, aPLast = 0.0;
      occ::handle<Geom2d_Curve> aCurve2d = BRep_Tool::CurveOnSurface(anEdge, theF, aPFirst, aPLast);
      if (aCurve2d.IsNull())
      {
        continue;
      }

      gp_Pnt2d     aPnt2d = aCurve2d->Value((aPFirst + aPLast) / 2.0);
      TopAbs_State aState = aClass2d.Perform(aPnt2d, false);
      if (aState == TopAbs_OUT || aState == TopAbs_IN)
      {
        if (aRes == TopAbs_UNKNOWN)
        {
          aRes = aState;
        }
        else if (aRes != aState)
        {
          return TopAbs_UNKNOWN;
        }
      }
    }
    return aRes;
  }
#endif
} // namespace

StdPrs_BRepFont::StdPrs_BRepFont()
    : myPrecision(Precision::Confusion()),
      myScaleUnits(1.0),
      myIsCompositeCurve(false),
      my3Poles(1, 3),
      my4Poles(1, 4)
{
  myFTFont = new Font_FTFont();
  init();
}

void StdPrs_BRepFont::init()
{
  mySurface                                   = new Geom_Plane(gp_Pln(gp::XOY()));
  myCurve2dAdaptor                            = new Geom2dAdaptor_Curve();
  occ::handle<Adaptor3d_Surface> aSurfAdaptor = new GeomAdaptor_Surface(mySurface);
  myCurvOnSurf.Load(aSurfAdaptor);
}

StdPrs_BRepFont::StdPrs_BRepFont(const NCollection_String& theFontPath,
                                 const double              theSize,
                                 const int                 theFaceId)
    : myPrecision(Precision::Confusion()),
      myScaleUnits(1.0),
      myIsCompositeCurve(false),
      my3Poles(1, 3),
      my4Poles(1, 4)
{
  init();
  if (theSize <= myPrecision * 100.0)
  {
    return;
  }

  myScaleUnits = getScale(theSize);
  myFTFont     = new Font_FTFont();
  myFTFont->Init(theFontPath.ToCString(), THE_FONT_PARAMS, theFaceId);
}

StdPrs_BRepFont::StdPrs_BRepFont(const NCollection_String& theFontName,
                                 const Font_FontAspect     theFontAspect,
                                 const double              theSize,
                                 const Font_StrictLevel    theStrictLevel)
    : myPrecision(Precision::Confusion()),
      myScaleUnits(1.0),
      myIsCompositeCurve(false),
      my3Poles(1, 3),
      my4Poles(1, 4)
{
  init();
  if (theSize <= myPrecision * 100.0)
  {
    return;
  }

  myScaleUnits = getScale(theSize);
  myFTFont     = new Font_FTFont();
  myFTFont->FindAndInit(theFontName.ToCString(), theFontAspect, THE_FONT_PARAMS, theStrictLevel);
}

void StdPrs_BRepFont::Release()
{
  myCache.Clear();
  myFTFont->Release();
}

occ::handle<StdPrs_BRepFont> StdPrs_BRepFont::FindAndCreate(
  const TCollection_AsciiString& theFontName,
  const Font_FontAspect          theFontAspect,
  const double                   theSize,
  const Font_StrictLevel         theStrictLevel)
{
  occ::handle<StdPrs_BRepFont> aFont = new StdPrs_BRepFont();

  if (aFont->FindAndInit(theFontName, theFontAspect, theSize, theStrictLevel))
    return aFont;

  return occ::handle<StdPrs_BRepFont>();
}

void StdPrs_BRepFont::SetCompositeCurveMode(const bool theToConcatenate)
{
  if (myIsCompositeCurve != theToConcatenate)
  {
    myIsCompositeCurve = theToConcatenate;
    myCache.Clear();
  }
}

bool StdPrs_BRepFont::Init(const NCollection_String& theFontPath,
                           const double              theSize,
                           const int                 theFaceId)
{
  if (theSize <= myPrecision * 100.0)
  {
    return false;
  }

  myScaleUnits = getScale(theSize);
  myCache.Clear();
  return myFTFont->Init(theFontPath.ToCString(), THE_FONT_PARAMS, theFaceId);
}

bool StdPrs_BRepFont::FindAndInit(const TCollection_AsciiString& theFontName,
                                  const Font_FontAspect          theFontAspect,
                                  const double                   theSize,
                                  const Font_StrictLevel         theStrictLevel)
{
  if (theSize <= myPrecision * 100.0)
  {
    return false;
  }

  myScaleUnits = getScale(theSize);
  myCache.Clear();
  return myFTFont->FindAndInit(theFontName.ToCString(),
                               theFontAspect,
                               THE_FONT_PARAMS,
                               theStrictLevel);
}

TopoDS_Shape StdPrs_BRepFont::RenderGlyph(const char32_t& theChar)
{
  TopoDS_Shape                aShape;
  std::lock_guard<std::mutex> aLock(myMutex);
  renderGlyph(theChar, aShape);
  return aShape;
}

bool StdPrs_BRepFont::to3d(const occ::handle<Geom2d_Curve>& theCurve2d,
                           const GeomAbs_Shape              theContinuity,
                           occ::handle<Geom_Curve>&         theCurve3d)
{
  double aMaxDeviation   = 0.0;
  double anAverDeviation = 0.0;
  myCurve2dAdaptor->Load(theCurve2d);
  const occ::handle<Adaptor2d_Curve2d>& aCurve = myCurve2dAdaptor;
  myCurvOnSurf.Load(aCurve);
  GeomLib::BuildCurve3d(myPrecision,
                        myCurvOnSurf,
                        myCurve2dAdaptor->FirstParameter(),
                        myCurve2dAdaptor->LastParameter(),
                        theCurve3d,
                        aMaxDeviation,
                        anAverDeviation,
                        theContinuity);
  return !theCurve3d.IsNull();
}

bool StdPrs_BRepFont::buildFaces(const NCollection_Sequence<TopoDS_Wire>& theWires,
                                 TopoDS_Shape&                            theRes)
{
#ifdef HAVE_FREETYPE

  NCollection_DataMap<TopoDS_Shape, NCollection_Sequence<TopoDS_Wire>, TopTools_ShapeMapHasher>
                                                                  aMapOutInts;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> aMapNbOuts;
  TopoDS_Face                                                     aF;
  myBuilder.MakeFace(aF, mySurface, myPrecision);
  int aWireIter1Index = 1;
  for (NCollection_Sequence<TopoDS_Wire>::Iterator aWireIter1(theWires); aWireIter1.More();
       ++aWireIter1Index, aWireIter1.Next())
  {
    const TopoDS_Wire& aW1 = aWireIter1.Value();
    if (!aMapNbOuts.IsBound(aW1))
    {
      const int aNbOuts = 0;
      aMapNbOuts.Bind(aW1, aNbOuts);
    }

    NCollection_Sequence<TopoDS_Wire>* anIntWs =
      aMapOutInts.Bound(aW1, NCollection_Sequence<TopoDS_Wire>());
    int aWireIter2Index = 1;
    for (NCollection_Sequence<TopoDS_Wire>::Iterator aWireIter2(theWires); aWireIter2.More();
         ++aWireIter2Index, aWireIter2.Next())
    {
      if (aWireIter1Index == aWireIter2Index)
      {
        continue;
      }

      const TopoDS_Wire& aW2    = aWireIter2.Value();
      const TopAbs_State aClass = classifyWW(aW1, aW2, aF);
      if (aClass == TopAbs_IN)
      {
        anIntWs->Append(aW2);
        if (int* aNbOutsPtr = aMapNbOuts.ChangeSeek(aW2))
        {
          ++(*aNbOutsPtr);
        }
        else
        {
          const int aNbOuts = 1;
          aMapNbOuts.Bind(aW2, aNbOuts);
        }
      }
    }
  }

  for (NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>::Iterator anOutIter(
         aMapNbOuts);
       anOutIter.More();
       anOutIter.Next())
  {
    const int aTmp = anOutIter.Value() % 2;
    if (aTmp > 0)
    {

      aMapOutInts.UnBind(anOutIter.Key());
    }
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> anUsedShapes;
  TopoDS_Compound                                        aFaceComp;
  myBuilder.MakeCompound(aFaceComp);
  for (; !aMapOutInts.IsEmpty();)
  {

    TopoDS_Shape aW;
    int          aMaxNbOuts = -1;
    for (NCollection_DataMap<TopoDS_Shape,
                             NCollection_Sequence<TopoDS_Wire>,
                             TopTools_ShapeMapHasher>::Iterator itMOI(aMapOutInts);
         itMOI.More();
         itMOI.Next())
    {
      const TopoDS_Shape& aKey    = itMOI.Key();
      const int           aNbOuts = aMapNbOuts.Find(aKey);
      if (aNbOuts > aMaxNbOuts)
      {
        aMaxNbOuts = aNbOuts;
        aW         = aKey;
      }
    }

    TopoDS_Face aNewF;
    myBuilder.MakeFace(aNewF, mySurface, myPrecision);
    myBuilder.Add(aNewF, aW);
    anUsedShapes.Add(aW);
    const NCollection_Sequence<TopoDS_Wire>& anIns = aMapOutInts.Find(aW);
    for (NCollection_Sequence<TopoDS_Wire>::Iterator aWireIter(anIns); aWireIter.More();
         aWireIter.Next())
    {
      TopoDS_Wire aWin = aWireIter.Value();
      if (anUsedShapes.Contains(aWin))
      {
        continue;
      }

      aWin.Reverse();
      myBuilder.Add(aNewF, aWin);
      anUsedShapes.Add(aWin);
    }

    myBuilder.Add(aFaceComp, aNewF);
    aMapOutInts.UnBind(aW);
  }

  if (aFaceComp.NbChildren() == 0)
  {
    return false;
  }

  if (aFaceComp.NbChildren() == 1)
  {
    theRes = TopoDS_Iterator(aFaceComp).Value();
  }
  else
  {
    theRes = aFaceComp;
  }
  return true;
#else
  (void)theWires;
  (void)theRes;
  return false;
#endif
}

bool StdPrs_BRepFont::renderGlyph(const char32_t theChar, TopoDS_Shape& theShape)
{
  theShape.Nullify();
#ifdef HAVE_FREETYPE
  const FT_Outline* anOutline = myFTFont->renderGlyphOutline(theChar);
  if (!anOutline)
  {
    return false;
  }
  else if (myCache.Find(theChar, theShape))
  {
    return !theShape.IsNull();
  }

  if (!anOutline->n_contours)
    return false;

  TopLoc_Location                   aLoc;
  NCollection_Sequence<TopoDS_Wire> aWires;
  TopoDS_Compound                   aFaceCompDraft;

  for (short aContour = 0, aStartIndex = 0; aContour < anOutline->n_contours; ++aContour)
  {
    const FT_Vector* aPntList   = &anOutline->points[aStartIndex];
    const auto*      aTags      = &anOutline->tags[aStartIndex];
    const short      anEndIndex = anOutline->contours[aContour];
    const short      aPntsNb    = (anEndIndex - aStartIndex) + 1;
    aStartIndex                 = anEndIndex + 1;
    if (aPntsNb < 3 && !myFTFont->IsSingleStrokeFont())
    {

      continue;
    }

    BRepBuilderAPI_MakeWire aWireMaker;

    gp_XY aPntPrev;
    gp_XY aPntCurr = readFTVec(aPntList[aPntsNb - 1], myScaleUnits, myFTFont->WidthScaling());
    gp_XY aPntNext = readFTVec(aPntList[0], myScaleUnits, myFTFont->WidthScaling());

    bool isLineSeg =
      !myFTFont->IsSingleStrokeFont() && FT_CURVE_TAG(aTags[aPntsNb - 1]) == FT_Curve_Tag_On;
    gp_XY aPntLine1 = aPntCurr;

    for (short aPntId = 0; aPntId < aPntsNb; ++aPntId)
    {
      aPntPrev = aPntCurr;
      aPntCurr = aPntNext;
      aPntNext =
        readFTVec(aPntList[(aPntId + 1) % aPntsNb], myScaleUnits, myFTFont->WidthScaling());

      if (FT_CURVE_TAG(aTags[aPntId]) == FT_Curve_Tag_On)
      {
        if (!isLineSeg)
        {
          aPntLine1 = aPntCurr;
          isLineSeg = true;
          continue;
        }

        const gp_XY  aDirVec = aPntCurr - aPntLine1;
        const double aLen    = aDirVec.Modulus();
        if (aLen <= myPrecision)
        {
          aPntLine1 = aPntCurr;
          isLineSeg = true;
          continue;
        }

        if (myIsCompositeCurve)
        {
          occ::handle<Geom2d_TrimmedCurve> aLine =
            GCE2d_MakeSegment(gp_Pnt2d(aPntLine1), gp_Pnt2d(aPntCurr));
          myConcatMaker.Add(aLine, myPrecision);
        }
        else
        {
          occ::handle<Geom_Curve>  aCurve3d;
          occ::handle<Geom2d_Line> aCurve2d =
            new Geom2d_Line(gp_Pnt2d(aPntLine1), gp_Dir2d(aDirVec));
          if (to3d(aCurve2d, GeomAbs_C1, aCurve3d))
          {
            TopoDS_Edge anEdge = BRepLib_MakeEdge(aCurve3d, 0.0, aLen);
            myBuilder.UpdateEdge(anEdge, aCurve2d, mySurface, aLoc, myPrecision);
            aWireMaker.Add(anEdge);
          }
        }
        aPntLine1 = aPntCurr;
      }
      else if (FT_CURVE_TAG(aTags[aPntId]) == FT_Curve_Tag_Conic)
      {
        isLineSeg       = false;
        gp_XY aPntPrev2 = aPntPrev;
        gp_XY aPntNext2 = aPntNext;

        if (FT_CURVE_TAG(aTags[(aPntId - 1 + aPntsNb) % aPntsNb]) == FT_Curve_Tag_Conic)
        {
          aPntPrev2 = (aPntCurr + aPntPrev) * 0.5;
        }

        if (FT_CURVE_TAG(aTags[(aPntId + 1) % aPntsNb]) == FT_Curve_Tag_Conic)
        {
          aPntNext2 = (aPntCurr + aPntNext) * 0.5;
        }

        my3Poles.SetValue(1, aPntPrev2);
        my3Poles.SetValue(2, aPntCurr);
        my3Poles.SetValue(3, aPntNext2);
        occ::handle<Geom2d_BezierCurve> aBezierArc = new Geom2d_BezierCurve(my3Poles);
        if (myIsCompositeCurve)
        {
          myConcatMaker.Add(aBezierArc, myPrecision);
        }
        else
        {
          occ::handle<Geom_Curve> aCurve3d;
          if (to3d(aBezierArc, GeomAbs_C1, aCurve3d))
          {
            TopoDS_Edge anEdge = BRepLib_MakeEdge(aCurve3d);
            myBuilder.UpdateEdge(anEdge, aBezierArc, mySurface, aLoc, myPrecision);
            aWireMaker.Add(anEdge);
          }
        }
      }
      else if (FT_CURVE_TAG(aTags[aPntId]) == FT_Curve_Tag_Cubic
               && FT_CURVE_TAG(aTags[(aPntId + 1) % aPntsNb]) == FT_Curve_Tag_Cubic)
      {
        isLineSeg = false;
        my4Poles.SetValue(1, aPntPrev);
        my4Poles.SetValue(2, aPntCurr);
        my4Poles.SetValue(3, aPntNext);
        my4Poles.SetValue(
          4,
          gp_Pnt2d(
            readFTVec(aPntList[(aPntId + 2) % aPntsNb], myScaleUnits, myFTFont->WidthScaling())));
        occ::handle<Geom2d_BezierCurve> aBezier = new Geom2d_BezierCurve(my4Poles);
        if (myIsCompositeCurve)
        {
          myConcatMaker.Add(aBezier, myPrecision);
        }
        else
        {
          occ::handle<Geom_Curve> aCurve3d;
          if (to3d(aBezier, GeomAbs_C1, aCurve3d))
          {
            TopoDS_Edge anEdge = BRepLib_MakeEdge(aCurve3d);
            myBuilder.UpdateEdge(anEdge, aBezier, mySurface, aLoc, myPrecision);
            aWireMaker.Add(anEdge);
          }
        }
      }
    }

    if (myIsCompositeCurve)
    {
      occ::handle<Geom2d_BSplineCurve> aDraft2d = myConcatMaker.BSplineCurve();
      if (aDraft2d.IsNull())
      {
        continue;
      }

      const gp_Pnt2d aFirstPnt = aDraft2d->StartPoint();
      const gp_Pnt2d aLastPnt  = aDraft2d->EndPoint();
      if (!myFTFont->IsSingleStrokeFont() && !aFirstPnt.IsEqual(aLastPnt, myPrecision))
      {
        occ::handle<Geom2d_TrimmedCurve> aLine = GCE2d_MakeSegment(aLastPnt, aFirstPnt);
        myConcatMaker.Add(aLine, myPrecision);
      }

      occ::handle<Geom2d_BSplineCurve> aCurve2d = myConcatMaker.BSplineCurve();
      occ::handle<Geom_Curve>          aCurve3d;
      if (to3d(aCurve2d, GeomAbs_C0, aCurve3d))
      {
        TopoDS_Edge anEdge = BRepLib_MakeEdge(aCurve3d);
        myBuilder.UpdateEdge(anEdge, aCurve2d, mySurface, aLoc, myPrecision);
        aWireMaker.Add(anEdge);
      }
      myConcatMaker.Clear();
    }
    else
    {
      if (!aWireMaker.IsDone())
      {
        continue;
      }

      TopoDS_Vertex aFirstV, aLastV;
      TopExp::Vertices(aWireMaker.Wire(), aFirstV, aLastV);
      gp_Pnt aFirstPoint = BRep_Tool::Pnt(aFirstV);
      gp_Pnt aLastPoint  = BRep_Tool::Pnt(aLastV);
      if (!myFTFont->IsSingleStrokeFont() && !aFirstPoint.IsEqual(aLastPoint, myPrecision))
      {
        aWireMaker.Add(BRepLib_MakeEdge(aFirstV, aLastV));
      }
    }

    if (!aWireMaker.IsDone())
    {
      continue;
    }

    TopoDS_Wire aWireDraft = aWireMaker.Wire();
    if (!myFTFont->IsSingleStrokeFont())
    {

      TopoDS_Face aFace;
      myBuilder.MakeFace(aFace, mySurface, myPrecision);
      myBuilder.Add(aFace, aWireDraft);
      BRepTopAdaptor_FClass2d aClass2d(aFace, ::Precision::PConfusion());
      TopAbs_State            aState = aClass2d.PerformInfinitePoint();
      if (aState != TopAbs_OUT)
      {

        aWireDraft.Reverse();
      }
      aWires.Append(aWireDraft);
    }
    else
    {
      if (aFaceCompDraft.IsNull())
      {
        myBuilder.MakeCompound(aFaceCompDraft);
      }
      myBuilder.Add(aFaceCompDraft, aWireDraft);
    }
  }

  if (!aWires.IsEmpty())
  {
    buildFaces(aWires, theShape);
  }
  else if (!aFaceCompDraft.IsNull())
  {
    theShape = aFaceCompDraft;
  }
#else
  (void)theChar;
#endif
  myCache.Bind(theChar, theShape);
  return !theShape.IsNull();
}
