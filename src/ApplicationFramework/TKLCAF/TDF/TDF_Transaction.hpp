#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
class TDF_Data;
class TDF_Delta;

class TDF_Transaction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDF_Transaction(const TCollection_AsciiString& aName = "");

  Standard_EXPORT TDF_Transaction(const occ::handle<TDF_Data>&   aDF,
                                  const TCollection_AsciiString& aName = "");

  Standard_EXPORT void Initialize(const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT int Open();

  Standard_EXPORT occ::handle<TDF_Delta> Commit(const bool withDelta = false);

  Standard_EXPORT void Abort();

  ~TDF_Transaction() { Abort(); }

  occ::handle<TDF_Data> Data() const;

  int Transaction() const;

  const TCollection_AsciiString& Name() const;

  bool IsOpen() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  TDF_Transaction(const TDF_Transaction& aTrans)              = delete;
  TDF_Transaction& operator=(const TDF_Transaction& theOther) = delete;

private:
  occ::handle<TDF_Data>   myDF;
  TCollection_AsciiString myName;
  int                     myUntilTransaction;
};

inline occ::handle<TDF_Data> TDF_Transaction::Data() const
{
  return myDF;
}

inline int TDF_Transaction::Transaction() const
{
  return myUntilTransaction;
}

inline const TCollection_AsciiString& TDF_Transaction::Name() const
{
  return myName;
}

inline bool TDF_Transaction::IsOpen() const
{
  return myUntilTransaction > 0;
}
