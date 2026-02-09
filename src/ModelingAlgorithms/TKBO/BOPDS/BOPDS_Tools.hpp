#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <TopAbs_ShapeEnum.hpp>

class BOPDS_Tools
{
public:
  DEFINE_STANDARD_ALLOC

  static int TypeToInteger(const TopAbs_ShapeEnum theT1, const TopAbs_ShapeEnum theT2);

  static int TypeToInteger(const TopAbs_ShapeEnum theT);

  static bool HasBRep(const TopAbs_ShapeEnum theT);

  static bool IsInterfering(const TopAbs_ShapeEnum theT);
};

inline bool BOPDS_Tools::HasBRep(const TopAbs_ShapeEnum aTi)
{
  return (aTi == TopAbs_VERTEX || aTi == TopAbs_EDGE || aTi == TopAbs_FACE);
}

inline bool BOPDS_Tools::IsInterfering(const TopAbs_ShapeEnum aTi)
{
  return (BOPDS_Tools::HasBRep(aTi) || aTi == TopAbs_SOLID);
}

inline int BOPDS_Tools::TypeToInteger(const TopAbs_ShapeEnum aType1, const TopAbs_ShapeEnum aType2)
{
  int iRet, iT1, iT2, iX;

  iRet = -1;
  iT1  = BOPDS_Tools::TypeToInteger(aType1);
  iT2  = BOPDS_Tools::TypeToInteger(aType2);

  iX = iT2 * 10 + iT1;
  switch (iX)
  {
    case 77:
      iRet = 0;
      break;
    case 76:
    case 67:
      iRet = 1;
      break;
    case 66:
      iRet = 2;
      break;
    case 74:
    case 47:
      iRet = 3;
      break;
    case 64:
    case 46:
      iRet = 4;
      break;
    case 44:
      iRet = 5;
      break;
    case 72:
    case 27:
      iRet = 6;
      break;
    case 62:
    case 26:
      iRet = 7;
      break;
    case 42:
    case 24:
      iRet = 8;
      break;
    case 22:
      iRet = 9;
      break;
    default:
      break;
  }
  return iRet;
}

inline int BOPDS_Tools::TypeToInteger(const TopAbs_ShapeEnum aType1)
{
  int iRet = 9;

  switch (aType1)
  {
    case TopAbs_COMPOUND:
      iRet = 0;
      break;
    case TopAbs_COMPSOLID:
      iRet = 1;
      break;
    case TopAbs_SOLID:
      iRet = 2;
      break;
    case TopAbs_SHELL:
      iRet = 3;
      break;
    case TopAbs_FACE:
      iRet = 4;
      break;
    case TopAbs_WIRE:
      iRet = 5;
      break;
    case TopAbs_EDGE:
      iRet = 6;
      break;
    case TopAbs_VERTEX:
      iRet = 7;
      break;
    case TopAbs_SHAPE:
      iRet = 8;
      break;
    default:
      break;
  }
  return iRet;
}
