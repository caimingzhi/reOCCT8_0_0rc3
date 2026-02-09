

#include <IGESSelect.hpp>

#include <IFSelect_Functions.hpp>
#include <IFSelect_SessionPilot.hpp>
#include <IFSelect_ShareOut.hpp>
#include <IFSelect_WorkSession.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_Activator.hpp>
#include <IGESSelect_WorkLibrary.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>

void IGESSelect::Run()
{

  IFSelect_Functions::Init();
  occ::handle<IFSelect_SessionPilot> pilot   = new IFSelect_SessionPilot("XSTEP-IGES>");
  occ::handle<IGESSelect_Activator>  igesact = new IGESSelect_Activator;
  pilot->SetSession(new IFSelect_WorkSession());
  pilot->SetLibrary(new IGESSelect_WorkLibrary);

  pilot->ReadScript();
}

int IGESSelect::WhatIges(const occ::handle<IGESData_IGESEntity>& ent,
                         const Interface_Graph&                  G,
                         occ::handle<IGESData_IGESEntity>&,
                         int&)
{
  const occ::handle<IGESData_IGESEntity>& igesent = ent;
  if (igesent.IsNull())
    return false;

  DeclareAndCast(IGESData_IGESModel, model, G.Model());
  if (igesent.IsNull() || model.IsNull())
    return 0;

  return 0;
}
