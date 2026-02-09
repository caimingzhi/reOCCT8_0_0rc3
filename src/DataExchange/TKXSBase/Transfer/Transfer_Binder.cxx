

#include <Geom2d_CartesianPoint.hpp>
#include <Interface_Check.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_TransferFailure.hpp>
#include <Transfer_VoidBinder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_Binder, Standard_Transient)

Transfer_Binder::Transfer_Binder()
{
  thestatus = Transfer_StatusVoid;
  theexecst = Transfer_StatusInitial;
  thecheck  = new Interface_Check;
}

void Transfer_Binder::Merge(const occ::handle<Transfer_Binder>& other)
{
  if (other.IsNull())
    return;
  if ((int)theexecst < (int)other->StatusExec())
    theexecst = other->StatusExec();
  thecheck->GetMessages(other->Check());
}

bool Transfer_Binder::IsMultiple() const
{
  if (thenextr.IsNull())
    return false;
  if (!HasResult())
    return thenextr->IsMultiple();

  occ::handle<Transfer_Binder> next = thenextr;
  while (!next.IsNull())
  {
    if (next->HasResult())
      return true;
    next = next->NextResult();
  }
  return false;
}

void Transfer_Binder::AddResult(const occ::handle<Transfer_Binder>& next)
{
  if (next == this || next.IsNull())
    return;
  next->CutResult(this);
  if (thenextr.IsNull())
    thenextr = next;
  else
  {

    occ::handle<Transfer_Binder> theBinder = theendr.IsNull() ? thenextr : theendr;
    while (theBinder != next)
    {
      if (theBinder->NextResult().IsNull())
      {
        theBinder->AddResult(next);
        theendr = next;
        return;
      }
      else
        theBinder = theBinder->NextResult();
    }
  }
}

void Transfer_Binder::CutResult(const occ::handle<Transfer_Binder>& next)
{
  if (thenextr.IsNull())
    return;
  if (thenextr == next)
  {
    thenextr.Nullify();
    theendr.Nullify();
  }

  else
  {
    occ::handle<Transfer_Binder> currBinder = thenextr, currNext;
    while (!((currNext = currBinder->NextResult()) == next))
    {
      if (currNext.IsNull())
        return;
      currBinder = currNext;
    }
    currBinder->CutResult(next);
  }
}

occ::handle<Transfer_Binder> Transfer_Binder::NextResult() const
{
  return thenextr;
}

void Transfer_Binder::SetResultPresent()
{
  if (thestatus == Transfer_StatusUsed)
    throw Transfer_TransferFailure("Binder : SetResult, Result is Already Set and Used");
  theexecst = Transfer_StatusDone;
  thestatus = Transfer_StatusDefined;
}

bool Transfer_Binder::HasResult() const
{
  return (thestatus != Transfer_StatusVoid);
}

void Transfer_Binder::SetAlreadyUsed()
{
  if (thestatus != Transfer_StatusVoid)
    thestatus = Transfer_StatusUsed;
}

Transfer_StatusResult Transfer_Binder::Status() const
{
  return thestatus;
}

Transfer_StatusExec Transfer_Binder::StatusExec() const
{
  return theexecst;
}

void Transfer_Binder::SetStatusExec(const Transfer_StatusExec stat)
{
  theexecst = stat;
}

void Transfer_Binder::AddFail(const char* mess, const char* orig)
{
  theexecst = Transfer_StatusError;
  thecheck->AddFail(mess, orig);
}

void Transfer_Binder::AddWarning(const char* mess, const char* orig)
{

  thecheck->AddWarning(mess, orig);
}

const occ::handle<Interface_Check> Transfer_Binder::Check() const
{
  return thecheck;
}

occ::handle<Interface_Check> Transfer_Binder::CCheck()
{
  return thecheck;
}

Transfer_Binder::~Transfer_Binder()
{

  if (!thenextr.IsNull())
  {
    occ::handle<Transfer_Binder> aCurr = thenextr;
    theendr.Nullify();
    thenextr.Nullify();

    while (!aCurr->thenextr.IsNull() && aCurr->thenextr->GetRefCount() == 1)
    {
      occ::handle<Transfer_Binder> aPrev = aCurr;
      aCurr                              = aCurr->thenextr;
      aPrev->thenextr.Nullify();
    }
  }
}
