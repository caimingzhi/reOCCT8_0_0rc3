#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepGeom_QuasiUniformCurveAndRationalBSplineCurve;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write Module for QuasiUniformCurveAndRationalBSplineCurve
class RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                           data,
    const int                                                             num,
    occ::handle<Interface_Check>&                                         ach,
    const occ::handle<StepGeom_QuasiUniformCurveAndRationalBSplineCurve>& ent) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                  SW,
    const occ::handle<StepGeom_QuasiUniformCurveAndRationalBSplineCurve>& ent) const;

  Standard_HIDDEN void Share(
    const occ::handle<StepGeom_QuasiUniformCurveAndRationalBSplineCurve>& ent,
    Interface_EntityIterator&                                             iter) const;
};
