#include <BOPAlgo_Options.hpp>
#include <Message_MsgFile.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TCollection_AsciiString.hpp>
#include <Precision.hpp>
#include <Standard_NotImplemented.hpp>
#include <BOPAlgo_Alerts.hpp>

namespace
{
  bool myGlobalRunParallel = false;

// Initialize textual messages for errors and warnings defined in BOPAlgo
#include "BOPAlgo_BOPAlgo_msg.hpp"
  bool BOPAlgo_InitMessages = false;

  void BOPAlgo_LoadMessages()
  {
    if (BOPAlgo_InitMessages)
      return;
    BOPAlgo_InitMessages = true;

    if (!Message_MsgFile::HasMsg("BOPAlgo_LOAD_CHECKER"))
    {
      Message_MsgFile::LoadFromString(BOPAlgo_BOPAlgo_msg);
    }
  }
} // namespace

//=================================================================================================

BOPAlgo_Options::BOPAlgo_Options()
    : myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
      myReport(new Message_Report),
      myRunParallel(myGlobalRunParallel),
      myFuzzyValue(Precision::Confusion()),
      myUseOBB(false)
{
  BOPAlgo_LoadMessages();
}

//=================================================================================================

BOPAlgo_Options::BOPAlgo_Options(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myAllocator(theAllocator),
      myReport(new Message_Report),
      myRunParallel(myGlobalRunParallel),
      myFuzzyValue(Precision::Confusion()),
      myUseOBB(false)
{
  BOPAlgo_LoadMessages();
}

//=================================================================================================

BOPAlgo_Options::~BOPAlgo_Options() = default;

//=================================================================================================

void BOPAlgo_Options::DumpErrors(Standard_OStream& theOS) const
{
  myReport->Dump(theOS, Message_Fail);
}

//=================================================================================================

void BOPAlgo_Options::DumpWarnings(Standard_OStream& theOS) const
{
  myReport->Dump(theOS, Message_Warning);
}

//=================================================================================================

void BOPAlgo_Options::SetParallelMode(bool theNewMode)
{
  myGlobalRunParallel = theNewMode;
}

//=================================================================================================

bool BOPAlgo_Options::GetParallelMode()
{
  return myGlobalRunParallel;
}

//=================================================================================================

void BOPAlgo_Options::SetFuzzyValue(const double theFuzz)
{
  myFuzzyValue = std::max(theFuzz, Precision::Confusion());
}

bool BOPAlgo_Options::UserBreak(const Message_ProgressScope& thePS)
{
  if (thePS.UserBreak())
  {
    AddError(new BOPAlgo_AlertUserBreak);
    return true;
  }
  return false;
}
