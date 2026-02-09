#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IFGraph_SubPartsIterator.hpp>
#include <Standard_Boolean.hpp>
class Interface_Graph;

class IFGraph_StrongComponants : public IFGraph_SubPartsIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_StrongComponants(const Interface_Graph& agraph, const bool whole);

  Standard_EXPORT void Evaluate() override;
};
