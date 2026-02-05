#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
class Standard_Transient;

//! this class gives content of the CONNECTED COMPONENT(S)
//! which include specific Entity(ies)
class IFGraph_AllConnected : public Interface_GraphContent
{
public:
  DEFINE_STANDARD_ALLOC

  //! creates an AllConnected from a graph, empty ready to be filled
  Standard_EXPORT IFGraph_AllConnected(const Interface_Graph& agraph);

  //! creates an AllConnected which memorizes Entities Connected to
  //! a given one, at any level : that is, itself, all Entities
  //! Shared by it and Sharing it, and so on.
  //! In other terms, this is the content of the CONNECTED COMPONENT
  //! which include a specific Entity
  Standard_EXPORT IFGraph_AllConnected(const Interface_Graph&                 agraph,
                                       const occ::handle<Standard_Transient>& ent);

  //! adds an entity and its Connected ones to the list (allows to
  //! cumulate all Entities Connected by some ones)
  //! Note that if "ent" is in the already computed list,, no entity
  //! will be added, but if "ent" is not already in the list, a new
  //! Connected Component will be cumulated
  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent);

  //! Allows to restart on a new data set
  Standard_EXPORT void ResetData();

  //! does the specific evaluation (Connected entities atall levels)
  Standard_EXPORT void Evaluate() override;

private:
  Interface_Graph thegraph;
};
