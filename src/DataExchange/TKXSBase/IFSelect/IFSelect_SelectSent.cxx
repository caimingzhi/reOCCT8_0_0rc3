

#include <IFSelect_SelectSent.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectSent, IFSelect_SelectExtract)

IFSelect_SelectSent::IFSelect_SelectSent(const int sentcount, const bool atleast)
{
  thecnt = sentcount;
  thelst = atleast;
}

int IFSelect_SelectSent::SentCount() const
{
  return thecnt;
}

bool IFSelect_SelectSent::AtLeast() const
{
  return thelst;
}

Interface_EntityIterator IFSelect_SelectSent::RootResult(const Interface_Graph& G) const
{
  bool                     direct = IsDirect();
  Interface_EntityIterator res;
  Interface_EntityIterator inp = InputResult(G);

  for (inp.Start(); inp.More(); inp.Next())
  {
    int num = G.EntityNumber(inp.Value());
    if (num == 0)
      continue;
    int  nb = G.Status(num);
    bool ok;
    if (thecnt == 0)
      ok = (nb == 0);
    else if (thelst)
      ok = (nb >= thecnt);
    else
      ok = (nb == thecnt);
    if (ok == direct)
      res.AddItem(G.Entity(num));
  }
  return res;
}

bool IFSelect_SelectSent::Sort(const int,
                               const occ::handle<Standard_Transient>&,
                               const occ::handle<Interface_InterfaceModel>&) const
{
  return false;
}

TCollection_AsciiString IFSelect_SelectSent::ExtractLabel() const
{
  char                    lb[80];
  TCollection_AsciiString lab;
  if (thecnt == 0)
    lab.AssignCat("Remaining (non-sent) entities");
  if (thecnt == 1 && thelst)
    lab.AssignCat("Sent entities");
  if (thecnt == 1 && !thelst)
    lab.AssignCat("Sent once (non-duplicated) entities");
  if (thecnt == 2 && thelst)
    lab.AssignCat("Sent several times entities");
  if (thecnt == 2 && !thelst)
    lab.AssignCat("Sent just twice entities");
  if (thecnt > 2)
  {
    if (thelst)
      Sprintf(lb, "Sent at least %d times entities", thecnt);
    else
      Sprintf(lb, "Sent just %d times entities", thecnt);
    lab.AssignCat(lb);
  }
  return lab;
}
