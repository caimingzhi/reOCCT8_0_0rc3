

#include <Interface_Check.hpp>
#include <Interface_CheckFailure.hpp>
#include <Interface_CheckIterator.hpp>
#include <Interface_CheckTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralModule.hpp>
#include <Interface_GTool.hpp>
#include <Interface_HGraph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ReportEntity.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_HAsciiString.hpp>

#ifdef _WIN32
  #include <OSD_Exception.hpp>
#else
  #include <OSD_Signal.hpp>
#endif
#include <cstdio>

static int errh = 1;

static void raisecheck(Standard_Failure& theException, occ::handle<Interface_Check>& ach)
{
  char mess[100];
  Sprintf(mess, "** Exception Raised during Check : %s **", theException.ExceptionType());
  ach->AddFail(mess);
#ifdef _WIN32
  if (dynamic_cast<OSD_Exception*>(&theException) != nullptr)
  {
#else
  if (dynamic_cast<OSD_Signal*>(&theException) != nullptr)
  {
#endif

    throw theException;
  }
}

Interface_CheckTool::Interface_CheckTool(const occ::handle<Interface_InterfaceModel>& model,
                                         const occ::handle<Interface_Protocol>&       protocol)
    : thegtool(new Interface_GTool(protocol, model->NbEntities())),
      theshare(model, protocol)
{
  thestat = 0;
}

Interface_CheckTool::Interface_CheckTool(const occ::handle<Interface_InterfaceModel>& model)
    : thegtool(model->GTool()),
      theshare(model, model->GTool())
{
  thestat = 0;
  thegtool->Reservate(model->NbEntities());
}

Interface_CheckTool::Interface_CheckTool(const Interface_Graph& graph)
    : thegtool(graph.Model()->GTool()),
      theshare(graph)
{
}

Interface_CheckTool::Interface_CheckTool(const occ::handle<Interface_HGraph>& hgraph)
    : thegtool(hgraph->Graph().Model()->GTool()),
      theshare(hgraph)
{
}

void Interface_CheckTool::FillCheck(const occ::handle<Standard_Transient>& ent,
                                    const Interface_ShareTool&             sh,
                                    occ::handle<Interface_Check>&          ach)
{
  occ::handle<Interface_GeneralModule> module;
  int                                  CN;
  if (thegtool->Select(ent, module, CN))
  {

    if (!errh)
    {
      module->CheckCase(CN, ent, sh, ach);
      return;
    }

    try
    {
      OCC_CATCH_SIGNALS
      module->CheckCase(CN, ent, sh, ach);
    }
    catch (Standard_Failure& anException)
    {
      raisecheck(anException, ach);
    }
  }
  else
  {
    DeclareAndCast(Interface_ReportEntity, rep, ent);
    if (rep.IsNull())
      return;
    ach = rep->Check();
  }
  if (theshare.Graph().HasShareErrors(ent))
    ach->AddFail("** Shared Items unknown from the containing Model");
}

void Interface_CheckTool::Print(const occ::handle<Interface_Check>& ach, Standard_OStream& S) const
{
  int i, nb;
  nb = ach->NbFails();
  if (nb > 0)
    S << " Fail Messages : " << nb << " :\n";
  for (i = 1; i <= nb; i++)
  {
    S << ach->Fail(i)->String() << "\n";
  }
  nb = ach->NbWarnings();
  if (nb > 0)
    S << " Warning Messages : " << nb << " :\n";
  for (i = 1; i <= nb; i++)
  {
    S << ach->Warning(i)->String() << "\n";
  }
}

void Interface_CheckTool::Print(const Interface_CheckIterator& list, Standard_OStream& S) const
{
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  list.Print(S, model, false);
}

occ::handle<Interface_Check> Interface_CheckTool::Check(const int num)
{
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  occ::handle<Standard_Transient>       ent   = model->Value(num);
  occ::handle<Interface_Check>          ach   = new Interface_Check(ent);
  errh                                        = 1;
  FillCheck(ent, theshare, ach);
  return ach;
}

void Interface_CheckTool::CheckSuccess(const bool reset)
{
  if (reset)
    thestat = 0;
  if (thestat > 3)
    throw Interface_CheckFailure("Interface Model : Global Check");
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  if (model->GlobalCheck()->NbFails() > 0)
    throw Interface_CheckFailure("Interface Model : Global Check");
  occ::handle<Interface_Check> modchk = new Interface_Check;
  model->VerifyCheck(modchk);
  if (!model->Protocol().IsNull())
    model->Protocol()->GlobalCheck(theshare.Graph(), modchk);
  if (modchk->HasFailed())
    throw Interface_CheckFailure("Interface Model : Verify Check");
  if (thestat == 3)
    return;

  errh   = 0;
  int nb = model->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    if (model->IsErrorEntity(i))
      throw Interface_CheckFailure("Interface Model : an Entity is recorded as Erroneous");
    occ::handle<Standard_Transient> ent = model->Value(i);
    if (thestat & 1)
    {
      if (!model->IsErrorEntity(i))
        continue;
    }
    if (thestat & 2)
    {
      if (model->IsErrorEntity(i))
        continue;
    }

    occ::handle<Interface_Check> ach = new Interface_Check(ent);
    FillCheck(ent, theshare, ach);
    if (ach->HasFailed())
      throw Interface_CheckFailure("Interface Model : Check on an Entity has Failed");
  }
}

