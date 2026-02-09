#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRAlgo_Projector.hpp>
#include <HLRBRep_Algo.hpp>
#include <HLRBRep_TypeOfResultingEdge.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Real.hpp>

class HLRAppli_ReflectLines
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRAppli_ReflectLines(const TopoDS_Shape& aShape);

  Standard_EXPORT void SetAxes(const double Nx,
                               const double Ny,
                               const double Nz,
                               const double XAt,
                               const double YAt,
                               const double ZAt,
                               const double XUp,
                               const double YUp,
                               const double ZUp);

  Standard_EXPORT void Perform();

  Standard_EXPORT TopoDS_Shape GetResult() const;

  Standard_EXPORT TopoDS_Shape GetCompoundOf3dEdges(const HLRBRep_TypeOfResultingEdge type,
                                                    const bool                        visible,
                                                    const bool                        In3d) const;

private:
  HLRAlgo_Projector         myProjector;
  occ::handle<HLRBRep_Algo> myHLRAlgo;
  TopoDS_Shape              myShape;
};
