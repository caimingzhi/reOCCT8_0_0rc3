#pragma once

enum Message_MetricType
{
  Message_MetricType_None,
  Message_MetricType_ThreadCPUUserTime,
  Message_MetricType_ThreadCPUSystemTime,
  Message_MetricType_ProcessCPUUserTime,
  Message_MetricType_ProcessCPUSystemTime,
  Message_MetricType_WallClock,
  Message_MetricType_MemPrivate,
  Message_MetricType_MemVirtual,
  Message_MetricType_MemWorkingSet,
  Message_MetricType_MemWorkingSetPeak,
  Message_MetricType_MemSwapUsage,
  Message_MetricType_MemSwapUsagePeak,
  Message_MetricType_MemHeapUsage
};
