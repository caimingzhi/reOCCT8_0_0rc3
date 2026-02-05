#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
class Interface_InterfaceModel;
class Interface_GeneralLib;
class Interface_Protocol;
class Interface_GTool;

//! This class allows to store a redefinable Graph, via a Handle
//! (useful for an Object which can work on several successive
//! Models, with the same general conditions)
class Interface_HGraph : public Standard_Transient
{

public:
  //! Creates an HGraph directly from a Graph.
  //! Remark that the starting Graph is duplicated
  Standard_EXPORT Interface_HGraph(const Interface_Graph& agraph);

  //! Creates an HGraph with a Graph created from <amodel> and <lib>
  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const Interface_GeneralLib&                  lib,
                                   const bool theModeStats = true);

  //! Creates an HGraph with a graph itself created from <amodel>
  //! and <protocol>
  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const occ::handle<Interface_Protocol>&       protocol,
                                   const bool theModeStats = true);

  //! Creates an HGraph with a graph itself created from <amodel>
  //! and <protocol>
  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const occ::handle<Interface_GTool>&          gtool,
                                   const bool theModeStats = true);

  //! Same a above, but works with the GTool in the model
  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const bool theModeStats = true);

  //! Returns the Graph contained in <me>, for Read Only Operations
  //! Remark that it is returns as "const &"
  //! Getting it in a new variable instead of a reference would be
  //! a pity, because all the graph's content would be duplicated
  Standard_EXPORT const Interface_Graph& Graph() const;

  //! Same as above, but for Read-Write Operations
  //! Then, The Graph will be modified in the HGraph itself
  Standard_EXPORT Interface_Graph& CGraph();

  DEFINE_STANDARD_RTTIEXT(Interface_HGraph, Standard_Transient)

private:
  Interface_Graph thegraph;
};
