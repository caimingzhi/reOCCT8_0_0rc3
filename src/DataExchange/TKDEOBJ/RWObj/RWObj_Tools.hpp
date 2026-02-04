#pragma once


#include <gp_XYZ.hpp>
#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <TCollection_AsciiString.hpp>

//! Auxiliary tools for OBJ format parser.
namespace RWObj_Tools
{
//! Read 3 float values.
inline bool ReadVec3(const char* thePos, char*& theNext, NCollection_Vec3<float>& theVec)
{
  const char* aPos = thePos;
  theVec.x()       = (float)Strtod(aPos, &theNext);
  aPos             = theNext;
  theVec.y()       = (float)Strtod(aPos, &theNext);
  aPos             = theNext;
  theVec.z()       = (float)Strtod(aPos, &theNext);
  return aPos != theNext;
}

//! Read 3 double values.
inline bool ReadVec3(const char* thePos, char*& theNext, gp_XYZ& theVec)
{
  const char* aPos = thePos;
  theVec.SetX(Strtod(aPos, &theNext));
  aPos = theNext;
  theVec.SetY(Strtod(aPos, &theNext));
  aPos = theNext;
  theVec.SetZ(Strtod(aPos, &theNext));
  return aPos != theNext;
}

//! Read string.
inline bool ReadName(const char* thePos, TCollection_AsciiString& theName)
{
  int aFrom = 0;
  int aTail = (int)std::strlen(thePos) - 1;
  if (aTail >= 0 && thePos[aTail] == '\n')
  {
    --aTail;
  }
  if (aTail >= 0 && thePos[aTail] == '\r')
  {
    --aTail;
  }
  for (; aTail >= 0 && IsSpace(thePos[aTail]); --aTail)
  {
  } // RightAdjust
  for (; aFrom < aTail && IsSpace(thePos[aFrom]); ++aFrom)
  {
  } // LeftAdjust
  if (aFrom > aTail)
  {
    theName.Clear();
    return false;
  }
  theName = TCollection_AsciiString(thePos + aFrom, aTail - aFrom + 1);
  return true;
}

//! Return true if specified char is a white space.
inline bool isSpaceChar(const char theChar)
{
  return theChar == ' ' || theChar == '\t';
  // return IsSpace (theChar);
}
} // namespace RWObj_Tools

