#include <TFunction_Driver.hpp>
#include <TFunction_Logbook.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TFunction_Driver, Standard_Transient)

TFunction_Driver::TFunction_Driver() = default;

void TFunction_Driver::Init(const TDF_Label& L)
{
  myLabel = L;
}

void TFunction_Driver::Validate(occ::handle<TFunction_Logbook>& log) const
{
  NCollection_List<TDF_Label> res;
  Results(res);

  NCollection_List<TDF_Label>::Iterator itr(res);
  for (; itr.More(); itr.Next())
  {
    log->SetValid(itr.Value(), true);
  }
}

bool TFunction_Driver::MustExecute(const occ::handle<TFunction_Logbook>& log) const
{

  NCollection_List<TDF_Label> args;
  Arguments(args);

  NCollection_List<TDF_Label>::Iterator itr(args);
  for (; itr.More(); itr.Next())
  {
    if (log->IsModified(itr.Value()))
      return true;
  }
  return false;
}

void TFunction_Driver::Arguments(NCollection_List<TDF_Label>&) const {}

void TFunction_Driver::Results(NCollection_List<TDF_Label>&) const {}
