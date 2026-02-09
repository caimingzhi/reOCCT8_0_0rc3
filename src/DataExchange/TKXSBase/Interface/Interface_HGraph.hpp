#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
class Interface_InterfaceModel;
class Interface_GeneralLib;
class Interface_Protocol;
class Interface_GTool;

class Interface_HGraph : public Standard_Transient
{

public:
  Standard_EXPORT Interface_HGraph(const Interface_Graph& agraph);

  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const Interface_GeneralLib&                  lib,
                                   const bool theModeStats = true);

  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const occ::handle<Interface_Protocol>&       protocol,
                                   const bool theModeStats = true);

  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const occ::handle<Interface_GTool>&          gtool,
                                   const bool theModeStats = true);

  Standard_EXPORT Interface_HGraph(const occ::handle<Interface_InterfaceModel>& amodel,
                                   const bool theModeStats = true);

  Standard_EXPORT const Interface_Graph& Graph() const;

  Standard_EXPORT Interface_Graph& CGraph();

  DEFINE_STANDARD_RTTIEXT(Interface_HGraph, Standard_Transient)

private:
  Interface_Graph thegraph;
};
