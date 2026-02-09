#pragma once

#include <AIS_InteractiveObject.hpp>
#include <Aspect_TypeOfColorScaleData.hpp>
#include <Aspect_TypeOfColorScalePosition.hpp>
#include <Quantity_Color.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard.hpp>
#include <Standard_DefineHandle.hpp>
#include <TCollection_ExtendedString.hpp>

class AIS_ColorScale : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_ColorScale, AIS_InteractiveObject)
public:
  Standard_EXPORT static bool FindColor(const double                    theValue,
                                        const double                    theMin,
                                        const double                    theMax,
                                        const int                       theColorsCount,
                                        const NCollection_Vec3<double>& theColorHlsMin,
                                        const NCollection_Vec3<double>& theColorHlsMax,
                                        Quantity_Color&                 theColor);

  static bool FindColor(const double    theValue,
                        const double    theMin,
                        const double    theMax,
                        const int       theColorsCount,
                        Quantity_Color& theColor)
  {
    return FindColor(theValue,
                     theMin,
                     theMax,
                     theColorsCount,
                     NCollection_Vec3<double>(230.0, 1.0, 1.0),
                     NCollection_Vec3<double>(0.0, 1.0, 1.0),
                     theColor);
  }

  static double hueToValidRange(const double theHue)
  {
    double aHue = theHue;
    while (aHue < 0.0)
    {
      aHue += 360.0;
    }
    while (aHue > 360.0)
    {
      aHue -= 360.0;
    }
    return aHue;
  }

public:
  Standard_EXPORT AIS_ColorScale();

  Standard_EXPORT bool FindColor(const double theValue, Quantity_Color& theColor) const;

  double GetMin() const { return myMin; }

  void SetMin(const double theMin) { SetRange(theMin, GetMax()); }

  double GetMax() const { return myMax; }

  void SetMax(const double theMax) { SetRange(GetMin(), theMax); }

  void GetRange(double& theMin, double& theMax) const
  {
    theMin = myMin;
    theMax = myMax;
  }

  Standard_EXPORT void SetRange(const double theMin, const double theMax);

  double HueMin() const { return myColorHlsMin[0]; }

  double HueMax() const { return myColorHlsMax[0]; }

  void HueRange(double& theMinAngle, double& theMaxAngle) const
  {
    theMinAngle = myColorHlsMin[0];
    theMaxAngle = myColorHlsMax[0];
  }

  void SetHueRange(const double theMinAngle, const double theMaxAngle)
  {
    myColorHlsMin[0] = theMinAngle;
    myColorHlsMax[0] = theMaxAngle;
  }

  void ColorRange(Quantity_Color& theMinColor, Quantity_Color& theMaxColor) const
  {
    theMinColor.SetValues(hueToValidRange(myColorHlsMin[0]),
                          myColorHlsMin[1],
                          myColorHlsMin[2],
                          Quantity_TOC_HLS);
    theMaxColor.SetValues(hueToValidRange(myColorHlsMax[0]),
                          myColorHlsMax[1],
                          myColorHlsMax[2],
                          Quantity_TOC_HLS);
  }

  void SetColorRange(const Quantity_Color& theMinColor, const Quantity_Color& theMaxColor)
  {
    theMinColor.Values(myColorHlsMin[0], myColorHlsMin[1], myColorHlsMin[2], Quantity_TOC_HLS);
    theMaxColor.Values(myColorHlsMax[0], myColorHlsMax[1], myColorHlsMax[2], Quantity_TOC_HLS);
  }

  Aspect_TypeOfColorScaleData GetLabelType() const { return myLabelType; }

  void SetLabelType(const Aspect_TypeOfColorScaleData theType) { myLabelType = theType; }

  Aspect_TypeOfColorScaleData GetColorType() const { return myColorType; }

  void SetColorType(const Aspect_TypeOfColorScaleData theType) { myColorType = theType; }

  int GetNumberOfIntervals() const { return myNbIntervals; }

  Standard_EXPORT void SetNumberOfIntervals(const int theNum);

  const TCollection_ExtendedString& GetTitle() const { return myTitle; }

  void SetTitle(const TCollection_ExtendedString& theTitle) { myTitle = theTitle; }

  const TCollection_AsciiString& GetFormat() const { return myFormat; }

  const TCollection_AsciiString& Format() const { return myFormat; }

  void SetFormat(const TCollection_AsciiString& theFormat) { myFormat = theFormat; }

  Standard_EXPORT TCollection_ExtendedString GetLabel(const int theIndex) const;

  Standard_EXPORT Quantity_Color GetIntervalColor(const int theIndex) const;

  Standard_EXPORT void SetIntervalColor(const Quantity_Color& theColor, const int theIndex);

  Standard_EXPORT void GetLabels(NCollection_Sequence<TCollection_ExtendedString>& theLabels) const;

  const NCollection_Sequence<TCollection_ExtendedString>& Labels() const { return myLabels; }

  Standard_EXPORT void SetLabels(const NCollection_Sequence<TCollection_ExtendedString>& theSeq);

  Standard_EXPORT void GetColors(NCollection_Sequence<Quantity_Color>& theColors) const;

  const NCollection_Sequence<Quantity_Color>& GetColors() const { return myColors; }

  Standard_EXPORT void SetColors(const NCollection_Sequence<Quantity_Color>& theSeq);

  void SetUniformColors(double theLightness, double theHueFrom, double theHueTo)
  {
    SetColors(MakeUniformColors(myNbIntervals, theLightness, theHueFrom, theHueTo));
    SetColorType(Aspect_TOCSD_USER);
  }

  Standard_EXPORT static NCollection_Sequence<Quantity_Color> MakeUniformColors(int    theNbColors,
                                                                                double theLightness,
                                                                                double theHueFrom,
                                                                                double theHueTo);

  Aspect_TypeOfColorScalePosition GetLabelPosition() const { return myLabelPos; }

  void SetLabelPosition(const Aspect_TypeOfColorScalePosition thePos) { myLabelPos = thePos; }

  Aspect_TypeOfColorScalePosition GetTitlePosition() const { return myTitlePos; }

  Standard_DEPRECATED("AIS_ColorScale::SetTitlePosition() has no effect!")

  void SetTitlePosition(const Aspect_TypeOfColorScalePosition thePos) { myTitlePos = thePos; }

  bool IsReversed() const { return myIsReversed; }

  void SetReversed(const bool theReverse) { myIsReversed = theReverse; }

  bool IsSmoothTransition() const { return myIsSmooth; }

  void SetSmoothTransition(const bool theIsSmooth) { myIsSmooth = theIsSmooth; }

  bool IsLabelAtBorder() const { return myIsLabelAtBorder; }

  void SetLabelAtBorder(const bool theOn) { myIsLabelAtBorder = theOn; }

  bool IsLogarithmic() const { return myIsLogarithmic; }

  void SetLogarithmic(const bool isLogarithmic) { myIsLogarithmic = isLogarithmic; }

  Standard_EXPORT void SetLabel(const TCollection_ExtendedString& theLabel, const int theIndex);

  void GetSize(int& theBreadth, int& theHeight) const
  {
    theBreadth = myBreadth;
    theHeight  = myHeight;
  }

  void SetSize(const int theBreadth, const int theHeight)
  {
    myBreadth = theBreadth;
    myHeight  = theHeight;
  }

  int GetBreadth() const { return myBreadth; }

  void SetBreadth(const int theBreadth) { myBreadth = theBreadth; }

  int GetHeight() const { return myHeight; }

  void SetHeight(const int theHeight) { myHeight = theHeight; }

  void GetPosition(double& theX, double& theY) const
  {
    theX = myXPos;
    theY = myYPos;
  }

  void SetPosition(const int theX, const int theY)
  {
    myXPos = theX;
    myYPos = theY;
  }

  int GetXPosition() const { return myXPos; }

  void SetXPosition(const int theX) { myXPos = theX; }

  int GetYPosition() const { return myYPos; }

  void SetYPosition(const int theY) { myYPos = theY; }

  int GetTextHeight() const { return myTextHeight; }

  void SetTextHeight(const int theHeight) { myTextHeight = theHeight; }

