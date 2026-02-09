

#include <Standard_OutOfRange.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_TransientListBinder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_TransientListBinder, Transfer_Binder)

Transfer_TransientListBinder::Transfer_TransientListBinder()
{
  theres = new NCollection_HSequence<occ::handle<Standard_Transient>>();
}

Transfer_TransientListBinder::Transfer_TransientListBinder(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list)
{
  theres = list;
}

bool Transfer_TransientListBinder::IsMultiple() const
{
  return (NbTransients() > 1);
}

occ::handle<Standard_Type> Transfer_TransientListBinder::ResultType() const
{
  return STANDARD_TYPE(Transfer_TransientListBinder);
}

const char* Transfer_TransientListBinder::ResultTypeName() const
{
  return "list(Standard_Transient)";
}

void Transfer_TransientListBinder::AddResult(const occ::handle<Standard_Transient>& Transient)
{
  theres->Append(Transient);
}

occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Transfer_TransientListBinder::
  Result() const
{
  return theres;
}

void Transfer_TransientListBinder::SetResult(const int                              num,
                                             const occ::handle<Standard_Transient>& Transient)
{
  theres->SetValue(num, Transient);
}

int Transfer_TransientListBinder::NbTransients() const
{
  return theres->Length();
}

const occ::handle<Standard_Transient>& Transfer_TransientListBinder::Transient(const int num) const
{
  return theres->Value(num);
}
