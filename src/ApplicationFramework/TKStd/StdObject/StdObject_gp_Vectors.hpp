#pragma once

#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>

#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_XY& theXY)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  double aX, aY;
  theReadData >> aX >> aY;
  theXY.SetCoord(aX, aY);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_XY& theXY)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  double aX = theXY.X(), aY = theXY.Y();
  theWriteData << aX << aY;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Pnt2d& thePnt)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  gp_XY aXY;
  theReadData >> aXY;
  thePnt.SetXY(aXY);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Pnt2d& thePnt)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << thePnt.XY();
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Vec2d& theVec)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  gp_XY aXY;
  theReadData >> aXY;
  theVec.SetXY(aXY);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Vec2d& theVec)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << theVec.XY();
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Dir2d& theDir)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  gp_XY aXY;
  theReadData >> aXY;
  theDir.SetXY(aXY);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Dir2d& theDir)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << theDir.XY();
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_XYZ& theXYZ)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  double aX, aY, aZ;
  theReadData >> aX >> aY >> aZ;
  theXYZ.SetCoord(aX, aY, aZ);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_XYZ& theXYZ)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  double aX = theXYZ.X(), aY = theXYZ.Y(), aZ = theXYZ.Z();
  theWriteData << aX << aY << aZ;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Pnt& thePnt)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  gp_XYZ aXYZ;
  theReadData >> aXYZ;
  thePnt.SetXYZ(aXYZ);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Pnt& thePnt)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << thePnt.XYZ();
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Vec& theVec)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  gp_XYZ aXYZ;
  theReadData >> aXYZ;
  theVec.SetXYZ(aXYZ);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Vec& theVec)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << theVec.XYZ();
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Dir& theDir)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  gp_XYZ aXYZ;
  theReadData >> aXYZ;
  theDir.SetXYZ(aXYZ);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Dir& theDir)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << theDir.XYZ();
  return theWriteData;
}
