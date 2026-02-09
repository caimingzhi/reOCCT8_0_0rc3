#pragma once

#include <NCollection_Array1.hpp>

enum Graphic3d_FrameStatsCounter
{

  Graphic3d_FrameStatsCounter_NbLayers = 0,
  Graphic3d_FrameStatsCounter_NbStructs,
  Graphic3d_FrameStatsCounter_EstimatedBytesGeom,
  Graphic3d_FrameStatsCounter_EstimatedBytesFbos,
  Graphic3d_FrameStatsCounter_EstimatedBytesTextures,

  Graphic3d_FrameStatsCounter_NbLayersNotCulled,
  Graphic3d_FrameStatsCounter_NbStructsNotCulled,
  Graphic3d_FrameStatsCounter_NbGroupsNotCulled,
  Graphic3d_FrameStatsCounter_NbElemsNotCulled,
  Graphic3d_FrameStatsCounter_NbElemsFillNotCulled,

  Graphic3d_FrameStatsCounter_NbElemsLineNotCulled,

  Graphic3d_FrameStatsCounter_NbElemsPointNotCulled,

  Graphic3d_FrameStatsCounter_NbElemsTextNotCulled,
  Graphic3d_FrameStatsCounter_NbTrianglesNotCulled,

  Graphic3d_FrameStatsCounter_NbLinesNotCulled,

  Graphic3d_FrameStatsCounter_NbPointsNotCulled,

  Graphic3d_FrameStatsCounter_NbLayersImmediate,
  Graphic3d_FrameStatsCounter_NbStructsImmediate,
  Graphic3d_FrameStatsCounter_NbGroupsImmediate,
  Graphic3d_FrameStatsCounter_NbElemsImmediate,
  Graphic3d_FrameStatsCounter_NbElemsFillImmediate,

  Graphic3d_FrameStatsCounter_NbElemsLineImmediate,

  Graphic3d_FrameStatsCounter_NbElemsPointImmediate,

  Graphic3d_FrameStatsCounter_NbElemsTextImmediate,
  Graphic3d_FrameStatsCounter_NbTrianglesImmediate,
  Graphic3d_FrameStatsCounter_NbLinesImmediate,
  Graphic3d_FrameStatsCounter_NbPointsImmediate,
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

class Graphic3d_FrameStatsData
{
public:
  DEFINE_STANDARD_ALLOC

  double FrameRate() const { return myFps; }

  double FrameRateCpu() const { return myFpsCpu; }

  double ImmediateFrameRate() const { return myFpsImmediate; }

  double ImmediateFrameRateCpu() const { return myFpsCpuImmediate; }

  size_t CounterValue(Graphic3d_FrameStatsCounter theIndex) const { return myCounters[theIndex]; }

  size_t operator[](Graphic3d_FrameStatsCounter theIndex) const { return CounterValue(theIndex); }

  double TimerValue(Graphic3d_FrameStatsTimer theIndex) const { return myTimers[theIndex]; }

  double operator[](Graphic3d_FrameStatsTimer theIndex) const { return TimerValue(theIndex); }

  Standard_EXPORT Graphic3d_FrameStatsData();

  Standard_EXPORT Graphic3d_FrameStatsData(const Graphic3d_FrameStatsData& theOther);

  Standard_EXPORT Graphic3d_FrameStatsData(Graphic3d_FrameStatsData&& theOther) noexcept;

  Standard_EXPORT Graphic3d_FrameStatsData& operator=(const Graphic3d_FrameStatsData& theOther);

  Standard_EXPORT Graphic3d_FrameStatsData& operator=(Graphic3d_FrameStatsData&& theOther) noexcept;

  Standard_EXPORT void Reset();

  Standard_EXPORT void FillMax(const Graphic3d_FrameStatsData& theOther);

protected:
  std::vector<size_t> myCounters;
  std::vector<double> myTimers;
  std::vector<double> myTimersMin;
  std::vector<double> myTimersMax;
  double              myFps;
  double              myFpsCpu;
  double              myFpsImmediate;
  double              myFpsCpuImmediate;
};

class Graphic3d_FrameStatsDataTmp : public Graphic3d_FrameStatsData
{
public:
  Standard_EXPORT Graphic3d_FrameStatsDataTmp();

  Standard_EXPORT void FlushTimers(size_t theNbFrames, bool theIsFinal);

  Standard_EXPORT void Reset();

  void operator=(const Graphic3d_FrameStatsData& theOther)
  {
    Graphic3d_FrameStatsData::operator=(theOther);
  }

  double& ChangeFrameRate() { return myFps; }

  double& ChangeFrameRateCpu() { return myFpsCpu; }

  double& ChangeImmediateFrameRate() { return myFpsImmediate; }

  double& ChangeImmediateFrameRateCpu() { return myFpsCpuImmediate; }

  OSD_Timer& ChangeTimer(Graphic3d_FrameStatsTimer theTimer) { return myOsdTimers[theTimer]; }

  size_t& ChangeCounterValue(Graphic3d_FrameStatsCounter theIndex) { return myCounters[theIndex]; }

  size_t& operator[](Graphic3d_FrameStatsCounter theIndex) { return ChangeCounterValue(theIndex); }

  double& ChangeTimerValue(Graphic3d_FrameStatsTimer theIndex) { return myTimers[theIndex]; }

  double& operator[](Graphic3d_FrameStatsTimer theIndex) { return ChangeTimerValue(theIndex); }

protected:
  std::vector<OSD_Timer> myOsdTimers;
  std::vector<double>    myTimersPrev;
};
