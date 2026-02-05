#pragma once

#include <NCollection_Array1.hpp>

// Copyright (c) 2018 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//! Stats counter.
enum Graphic3d_FrameStatsCounter
{
  // overall scene counters
  Graphic3d_FrameStatsCounter_NbLayers = 0,           //!< number of ZLayers
  Graphic3d_FrameStatsCounter_NbStructs,              //!< number of defined OpenGl_Structure
  Graphic3d_FrameStatsCounter_EstimatedBytesGeom,     //!< estimated GPU memory used for geometry
  Graphic3d_FrameStatsCounter_EstimatedBytesFbos,     //!< estimated GPU memory used for FBOs
  Graphic3d_FrameStatsCounter_EstimatedBytesTextures, //!< estimated GPU memory used for textures

  // rendered counters
  Graphic3d_FrameStatsCounter_NbLayersNotCulled,     //!< number of not culled ZLayers
  Graphic3d_FrameStatsCounter_NbStructsNotCulled,    //!< number of not culled OpenGl_Structure
  Graphic3d_FrameStatsCounter_NbGroupsNotCulled,     //!< number of not culled OpenGl_Group
  Graphic3d_FrameStatsCounter_NbElemsNotCulled,      //!< number of not culled OpenGl_Element
  Graphic3d_FrameStatsCounter_NbElemsFillNotCulled,  //!< number of not culled OpenGl_PrimitiveArray
                                                     //!< drawing triangles
  Graphic3d_FrameStatsCounter_NbElemsLineNotCulled,  //!< number of not culled OpenGl_PrimitiveArray
                                                     //!< drawing lines
  Graphic3d_FrameStatsCounter_NbElemsPointNotCulled, //!< number of not culled OpenGl_PrimitiveArray
                                                     //!< drawing points
  Graphic3d_FrameStatsCounter_NbElemsTextNotCulled,  //!< number of not culled OpenGl_Text
  Graphic3d_FrameStatsCounter_NbTrianglesNotCulled,  //!< number of not culled (as structure)
                                                     //!< triangles
  Graphic3d_FrameStatsCounter_NbLinesNotCulled,      //!< number of not culled (as structure) line
                                                     //!< segments
  Graphic3d_FrameStatsCounter_NbPointsNotCulled,     //!< number of not culled (as structure) points
  // Graphic3d_FrameStatsCounter_NbGlyphsNotCulled,    //!< number glyphs, to be considered in
  // future

  // immediate layer rendered counters
  Graphic3d_FrameStatsCounter_NbLayersImmediate,  //!< number of ZLayers in immediate layer
  Graphic3d_FrameStatsCounter_NbStructsImmediate, //!< number of OpenGl_Structure in immediate layer
  Graphic3d_FrameStatsCounter_NbGroupsImmediate,  //!< number of OpenGl_Group in immediate layer
  Graphic3d_FrameStatsCounter_NbElemsImmediate,   //!< number of OpenGl_Element in immediate layer
  Graphic3d_FrameStatsCounter_NbElemsFillImmediate,  //!< number of OpenGl_PrimitiveArray drawing
                                                     //!< triangles in immediate layer
  Graphic3d_FrameStatsCounter_NbElemsLineImmediate,  //!< number of OpenGl_PrimitiveArray drawing
                                                     //!< lines in immediate layer
  Graphic3d_FrameStatsCounter_NbElemsPointImmediate, //!< number of OpenGl_PrimitiveArray drawing
                                                     //!< points in immediate layer
  Graphic3d_FrameStatsCounter_NbElemsTextImmediate,  //!< number of OpenGl_Text in immediate layer
  Graphic3d_FrameStatsCounter_NbTrianglesImmediate,  //!< number of triangles in immediate layer
  Graphic3d_FrameStatsCounter_NbLinesImmediate,      //!< number of line segments in immediate layer
  Graphic3d_FrameStatsCounter_NbPointsImmediate,     //!< number of points in immediate layer
};

enum
{
  Graphic3d_FrameStatsCounter_NB              = Graphic3d_FrameStatsCounter_NbPointsImmediate + 1,
  Graphic3d_FrameStatsCounter_SCENE_LOWER     = Graphic3d_FrameStatsCounter_NbLayers,
  Graphic3d_FrameStatsCounter_SCENE_UPPER     = Graphic3d_FrameStatsCounter_EstimatedBytesTextures,
  Graphic3d_FrameStatsCounter_RENDERED_LOWER  = Graphic3d_FrameStatsCounter_NbLayersNotCulled,
  Graphic3d_FrameStatsCounter_RENDERED_UPPER  = Graphic3d_FrameStatsCounter_NbPointsNotCulled,
  Graphic3d_FrameStatsCounter_IMMEDIATE_LOWER = Graphic3d_FrameStatsCounter_NbLayersImmediate,
  Graphic3d_FrameStatsCounter_IMMEDIATE_UPPER = Graphic3d_FrameStatsCounter_NbPointsImmediate,
};

// Copyright (c) 2018 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//! Timers for collecting frame performance statistics.
enum Graphic3d_FrameStatsTimer
{
  Graphic3d_FrameStatsTimer_ElapsedFrame,
  Graphic3d_FrameStatsTimer_CpuFrame,
  Graphic3d_FrameStatsTimer_CpuCulling,
  Graphic3d_FrameStatsTimer_CpuPicking,
  Graphic3d_FrameStatsTimer_CpuDynamics,
};

