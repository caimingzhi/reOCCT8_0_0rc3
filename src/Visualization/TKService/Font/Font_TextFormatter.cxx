#include <Font_TextFormatter.hpp>

#include <Font_FTFont.hpp>

#include <Precision.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Font_TextFormatter, Standard_Transient)

namespace
{
  typedef NCollection_Vec2<float> Vec2f;

  inline void move(NCollection_Vector<Vec2f>& theCorners,
                   const Vec2f&               theMoveVec,
                   int                        theCharLower,
                   const int                  theCharUpper)
  {
    for (; theCharLower <= theCharUpper; ++theCharLower)
    {
      theCorners.ChangeValue(theCharLower) += theMoveVec;
    }
  }

  inline void moveY(NCollection_Vector<Vec2f>& theCorners,
                    const float                theMoveVec,
                    int                        theCharLower,
                    const int                  theCharUpper)
  {
    for (; theCharLower <= theCharUpper; ++theCharLower)
    {
      theCorners.ChangeValue(theCharLower).y() += theMoveVec;
    }
  }

} // namespace

Font_TextFormatter::Font_TextFormatter()
    : myAlignX(Graphic3d_HTA_LEFT),
      myAlignY(Graphic3d_VTA_TOP),
      myTabSize(8),
      myWrappingWidth(0.0f),
      myIsWordWrapping(true),
      myLastSymbolWidth(0.0f),
      myMaxSymbolWidth(0.0f),

      myPen(0.0f, 0.0f),
      myLineSpacing(0.0f),
      myAscender(0.0f),
      myIsFormatted(false),

      myLinesNb(0),
      myRectLineStart(0),
      myNewLineNb(0),
      myPenCurrLine(0.0f),
      myBndTop(0.0f),
      myBndWidth(0.0f),
      myMoveVec(0.0f, 0.0f)
{
}

void Font_TextFormatter::SetupAlignment(const Graphic3d_HorizontalTextAlignment theAlignX,
                                        const Graphic3d_VerticalTextAlignment   theAlignY)
{
  myAlignX = theAlignX;
  myAlignY = theAlignY;
}

void Font_TextFormatter::Reset()
{
  myIsFormatted = false;
  myString.Clear();
  myPen.x() = myPen.y() = 0.0f;
  myLineSpacing = myAscender = 0.0f;
  myCorners.Clear();
  myNewLines.Clear();

  myLastSymbolWidth = 0.0f;
  myMaxSymbolWidth  = 0.0f;
}

void Font_TextFormatter::Append(const NCollection_String& theString, Font_FTFont& theFont)
{
  if (theString.IsEmpty())
  {
    return;
  }

  myAscender    = std::max(myAscender, theFont.Ascender());
  myLineSpacing = std::max(myLineSpacing, theFont.LineSpacing());
  myString += theString;

  int aSymbolsCounter = 0;

  for (Font_TextFormatter::Iterator aFormatterIt(*this); aFormatterIt.More(); aFormatterIt.Next())
  {
    const char32_t aCharThis = aFormatterIt.Symbol();
    const char32_t aCharNext = aFormatterIt.SymbolNext();

    float anAdvanceX = 0;
    if (IsCommandSymbol(aCharThis))
    {
      continue;
    }
    else if (aCharThis == '\x0A')
    {
      aSymbolsCounter = 0;
      myNewLines.Append(myPen.x());
      anAdvanceX = 0;
    }
    else if (aCharThis == ' ')
    {
      anAdvanceX = theFont.AdvanceX(' ', aCharNext);
    }
    else if (aCharThis == '\t')
    {
      const int aSpacesNum = (myTabSize - (aSymbolsCounter - 1) % myTabSize);
      anAdvanceX           = theFont.AdvanceX(' ', aCharNext) * float(aSpacesNum);
      aSymbolsCounter += aSpacesNum;
    }
    else
    {
      anAdvanceX = theFont.AdvanceX(aCharThis, aCharNext);
    }
    ++aSymbolsCounter;
    myCorners.Append(myPen);
    myPen.x() += anAdvanceX;
    myMaxSymbolWidth = std::max(myMaxSymbolWidth, anAdvanceX);
  }
  myLastSymbolWidth = myPen.x() - myCorners.Last().x();
}

