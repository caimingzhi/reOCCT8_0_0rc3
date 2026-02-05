#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Dispatch.hpp>
class IGESSelect_ViewSorter;
class TCollection_AsciiString;
class Interface_Graph;
class IFGraph_SubPartsIterator;
class Interface_EntityIterator;

//! This type of dispatch defines sets of entities attached to
//! distinct single views. This information appears in the
//! Directory Part. Drawings are taken into account too,
//! because of their frames (proper lists of annotations)
//!
//! Remaining data concern entities not attached to a single view.
class IGESSelect_DispPerSingleView : public IFSelect_Dispatch
{

public:
  //! Creates a DispPerSingleView
  Standard_EXPORT IGESSelect_DispPerSingleView();

  //! Returns as Label, "One File per single View or Drawing Frame"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  //! Computes the list of produced Packets. Packets are computed
  //! by a ViewSorter (SortSingleViews with also frames).
  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  //! Returns True, because of entities attached to no view.
  Standard_EXPORT bool CanHaveRemainder() const override;

  //! Returns Remainder which is a set of Entities.
  //! It is supposed to be called once Packets has been called.
  Standard_EXPORT Interface_EntityIterator Remainder(const Interface_Graph& G) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_DispPerSingleView, IFSelect_Dispatch)

private:
  occ::handle<IGESSelect_ViewSorter> thesorter;
};
