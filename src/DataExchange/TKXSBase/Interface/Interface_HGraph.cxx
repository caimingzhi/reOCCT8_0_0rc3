

#include <Interface_GTool.hpp>
#include <Interface_HGraph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_HGraph, Standard_Transient)

Interface_HGraph::Interface_HGraph(const Interface_Graph& agraph)
    : thegraph(agraph)
{
}

Interface_HGraph::Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const Interface_GeneralLib&                  lib,
                                   const bool                                   theModeStat)
    : thegraph(amodel, lib, theModeStat)
{
}

Interface_HGraph::Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const occ::handle<Interface_Protocol>&       protocol,
                                   const bool                                   theModeStat)
    : thegraph(amodel, protocol, theModeStat)
{
}

Interface_HGraph::Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const occ::handle<Interface_GTool>&          gtool,
                                   const bool                                   theModeStat)
    : thegraph(amodel, gtool, theModeStat)
{
}

Interface_HGraph::Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const bool                                   theModeStat)
    : thegraph(amodel, theModeStat)
{
}

const Interface_Graph& Interface_HGraph::Graph() const
{
  return thegraph;
}

Interface_Graph& Interface_HGraph::CGraph()
{
  return thegraph;
}
