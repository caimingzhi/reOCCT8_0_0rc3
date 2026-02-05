#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_EntityIterator.hpp>
#include <Standard_Integer.hpp>
class Interface_Graph;
class Standard_Transient;

//! Defines general form for classes of graph algorithms on
//! Interfaces, this form is that of EntityIterator
//! Each sub-class fills it according to its own algorithm
//! This also allows to combine any graph result to others,
//! all being given under one unique form
class Interface_GraphContent : public Interface_EntityIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty GraphContent, ready to be filled
  Standard_EXPORT Interface_GraphContent();

  //! Creates with all entities designated by a Graph
  Standard_EXPORT Interface_GraphContent(const Interface_Graph& agraph);

  //! Creates with entities having specific Status value in a Graph
  Standard_EXPORT Interface_GraphContent(const Interface_Graph& agraph, const int stat);

  //! Creates an Iterator with Shared entities of an entity
  //! (equivalente to EntityIterator but with a Graph)
  Standard_EXPORT Interface_GraphContent(const Interface_Graph&                 agraph,
                                         const occ::handle<Standard_Transient>& ent);

  //! Gets all Entities designated by a Graph (once created), adds
  //! them to those already recorded
  Standard_EXPORT void GetFromGraph(const Interface_Graph& agraph);

  //! Gets entities from a graph which have a specific Status value
  //! (one created), adds them to those already recorded
  Standard_EXPORT void GetFromGraph(const Interface_Graph& agraph, const int stat);

  //! Returns Result under the exact form of an EntityIterator :
  //! Can be used when EntityIterator itself is required (as a
  //! returned value for instance), without way for a sub-class
  Standard_EXPORT Interface_EntityIterator Result();

  //! Does the Evaluation before starting the iteration itself
  //! (in out)
  Standard_EXPORT void Begin();

  //! Evaluates list of Entities to be iterated. Called by Start
  //! Default is set to doing nothing : intended to be redefined
  //! by each sub-class
  Standard_EXPORT virtual void Evaluate();
};
