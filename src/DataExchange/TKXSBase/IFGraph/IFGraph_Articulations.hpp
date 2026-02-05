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

//! this class gives entities which are Articulation points
//! in a whole Model or in a sub-part
//! An Articulation Point divides the graph in two (or more)
//! disconnected sub-graphs
//! Identifying Articulation Points allows improving
//! efficiency of splitting a set of Entities into sub-sets
class IFGraph_Articulations : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates Articulations to evaluate a Graph
  //! whole True : works on the whole Model
  //! whole False : remains empty, ready to work on a sub-part
  Standard_EXPORT IFGraph_Articulations(const Interface_Graph& agraph, const bool whole);

  //! adds an entity and its shared ones to the list
  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  //! adds a list of entities (as an iterator)
  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter);

  //! Allows to restart on a new data set
  Standard_EXPORT void ResetData();

  //! Evaluates the list of Articulation points
  Standard_EXPORT void Evaluate() override;

private:
  //! basic routine of computation
  //! (see book Sedgewick "Algorithms", p 392)
  Standard_EXPORT int Visit(const int num);

private:
  Interface_Graph                         thegraph;
  int                                     thenow;
  occ::handle<NCollection_HSequence<int>> thelist;
};
