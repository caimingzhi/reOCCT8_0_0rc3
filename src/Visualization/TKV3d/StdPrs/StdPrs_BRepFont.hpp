#pragma once

#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRep_Builder.hpp>
#include <Font_FTFont.hpp>
#include <Font_TextFormatter.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dConvert_CompCurveToBSplineCurve.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_String.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>

#include <mutex>

class StdPrs_BRepFont : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(StdPrs_BRepFont, Standard_Transient)
public:
  Standard_EXPORT static occ::handle<StdPrs_BRepFont> FindAndCreate(
    const TCollection_AsciiString& theFontName,
    const Font_FontAspect          theFontAspect,
    const double                   theSize,
    const Font_StrictLevel         theStrictLevel = Font_StrictLevel_Any);

  Standard_EXPORT StdPrs_BRepFont();

  Standard_EXPORT StdPrs_BRepFont(const NCollection_String& theFontPath,
                                  const double              theSize,
                                  const int                 theFaceId = 0);

  Standard_EXPORT StdPrs_BRepFont(const NCollection_String& theFontName,
                                  const Font_FontAspect     theFontAspect,
                                  const double              theSize,
                                  const Font_StrictLevel    theStrictLevel = Font_StrictLevel_Any);

  Standard_EXPORT virtual void Release();

  Standard_EXPORT bool Init(const NCollection_String& theFontPath,
                            const double              theSize,
                            const int                 theFaceId);

  Standard_EXPORT bool FindAndInit(const TCollection_AsciiString& theFontName,
                                   const Font_FontAspect          theFontAspect,
                                   const double                   theSize,
                                   const Font_StrictLevel theStrictLevel = Font_StrictLevel_Any);

  const occ::handle<Font_FTFont>& FTFont() const { return myFTFont; }

  Standard_EXPORT TopoDS_Shape RenderGlyph(const char32_t& theChar);

  Standard_EXPORT void SetCompositeCurveMode(const bool theToConcatenate);

  void SetWidthScaling(const float theScaleFactor) { myFTFont->SetWidthScaling(theScaleFactor); }

public:
  double Ascender() const { return myScaleUnits * double(myFTFont->Ascender()); }

  double Descender() const { return myScaleUnits * double(myFTFont->Descender()); }

  double LineSpacing() const { return myScaleUnits * double(myFTFont->LineSpacing()); }

  double PointSize() const { return myScaleUnits * double(myFTFont->PointSize()); }

  double AdvanceX(const char32_t theUCharNext)
  {
    return myScaleUnits * double(myFTFont->AdvanceX(theUCharNext));
  }

  double AdvanceX(const char32_t theUChar, const char32_t theUCharNext)
  {
    return myScaleUnits * double(myFTFont->AdvanceX(theUChar, theUCharNext));
  }

  double AdvanceY(const char32_t theUCharNext)
  {
    return myScaleUnits * double(myFTFont->AdvanceY(theUCharNext));
  }

  double AdvanceY(const char32_t theUChar, const char32_t theUCharNext)
  {
    return myScaleUnits * double(myFTFont->AdvanceY(theUChar, theUCharNext));
  }

  double Scale() const { return myScaleUnits; }

  std::mutex& Mutex() { return myMutex; }

public:
  bool Init(const NCollection_String& theFontName,
            const Font_FontAspect     theFontAspect,
            const double              theSize)
  {
    return FindAndInit(theFontName.ToCString(), theFontAspect, theSize, Font_StrictLevel_Any);
  }

protected:
  Standard_EXPORT bool renderGlyph(const char32_t theChar, TopoDS_Shape& theShape);

private:
  void init();

  bool to3d(const occ::handle<Geom2d_Curve>& theCurve2d,
            const GeomAbs_Shape              theContinuity,
            occ::handle<Geom_Curve>&         theCurve3d);

  bool buildFaces(const NCollection_Sequence<TopoDS_Wire>& theWires, TopoDS_Shape& theRes);

protected:
  occ::handle<Font_FTFont>                    myFTFont;
  NCollection_DataMap<char32_t, TopoDS_Shape> myCache;
  std::mutex                                  myMutex;
  occ::handle<Geom_Surface>                   mySurface;
  double                                      myPrecision;
  double                                      myScaleUnits;

  bool myIsCompositeCurve;

protected:
  Adaptor3d_CurveOnSurface              myCurvOnSurf;
  occ::handle<Geom2dAdaptor_Curve>      myCurve2dAdaptor;
  Geom2dConvert_CompCurveToBSplineCurve myConcatMaker;
  NCollection_Array1<gp_Pnt2d>          my3Poles;
  NCollection_Array1<gp_Pnt2d>          my4Poles;
  BRep_Builder                          myBuilder;
};
