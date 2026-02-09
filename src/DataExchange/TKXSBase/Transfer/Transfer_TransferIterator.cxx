

#include <Interface_Check.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransferIterator.hpp>

static occ::handle<Standard_Transient> nultrans;

Transfer_TransferIterator::Transfer_TransferIterator()
{
  theitems  = new NCollection_HSequence<occ::handle<Transfer_Binder>>();
  theselect = new NCollection_HSequence<int>();
  themaxi   = 0;
  thecurr   = 1;
}

void Transfer_TransferIterator::AddItem(const occ::handle<Transfer_Binder>& atr)
{
  theitems->Append(atr);
  theselect->Append(1);
  themaxi = theselect->Length();
}

void Transfer_TransferIterator::SelectBinder(const occ::handle<Standard_Type>& atype,
                                             const bool                        keep)
{
  for (int i = theitems->Length(); i > 0; i--)
  {
    if (theitems->Value(i)->IsKind(atype) != keep)
    {
      theselect->SetValue(i, 0);
      if (themaxi == i)
        themaxi = i - 1;
    }
  }
}

void Transfer_TransferIterator::SelectResult(const occ::handle<Standard_Type>& atype,
                                             const bool                        keep)
{
  int casetype = 0;
  if (atype->SubType(STANDARD_TYPE(Standard_Transient)))
    casetype = 2;

  for (int i = theitems->Length(); i > 0; i--)
  {
    occ::handle<Transfer_Binder> atr   = theitems->Value(i);
    occ::handle<Standard_Type>   btype = ResultType();
    bool                         matchtype;
    if (!atr->HasResult())
      matchtype = false;
    else if (atr->IsMultiple())
      matchtype = false;
    else if (casetype == 0)
      matchtype = (atype == btype);
    else
      matchtype = (btype->SubType(atype));
    if (matchtype != keep)
    {
      theselect->SetValue(i, 0);
      if (themaxi == i)
        themaxi = i - 1;
    }
  }
}

void Transfer_TransferIterator::SelectUnique(const bool keep)
{
  for (int i = theitems->Length(); i > 0; i--)
  {
    occ::handle<Transfer_Binder> atr = theitems->Value(i);
    if (atr->IsMultiple() == keep)
    {
      theselect->SetValue(i, 0);
      if (themaxi == i)
        themaxi = i - 1;
    }
  }
}

void Transfer_TransferIterator::SelectItem(const int num, const bool keep)
{
  if (num < 1 || num > theselect->Length())
    return;
  if (keep)
    theselect->SetValue(num, 1);
  else
    theselect->SetValue(num, 0);
}

int Transfer_TransferIterator::Number() const
{
  int numb, i;
  numb = 0;
  for (i = 1; i <= themaxi; i++)
  {
    if (theselect->Value(i) != 0)
      numb++;
  }
  return numb;
}

void Transfer_TransferIterator::Start()
{
  thecurr = 0;
  Next();
}

bool Transfer_TransferIterator::More()
{
  if (thecurr > themaxi)
    return false;
  if (theselect->Value(thecurr) == 0)
    Next();
  if (thecurr > themaxi)
    return false;
  return (theselect->Value(thecurr) > 0);
}

void Transfer_TransferIterator::Next()
{
  thecurr++;
  if (thecurr > themaxi)
    return;
  if (theselect->Value(thecurr) == 0)
    Next();
}

const occ::handle<Transfer_Binder>& Transfer_TransferIterator::Value() const
{
  if (thecurr == 0 || thecurr > themaxi)
    throw Standard_NoSuchObject("TransferIterator : Value");
  if (theselect->Value(thecurr) == 0)
    throw Standard_NoSuchObject("TransferIterator : Value");
  return theitems->Value(thecurr);
}

bool Transfer_TransferIterator::HasResult() const
{
  occ::handle<Transfer_Binder> atr = Value();
  return atr->HasResult();
}

bool Transfer_TransferIterator::HasUniqueResult() const
{
  occ::handle<Transfer_Binder> atr = Value();
  if (atr->IsMultiple())
    return false;
  return atr->HasResult();
}

occ::handle<Standard_Type> Transfer_TransferIterator::ResultType() const
{
  occ::handle<Standard_Type>   btype;
  occ::handle<Transfer_Binder> atr = Value();
  if (!atr->IsMultiple())
    btype = atr->ResultType();

  return btype;
}

bool Transfer_TransferIterator::HasTransientResult() const
{
  occ::handle<Standard_Type> btype = ResultType();
  if (btype.IsNull())
    return false;
  return btype->SubType(STANDARD_TYPE(Standard_Transient));
}

const occ::handle<Standard_Transient>& Transfer_TransferIterator::TransientResult() const
{
  occ::handle<Transfer_SimpleBinderOfTransient> atr =
    occ::down_cast<Transfer_SimpleBinderOfTransient>(Value());
  if (!atr.IsNull())
    return atr->Result();
  return nultrans;
}

Transfer_StatusExec Transfer_TransferIterator::Status() const
{
  occ::handle<Transfer_Binder> atr = Value();
  return atr->StatusExec();
}

bool Transfer_TransferIterator::HasFails() const
{
  occ::handle<Transfer_Binder> atr = Value();
  return atr->Check()->HasFailed();
}

bool Transfer_TransferIterator::HasWarnings() const
{
  occ::handle<Transfer_Binder> atr = Value();
  return atr->Check()->HasWarnings();
}

const occ::handle<Interface_Check> Transfer_TransferIterator::Check() const
{
  occ::handle<Transfer_Binder> atr = Value();
  return atr->Check();
}
