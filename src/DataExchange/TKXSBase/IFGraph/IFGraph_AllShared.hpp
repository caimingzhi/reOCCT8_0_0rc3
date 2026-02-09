#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
class Standard_Transient;
class Interface_EntityIterator;

class IFGraph_AllShared : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_AllShared(const Interface_Graph& agraph);

  Standard_EXPORT IFGraph_AllShared(const Interface_Graph&                 agraph,
                                    const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  Standard_EXPORT void ResetData();

  Standard_EXPORT void Evaluate() override;

private:
  Interface_Graph thegraph;
};
