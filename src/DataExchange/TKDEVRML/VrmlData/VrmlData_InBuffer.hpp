#pragma once

#include <Standard_IStream.hpp>

/**
 * Structure passed to the methods dealing with input stream.
 */
struct VrmlData_InBuffer
{
  Standard_IStream& Input;
  char              Line[8096];
  char*             LinePtr;
  bool              IsProcessed;
  int               LineCount;
  VrmlData_InBuffer(Standard_IStream& theStream)
      : Input(theStream),
        LinePtr(&Line[0]),
        IsProcessed(false),
        LineCount(0) {};

private:
  void operator=(const VrmlData_InBuffer&) = delete;
};
