#pragma once

#include <StdObject_gp_Axes.hpp>

#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Lin2d& theLin)
{
  gp_Ax2d anAx;
  theReadData >> anAx;
  theLin.SetPosition(anAx);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Lin2d& theLin)
{
  const gp_Ax2d& anAx = theLin.Position();
  write(theWriteData, anAx);
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Circ2d& theCirc)
{
  gp_Ax22d anAx;
  double   aRadius;

  theReadData >> anAx >> aRadius;

  theCirc.SetAxis(anAx);
  theCirc.SetRadius(aRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Circ2d& theCirc)
{
  const gp_Ax22d& anAx    = theCirc.Position();
  double          aRadius = theCirc.Radius();
  theWriteData << anAx << aRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Elips2d& theElips)
{
  gp_Ax22d anAx;
  double   aMajorRadius, aMinorRadius;

  theReadData >> anAx >> aMajorRadius >> aMinorRadius;

  theElips.SetAxis(anAx);
  theElips.SetMajorRadius(aMajorRadius);
  theElips.SetMinorRadius(aMinorRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData,
                                       const gp_Elips2d&    theElips)
{
  const gp_Ax22d& anAx         = theElips.Axis();
  double          aMajorRadius = theElips.MajorRadius();
  double          aMinorRadius = theElips.MinorRadius();
  theWriteData << anAx << aMajorRadius << aMinorRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Hypr2d& theHypr)
{
  gp_Ax22d anAx;
  double   aMajorRadius, aMinorRadius;

  theReadData >> anAx >> aMajorRadius >> aMinorRadius;

  theHypr.SetAxis(anAx);
  theHypr.SetMajorRadius(aMajorRadius);
  theHypr.SetMinorRadius(aMinorRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Hypr2d& theHypr)
{
  const gp_Ax22d& anAx         = theHypr.Axis();
  double          aMajorRadius = theHypr.MajorRadius();
  double          aMinorRadius = theHypr.MinorRadius();
  theWriteData << anAx << aMajorRadius << aMinorRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Parab2d& theParab)
{
  gp_Ax22d anAx;
  double   aFocalLength;

  theReadData >> anAx >> aFocalLength;

  theParab.SetAxis(anAx);
  theParab.SetFocal(aFocalLength);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData,
                                       const gp_Parab2d&    theParab)
{
  const gp_Ax22d& anAx         = theParab.Axis();
  double          aFocalLength = theParab.Focal();
  theWriteData << anAx << aFocalLength;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Lin& theLin)
{
  gp_Ax1 anAx;
  theReadData >> anAx;
  theLin.SetPosition(anAx);
  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Lin& theLin)
{
  const gp_Ax1& anAx = theLin.Position();
  write(theWriteData, anAx);
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Circ& theCirc)
{
  gp_Ax2 anAx;
  double aRadius;

  theReadData >> anAx >> aRadius;

  theCirc.SetPosition(anAx);
  theCirc.SetRadius(aRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Circ& theCirc)
{
  const gp_Ax2& anAx    = theCirc.Position();
  double        aRadius = theCirc.Radius();
  theWriteData << anAx << aRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Elips& theElips)
{
  gp_Ax2 anAx;
  double aMajorRadius, aMinorRadius;

  theReadData >> anAx >> aMajorRadius >> aMinorRadius;

  theElips.SetPosition(anAx);
  theElips.SetMajorRadius(aMajorRadius);
  theElips.SetMinorRadius(aMinorRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Elips& theElips)
{
  const gp_Ax2& anAx         = theElips.Position();
  double        aMajorRadius = theElips.MajorRadius();
  double        aMinorRadius = theElips.MinorRadius();
  theWriteData << anAx << aMajorRadius << aMinorRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Hypr& theHypr)
{
  gp_Ax2 anAx;
  double aMajorRadius, aMinorRadius;

  theReadData >> anAx >> aMajorRadius >> aMinorRadius;

  theHypr.SetPosition(anAx);
  theHypr.SetMajorRadius(aMajorRadius);
  theHypr.SetMinorRadius(aMinorRadius);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Hypr& theHypr)
{
  const gp_Ax2& anAx         = theHypr.Position();
  double        aMajorRadius = theHypr.MajorRadius();
  double        aMinorRadius = theHypr.MinorRadius();
  theWriteData << anAx << aMajorRadius << aMinorRadius;
  return theWriteData;
}

inline StdObjMgt_ReadData& operator>>(StdObjMgt_ReadData& theReadData, gp_Parab& theParab)
{
  gp_Ax2 anAx;
  double aFocalLength;

  theReadData >> anAx >> aFocalLength;

  theParab.SetPosition(anAx);
  theParab.SetFocal(aFocalLength);

  return theReadData;
}

inline StdObjMgt_WriteData& operator<<(StdObjMgt_WriteData& theWriteData, const gp_Parab& theParab)
{
  const gp_Ax2& anAx         = theParab.Position();
  double        aFocalLength = theParab.Focal();
  theWriteData << anAx << aFocalLength;
  return theWriteData;
}
