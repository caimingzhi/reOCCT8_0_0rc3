#pragma once


#include <StdObject_gp_Vectors.hpp>

#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Ax3.hpp>

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Ax2d& theAx)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  gp_Pnt2d                         aLoc;
  gp_Dir2d                         aDir;
  theReadData >> aLoc >> aDir;
  theAx = gp_Ax2d(aLoc, aDir);
  return theReadData;
}

inline StdObjMgt_WriteData& write(StdObjMgt_WriteData& theWriteData, const gp_Ax2d& theAx)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const gp_Pnt2d& aLoc = theAx.Location();
  const gp_Dir2d& aDir = theAx.Direction();
  theWriteData << aLoc << aDir;
  return theWriteData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Ax2d& theAx)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const gp_Pnt2d& aLoc = theAx.Location();
  const gp_Dir2d& aDir = theAx.Direction();
  theWriteData << aLoc << aDir;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Ax22d& theAx)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  gp_Pnt2d                         aLoc;
  gp_Dir2d                         aYDir, aXDir;
  theReadData >> aLoc >> aYDir >> aXDir;
  theAx = gp_Ax22d(aLoc, aXDir, aYDir);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Ax22d& theAx)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const gp_Pnt2d& aLoc  = theAx.Location();
  const gp_Dir2d& aYDir = theAx.YDirection();
  const gp_Dir2d& aXDir = theAx.XDirection();
  theWriteData << aLoc << aYDir << aXDir;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Ax1& theAx)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  gp_Pnt                           aLoc;
  gp_Dir                           aDir;
  theReadData >> aLoc >> aDir;
  theAx = gp_Ax1(aLoc, aDir);
  return theReadData;
}

inline StdObjMgt_WriteData& write(StdObjMgt_WriteData& theWriteData, const gp_Ax1& theAx)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const gp_Pnt& aLoc = theAx.Location();
  const gp_Dir& aDir = theAx.Direction();
  theWriteData << aLoc << aDir;
  return theWriteData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Ax1& theAx)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const gp_Pnt& aLoc = theAx.Location();
  const gp_Dir& aDir = theAx.Direction();
  theWriteData << aLoc << aDir;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Ax2& theAx)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  gp_Ax1                           anAx;
  gp_Dir                           aYDir, aXDir;
  theReadData >> anAx >> aYDir >> aXDir;
  theAx = gp_Ax2(anAx.Location(), anAx.Direction(), aXDir);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Ax2& theAx)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const gp_Ax1& anAx  = theAx.Axis();
  const gp_Dir& aYDir = theAx.YDirection();
  const gp_Dir& aXDir = theAx.XDirection();
  theWriteData << anAx << aYDir << aXDir;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Ax3& theAx)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  gp_Ax1                           anAx;
  gp_Dir                           aYDir, aXDir;
  theReadData >> anAx >> aYDir >> aXDir;
  theAx = gp_Ax3(anAx.Location(), anAx.Direction(), aXDir);
  if (aYDir * theAx.YDirection() < 0.)
    theAx.YReverse();
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Ax3& theAx)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  const gp_Ax1& anAx  = theAx.Axis();
  const gp_Dir& aYDir = theAx.YDirection();
  const gp_Dir& aXDir = theAx.XDirection();
  theWriteData << anAx << aYDir << aXDir;
  return theWriteData;
}

