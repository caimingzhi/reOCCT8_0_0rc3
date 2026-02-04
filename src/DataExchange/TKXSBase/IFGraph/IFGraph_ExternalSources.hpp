#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Standard_Boolean.hpp>
class Standard_Transient;
class Interface_EntityIterator;

//! this class gives entities which are Source of entities of
//! a sub-part, but are not contained by this sub-part
class IFGraph_ExternalSources : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates empty ExternalSources, ready to work
  Standard_EXPORT IFGraph_ExternalSources(const Interface_Graph& agraph);

  //! adds an entity and its shared ones to the list
  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  //! adds a list of entities (as an iterator) with shared ones
  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  //! Allows to restart on a new data set
  Standard_EXPORT void ResetData();

  //! Evaluates external sources of a set of entities
  Standard_EXPORT void Evaluate() override;

  //! Returns True if no External Source are found
  //! It means that we have a "root" set
  //! (performs an Evaluation as necessary)
  Standard_EXPORT bool IsEmpty();

private:
  Interface_Graph thegraph;
};

