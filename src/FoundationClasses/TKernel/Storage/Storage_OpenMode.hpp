#pragma once

//! Specifies opening modes for a file:
//! -   Storage_VSNone : no mode is specified
//! -   Storage_VSRead : the file is open for  reading operations
//! -   Storage_VSWrite : the file is open for writing operations
//! -   Storage_VSReadWrite : the file is open
//! for both reading and writing operations.
enum Storage_OpenMode
{
  Storage_VSNone,
  Storage_VSRead,
  Storage_VSWrite,
  Storage_VSReadWrite
};
