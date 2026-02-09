#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Draw_Interpretor.hpp>
class HLRAlgo_Projector;
class TopoDS_Shape;
class HLRTopoBRep_OutLiner;

class HLRTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Set(const char* Name, const HLRAlgo_Projector& P);

  Standard_EXPORT static bool GetProjector(const char*& Name, HLRAlgo_Projector& P);

  Standard_EXPORT static void Set(const char* Name, const TopoDS_Shape& S);

  Standard_EXPORT static occ::handle<HLRTopoBRep_OutLiner> GetOutLiner(const char*& Name);

  Standard_EXPORT static void Commands(Draw_Interpretor& I);
};
