#pragma once

#include <Message_Report.hpp>
#include <Standard_OStream.hpp>

#include <NCollection_BaseAllocator.hpp>

class Message_ProgressScope;

class BOPAlgo_Options
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_Options();

  Standard_EXPORT BOPAlgo_Options(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT virtual ~BOPAlgo_Options();

  const occ::handle<NCollection_BaseAllocator>& Allocator() const { return myAllocator; }

  virtual void Clear() { myReport->Clear(); }

public:
  void AddError(const occ::handle<Message_Alert>& theAlert)
  {
    myReport->AddAlert(Message_Fail, theAlert);
  }

  void AddWarning(const occ::handle<Message_Alert>& theAlert)
  {
    myReport->AddAlert(Message_Warning, theAlert);
  }

  bool HasErrors() const { return !myReport->GetAlerts(Message_Fail).IsEmpty(); }

  bool HasError(const occ::handle<Standard_Type>& theType) const
  {
    return myReport->HasAlert(theType, Message_Fail);
  }

  bool HasWarnings() const { return !myReport->GetAlerts(Message_Warning).IsEmpty(); }

  bool HasWarning(const occ::handle<Standard_Type>& theType) const
  {
    return myReport->HasAlert(theType, Message_Warning);
  }

  const occ::handle<Message_Report>& GetReport() const { return myReport; }

  Standard_EXPORT void DumpErrors(Standard_OStream& theOS) const;

  Standard_EXPORT void DumpWarnings(Standard_OStream& theOS) const;

  void ClearWarnings() { myReport->Clear(Message_Warning); }

public:
  Standard_EXPORT static bool GetParallelMode();

  Standard_EXPORT static void SetParallelMode(const bool theNewMode);

  void SetRunParallel(const bool theFlag) { myRunParallel = theFlag; }

  bool RunParallel() const { return myRunParallel; }

public:
  Standard_EXPORT void SetFuzzyValue(const double theFuzz);

  double FuzzyValue() const { return myFuzzyValue; }

public:
  void SetUseOBB(const bool theUseOBB) { myUseOBB = theUseOBB; }

  bool UseOBB() const { return myUseOBB; }

protected:
  Standard_EXPORT bool UserBreak(const Message_ProgressScope& thePS);

protected:
  occ::handle<NCollection_BaseAllocator> myAllocator;
  occ::handle<Message_Report>            myReport;
  bool                                   myRunParallel;
  double                                 myFuzzyValue;
  bool                                   myUseOBB;
};
