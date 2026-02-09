#pragma once

#include <Font_FontAspect.hpp>
#include <NCollection_Array1.hpp>
#include <Quantity_Color.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

class Graphic3d_CView;

class Graphic3d_GraduatedTrihedron
{

public:
  class AxisAspect
  {
  public:
    AxisAspect(const TCollection_ExtendedString theName            = "",
               const Quantity_Color             theNameColor       = Quantity_NOC_BLACK,
               const Quantity_Color             theColor           = Quantity_NOC_BLACK,
               const int                        theValuesOffset    = 10,
               const int                        theNameOffset      = 30,
               const int                        theTickmarksNumber = 5,
               const int                        theTickmarksLength = 10,
               const bool                       theToDrawName      = true,
               const bool                       theToDrawValues    = true,
               const bool                       theToDrawTickmarks = true)
        : myName(theName),
          myToDrawName(theToDrawName),
          myToDrawTickmarks(theToDrawTickmarks),
          myToDrawValues(theToDrawValues),
          myNameColor(theNameColor),
          myTickmarksNumber(theTickmarksNumber),
          myTickmarksLength(theTickmarksLength),
          myColor(theColor),
          myValuesOffset(theValuesOffset),
          myNameOffset(theNameOffset)
    {
    }

  public:
    void SetName(const TCollection_ExtendedString& theName) { myName = theName; }

    const TCollection_ExtendedString& Name() const { return myName; }

    bool ToDrawName() const { return myToDrawName; }

    void SetDrawName(const bool theToDraw) { myToDrawName = theToDraw; }

    bool ToDrawTickmarks() const { return myToDrawTickmarks; }

    void SetDrawTickmarks(const bool theToDraw) { myToDrawTickmarks = theToDraw; }

    bool ToDrawValues() const { return myToDrawValues; }

    void SetDrawValues(const bool theToDraw) { myToDrawValues = theToDraw; }

    const Quantity_Color& NameColor() const { return myNameColor; }

    void SetNameColor(const Quantity_Color& theColor) { myNameColor = theColor; }

    const Quantity_Color& Color() const { return myColor; }

    void SetColor(const Quantity_Color& theColor) { myColor = theColor; }

    int TickmarksNumber() const { return myTickmarksNumber; }

    void SetTickmarksNumber(const int theValue) { myTickmarksNumber = theValue; }

    int TickmarksLength() const { return myTickmarksLength; }

    void SetTickmarksLength(const int theValue) { myTickmarksLength = theValue; }

    int ValuesOffset() const { return myValuesOffset; }

    void SetValuesOffset(const int theValue) { myValuesOffset = theValue; }

    int NameOffset() const { return myNameOffset; }

    void SetNameOffset(const int theValue) { myNameOffset = theValue; }

  protected:
    TCollection_ExtendedString myName;

    bool myToDrawName;
    bool myToDrawTickmarks;
    bool myToDrawValues;

    Quantity_Color myNameColor;

    int            myTickmarksNumber;
    int            myTickmarksLength;
    Quantity_Color myColor;

    int myValuesOffset;
    int myNameOffset;
  };

public:
  typedef void (*MinMaxValuesCallback)(Graphic3d_CView*);

public:
  Graphic3d_GraduatedTrihedron(const TCollection_AsciiString& theNamesFont    = "Arial",
                               const Font_FontAspect&         theNamesStyle   = Font_FA_Bold,
                               const int                      theNamesSize    = 12,
                               const TCollection_AsciiString& theValuesFont   = "Arial",
                               const Font_FontAspect&         theValuesStyle  = Font_FA_Regular,
                               const int                      theValuesSize   = 12,
                               const float                    theArrowsLength = 30.0f,
                               const Quantity_Color           theGridColor    = Quantity_NOC_WHITE,
                               const bool                     theToDrawGrid   = true,
                               const bool                     theToDrawAxes   = true)
      : myCubicAxesCallback(nullptr),
        myNamesFont(theNamesFont),
        myNamesStyle(theNamesStyle),
        myNamesSize(theNamesSize),
        myValuesFont(theValuesFont),
        myValuesStyle(theValuesStyle),
        myValuesSize(theValuesSize),
        myArrowsLength(theArrowsLength),
        myGridColor(theGridColor),
        myToDrawGrid(theToDrawGrid),
        myToDrawAxes(theToDrawAxes),
        myAxes(0, 2)
  {
    myAxes(0) = AxisAspect("X", Quantity_NOC_RED, Quantity_NOC_RED);
    myAxes(1) = AxisAspect("Y", Quantity_NOC_GREEN, Quantity_NOC_GREEN);
    myAxes(2) = AxisAspect("Z", Quantity_NOC_BLUE1, Quantity_NOC_BLUE1);
  }

public:
  AxisAspect& ChangeXAxisAspect() { return myAxes(0); }

