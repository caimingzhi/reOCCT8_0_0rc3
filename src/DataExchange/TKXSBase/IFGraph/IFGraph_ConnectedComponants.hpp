#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IFGraph_SubPartsIterator.hpp>
class Interface_Graph;

class IFGraph_ConnectedComponants : public IFGraph_SubPartsIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_ConnectedComponants(const Interface_Graph& agraph, const bool whole);

  Standard_EXPORT void Evaluate() override;
};
