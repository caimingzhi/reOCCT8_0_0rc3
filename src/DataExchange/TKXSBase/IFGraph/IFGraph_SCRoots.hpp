#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IFGraph_StrongComponants.hpp>
class Interface_Graph;

class IFGraph_SCRoots : public IFGraph_StrongComponants
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_SCRoots(const Interface_Graph& agraph, const bool whole);

  Standard_EXPORT IFGraph_SCRoots(IFGraph_StrongComponants& subparts);

  Standard_EXPORT void Evaluate() override;
};
