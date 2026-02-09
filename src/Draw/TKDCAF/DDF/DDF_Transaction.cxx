#include <DDF_Transaction.hpp>
#include <Standard_Type.hpp>
#include <TDF_Data.hpp>
#include <TDF_Delta.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DDF_Transaction, Standard_Transient)

DDF_Transaction::DDF_Transaction()
    : myTransaction(TCollection_AsciiString())
{
}

DDF_Transaction::DDF_Transaction(const occ::handle<TDF_Data>& aDF)
    : myTransaction(TCollection_AsciiString())
{
  myTransaction.Initialize(aDF);
}

int DDF_Transaction::Open()
{
  return myTransaction.Open();
}

occ::handle<TDF_Delta> DDF_Transaction::Commit(const bool withDelta)
{
  return myTransaction.Commit(withDelta);
}

void DDF_Transaction::Abort()
{
  myTransaction.Abort();
}

occ::handle<TDF_Data> DDF_Transaction::Data() const
{
  return myTransaction.Data();
}

int DDF_Transaction::Transaction() const
{
  return myTransaction.Transaction();
}

bool DDF_Transaction::IsOpen() const
{
  return myTransaction.IsOpen();
}
