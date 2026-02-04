#pragma once


#include <Media_Frame.hpp>

//! Interface defining frame queuing.
class Media_IFrameQueue
{
public:
  //! Lock the frame, e.g. take ownership on a single (not currently displayed) frame from the queue
  //! to perform decoding into.
  virtual occ::handle<Media_Frame> LockFrame() = 0;

  //! Release previously locked frame, e.g. it can be displayed on the screen.
  virtual void ReleaseFrame(const occ::handle<Media_Frame>& theFrame) = 0;
};

