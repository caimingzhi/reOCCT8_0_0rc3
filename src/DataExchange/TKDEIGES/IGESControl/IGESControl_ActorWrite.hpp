#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Transfer_ActorOfFinderProcess.hpp>

class Transfer_Finder;
class Transfer_Binder;
class Transfer_FinderProcess;

//! Actor to write Shape to IGES
class IGESControl_ActorWrite : public Transfer_ActorOfFinderProcess
{
public:
  Standard_EXPORT IGESControl_ActorWrite();

  //! Recognizes a ShapeMapper
  Standard_EXPORT bool Recognize(const occ::handle<Transfer_Finder>& start) override;

  //! Transfers Shape to IGES Entities
  //!
  //! ModeTrans may be : 0 -> groups of Faces
  //! or 1 -> BRep
  Standard_EXPORT occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Transfer_Finder>&        start,
    const occ::handle<Transfer_FinderProcess>& FP,
    const Message_ProgressRange&               theProgress = Message_ProgressRange()) override;

  DEFINE_STANDARD_RTTIEXT(IGESControl_ActorWrite, Transfer_ActorOfFinderProcess)
};
