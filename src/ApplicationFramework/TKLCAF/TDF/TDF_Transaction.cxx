#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_NullObject.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Data.hpp>
#include <TDF_Delta.hpp>
#include <TDF_Transaction.hpp>

#undef DEB_TRANSACTION
#ifdef OCCT_DEBUG
  #define DEB_TRANSACTION
#endif
#undef DEB_TRANSACTION_DUMP

#include <TDF_Tool.hpp>

//=================================================================================================

TDF_Transaction::TDF_Transaction(const TCollection_AsciiString& aName)
    : myName(aName),
      myUntilTransaction(0)
{
}

//=================================================================================================

TDF_Transaction::TDF_Transaction(const occ::handle<TDF_Data>&   aDF,
                                 const TCollection_AsciiString& aName)
    : myDF(aDF),
      myName(aName),
      myUntilTransaction(0)
{
}

//=======================================================================
// function : Initialize
// purpose  : Initializes a transaction ready to be opened.
//=======================================================================

void TDF_Transaction::Initialize(const occ::handle<TDF_Data>& aDF)
{
  if (IsOpen())
    myDF->AbortUntilTransaction(myUntilTransaction);
  myDF               = aDF;
  myUntilTransaction = 0;
}

//=================================================================================================

int TDF_Transaction::Open()
{
#ifdef OCCT_DEBUG_TRANSACTION
  std::cout << "Transaction " << myName << " opens #" << myDF->Transaction() + 1 << std::endl;
#endif
  if (IsOpen())
    throw Standard_DomainError("This transaction is already open.");
  if (myDF.IsNull())
    throw Standard_NullObject("Null TDF_Data.");
  return myUntilTransaction = myDF->OpenTransaction();
}

//=================================================================================================

occ::handle<TDF_Delta> TDF_Transaction::Commit(const bool withDelta)
{
#ifdef OCCT_DEBUG_TRANSACTION
  std::cout << "Transaction " << myName << " commits ";
#endif
  occ::handle<TDF_Delta> delta;
  if (IsOpen())
  {
#ifdef OCCT_DEBUG_TRANSACTION
    std::cout << "from #" << myDF->Transaction() << " until #" << myUntilTransaction
              << " while current is #" << myDF->Transaction() << std::endl;
#endif
#ifdef OCCT_DEBUG_TRANSACTION_DUMP
    std::cout << "DF before commit" << std::endl;
    TDF_Tool::DeepDump(std::cout, myDF);
#endif
    int until          = myUntilTransaction;
    myUntilTransaction = 0;
    delta              = myDF->CommitUntilTransaction(until, withDelta);
#ifdef OCCT_DEBUG_TRANSACTION_DUMP
    std::cout << "DF after commit" << std::endl;
    TDF_Tool::DeepDump(std::cout, myDF);
#endif
  }
#ifdef OCCT_DEBUG_TRANSACTION
  else
    std::cout << "but this transaction is not open!" << std::endl;
#endif
  return delta;
}

//=================================================================================================

void TDF_Transaction::Abort()
{
  if (IsOpen())
  {
#ifdef OCCT_DEBUG_TRANSACTION
    std::cout << "Transaction " << myName << " aborts from #" << myDF->Transaction() << " until #"
              << myUntilTransaction << " while current is #" << myDF->Transaction() << std::endl;
#endif
#ifdef OCCT_DEBUG_TRANSACTION_DUMP
    std::cout << "DF before abort" << std::endl;
    TDF_Tool::DeepDump(std::cout, myDF);
#endif
    myDF->AbortUntilTransaction(myUntilTransaction);
    myUntilTransaction = 0;
#ifdef OCCT_DEBUG_TRANSACTION_DUMP
    std::cout << "DF after abort" << std::endl;
    TDF_Tool::DeepDump(std::cout, myDF);
#endif
  }
}

//=================================================================================================

void TDF_Transaction::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, TDF_Transaction)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myDF.get())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUntilTransaction)
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myName)
}
