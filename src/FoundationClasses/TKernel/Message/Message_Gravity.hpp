#pragma once


//! Defines gravity level of messages
//! - Trace: low-level details on algorithm execution (usually for debug purposes)
//! - Info: informative message
//! - Warning: warning message
//! - Alarm: non-critical error
//! - Fail: fatal error
enum Message_Gravity
{
  Message_Trace,
  Message_Info,
  Message_Warning,
  Message_Alarm,
  Message_Fail
};

