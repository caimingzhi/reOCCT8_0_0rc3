#pragma once

#include <Media_Frame.hpp>

class Media_IFrameQueue
{
public:
  virtual occ::handle<Media_Frame> LockFrame() = 0;

  virtual void ReleaseFrame(const occ::handle<Media_Frame>& theFrame) = 0;
};
