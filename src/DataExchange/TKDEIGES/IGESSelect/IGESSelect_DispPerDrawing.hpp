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
//! distinct drawings. This information is taken from attached
//! views which appear in the Directory Part. Also Drawing Frames
//! are considered when Drawings are part of input list.
//!
//! Remaining data concern entities not attached to a drawing.
class IGESSelect_DispPerDrawing : public IFSelect_Dispatch
{

public:
  //! Creates a DispPerDrawing
  Standard_EXPORT IGESSelect_DispPerDrawing();

  //! Returns as Label, "One File per Drawing"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  //! Computes the list of produced Packets. Packets are computed
  //! by a ViewSorter (SortDrawings with also frames).
  Standard_EXPORT void Packets(const Interface_Graph&    G,
                               IFGraph_SubPartsIterator& packs) const override;

  //! Returns True, because of entities attached to no view.
  Standard_EXPORT bool CanHaveRemainder() const override;

  //! Returns Remainder which is a set of Entities.
  //! It is supposed to be called once Packets has been called.
  Standard_EXPORT Interface_EntityIterator Remainder(const Interface_Graph& G) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_DispPerDrawing, IFSelect_Dispatch)

private:
  occ::handle<IGESSelect_ViewSorter> thesorter;
};

