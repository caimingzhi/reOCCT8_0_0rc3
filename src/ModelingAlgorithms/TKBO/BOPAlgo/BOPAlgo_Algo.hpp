#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Message_ProgressRange.hpp>
#include <NCollection_Array1.hpp>

#include <BOPAlgo_Options.hpp>

class BOPAlgo_PISteps;

class BOPAlgo_Algo : public BOPAlgo_Options
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) = 0;

protected:
  Standard_EXPORT BOPAlgo_Algo();
  Standard_EXPORT ~BOPAlgo_Algo() override;

  Standard_EXPORT BOPAlgo_Algo(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT virtual void CheckData();

  Standard_EXPORT virtual void CheckResult();

protected:
  Standard_EXPORT void analyzeProgress(const double theWhole, BOPAlgo_PISteps& theSteps) const;

  Standard_EXPORT virtual void fillPIConstants(const double     theWhole,
                                               BOPAlgo_PISteps& theSteps) const;

  Standard_EXPORT virtual void fillPISteps(BOPAlgo_PISteps& theSteps) const;
};

class BOPAlgo_ParallelAlgo : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual void Perform() = 0;

public:
  void SetProgressRange(const Message_ProgressRange& theRange) { myProgressRange = theRange; }

private:
  void Perform(const Message_ProgressRange& = Message_ProgressRange()) override {};

protected:
  Message_ProgressRange myProgressRange;
};

class BOPAlgo_PISteps
{
public:
  BOPAlgo_PISteps(const int theNbOp)
      : mySteps(0, theNbOp - 1)
  {
    mySteps.Init(0);
  }

  const NCollection_Array1<double>& Steps() const { return mySteps; }

  NCollection_Array1<double>& ChangeSteps() { return mySteps; }

  void SetStep(const int theOperation, const double theStep)
  {
    if (theOperation >= mySteps.Lower() && theOperation <= mySteps.Upper())
    {
      mySteps(theOperation) = theStep;
    }
  }

  double GetStep(const int theOperation)
  {
    if (theOperation < mySteps.Lower() || theOperation > mySteps.Upper())
    {
      return 0.;
    }
    return mySteps(theOperation);
  }

protected:
  NCollection_Array1<double> mySteps;
};
