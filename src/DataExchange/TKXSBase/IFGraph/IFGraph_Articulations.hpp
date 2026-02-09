#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Interface_GraphContent.hpp>
#include <Standard_Boolean.hpp>
class Standard_Transient;
class Interface_EntityIterator;

class IFGraph_Articulations : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_Articulations(const Interface_Graph& agraph, const bool whole);

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  Standard_EXPORT void ResetData();

  Standard_EXPORT void Evaluate() override;

private:
  Standard_EXPORT int Visit(const int num);

private:
  Interface_Graph                         thegraph;
  int                                     thenow;
  occ::handle<NCollection_HSequence<int>> thelist;
};
