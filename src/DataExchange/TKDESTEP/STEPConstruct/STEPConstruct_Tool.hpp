#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class XSControl_WorkSession;
class Transfer_FinderProcess;
class Transfer_TransientProcess;
class Interface_HGraph;
class Interface_InterfaceModel;
class Interface_Graph;

class STEPConstruct_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_Tool();

  Standard_EXPORT STEPConstruct_Tool(const occ::handle<XSControl_WorkSession>& WS);

  const occ::handle<XSControl_WorkSession>& WS() const;

  occ::handle<Interface_InterfaceModel> Model() const;

  const Interface_Graph& Graph(const bool recompute = false) const;

  const occ::handle<Transfer_TransientProcess>& TransientProcess() const;

  const occ::handle<Transfer_FinderProcess>& FinderProcess() const;

protected:
  Standard_EXPORT bool SetWS(const occ::handle<XSControl_WorkSession>& WS);

private:
  occ::handle<XSControl_WorkSession>     myWS;
  occ::handle<Transfer_FinderProcess>    myFinderProcess;
  occ::handle<Transfer_TransientProcess> myTransientProcess;
  occ::handle<Interface_HGraph>          myHGraph;
};

#include <Interface_InterfaceModel.hpp>
#include <Interface_Graph.hpp>
#include <Interface_HGraph.hpp>
#include <Transfer_TransientProcess.hpp>
#include <Transfer_FinderProcess.hpp>
#include <XSControl_WorkSession.hpp>

inline const occ::handle<XSControl_WorkSession>& STEPConstruct_Tool::WS() const
{
  return myWS;
}

inline occ::handle<Interface_InterfaceModel> STEPConstruct_Tool::Model() const
{
  return myWS->Model();
}

inline const Interface_Graph& STEPConstruct_Tool::Graph(const bool recompute) const
{

  return recompute ? myWS->Graph() : myHGraph->Graph();
}

inline const occ::handle<Transfer_TransientProcess>& STEPConstruct_Tool::TransientProcess() const
{
  return myTransientProcess;
}

inline const occ::handle<Transfer_FinderProcess>& STEPConstruct_Tool::FinderProcess() const
{
  return myFinderProcess;
}