void Font_TextFormatter::newLine(const int theLastRect, const float theMaxLineWidth)
{
  int aFirstCornerId = myRectLineStart;
  int aLastCornerId  = theLastRect;

  if (aFirstCornerId >= myCorners.Length())
  {
    ++myLinesNb;
    myPenCurrLine -= myLineSpacing;
    return;
  }

  float     aXMin = BottomLeft(aFirstCornerId).x();
  Font_Rect aBndBox;
  GlyphBoundingBox(aLastCornerId, aBndBox);
  float aXMax = aBndBox.Right;

  myMoveVec.y() = myPenCurrLine;
  switch (myAlignX)
  {
    default:
    case Graphic3d_HTA_LEFT:
      myMoveVec.x() = -aXMin;
      break;
    case Graphic3d_HTA_RIGHT:
      myMoveVec.x() = -aXMin + (theMaxLineWidth - (aXMax - aXMin)) - theMaxLineWidth;
      break;
    case Graphic3d_HTA_CENTER:
      myMoveVec.x() = -aXMin + 0.5f * (theMaxLineWidth - (aXMax - aXMin)) - 0.5f * theMaxLineWidth;
      break;
  }

  move(myCorners, myMoveVec, myRectLineStart, theLastRect);

  ++myLinesNb;
  myPenCurrLine -= myLineSpacing;
  myRectLineStart = theLastRect + 1;
}

void Font_TextFormatter::Format()
{
  if (myCorners.Length() == 0 || myIsFormatted)
  {
    return;
  }

  myIsFormatted = true;
  myLinesNb = myRectLineStart = 0;
  myBndTop                    = 0.0f;
  myBndWidth                  = 0.0f;
  myMoveVec.x() = myMoveVec.y() = 0.0f;

  myPenCurrLine = -myAscender;
  int aRectIter = 0;
  myNewLineNb   = 0;

  float aMaxLineWidth = Wrapping();
  if (HasWrapping())
  {

    aMaxLineWidth = std::max(aMaxLineWidth, MaximumSymbolWidth());
  }
  else
  {
    if (myNewLines.IsEmpty())
    {
      aMaxLineWidth = myPen.x();
    }
    else
    {
      for (int aLineIt = 0; aLineIt < myNewLines.Size(); aLineIt++)
      {
        aMaxLineWidth = std::max(aMaxLineWidth, LineWidth(aLineIt));
      }

      aMaxLineWidth = std::max(aMaxLineWidth, LineWidth(myNewLines.Size()));
    }
  }

  char32_t aCharPrev = 0;
  for (Font_TextFormatter::Iterator aFormatterIt(*this); aFormatterIt.More(); aFormatterIt.Next())
  {
    const char32_t aCharThis = aFormatterIt.Symbol();
    aRectIter                = aFormatterIt.SymbolPosition();

    if (aCharThis == '\x0A')
    {
      const int aLastRect = aRectIter;
      newLine(aLastRect, aMaxLineWidth);
      ++myNewLineNb;
      continue;
    }
    else if (HasWrapping())
    {
      int aFirstCornerId = myRectLineStart;

      Font_Rect aBndBox;
      GlyphBoundingBox(aRectIter, aBndBox);
      const float aNextXPos     = aBndBox.Right - BottomLeft(aFirstCornerId).x();
      bool        isCurWordFits = true;
      if (myIsWordWrapping && IsSeparatorSymbol(aCharPrev))
      {
        for (Font_TextFormatter::Iterator aWordIt = aFormatterIt; aWordIt.More(); aWordIt.Next())
        {
          if (IsSeparatorSymbol(aWordIt.Symbol()))
          {
            break;
          }
          float aWordWidthPx = myCorners[aWordIt.SymbolPosition()].x() - myCorners[aRectIter].x();
          if (aNextXPos + aWordWidthPx > aMaxLineWidth)
          {
            isCurWordFits = false;
            break;
          }
        }
      }
      if (aNextXPos > aMaxLineWidth || !isCurWordFits)
      {
        const int aLastRect = aRectIter - 1;
        newLine(aLastRect, aMaxLineWidth);
      }
    }
    aCharPrev = aCharThis;
  }

  myBndWidth = aMaxLineWidth;

  newLine(myCorners.Length() - 1, aMaxLineWidth);

  if (myAlignY == Graphic3d_VTA_BOTTOM)
  {
    myBndTop = -myLineSpacing - myPenCurrLine;
  }
  else if (myAlignY == Graphic3d_VTA_CENTER)
  {
    myBndTop = 0.5f * (myLineSpacing * float(myLinesNb));
  }
  else if (myAlignY == Graphic3d_VTA_TOPFIRSTLINE)
  {
    myBndTop = myAscender;
  }

  if (myAlignY != Graphic3d_VTA_TOP)
  {
    moveY(myCorners, myBndTop, 0, myCorners.Length() - 1);
  }
}

