#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
class Standard_Transient;
class Interface_EntityIterator;

//! this class determines all Entities shared by some specific
//! ones, at any level (those which will be lead in a Transfer
//! for instance)
class IFGraph_AllShared : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates an AllShared from a graph, empty ready to be filled
  Standard_EXPORT IFGraph_AllShared(const Interface_Graph& agraph);

  //! creates an AllShared which memrizes Entities shared by a given
  //! one, at any level, including itself
  Standard_EXPORT IFGraph_AllShared(const Interface_Graph&                 agraph,
                                    const occ::handle<Standard_Transient>& ent);

  //! adds an entity and its shared ones to the list (allows to
  //! cumulate all Entities shared by some ones)
  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  //! Adds Entities from an EntityIterator and all their shared
  //! ones at any level
  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  //! Allows to restart on a new data set
  Standard_EXPORT void ResetData();

  //! does the specific evaluation (shared entities atall levels)
  Standard_EXPORT void Evaluate() override;

private:
  Interface_Graph thegraph;
};

