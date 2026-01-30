// Created on: 2000-09-29
// Created by: data exchange team
// Copyright (c) 2000-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <Interface_InterfaceModel.hpp>
#include <Interface_Graph.hpp>
#include <Interface_HGraph.hpp>
#include <Transfer_TransientProcess.hpp>
#include <Transfer_FinderProcess.hpp>
#include <XSControl_WorkSession.hpp>

//=================================================================================================

inline const occ::handle<XSControl_WorkSession>& STEPConstruct_Tool::WS() const
{
  return myWS;
}

//=================================================================================================

inline occ::handle<Interface_InterfaceModel> STEPConstruct_Tool::Model() const
{
  return myWS->Model();
}

//=================================================================================================

inline const Interface_Graph& STEPConstruct_Tool::Graph(const bool recompute) const
{
  // Note: myWS->Graph() recomputes graph each time!
  return recompute ? myWS->Graph() : myHGraph->Graph();
}

//=================================================================================================

inline const occ::handle<Transfer_TransientProcess>& STEPConstruct_Tool::TransientProcess() const
{
  return myTransientProcess;
}

//=================================================================================================

inline const occ::handle<Transfer_FinderProcess>& STEPConstruct_Tool::FinderProcess() const
{
  return myFinderProcess;
}
