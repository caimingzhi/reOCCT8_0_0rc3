#pragma once

#include <NCollection_Vec2.hpp>
#include <Standard_Dump.hpp>

struct Font_Rect
{

  float Left;
  float Right;
  float Top;
  float Bottom;

  NCollection_Vec2<float> TopLeft() const { return NCollection_Vec2<float>(Left, Top); }

  NCollection_Vec2<float>& TopLeft(NCollection_Vec2<float>& theVec) const
  {
    theVec.x() = Left;
    theVec.y() = Top;
    return theVec;
  }

  NCollection_Vec2<float>& TopRight(NCollection_Vec2<float>& theVec) const
  {
    theVec.x() = Right;
    theVec.y() = Top;
    return theVec;
  }

  NCollection_Vec2<float>& BottomLeft(NCollection_Vec2<float>& theVec) const
  {
    theVec.x() = Left;
    theVec.y() = Bottom;
    return theVec;
  }

  NCollection_Vec2<float>& BottomRight(NCollection_Vec2<float>& theVec) const
  {
    theVec.x() = Right;
    theVec.y() = Bottom;
    return theVec;
  }

  float Width() const { return Right - Left; }

  float Height() const { return Top - Bottom; }

  void DumpJson(Standard_OStream& theOStream, int) const
  {
    OCCT_DUMP_CLASS_BEGIN(theOStream, Font_Rect)

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Left)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Right)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Top)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Bottom)
  }
};
