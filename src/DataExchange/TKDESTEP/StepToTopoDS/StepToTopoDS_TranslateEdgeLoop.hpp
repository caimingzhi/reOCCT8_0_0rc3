#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum StepToTopoDS_TranslateEdgeLoopError
{
  StepToTopoDS_TranslateEdgeLoopDone,
  StepToTopoDS_TranslateEdgeLoopOther
};

#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
class StepShape_FaceBound;
class TopoDS_Face;
class Geom_Surface;
class StepGeom_Surface;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;

class StepToTopoDS_TranslateEdgeLoop : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateEdgeLoop();

  Standard_EXPORT StepToTopoDS_TranslateEdgeLoop(
    const occ::handle<StepShape_FaceBound>& FB,
    const TopoDS_Face&                      F,
    const occ::handle<Geom_Surface>&        S,
    const occ::handle<StepGeom_Surface>&    SS,
    const bool                              ss,
    StepToTopoDS_Tool&                      T,
    StepToTopoDS_NMTool&                    NMTool,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_FaceBound>& FB,
                            const TopoDS_Face&                      F,
                            const occ::handle<Geom_Surface>&        S,
                            const occ::handle<StepGeom_Surface>&    SS,
                            const bool                              ss,
                            StepToTopoDS_Tool&                      T,
                            StepToTopoDS_NMTool&                    NMTool,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateEdgeLoopError Error() const;

private:
  StepToTopoDS_TranslateEdgeLoopError myError;
  TopoDS_Shape                        myResult;
};
