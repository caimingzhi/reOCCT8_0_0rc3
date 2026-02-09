#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
class Standard_Transient;
class Interface_EntityIterator;

class IFGraph_Compare : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFGraph_Compare(const Interface_Graph& agraph);

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent, const bool first);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter, const bool first);

  Standard_EXPORT void Merge();

  Standard_EXPORT void RemoveSecond();

  Standard_EXPORT void KeepCommon();

  Standard_EXPORT void ResetData();

  Standard_EXPORT void Evaluate() override;

  Standard_EXPORT Interface_EntityIterator Common() const;

  Standard_EXPORT Interface_EntityIterator FirstOnly() const;

  Standard_EXPORT Interface_EntityIterator SecondOnly() const;

private:
  Interface_Graph thegraph;
};
