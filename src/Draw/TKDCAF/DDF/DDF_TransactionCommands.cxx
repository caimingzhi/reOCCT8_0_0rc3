#include <DDF.hpp>
#include <DDF_Data.hpp>
#include <DDF_Transaction.hpp>
#include <NCollection_List.hpp>

#include <Draw_Appli.hpp>
#include <Draw_Interpretor.hpp>

#include <TDF_Data.hpp>
#include <TDF_Delta.hpp>

static NCollection_List<occ::handle<DDF_Transaction>> DDF_TStack;
static occ::handle<TDF_Delta>                         DDF_LastDelta;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Transaction commands
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================

static int OpenTran(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDF_Data> DF;
  if (DDF::GetDF(a[1], DF))
  {
    occ::handle<DDF_Transaction> tr = new DDF_Transaction(DF);
    di << "Open transaction # " << tr->Open() << " # " << DF->Transaction() << "\n";
    DDF_TStack.Prepend(tr);
  }
  return 0;
}

//=================================================================================================

static int AbortTran(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDF_Data> DF;
  if (DDF::GetDF(a[1], DF))
  {
    if (DF->Transaction() > 0)
    {
      occ::handle<DDF_Transaction> tr = DDF_TStack.First();
      di << "Abort transaction # " << tr->Transaction() << " # " << DF->Transaction() << "\n";
      tr->Abort();
      DDF_TStack.RemoveFirst();
    }
    else
    {
      di << "DDF_BasicCommands::AbortTran - No more transaction to abort\n";
    }
  }
  return 0;
}

//=================================================================================================

static int CommitTran(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDF_Data> DF;
  if (DDF::GetDF(a[1], DF))
  {
    if (DF->Transaction() > 0)
    {
      occ::handle<DDF_Transaction> tr = DDF_TStack.First();
      di << "Commit transaction # " << tr->Transaction() << " # " << DF->Transaction() << "\n";
      bool withDelta = false;
      if (n > 2)
        withDelta = (Draw::Atoi(a[2]) != 0);
      DDF_LastDelta = tr->Commit(withDelta);
      DDF_TStack.RemoveFirst();
    }
    else
    {
      di << "DDF_BasicCommands::CommitTran - No more transaction to commit\n";
    }
  }
  return 0;
}

//=======================================================================
// function : CurrentTran
// purpose  : Current transaction number.
//=======================================================================

static int CurrentTran(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDF_Data> DF;
  if (DDF::GetDF(a[1], DF))
  {
    di << "# " << DF->Transaction() << "\n";
    if (!DDF_TStack.IsEmpty())
      if (DF->Transaction() != DDF_TStack.First()->Transaction())
        di << "Transaction object said # " << DDF_TStack.First()->Transaction() << "\n";
  }
  return 0;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Delta commands
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================

static int Undo(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 2)
    return 1;

  occ::handle<TDF_Data> DF;
  if (DDF::GetDF(a[1], DF))
  {
    bool withDelta = false;
    if (n > 2)
      withDelta = (Draw::Atoi(a[2]) != 0);
    if (!DDF_LastDelta.IsNull())
    {
      if (DF->IsApplicable(DDF_LastDelta))
      {
        occ::handle<TDF_Delta> tmp = DF->Undo(DDF_LastDelta, withDelta);
        DDF_LastDelta              = tmp;
      }
      else
      {
        di << "Undo not applicable HERE and NOW.\n";
        return 1;
      }
    }
    else
    {
      di << "No undo to apply.\n";
      return 1;
    }
  }
  else
  {
    di << "Unknown DF.\n";
    return 1;
  }
  return 0;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================

void DDF::TransactionCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DF transaction and undo commands";

  // Transaction :
  // +++++++++++++
  theCommands.Add("OpenTran",
                  "Opens a transaction on a DF: OpenTran dfname",
                  __FILE__,
                  OpenTran,
                  g);

  theCommands.Add("AbortTran",
                  "Aborts a transaction on a DF: AbortTran dfname",
                  __FILE__,
                  AbortTran,
                  g);

  theCommands.Add(
    "CommitTran",
    "Commits a transaction on a DF with/without delta generation : CommitTran dfname [withDelta]",
    __FILE__,
    CommitTran,
    g);

  theCommands.Add("CurrentTran",
                  "Returns the current transaction number on a DF : CurrentTran dfname",
                  __FILE__,
                  CurrentTran,
                  g);

  // Undo :
  // ++++++
  theCommands.Add("DFUndo",
                  " Undos last DF commit modifications: Undo dfname [withDelta]",
                  __FILE__,
                  Undo,
                  g);
}
