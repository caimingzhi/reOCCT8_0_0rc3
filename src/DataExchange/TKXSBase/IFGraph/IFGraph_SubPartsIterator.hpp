#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Boolean.hpp>
class Interface_InterfaceModel;
class Standard_Transient;
class Interface_EntityIterator;
class Interface_GraphContent;

class IFGraph_SubPartsIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_SubPartsIterator(const Interface_Graph& agraph, const bool whole);

  Standard_EXPORT IFGraph_SubPartsIterator(IFGraph_SubPartsIterator& other);

  Standard_EXPORT void GetParts(IFGraph_SubPartsIterator& other);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void AddPart();

  Standard_EXPORT int NbParts() const;

  Standard_EXPORT int PartNum() const;

  Standard_EXPORT void SetLoad();

  Standard_EXPORT void SetPartNum(const int num);

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent, const bool shared);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  Standard_EXPORT void Reset();

  Standard_EXPORT virtual void Evaluate();

  Standard_EXPORT Interface_GraphContent Loaded() const;

  Standard_EXPORT Interface_Graph LoadedGraph() const;

  Standard_EXPORT bool IsLoaded(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT bool IsInPart(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT int EntityPartNum(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More();

  Standard_EXPORT void Next();

  Standard_EXPORT bool IsSingle() const;

  Standard_EXPORT occ::handle<Standard_Transient> FirstEntity() const;

  Standard_EXPORT Interface_EntityIterator Entities() const;

  Standard_EXPORT virtual ~IFGraph_SubPartsIterator();

protected:
  Interface_Graph thegraph;

private:
  Standard_EXPORT const Interface_Graph& Graph() const;

  occ::handle<NCollection_HSequence<int>> theparts;
  occ::handle<NCollection_HSequence<int>> thefirsts;
  int                                     thepart;
  int                                     thecurr;
};
