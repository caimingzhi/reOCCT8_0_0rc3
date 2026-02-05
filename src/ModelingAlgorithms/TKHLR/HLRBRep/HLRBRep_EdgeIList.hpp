#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRAlgo_Interference.hpp>
#include <NCollection_List.hpp>
class HLRAlgo_Interference;
class HLRBRep_EdgeInterferenceTool;

class HLRBRep_EdgeIList
{
public:
  DEFINE_STANDARD_ALLOC

  //! Add the interference <I> to the list <IL>.
  Standard_EXPORT static void AddInterference(NCollection_List<HLRAlgo_Interference>& IL,
                                              const HLRAlgo_Interference&             I,
                                              const HLRBRep_EdgeInterferenceTool&     T);

  //! Process complex transitions on the list IL.
  Standard_EXPORT static void ProcessComplex(NCollection_List<HLRAlgo_Interference>& IL,
                                             const HLRBRep_EdgeInterferenceTool&     T);
};
