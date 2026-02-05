#pragma once

//! Thisd is a set of possible system types.
//! 'Default' means SysType of machine operating this process.
//! This can be used with the Path class.
//! All UNIX-like are grouped under "UnixBSD" or "UnixSystemV".
//! Such systems are Solaris, NexTOS ...
//! A category of systems accept MSDOS-like path such as
//! WindowsNT and OS2.
enum OSD_SysType
{
  OSD_Unknown,
  OSD_Default,
  OSD_UnixBSD,
  OSD_UnixSystemV,
  OSD_VMS,
  OSD_OS2,
  OSD_OSF,
  OSD_MacOs,
  OSD_Taligent,
  OSD_WindowsNT,
  OSD_LinuxREDHAT,
  OSD_Aix
};
