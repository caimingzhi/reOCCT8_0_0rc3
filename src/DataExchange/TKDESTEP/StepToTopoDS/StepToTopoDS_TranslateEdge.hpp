#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_TranslateEdgeError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
class StepShape_Edge;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;
class StepGeom_Curve;
class StepShape_EdgeCurve;
class StepShape_Vertex;
class TopoDS_Edge;
class TopoDS_Vertex;
class Geom2d_Curve;
class StepGeom_Pcurve;
class Geom_Surface;

class StepToTopoDS_TranslateEdge : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateEdge();

  Standard_EXPORT StepToTopoDS_TranslateEdge(
    const occ::handle<StepShape_Edge>& E,
    StepToTopoDS_Tool&                 T,
    StepToTopoDS_NMTool&               NMTool,
    const StepData_Factors&            theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_Edge>& E,
                            StepToTopoDS_Tool&                 T,
                            StepToTopoDS_NMTool&               NMTool,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  //! Warning! C3D is assumed to be a Curve 3D ...
  //! other cases to checked before calling this
  Standard_EXPORT void MakeFromCurve3D(
    const occ::handle<StepGeom_Curve>&      C3D,
    const occ::handle<StepShape_EdgeCurve>& EC,
    const occ::handle<StepShape_Vertex>&    Vend,
    const double                            preci,
    TopoDS_Edge&                            E,
    TopoDS_Vertex&                          V1,
    TopoDS_Vertex&                          V2,
    StepToTopoDS_Tool&                      T,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT occ::handle<Geom2d_Curve> MakePCurve(
    const occ::handle<StepGeom_Pcurve>& PCU,
    const occ::handle<Geom_Surface>&    ConvSurf,
    const StepData_Factors&             theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateEdgeError Error() const;

private:
  StepToTopoDS_TranslateEdgeError myError;
  TopoDS_Shape                    myResult;
};

