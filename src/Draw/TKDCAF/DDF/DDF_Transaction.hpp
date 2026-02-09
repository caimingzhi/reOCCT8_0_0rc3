#pragma once

#include <Standard.hpp>

#include <TDF_Transaction.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DefineAlloc.hpp>
class TDF_Data;
class TDF_Delta;

class DDF_Transaction : public Standard_Transient
{

public:
  Standard_EXPORT DDF_Transaction();

  Standard_EXPORT DDF_Transaction(const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT int Open();

  Standard_EXPORT occ::handle<TDF_Delta> Commit(const bool withDelta = false);

  Standard_EXPORT void Abort();

  ~DDF_Transaction() override { Abort(); }

  Standard_EXPORT occ::handle<TDF_Data> Data() const;

  Standard_EXPORT int Transaction() const;

  Standard_EXPORT bool IsOpen() const;

  DEFINE_STANDARD_RTTIEXT(DDF_Transaction, Standard_Transient)

private:
  TDF_Transaction myTransaction;
};
