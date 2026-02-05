#pragma once

#include <Standard.hpp>

#include <IFSelect_SignCounter.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class IFSelect_SelectDeduct;
class Interface_Graph;

//! A GraphCounter computes values to be sorted with the help of
//! a Graph. I.E. not from a Signature
//!
//! The default GraphCounter works with an Applied Selection (a
//! SelectDeduct), the value is the count of selected entities
//! from each input entities)
class IFSelect_GraphCounter : public IFSelect_SignCounter
{

public:
  //! Creates a GraphCounter, without applied selection
  Standard_EXPORT IFSelect_GraphCounter(const bool withmap = true, const bool withlist = false);

  //! Returns the applied selection
  Standard_EXPORT occ::handle<IFSelect_SelectDeduct> Applied() const;

  //! Sets a new applied selection
  Standard_EXPORT void SetApplied(const occ::handle<IFSelect_SelectDeduct>& sel);

  //! Adds a list of entities in the context given by the graph
  //! Default takes the count of entities selected by the applied
  //! selection, when it is given each entity of the list
  //! Can be redefined
  Standard_EXPORT void AddWithGraph(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const Interface_Graph&                                                     graph) override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_GraphCounter, IFSelect_SignCounter)

private:
  occ::handle<IFSelect_SelectDeduct> theapplied;
};