public:
  Standard_EXPORT int TextWidth(const TCollection_ExtendedString& theText) const;

  Standard_EXPORT int TextHeight(const TCollection_ExtendedString& theText) const;

  Standard_EXPORT void TextSize(const TCollection_ExtendedString& theText,
                                const int                         theHeight,
                                int&                              theWidth,
                                int&                              theAscent,
                                int&                              theDescent) const;

public:
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePresentation,
                               const int                                      theMode) override;

  void ComputeSelection(const occ::handle<SelectMgr_Selection>&, const int) override {}

private:
  void SizeHint(int& theWidth, int& theHeight) const;

  double GetIntervalValue(const int theIndex) const;

  Quantity_Color colorFromValue(const double theValue,
                                const double theMin,
                                const double theMax) const;

  void updateTextAspect();

  void drawText(const occ::handle<Graphic3d_Group>&   theGroup,
                const TCollection_ExtendedString&     theText,
                const int                             theX,
                const int                             theY,
                const Graphic3d_VerticalTextAlignment theVertAlignment);

  int computeMaxLabelWidth(const NCollection_Sequence<TCollection_ExtendedString>& theLabels) const;

  void drawLabels(const occ::handle<Graphic3d_Group>&                     theGroup,
                  const NCollection_Sequence<TCollection_ExtendedString>& theLabels,
                  const int                                               theBarBottom,
                  const int                                               theBarHeight,
                  const int                                               theMaxLabelWidth,
                  const int                                               theColorBreadth);

  void drawColorBar(const occ::handle<Prs3d_Presentation>& thePrs,
                    const int                              theBarBottom,
                    const int                              theBarHeight,
                    const int                              theMaxLabelWidth,
                    const int                              theColorBreadth);

  void drawFrame(const occ::handle<Prs3d_Presentation>& thePrs,
                 const int                              theX,
                 const int                              theY,
                 const int                              theWidth,
                 const int                              theHeight,
                 const Quantity_Color&                  theColor);

private:
  double myMin;
  double myMax;

  NCollection_Vec3<double>                         myColorHlsMin;
  NCollection_Vec3<double>                         myColorHlsMax;
  TCollection_ExtendedString                       myTitle;
  TCollection_AsciiString                          myFormat;
  int                                              myNbIntervals;
  Aspect_TypeOfColorScaleData                      myColorType;
  Aspect_TypeOfColorScaleData                      myLabelType;
  bool                                             myIsLabelAtBorder;
  bool                                             myIsReversed;
  bool                                             myIsLogarithmic;
  bool                                             myIsSmooth;
  NCollection_Sequence<Quantity_Color>             myColors;
  NCollection_Sequence<TCollection_ExtendedString> myLabels;
  Aspect_TypeOfColorScalePosition                  myLabelPos;

  Aspect_TypeOfColorScalePosition myTitlePos;
  int                             myXPos;
  int                             myYPos;
  int                             myBreadth;
  int                             myHeight;
  int                             mySpacing;
  int                             myTextHeight;
};
