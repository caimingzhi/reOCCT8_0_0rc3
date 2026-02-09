#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Standard_Boolean.hpp>
class Standard_Transient;
class Interface_EntityIterator;

class IFGraph_ExternalSources : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_ExternalSources(const Interface_Graph& agraph);

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  Standard_EXPORT void ResetData();

  Standard_EXPORT void Evaluate() override;

  Standard_EXPORT bool IsEmpty();

private:
  Interface_Graph thegraph;
};
