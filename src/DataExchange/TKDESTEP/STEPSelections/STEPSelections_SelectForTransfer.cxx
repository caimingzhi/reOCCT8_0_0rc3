

#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <STEPSelections_SelectForTransfer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_TransientProcess.hpp>
#include <XSControl_TransferReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_SelectForTransfer, XSControl_SelectForTransfer)

STEPSelections_SelectForTransfer::STEPSelections_SelectForTransfer() = default;

STEPSelections_SelectForTransfer::STEPSelections_SelectForTransfer(
  const occ::handle<XSControl_TransferReader>& TR)
{
  SetReader(TR);
}

Interface_EntityIterator STEPSelections_SelectForTransfer::RootResult(const Interface_Graph&) const
{
  Interface_EntityIterator                                            iter;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> roots =
    Reader()->TransientProcess()->RootsForTransfer();
  int nb = roots->Length();
  for (int i = 1; i <= nb; i++)
    iter.GetOneItem(roots->Value(i));
  return iter;
}
