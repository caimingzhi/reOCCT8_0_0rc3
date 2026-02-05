#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
class TDF_Data;
class TDF_Delta;

//! This class offers services to open, commit or
//! abort a transaction in a more secure way than
//! using Data from TDF. If you forget to close a
//! transaction, it will be automatically aborted at
//! the destruction of this object, at the closure of
//! its scope.
//!
//! In case of catching errors, the effect will be the
//! same: aborting transactions until the good current
//! one.
class TDF_Transaction
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty transaction context, unable to be
  //! opened.
  Standard_EXPORT TDF_Transaction(const TCollection_AsciiString& aName = "");

  //! Creates a transaction context on <aDF>, ready to
  //! be opened.
  Standard_EXPORT TDF_Transaction(const occ::handle<TDF_Data>&   aDF,
                                  const TCollection_AsciiString& aName = "");

  //! Aborts all the transactions on <myDF> and sets
  //! <aDF> to build a transaction context on <aDF>,
  //! ready to be opened.
  Standard_EXPORT void Initialize(const occ::handle<TDF_Data>& aDF);

  //! If not yet done, opens a new transaction on
  //! <myDF>. Returns the index of the just opened
  //! transaction.
  //!
  //! It raises DomainError if the transaction is
  //! already open, and NullObject if there is no
  //! current Data framework.
  Standard_EXPORT int Open();

  //! Commits the transactions until AND including the
  //! current opened one.
  Standard_EXPORT occ::handle<TDF_Delta> Commit(const bool withDelta = false);

  //! Aborts the transactions until AND including the
  //! current opened one.
  Standard_EXPORT void Abort();

  ~TDF_Transaction() { Abort(); }

  //! Returns the Data from TDF.
  occ::handle<TDF_Data> Data() const;

  //! Returns the number of the transaction opened by <me>.
  int Transaction() const;

  //! Returns the transaction name.
  const TCollection_AsciiString& Name() const;

  //! Returns true if the transaction is open.
  bool IsOpen() const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  //! Private to avoid copy.
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
