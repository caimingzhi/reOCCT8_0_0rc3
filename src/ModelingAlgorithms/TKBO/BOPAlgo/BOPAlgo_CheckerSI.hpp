#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_PaveFiller.hpp>

class BOPAlgo_CheckerSI : public BOPAlgo_PaveFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_CheckerSI();
  Standard_EXPORT ~BOPAlgo_CheckerSI() override;

  Standard_EXPORT void Perform(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void SetLevelOfCheck(const int theLevel);

protected:
  Standard_EXPORT void Init(const Message_ProgressRange& theRange) override;

  Standard_EXPORT void PostTreat();

  Standard_EXPORT void CheckFaceSelfIntersection(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformVZ(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformEZ(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformFZ(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformZZ(const Message_ProgressRange& theRange);

  Standard_EXPORT virtual void PerformSZ(const TopAbs_ShapeEnum       aTS,
                                         const Message_ProgressRange& theRange);

  int myLevelOfCheck;
};
