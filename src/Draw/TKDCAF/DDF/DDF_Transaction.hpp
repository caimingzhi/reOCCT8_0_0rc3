#pragma once


#include <Standard.hpp>

#include <TDF_Transaction.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DefineAlloc.hpp>
class TDF_Data;
class TDF_Delta;

//! This class encapsulates TDF_Transaction.
class DDF_Transaction : public Standard_Transient
{

public:
  //! Creates an empty transaction context, unable to be
  //! opened.
  Standard_EXPORT DDF_Transaction();

  //! Creates a transaction context on <aDF>, ready to
  //! be opened.
  Standard_EXPORT DDF_Transaction(const occ::handle<TDF_Data>& aDF);

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

  ~DDF_Transaction() override { Abort(); }

  //! Returns the Data from TDF.
  Standard_EXPORT occ::handle<TDF_Data> Data() const;

  //! Returns the number of the transaction opened by <me>.
  Standard_EXPORT int Transaction() const;

  //! Returns true if the transaction is open.
  Standard_EXPORT bool IsOpen() const;

  DEFINE_STANDARD_RTTIEXT(DDF_Transaction, Standard_Transient)

private:
  TDF_Transaction myTransaction;
};