enum
{
  Graphic3d_FrameStatsTimer_NB = Graphic3d_FrameStatsTimer_CpuDynamics + 1
};

#include <OSD_Timer.hpp>

#include <vector>

//! Data frame definition.
class Graphic3d_FrameStatsData
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns FPS (frames per seconds, elapsed time).
  //! This number indicates an actual frame rate averaged for several frames within UpdateInterval()
  //! duration, basing on a real elapsed time between updates.
  double FrameRate() const { return myFps; }

  //! Returns CPU FPS (frames per seconds, CPU time).
  //! This number indicates a PREDICTED frame rate,
  //! basing on CPU elapsed time between updates and NOT real elapsed time (which might include
  //! periods of CPU inactivity). Number is expected to be greater then actual frame rate returned
  //! by FrameRate(). Values significantly greater actual frame rate indicate that rendering is
  //! limited by GPU performance (CPU is stalled in-between), while values around actual frame rate
  //! indicate rendering being limited by CPU performance (GPU is stalled in-between).
  double FrameRateCpu() const { return myFpsCpu; }

  //! Returns FPS for immediate redraws.
  double ImmediateFrameRate() const { return myFpsImmediate; }

  //! Returns CPU FPS for immediate redraws.
  double ImmediateFrameRateCpu() const { return myFpsCpuImmediate; }

  //! Get counter value.
  size_t CounterValue(Graphic3d_FrameStatsCounter theIndex) const { return myCounters[theIndex]; }

  //! Get counter value.
  size_t operator[](Graphic3d_FrameStatsCounter theIndex) const { return CounterValue(theIndex); }

  //! Get timer value.
  double TimerValue(Graphic3d_FrameStatsTimer theIndex) const { return myTimers[theIndex]; }

  //! Get timer value.
  double operator[](Graphic3d_FrameStatsTimer theIndex) const { return TimerValue(theIndex); }

  //! Empty constructor.
  Standard_EXPORT Graphic3d_FrameStatsData();

  //! Copy constructor.
  Standard_EXPORT Graphic3d_FrameStatsData(const Graphic3d_FrameStatsData& theOther);

  //! Move constructor.
  Standard_EXPORT Graphic3d_FrameStatsData(Graphic3d_FrameStatsData&& theOther) noexcept;

  //! Assignment operator.
  Standard_EXPORT Graphic3d_FrameStatsData& operator=(const Graphic3d_FrameStatsData& theOther);

  //! Assignment with move operator.
  Standard_EXPORT Graphic3d_FrameStatsData& operator=(Graphic3d_FrameStatsData&& theOther) noexcept;

  //! Reset data.
  Standard_EXPORT void Reset();

  //! Fill with maximum values.
  Standard_EXPORT void FillMax(const Graphic3d_FrameStatsData& theOther);

protected:
  std::vector<size_t> myCounters;        //!< counters
  std::vector<double> myTimers;          //!< timers
  std::vector<double> myTimersMin;       //!< minimal values of timers
  std::vector<double> myTimersMax;       //!< maximum values of timers
  double              myFps;             //!< FPS     meter (frames per seconds, elapsed time)
  double              myFpsCpu;          //!< CPU FPS meter (frames per seconds, CPU time)
  double              myFpsImmediate;    //!< FPS     meter for immediate redraws
  double              myFpsCpuImmediate; //!< CPU FPS meter for immediate redraws
};

//! Temporary data frame definition.
class Graphic3d_FrameStatsDataTmp : public Graphic3d_FrameStatsData
{
public:
  //! Empty constructor.
  Standard_EXPORT Graphic3d_FrameStatsDataTmp();

  //! Compute average data considering the amount of rendered frames.
  Standard_EXPORT void FlushTimers(size_t theNbFrames, bool theIsFinal);

  //! Reset data.
  Standard_EXPORT void Reset();

  //! Assignment operator (skip copying irrelevant properties).
  void operator=(const Graphic3d_FrameStatsData& theOther)
  {
    Graphic3d_FrameStatsData::operator=(theOther);
  }

  //! Returns FPS (frames per seconds, elapsed time).
  double& ChangeFrameRate() { return myFps; }

  //! Returns CPU FPS (frames per seconds, CPU time).
  double& ChangeFrameRateCpu() { return myFpsCpu; }

  //! Returns FPS for immediate redraws.
  double& ChangeImmediateFrameRate() { return myFpsImmediate; }

  //! Returns CPU FPS for immediate redraws.
  double& ChangeImmediateFrameRateCpu() { return myFpsCpuImmediate; }

  //! Return a timer object for time measurements.
  OSD_Timer& ChangeTimer(Graphic3d_FrameStatsTimer theTimer) { return myOsdTimers[theTimer]; }

  //! Get counter value.
  size_t& ChangeCounterValue(Graphic3d_FrameStatsCounter theIndex) { return myCounters[theIndex]; }

  //! Modify counter value.
  size_t& operator[](Graphic3d_FrameStatsCounter theIndex) { return ChangeCounterValue(theIndex); }

  //! Modify timer value.
  double& ChangeTimerValue(Graphic3d_FrameStatsTimer theIndex) { return myTimers[theIndex]; }

  //! Modify timer value.
  double& operator[](Graphic3d_FrameStatsTimer theIndex) { return ChangeTimerValue(theIndex); }

protected:
  std::vector<OSD_Timer> myOsdTimers;  //!< precise timers for time measurements
  std::vector<double>    myTimersPrev; //!< previous timers values
};
