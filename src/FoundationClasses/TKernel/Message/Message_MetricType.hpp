#pragma once

//! Specifies kind of report information to collect
enum Message_MetricType
{
  Message_MetricType_None,                 //!< no computation
  Message_MetricType_ThreadCPUUserTime,    //!< OSD_Chronometer::GetThreadCPU user time
  Message_MetricType_ThreadCPUSystemTime,  //!< OSD_Chronometer::GetThreadCPU system time
  Message_MetricType_ProcessCPUUserTime,   //!< OSD_Chronometer::GetProcessCPU user time
  Message_MetricType_ProcessCPUSystemTime, //!< OSD_Chronometer::GetProcessCPU system time
  Message_MetricType_WallClock,            //!< OSD_Timer elapsed time
  Message_MetricType_MemPrivate,           //!< OSD_MemInfo::MemPrivate
  Message_MetricType_MemVirtual,           //!< OSD_MemInfo::MemVirtual
  Message_MetricType_MemWorkingSet,        //!< OSD_MemInfo::MemWorkingSet
  Message_MetricType_MemWorkingSetPeak,    //!< OSD_MemInfo::MemWorkingSetPeak
  Message_MetricType_MemSwapUsage,         //!< OSD_MemInfo::MemSwapUsage
  Message_MetricType_MemSwapUsagePeak,     //!< OSD_MemInfo::MemSwapUsagePeak
  Message_MetricType_MemHeapUsage          //!< OSD_MemInfo::MemHeapUsage
};
