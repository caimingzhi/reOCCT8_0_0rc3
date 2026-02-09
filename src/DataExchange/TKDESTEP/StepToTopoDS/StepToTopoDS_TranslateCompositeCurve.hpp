#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Wire.hpp>
#include <StepToTopoDS_Root.hpp>
class StepGeom_CompositeCurve;
class Transfer_TransientProcess;
class StepGeom_Surface;
class Geom_Surface;

class StepToTopoDS_TranslateCompositeCurve : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateCompositeCurve();

  Standard_EXPORT StepToTopoDS_TranslateCompositeCurve(
    const occ::handle<StepGeom_CompositeCurve>&   CC,
    const occ::handle<Transfer_TransientProcess>& TP,
    const StepData_Factors&                       theLocalFactors = StepData_Factors());

  Standard_EXPORT StepToTopoDS_TranslateCompositeCurve(
    const occ::handle<StepGeom_CompositeCurve>&   CC,
    const occ::handle<Transfer_TransientProcess>& TP,
    const occ::handle<StepGeom_Surface>&          S,
    const occ::handle<Geom_Surface>&              Surf,
    const StepData_Factors&                       theLocalFactors = StepData_Factors());

  Standard_EXPORT bool Init(const occ::handle<StepGeom_CompositeCurve>&   CC,
                            const occ::handle<Transfer_TransientProcess>& TP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT bool Init(const occ::handle<StepGeom_CompositeCurve>&   CC,
                            const occ::handle<Transfer_TransientProcess>& TP,
                            const occ::handle<StepGeom_Surface>&          S,
                            const occ::handle<Geom_Surface>&              Surf,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Wire& Value() const;

  bool IsInfiniteSegment() const;

private:
  TopoDS_Wire myWire;
  bool        myInfiniteSegment;
};

#include <StepToTopoDS_TranslateCompositeCurve.hpp>

inline bool StepToTopoDS_TranslateCompositeCurve::IsInfiniteSegment() const
{
  return myInfiniteSegment;
}
