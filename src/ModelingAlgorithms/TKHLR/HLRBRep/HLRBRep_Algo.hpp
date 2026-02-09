#pragma once

#include <Standard.hpp>

#include <HLRBRep_InternalAlgo.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;
class Standard_Transient;

class HLRBRep_Algo : public HLRBRep_InternalAlgo
{

public:
  Standard_EXPORT HLRBRep_Algo();

  Standard_EXPORT HLRBRep_Algo(const occ::handle<HLRBRep_Algo>& A);

  Standard_EXPORT void Add(const TopoDS_Shape&                    S,
                           const occ::handle<Standard_Transient>& SData,
                           const int                              nbIso = 0);

  Standard_EXPORT void Add(const TopoDS_Shape& S, const int nbIso = 0);

  Standard_EXPORT int Index(const TopoDS_Shape& S);

  Standard_EXPORT void OutLinedShapeNullify();

  DEFINE_STANDARD_RTTIEXT(HLRBRep_Algo, HLRBRep_InternalAlgo)
};