bool Font_TextFormatter::GlyphBoundingBox(const int theIndex, Font_Rect& theBndBox) const
{
  if (theIndex < 0 || theIndex >= Corners().Size())
  {
    return false;
  }

  const NCollection_Vec2<float>& aLeftCorner = BottomLeft(theIndex);
  theBndBox.Left                             = aLeftCorner.x();
  theBndBox.Right                            = aLeftCorner.x() + myLastSymbolWidth;
  theBndBox.Bottom                           = aLeftCorner.y();
  theBndBox.Top                              = theBndBox.Bottom + myLineSpacing;
  if (theIndex + 1 >= myCorners.Length())
  {

    return true;
  }

  const NCollection_Vec2<float>& aNextLeftCorner = BottomLeft(theIndex + 1);
  if (std::abs(aLeftCorner.y() - aNextLeftCorner.y()) < Precision::Confusion())
  {
    theBndBox.Right = aNextLeftCorner.x();
  }
  else
  {

    float aLineWidth = LineWidth(LineIndex(theIndex));
    theBndBox.Left   = aLeftCorner.x();
    switch (myAlignX)
    {
      case Graphic3d_HTA_LEFT:
        theBndBox.Right = aLineWidth;
        break;
      case Graphic3d_HTA_RIGHT:
        theBndBox.Right = myBndWidth;
        break;
      case Graphic3d_HTA_CENTER:
        theBndBox.Right = 0.5f * (myBndWidth + aLineWidth);
        break;
    }
  }
  return true;
}

bool Font_TextFormatter::IsLFSymbol(const int theIndex) const
{
  Font_Rect aBndBox;
  if (!GlyphBoundingBox(theIndex, aBndBox))
  {
    return false;
  }

  return std::abs(aBndBox.Right - aBndBox.Left) < Precision::Confusion();
}

float Font_TextFormatter::FirstPosition() const
{
  switch (myAlignX)
  {
    default:
    case Graphic3d_HTA_LEFT:
      return 0;
    case Graphic3d_HTA_RIGHT:
      return myBndWidth;
    case Graphic3d_HTA_CENTER:
      return 0.5f * myBndWidth;
  }
}

int Font_TextFormatter::LinePositionIndex(const int theIndex) const
{
  int anIndex = 0;

  float anIndexHeight = BottomLeft(theIndex).y();
  for (int aPrevIndex = theIndex - 1; aPrevIndex >= 0; aPrevIndex--)
  {
    if (BottomLeft(aPrevIndex).y() > anIndexHeight)
    {
      break;
    }
    anIndex++;
  }
  return anIndex;
}

int Font_TextFormatter::LineIndex(const int theIndex) const
{
  if (myLineSpacing < 0.0f)
  {
    return 0;
  }

  return (int)std::abs((BottomLeft(theIndex).y() + myAscender) / myLineSpacing);
}

float Font_TextFormatter::LineWidth(const int theIndex) const
{
  if (theIndex < 0)
  {
    return 0;
  }

  if (theIndex < myNewLines.Length())
  {
    return theIndex == 0 ? myNewLines[0] : myNewLines[theIndex] - myNewLines[theIndex - 1];
  }

  if (theIndex == myNewLines.Length())
  {
    return theIndex == 0 ? myPen.x() : myPen.x() - myNewLines[theIndex - 1];
  }

  return 0;
}
