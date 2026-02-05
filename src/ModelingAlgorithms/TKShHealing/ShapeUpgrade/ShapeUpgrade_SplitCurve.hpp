#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <ShapeExtend_Status.hpp>

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

//! Splits a curve with a criterion.
class ShapeUpgrade_SplitCurve : public Standard_Transient
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_SplitCurve();

  //! Initializes with curve first and last parameters.
  Standard_EXPORT void Init(const double First, const double Last);

  //! Sets the parameters where splitting has to be done.
  Standard_EXPORT void SetSplitValues(
    const occ::handle<NCollection_HSequence<double>>& SplitValues);

  //! If Segment is True, the result is composed with
  //! segments of the curve bounded by the SplitValues. If
  //! Segment is False, the result is composed with trimmed
  //! Curves all based on the same complete curve.
  Standard_EXPORT virtual void Build(const bool Segment);

  //! returns all the splitting values including the
  //! First and Last parameters of the input curve
  //! Merges input split values and new ones into myGlobalKnots
  Standard_EXPORT const occ::handle<NCollection_HSequence<double>>& SplitValues() const;

  //! Calculates points for correction/splitting of the curve
  Standard_EXPORT virtual void Compute();

  //! Performs correction/splitting of the curve.
  //! First defines splitting values by method Compute(), then calls method Build().
  Standard_EXPORT void Perform(const bool Segment = true);

  //! Returns the status
  //! OK    - no splitting is needed
  //! DONE1 - splitting required and gives more than one segment
  //! DONE2 - splitting is required, but gives only one segment (initial)
  //! DONE3 - geometric form of the curve or parametrisation is modified
  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve, Standard_Transient)

protected:
  occ::handle<NCollection_HSequence<double>> mySplitValues;
  int                                        myNbCurves;
  int                                        myStatus;
};
