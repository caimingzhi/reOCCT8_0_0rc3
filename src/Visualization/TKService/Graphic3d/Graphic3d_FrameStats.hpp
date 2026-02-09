#pragma once

#include <Graphic3d_FrameStatsData.hpp>
#include <Graphic3d_RenderingParams.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>

class Graphic3d_CView;

class Graphic3d_FrameStats : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_FrameStats, Standard_Transient)
public:
  Standard_EXPORT Graphic3d_FrameStats();

  Standard_EXPORT ~Graphic3d_FrameStats() override;

  double UpdateInterval() const { return myUpdateInterval; }

  void SetUpdateInterval(double theInterval) { myUpdateInterval = theInterval; }

  bool IsLongLineFormat() const { return myIsLongLineFormat; }

  void SetLongLineFormat(bool theValue) { myIsLongLineFormat = theValue; }

  Standard_EXPORT virtual void FrameStart(const occ::handle<Graphic3d_CView>& theView,
                                          bool                                theIsImmediateOnly);

  Standard_EXPORT virtual void FrameEnd(const occ::handle<Graphic3d_CView>& theView,
                                        bool                                theIsImmediateOnly);

public:
  Standard_EXPORT virtual TCollection_AsciiString FormatStats(
    Graphic3d_RenderingParams::PerfCounters theFlags) const;

  Standard_EXPORT virtual void FormatStats(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict,
    Graphic3d_RenderingParams::PerfCounters                                       theFlags) const;

  double FrameDuration() const { return myFrameDuration; }

  double FrameRate() const { return LastDataFrame().FrameRate(); }

  double FrameRateCpu() const { return LastDataFrame().FrameRateCpu(); }

  size_t CounterValue(Graphic3d_FrameStatsCounter theCounter) const
  {
    return LastDataFrame()[theCounter];
  }

  double TimerValue(Graphic3d_FrameStatsTimer theTimer) const { return LastDataFrame()[theTimer]; }

  bool HasCulledLayers() const
  {
    return LastDataFrame()[Graphic3d_FrameStatsCounter_NbLayersNotCulled]
           != LastDataFrame()[Graphic3d_FrameStatsCounter_NbLayers];
  }

  bool HasCulledStructs() const
  {
    return LastDataFrame()[Graphic3d_FrameStatsCounter_NbStructsNotCulled]
           != LastDataFrame()[Graphic3d_FrameStatsCounter_NbStructs];
  }

  const Graphic3d_FrameStatsData& LastDataFrame() const
  {
    return myCounters.Value(myLastFrameIndex);
  }

  int LastDataFrameIndex() const { return myLastFrameIndex; }

  const NCollection_Array1<Graphic3d_FrameStatsData>& DataFrames() const { return myCounters; }

  NCollection_Array1<Graphic3d_FrameStatsData>& ChangeDataFrames() { return myCounters; }

public:
  size_t& ChangeCounter(Graphic3d_FrameStatsCounter theCounter)
  {
    return ActiveDataFrame()[theCounter];
  }

  double& ChangeTimer(Graphic3d_FrameStatsTimer theTimer) { return ActiveDataFrame()[theTimer]; }

  Graphic3d_FrameStatsDataTmp& ActiveDataFrame() { return myCountersTmp; }

protected:
  virtual void updateStatistics(const occ::handle<Graphic3d_CView>& theView,
                                bool                                theIsImmediateOnly) = 0;

protected:
  OSD_Timer myFpsTimer;
  double    myFrameStartTime;
  double    myFrameDuration;
  double    myUpdateInterval;

  size_t                                       myFpsFrameCount;
  NCollection_Array1<Graphic3d_FrameStatsData> myCounters;
  Graphic3d_FrameStatsDataTmp                  myCountersTmp;
  Graphic3d_FrameStatsData                     myCountersMax;
  int                                          myLastFrameIndex;
  bool                                         myIsLongLineFormat;
};
