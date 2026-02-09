#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_EntityIterator.hpp>
#include <Standard_Integer.hpp>
class Interface_Graph;
class Standard_Transient;

class Interface_GraphContent : public Interface_EntityIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_GraphContent();

  Standard_EXPORT Interface_GraphContent(const Interface_Graph& agraph);

  Standard_EXPORT Interface_GraphContent(const Interface_Graph& agraph, const int stat);

  Standard_EXPORT Interface_GraphContent(const Interface_Graph&                 agraph,
                                         const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void GetFromGraph(const Interface_Graph& agraph);

  Standard_EXPORT void GetFromGraph(const Interface_Graph& agraph, const int stat);

  Standard_EXPORT Interface_EntityIterator Result();

  Standard_EXPORT void Begin();

  Standard_EXPORT virtual void Evaluate();
};
