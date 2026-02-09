#include <TObj_ObjectIterator.hpp>
#include <TObj_Object.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TObj_ObjectIterator, Standard_Transient)

bool TObj_ObjectIterator::More() const
{
  return false;
}

void TObj_ObjectIterator::Next() {}

occ::handle<TObj_Object> TObj_ObjectIterator::Value() const
{
  return nullptr;
}
