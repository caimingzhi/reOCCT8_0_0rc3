#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Line;
class gp_Lin;
class gp_Lin2d;
class Geom_Line;
class Geom2d_Line;

class GeomToStep_MakeLine : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeLine(const gp_Lin&           L,
                                      const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeLine(const gp_Lin2d&         L,
                                      const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeLine(const occ::handle<Geom_Line>& C,
                                      const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeLine(const occ::handle<Geom2d_Line>& C,
                                      const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Line>& Value() const;

private:
  occ::handle<StepGeom_Line> theLine;
};
