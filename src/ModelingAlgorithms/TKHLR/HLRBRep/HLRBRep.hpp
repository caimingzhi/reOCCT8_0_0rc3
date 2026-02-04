#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class TopoDS_Edge;
class HLRBRep_Curve;

//! Hidden Lines Removal
//! algorithms on the BRep DataStructure.
//!
//! The class PolyAlgo is used to remove Hidden lines
//! on Shapes with Triangulations.
class HLRBRep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Edge MakeEdge(const HLRBRep_Curve& ec,
                                              const double         U1,
                                              const double         U2);

  Standard_EXPORT static TopoDS_Edge MakeEdge3d(const HLRBRep_Curve& ec,
                                                const double         U1,
                                                const double         U2);

  Standard_EXPORT static void PolyHLRAngleAndDeflection(const double InAngl,
                                                        double&      OutAngl,
                                                        double&      OutDefl);
};