Interface_CheckIterator Interface_CheckTool::CompleteCheckList()
{
  thestat                                     = 3;
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  Interface_CheckIterator               res;
  res.SetModel(model);
  occ::handle<Interface_Check> globch = model->GlobalCheck();
  if (!model->Protocol().IsNull())
    model->Protocol()->GlobalCheck(theshare.Graph(), globch);
  model->VerifyCheck(globch);
  if (globch->HasFailed() || globch->HasWarnings())
    res.Add(globch, 0);
  if (globch->HasFailed())
    thestat |= 12;

  int i = 0, n0 = 1, nb = model->NbEntities();
  errh = 0;
  while (n0 <= nb)
  {
    occ::handle<Interface_Check>    ach = new Interface_Check;
    occ::handle<Standard_Transient> ent;
    try
    {
      OCC_CATCH_SIGNALS
      for (i = n0; i <= nb; i++)
      {
        ach->Clear();
        ent = model->Value(i);
        ach->SetEntity(ent);
        if (model->IsReportEntity(i))
        {
          ach = model->ReportEntity(i)->Check();
          if (ach->HasFailed())
          {
            res.Add(ach, i);
            ach = new Interface_Check;
            thestat |= 12;
            continue;
          }
        }
        if (!model->HasSemanticChecks())
          FillCheck(ent, theshare, ach);
        else
          ach->GetMessages(model->Check(i, false));
        if (ach->HasFailed() || ach->HasWarnings())
        {
          res.Add(ach, i);
          ach = new Interface_Check;
          if (ach->HasFailed())
            thestat |= 12;
        }
      }
      n0 = nb + 1;
    }
    catch (Standard_Failure& anException)
    {
      n0 = i + 1;
      raisecheck(anException, ach);
      res.Add(ach, i);
      thestat |= 12;
    }
  }
  return res;
}

Interface_CheckIterator Interface_CheckTool::CheckList()
{
  thestat                                     = 3;
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  Interface_CheckIterator               res;
  res.SetModel(model);
  int                          i = 0, n0 = 1, nb = model->NbEntities();
  occ::handle<Interface_Check> globch = model->GlobalCheck();
  if (!model->Protocol().IsNull())
    model->Protocol()->GlobalCheck(theshare.Graph(), globch);
  model->VerifyCheck(globch);
  if (globch->HasFailed())
  {
    thestat |= 12;
    res.Add(globch, 0);
  }

  errh = 0;
  while (n0 <= nb)
  {
    occ::handle<Interface_Check>    ach = new Interface_Check;
    occ::handle<Standard_Transient> ent;
    try
    {
      OCC_CATCH_SIGNALS
      for (i = n0; i <= nb; i++)
      {
        if (model->IsReportEntity(i))
        {
          ach = model->ReportEntity(i)->Check();
          if (ach->HasFailed())
          {
            thestat |= 12;
            res.Add(ach, i);
          }
        }
        else
        {
          ent = model->Value(i);
          ach->Clear();
          ach->SetEntity(ent);
          if (!model->HasSemanticChecks())
            FillCheck(ent, theshare, ach);
          else
            ach = model->Check(i, false);
          if (ach->HasFailed())
          {
            thestat |= 12;
            res.Add(ach, i);
          }
        }
      }
      n0 = nb + 1;
    }
    catch (Standard_Failure& anException)
    {
      n0 = i + 1;
      raisecheck(anException, ach);
      res.Add(ach, i);
      thestat |= 12;
    }
  }
  return res;
}

