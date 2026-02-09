#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class TopoDS_Edge;
class HLRBRep_Curve;

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
