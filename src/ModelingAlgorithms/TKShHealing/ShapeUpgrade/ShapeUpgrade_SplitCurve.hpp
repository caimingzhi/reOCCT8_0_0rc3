#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <ShapeExtend_Status.hpp>

#ifdef Status
  #undef Status
#endif

class ShapeUpgrade_SplitCurve : public Standard_Transient
{

public:
  Standard_EXPORT ShapeUpgrade_SplitCurve();

  Standard_EXPORT void Init(const double First, const double Last);

  Standard_EXPORT void SetSplitValues(
    const occ::handle<NCollection_HSequence<double>>& SplitValues);

  Standard_EXPORT virtual void Build(const bool Segment);

  Standard_EXPORT const occ::handle<NCollection_HSequence<double>>& SplitValues() const;

  Standard_EXPORT virtual void Compute();

  Standard_EXPORT void Perform(const bool Segment = true);

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve, Standard_Transient)

protected:
  occ::handle<NCollection_HSequence<double>> mySplitValues;
  int                                        myNbCurves;
  int                                        myStatus;
};