Interface_CheckIterator Interface_CheckTool::AnalyseCheckList()
{
  thestat                                     = 2;
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  Interface_CheckIterator               res;
  res.SetModel(model);
  int i = 0, n0 = 1, nb = model->NbEntities();

  errh = 0;
  while (n0 <= nb)
  {
    occ::handle<Interface_Check> ach = new Interface_Check;
    try
    {
      OCC_CATCH_SIGNALS
      for (i = n0; i <= nb; i++)
      {
        if (!model->IsReportEntity(i))
          continue;
        occ::handle<Interface_ReportEntity> rep = model->ReportEntity(i);
        ach                                     = rep->Check();
        if (ach->HasFailed() || ach->HasWarnings())
        {
          thestat |= 8;
          res.Add(ach, i);
        }
      }
      n0 = nb + 1;
    }
    catch (Standard_Failure& anException)
    {
      n0 = i + 1;
      raisecheck(anException, ach);
      res.Add(ach, i);
      thestat |= 8;
    }
  }
  return res;
}

Interface_CheckIterator Interface_CheckTool::VerifyCheckList()
{
  thestat                                     = 1;
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  Interface_CheckIterator               res;
  res.SetModel(model);
  int i = 0, n0 = 1, nb = model->NbEntities();

  errh = 0;
  while (n0 <= nb)
  {
    occ::handle<Standard_Transient> ent;
    occ::handle<Interface_Check>    ach = new Interface_Check;
    try
    {
      OCC_CATCH_SIGNALS
      for (i = n0; i <= nb; i++)
      {
        if (model->IsErrorEntity(i))
          continue;
        ent = model->Value(i);
        ach->Clear();
        ach->SetEntity(ent);
        if (!model->HasSemanticChecks())
          FillCheck(ent, theshare, ach);
        else
          ach = model->Check(i, false);
        if (ach->HasFailed() || ach->HasWarnings())
        {
          thestat |= 4;
          res.Add(ach, i);
        }
      }
      n0 = nb + 1;
    }
    catch (Standard_Failure& anException)
    {
      n0 = i + 1;
      raisecheck(anException, ach);
      res.Add(ach, i);
      thestat |= 4;
    }
  }
  return res;
}

Interface_CheckIterator Interface_CheckTool::WarningCheckList()
{
  thestat                                     = 3;
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  Interface_CheckIterator               res;
  res.SetModel(model);
  int i = 0, n0 = 1, nb = model->NbEntities();

  errh = 0;
  while (n0 <= nb)
  {
    occ::handle<Interface_Check>    ach = new Interface_Check;
    occ::handle<Standard_Transient> ent;
    try
    {
      OCC_CATCH_SIGNALS
      for (i = n0; i <= nb; i++)
      {
        ach->Clear();
        ach->SetEntity(ent);
        if (model->IsReportEntity(i))
        {
          occ::handle<Interface_ReportEntity> rep = model->ReportEntity(i);
          if (rep->IsError())
          {
            thestat |= 12;
            continue;
          }
          ach = rep->Check();
        }
        ent = model->Value(i);
        if (!model->HasSemanticChecks())
          FillCheck(ent, theshare, ach);
        else
          ach = model->Check(i, false);
        if (ach->HasFailed())
          thestat |= 12;
        else if (ach->HasWarnings())
          res.Add(ach, i);
      }
      n0 = nb + 1;
    }
    catch (Standard_Failure& anException)
    {
      n0 = i + 1;
      raisecheck(anException, ach);
      res.Add(ach, i);
      thestat |= 12;
    }
  }

  return res;
}

Interface_EntityIterator Interface_CheckTool::UnknownEntities()
{
  occ::handle<Interface_InterfaceModel> model = theshare.Model();
  Interface_EntityIterator              res;
  int                                   nb = model->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    if (model->IsUnknownEntity(i))
      res.GetOneItem(model->Value(i));
  }
  return res;
}
