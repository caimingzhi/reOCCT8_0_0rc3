#pragma once


#include <StdObject_gp_Vectors.hpp>

#include <gp_Mat2d.hpp>
#include <gp_Mat.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Trsf.hpp>

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Mat2d& theMat)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  theReadData >> theMat(1, 1) >> theMat(1, 2) >> theMat(2, 1) >> theMat(2, 2);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Mat2d& theMat)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << theMat(1, 1) << theMat(1, 2) << theMat(2, 1) << theMat(2, 2);
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Mat& theMat)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);
  theReadData >> theMat(1, 1) >> theMat(1, 2) >> theMat(1, 3) >> theMat(2, 1) >> theMat(2, 2)
    >> theMat(2, 3) >> theMat(3, 1) >> theMat(3, 2) >> theMat(3, 3);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Mat& theMat)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  theWriteData << theMat(1, 1) << theMat(1, 2) << theMat(1, 3) << theMat(2, 1) << theMat(2, 2)
               << theMat(2, 3) << theMat(3, 1) << theMat(3, 2) << theMat(3, 3);
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Trsf2d& theTrsf)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  double   aScale;
  int      aForm;
  gp_Mat2d aMat;
  gp_XY    aLoc;

  theReadData >> aScale >> aForm >> aMat >> aLoc;

  theTrsf.SetValues(aScale * aMat(1, 1),
                    aScale * aMat(1, 2),
                    aLoc.X(),
                    aScale * aMat(2, 1),
                    aScale * aMat(2, 2),
                    aLoc.Y());

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Trsf2d& theTrsf)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  double          aScale = theTrsf.ScaleFactor();
  int             aForm  = theTrsf.Form();
  const gp_Mat2d& aMat   = theTrsf.HVectorialPart();
  const gp_XY&    aLoc   = theTrsf.TranslationPart();

  theWriteData << aScale << aForm << aMat << aLoc;

  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Trsf& theTrsf)
{
  StdObjMgt_ReadData::ObjectSentry aSentry(theReadData);

  double aScale;
  int    aForm;
  gp_Mat aMat;
  gp_XYZ aLoc;

  theReadData >> aScale >> aForm >> aMat >> aLoc;

  theTrsf.SetValues(aScale * aMat(1, 1),
                    aScale * aMat(1, 2),
                    aScale * aMat(1, 3),
                    aLoc.X(),
                    aScale * aMat(2, 1),
                    aScale * aMat(2, 2),
                    aScale * aMat(2, 3),
                    aLoc.Y(),
                    aScale * aMat(3, 1),
                    aScale * aMat(3, 2),
                    aScale * aMat(3, 3),
                    aLoc.Z());

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Trsf& theTrsf)
{
  StdObjMgt_WriteData::ObjectSentry aSentry(theWriteData);

  double        aScale = theTrsf.ScaleFactor();
  int           aForm  = theTrsf.Form();
  const gp_Mat& aMat   = theTrsf.HVectorialPart();
  const gp_XYZ& aLoc   = theTrsf.TranslationPart();

  theWriteData << aScale << aForm << aMat << aLoc;

  return theWriteData;
}