  AxisAspect& ChangeYAxisAspect() { return myAxes(1); }

  AxisAspect& ChangeZAxisAspect() { return myAxes(2); }

  AxisAspect& ChangeAxisAspect(const int theIndex)
  {
    Standard_OutOfRange_Raise_if(
      theIndex < 0 || theIndex > 2,
      "Graphic3d_GraduatedTrihedron::ChangeAxisAspect: theIndex is out of bounds [0,2].");
    return myAxes(theIndex);
  }

  const AxisAspect& XAxisAspect() const { return myAxes(0); }

  const AxisAspect& YAxisAspect() const { return myAxes(1); }

  const AxisAspect& ZAxisAspect() const { return myAxes(2); }

  const AxisAspect& AxisAspectAt(const int theIndex) const
  {
    Standard_OutOfRange_Raise_if(
      theIndex < 0 || theIndex > 2,
      "Graphic3d_GraduatedTrihedron::AxisAspect: theIndex is out of bounds [0,2].");
    return myAxes(theIndex);
  }

  float ArrowsLength() const { return myArrowsLength; }

  void SetArrowsLength(const float theValue) { myArrowsLength = theValue; }

  const Quantity_Color& GridColor() const { return myGridColor; }

  void SetGridColor(const Quantity_Color& theColor) { myGridColor = theColor; }

  bool ToDrawGrid() const { return myToDrawGrid; }

  void SetDrawGrid(const bool theToDraw) { myToDrawGrid = theToDraw; }

  bool ToDrawAxes() const { return myToDrawAxes; }

  void SetDrawAxes(const bool theToDraw) { myToDrawAxes = theToDraw; }

  const TCollection_AsciiString& NamesFont() const { return myNamesFont; }

  void SetNamesFont(const TCollection_AsciiString& theFont) { myNamesFont = theFont; }

  Font_FontAspect NamesFontAspect() const { return myNamesStyle; }

  void SetNamesFontAspect(Font_FontAspect theAspect) { myNamesStyle = theAspect; }

  int NamesSize() const { return myNamesSize; }

  void SetNamesSize(const int theValue) { myNamesSize = theValue; }

  const TCollection_AsciiString& ValuesFont() const { return myValuesFont; }

  void SetValuesFont(const TCollection_AsciiString& theFont) { myValuesFont = theFont; }

  Font_FontAspect ValuesFontAspect() const { return myValuesStyle; }

  void SetValuesFontAspect(Font_FontAspect theAspect) { myValuesStyle = theAspect; }

  int ValuesSize() const { return myValuesSize; }

  void SetValuesSize(const int theValue) { myValuesSize = theValue; }

  bool CubicAxesCallback(Graphic3d_CView* theView) const
  {
    if (myCubicAxesCallback != nullptr)
    {
      myCubicAxesCallback(theView);
      return true;
    }
    return false;
  }

  void SetCubicAxesCallback(const MinMaxValuesCallback theCallback)
  {
    myCubicAxesCallback = theCallback;
  }

protected:
  MinMaxValuesCallback myCubicAxesCallback;

  TCollection_AsciiString myNamesFont;
  Font_FontAspect         myNamesStyle;

  int myNamesSize;

protected:
  TCollection_AsciiString myValuesFont;
  Font_FontAspect         myValuesStyle;
  int                     myValuesSize;

protected:
  float          myArrowsLength;
  Quantity_Color myGridColor;

  bool myToDrawGrid;
  bool myToDrawAxes;

  NCollection_Array1<AxisAspect> myAxes;
};
