#include <Standard_NoSuchObject.hpp>

static occ::handle<LibCtl_GlobalNode> theglobal;

static occ::handle<TheProtocol> theprotocol;
static occ::handle<LibCtl_Node> thelast;

void LibCtl_Library::SetGlobal(const occ::handle<TheModule>&   amodule,
                               const occ::handle<TheProtocol>& aprotocol)
{
  if (theglobal.IsNull())
    theglobal = new LibCtl_GlobalNode;
  theglobal->Add(amodule, aprotocol);
}

LibCtl_Library::LibCtl_Library(const occ::handle<TheProtocol>& aprotocol)
{
  bool last = false;
  if (aprotocol.IsNull())
    return;
  if (!theprotocol.IsNull())
    last = (theprotocol == aprotocol);

  if (last)
    thelist = thelast;

  else
  {
    AddProtocol(aprotocol);

    thelast     = thelist;
    theprotocol = aprotocol;
  }
}

LibCtl_Library::LibCtl_Library() {}

void LibCtl_Library::AddProtocol(const occ::handle<Standard_Transient>& aprotocol)
{

  occ::handle<TheProtocol> aproto = occ::down_cast<TheProtocol>(aprotocol);
  if (aproto.IsNull())
    return;

  occ::handle<LibCtl_GlobalNode> curr;
  for (curr = theglobal; !curr.IsNull();)
  {
    const occ::handle<TheProtocol>& protocol = curr->Protocol();
    if (!protocol.IsNull())
    {

      if (protocol->DynamicType() == aprotocol->DynamicType())
      {
        if (thelist.IsNull())
          thelist = new LibCtl_Node;
        thelist->AddNode(curr);
        break;
      }
    }
    curr = curr->Next();
  }

  int nb = aproto->NbResources();
  for (int i = 1; i <= nb; i++)
  {
    AddProtocol(aproto->Resource(i));
  }

  theprotocol.Nullify();
  thelast.Nullify();
}

void LibCtl_Library::Clear()
{
  thelist = new LibCtl_Node;
}

void LibCtl_Library::SetComplete()
{
  thelist = new LibCtl_Node;

  occ::handle<LibCtl_GlobalNode> curr;
  for (curr = theglobal; !curr.IsNull();)
  {
    const occ::handle<TheProtocol>& protocol = curr->Protocol();

    if (!protocol.IsNull())
      thelist->AddNode(curr);
    curr = curr->Next();
  }
}

bool LibCtl_Library::Select(const TheObject& obj, occ::handle<TheModule>& module, int& CN) const
{
  module.Nullify();
  CN = 0;
  if (thelist.IsNull())
    return false;
  occ::handle<LibCtl_Node> curr = thelist;
  for (curr = thelist; !curr.IsNull();)
  {
    const occ::handle<TheProtocol>& protocol = curr->Protocol();
    if (!protocol.IsNull())
    {
      CN = protocol->CaseNumber(obj);
      if (CN > 0)
      {
        module = curr->Module();
        return true;
      }
    }
    curr = curr->Next();
  }
  return false;
}

void LibCtl_Library::Start()
{
  thecurr = thelist;
}

bool LibCtl_Library::More() const
{
  return (!thecurr.IsNull());
}

void LibCtl_Library::Next()
{
  if (!thecurr.IsNull())
    thecurr = thecurr->Next();
}

const occ::handle<TheModule>& LibCtl_Library::Module() const
{
  if (thecurr.IsNull())
    throw Standard_NoSuchObject("Library from LibCtl");
  return thecurr->Module();
}

const occ::handle<TheProtocol>& LibCtl_Library::Protocol() const
{
  if (thecurr.IsNull())
    throw Standard_NoSuchObject("Library from LibCtl");
  return thecurr->Protocol();
}
