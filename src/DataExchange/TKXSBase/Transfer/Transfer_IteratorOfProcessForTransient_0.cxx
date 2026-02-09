#include <Transfer_IteratorOfProcessForTransient.hpp>

#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>
#include <Transfer_ProcessForTransient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_ActorOfProcessForTransient.hpp>

Transfer_IteratorOfProcessForTransient::Transfer_IteratorOfProcessForTransient(
  const bool withstarts)

{
  if (withstarts)
    thestarts = new NCollection_HSequence<occ::handle<Standard_Transient>>();
}

void Transfer_IteratorOfProcessForTransient::Add(const occ::handle<Transfer_Binder>& binder)
{
  if (!thestarts.IsNull())
    throw Standard_NoSuchObject(
      "Transfer_IteratorOfProcessForTransient : Add, Starting Object required not provided");
  AddItem(binder);
}

void Transfer_IteratorOfProcessForTransient::Add(const occ::handle<Transfer_Binder>&    binder,
                                                 const occ::handle<Standard_Transient>& start)
{
  AddItem(binder);
  if (!thestarts.IsNull())
    thestarts->Append(start);
}

void Transfer_IteratorOfProcessForTransient::Filter(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
  const bool                                                                 keep)
{
  if (list.IsNull() || thestarts.IsNull())
    return;
  int i, j, nb = thestarts->Length();
  if (nb == 0)
    return;
  occ::handle<Transfer_Binder>                                                              factice;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Transfer_Binder>> amap(
    nb);
  for (i = 1; i <= nb; i++)
  {
    j = amap.Add(thestarts->Value(i), factice);
    SelectItem(j, !keep);
  }

  nb = list->Length();
  for (i = 1; i <= nb; i++)
  {
    j = amap.FindIndex(list->Value(i));
    if (j > 0)
      SelectItem(j, keep);
  }
}

bool Transfer_IteratorOfProcessForTransient::HasStarting() const
{
  return (!thestarts.IsNull());
}

const occ::handle<Standard_Transient>& Transfer_IteratorOfProcessForTransient::Starting() const
{
  if (thestarts.IsNull())
    throw Standard_NoSuchObject("TransferIterator : No Starting defined at all");
  return thestarts->Value(thecurr);
}
