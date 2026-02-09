

#include <Standard_OutOfRange.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_MultipleBinder.hpp>
#include <Transfer_TransferFailure.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_MultipleBinder, Transfer_Binder)

Transfer_MultipleBinder::Transfer_MultipleBinder() = default;

bool Transfer_MultipleBinder::IsMultiple() const
{
  if (themulres.IsNull())
    return false;
  return (themulres->Length() != 1);
}

occ::handle<Standard_Type> Transfer_MultipleBinder::ResultType() const
{
  return STANDARD_TYPE(Standard_Transient);
}

const char* Transfer_MultipleBinder::ResultTypeName() const
{
  return "(list)";
}

void Transfer_MultipleBinder::AddResult(const occ::handle<Standard_Transient>& res)
{
  if (themulres.IsNull())
    themulres = new NCollection_HSequence<occ::handle<Standard_Transient>>();
  themulres->Append(res);
}

int Transfer_MultipleBinder::NbResults() const
{
  return (themulres.IsNull() ? 0 : themulres->Length());
}

occ::handle<Standard_Transient> Transfer_MultipleBinder::ResultValue(const int num) const
{
  return themulres->Value(num);
}

occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Transfer_MultipleBinder::
  MultipleResult() const
{
  if (!themulres.IsNull())
    return themulres;
  return new NCollection_HSequence<occ::handle<Standard_Transient>>();
}

void Transfer_MultipleBinder::SetMultipleResult(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& mulres)
{
  themulres = mulres;
}
