#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <AppParCurves_MultiBSpCurve.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <NCollection_Sequence.hpp>
class AppParCurves_MultiCurve;

class Approx_MCurvesToBSpCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Approx_MCurvesToBSpCurve();

  Standard_EXPORT void Reset();

  Standard_EXPORT void Append(const AppParCurves_MultiCurve& MC);

  Standard_EXPORT void Perform();

  Standard_EXPORT void Perform(const NCollection_Sequence<AppParCurves_MultiCurve>& TheSeq);

  //! return the composite MultiCurves as a MultiBSpCurve.
  Standard_EXPORT const AppParCurves_MultiBSpCurve& Value() const;

  //! return the composite MultiCurves as a MultiBSpCurve.
  Standard_EXPORT const AppParCurves_MultiBSpCurve& ChangeValue();

private:
  AppParCurves_MultiBSpCurve                    mySpline;
  bool                                          myDone;
  NCollection_Sequence<AppParCurves_MultiCurve> myCurves;
};

