#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_TranslateFaceError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
class Poly_Triangulation;
class StepShape_FaceSurface;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;
class StepVisual_ComplexTriangulatedFace;
class StepVisual_TessellatedFace;
class StepVisual_TessellatedItem;
class StepVisual_TessellatedSurfaceSet;
class StepVisual_TriangulatedFace;

class StepToTopoDS_TranslateFace : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateFace();

  Standard_EXPORT StepToTopoDS_TranslateFace(
    const occ::handle<StepShape_FaceSurface>& FS,
    StepToTopoDS_Tool&                        T,
    StepToTopoDS_NMTool&                      NMTool,
    const StepData_Factors&                   theLocalFactors = StepData_Factors());

  Standard_EXPORT StepToTopoDS_TranslateFace(
    const occ::handle<StepVisual_TessellatedFace>& theTF,
    StepToTopoDS_Tool&                             theTool,
    StepToTopoDS_NMTool&                           theNMTool,
    const bool                                     theReadTessellatedWhenNoBRepOnly,
    bool&                                          theHasGeom,
    const StepData_Factors&                        theLocalFactors = StepData_Factors());

  Standard_EXPORT StepToTopoDS_TranslateFace(
    const occ::handle<StepVisual_TessellatedSurfaceSet>& theTSS,
    StepToTopoDS_Tool&                                   theTool,
    StepToTopoDS_NMTool&                                 theNMTool,
    const StepData_Factors&                              theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_FaceSurface>& theFaceSurface,
                            StepToTopoDS_Tool&                        theTopoDSTool,
                            StepToTopoDS_NMTool&                      theTopoDSToolNM,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedFace>& theTF,
                            StepToTopoDS_Tool&                             theTool,
                            StepToTopoDS_NMTool&                           theNMTool,
                            const bool              theReadTessellatedWhenNoBRepOnly,
                            bool&                   theHasGeom,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedSurfaceSet>& theTSS,
                            StepToTopoDS_Tool&                                   theTool,
                            StepToTopoDS_NMTool&                                 theNMTool,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateFaceError Error() const;

private:
  occ::handle<Poly_Triangulation> createMesh(
    const occ::handle<StepVisual_TessellatedItem>& theTI,
    const StepData_Factors&                        theLocalFactors = StepData_Factors()) const;

  StepToTopoDS_TranslateFaceError myError;
  TopoDS_Shape                    myResult;
};

