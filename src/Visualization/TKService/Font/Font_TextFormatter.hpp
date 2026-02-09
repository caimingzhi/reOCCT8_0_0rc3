#pragma once

#include <Font_Rect.hpp>
#include <Graphic3d_HorizontalTextAlignment.hpp>
#include <Graphic3d_VerticalTextAlignment.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Vector.hpp>
#include <NCollection_String.hpp>

class Font_FTFont;

class Font_TextFormatter : public Standard_Transient
{
public:
  enum IterationFilter
  {
    IterationFilter_None             = 0x0000,
    IterationFilter_ExcludeInvisible = 0x0002,
  };

  class Iterator
  {
  public:
    Iterator(const Font_TextFormatter& theFormatter,
             IterationFilter           theFilter = IterationFilter_None)
        : myFilter(theFilter),
          myIter(theFormatter.myString.Iterator()),
          mySymbolChar(0),
          mySymbolCharNext(0)
    {
      mySymbolPosition = readNextSymbol(-1, mySymbolChar);
      mySymbolNext     = readNextSymbol(mySymbolPosition, mySymbolCharNext);
    }

    bool More() const { return mySymbolPosition >= 0; }

    bool HasNext() const { return mySymbolNext >= 0; }

    char32_t Symbol() const { return mySymbolChar; }

    char32_t SymbolNext() const { return mySymbolCharNext; }

    int SymbolPosition() const { return mySymbolPosition; }

    int SymbolPositionNext() const { return mySymbolNext; }

    void Next()
    {
      mySymbolPosition = mySymbolNext;
      mySymbolChar     = mySymbolCharNext;
      mySymbolNext     = readNextSymbol(mySymbolPosition, mySymbolCharNext);
    }

  protected:
    int readNextSymbol(const int theSymbolStartingFrom, char32_t& theSymbolChar)
    {
      int aNextSymbol = theSymbolStartingFrom;
      for (; *myIter != 0; ++myIter)
      {
        const char32_t aCharCurr = *myIter;
        if (Font_TextFormatter::IsCommandSymbol(aCharCurr))
        {
          continue;
        }
        aNextSymbol++;
        if ((myFilter & IterationFilter_ExcludeInvisible) != 0)
        {
          if (aCharCurr == '\x0A' || aCharCurr == ' ' || aCharCurr == '\t')
          {
            continue;
          }
        }
        ++myIter;
        theSymbolChar = aCharCurr;
        return aNextSymbol;
      }
      return -1;
    }

  protected:
    IterationFilter myFilter;

    NCollection_UtfIterator<char> myIter;
    int                           mySymbolPosition;
    char32_t                      mySymbolChar;
    int                           mySymbolNext;

    char32_t mySymbolCharNext;
  };

  Standard_EXPORT Font_TextFormatter();

  Standard_EXPORT void SetupAlignment(const Graphic3d_HorizontalTextAlignment theAlignX,
                                      const Graphic3d_VerticalTextAlignment   theAlignY);

  Standard_EXPORT void Reset();

  Standard_EXPORT void Append(const NCollection_String& theString, Font_FTFont& theFont);

  Standard_EXPORT void Format();

  Standard_DEPRECATED("BottomLeft should be used instead")

  const NCollection_Vec2<float>& TopLeft(const int theIndex) const { return BottomLeft(theIndex); }

  const NCollection_Vec2<float>& BottomLeft(const int theIndex) const
  {
    return myCorners.Value(theIndex);
  }

  inline const NCollection_String& String() const { return myString; }

  Standard_EXPORT bool GlyphBoundingBox(const int theIndex, Font_Rect& theBndBox) const;

  float LineHeight(const int theIndex) const { return theIndex == 0 ? myAscender : myLineSpacing; }

  Standard_EXPORT float LineWidth(const int theIndex) const;

  Standard_EXPORT bool IsLFSymbol(const int theIndex) const;

  Standard_EXPORT float FirstPosition() const;

  Standard_EXPORT int LinePositionIndex(const int theIndex) const;

  Standard_EXPORT int LineIndex(const int theIndex) const;

  inline int TabSize() const { return myTabSize; }

  Graphic3d_HorizontalTextAlignment HorizontalTextAlignment() const { return myAlignX; }

  Graphic3d_VerticalTextAlignment VerticalTextAlignment() const { return myAlignY; }

  void SetWrapping(const float theWidth) { myWrappingWidth = theWidth; }

  bool HasWrapping() const { return myWrappingWidth > 0; }

  float Wrapping() const { return myWrappingWidth; }

  bool WordWrapping() const { return myIsWordWrapping; }

  void SetWordWrapping(const bool theIsWordWrapping) { myIsWordWrapping = theIsWordWrapping; }

  inline float ResultWidth() const { return myBndWidth; }

  inline float ResultHeight() const { return myLineSpacing * float(myLinesNb); }

  float MaximumSymbolWidth() const { return myMaxSymbolWidth; }

  inline void BndBox(Font_Rect& theBndBox) const
  {
    theBndBox.Left = 0.0f;
    switch (myAlignX)
    {
      default:
      case Graphic3d_HTA_LEFT:
        theBndBox.Right = myBndWidth;
        break;
      case Graphic3d_HTA_RIGHT:
        theBndBox.Right = -myBndWidth;
        break;
      case Graphic3d_HTA_CENTER:
      {
        theBndBox.Left  = -0.5f * myBndWidth;
        theBndBox.Right = 0.5f * myBndWidth;
        break;
      }
    }
    theBndBox.Top    = myBndTop;
    theBndBox.Bottom = theBndBox.Top - myLineSpacing * float(myLinesNb);
  }

  const NCollection_Vector<NCollection_Vec2<float>>& Corners() const { return myCorners; }

  const NCollection_Vector<float>& NewLines() const { return myNewLines; }

  static inline bool IsCommandSymbol(const char32_t& theSymbol)
  {
    return (theSymbol == '\x0D' || theSymbol == '\a' || theSymbol == '\f' || theSymbol == '\b'
            || theSymbol == '\v');
  }

  static bool IsSeparatorSymbol(const char32_t& theSymbol)
  {
    return theSymbol == '\x0A' || theSymbol == ' ' || theSymbol == '\x09';
  }

  DEFINE_STANDARD_RTTIEXT(Font_TextFormatter, Standard_Transient)

protected:
  Standard_EXPORT void newLine(const int theLastRect, const float theMaxLineWidth);

protected:
  Graphic3d_HorizontalTextAlignment myAlignX;
  Graphic3d_VerticalTextAlignment   myAlignY;

  int   myTabSize;
  float myWrappingWidth;
  bool  myIsWordWrapping;
  float myLastSymbolWidth;
  float myMaxSymbolWidth;

protected:
  NCollection_String                          myString;
  NCollection_Vec2<float>                     myPen;
  NCollection_Vector<NCollection_Vec2<float>> myCorners;
  NCollection_Vector<float>                   myNewLines;

  float myLineSpacing;
  float myAscender;
  bool  myIsFormatted;

protected:
  int myLinesNb;

  int myRectLineStart;
  int myNewLineNb;

  float                   myPenCurrLine;
  float                   myBndTop;
  float                   myBndWidth;
  NCollection_Vec2<float> myMoveVec;
};
