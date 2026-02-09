#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_EntityIterator;

class IFGraph_Cumulate : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_Cumulate(const Interface_Graph& agraph);

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  Standard_EXPORT void ResetData();

  Standard_EXPORT void Evaluate() override;

  Standard_EXPORT Interface_EntityIterator Overlapped() const;

  Standard_EXPORT Interface_EntityIterator Forgotten() const;

  Standard_EXPORT Interface_EntityIterator PerCount(const int count = 1) const;

  Standard_EXPORT int NbTimes(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT int HighestNbTimes() const;

private:
  Interface_Graph thegraph;
};
