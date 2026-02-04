#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_TessellatedStructuredItem.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_ConnectedFaceSet.hpp>

//! Representation of STEP entity TessellatedShell
class StepVisual_TessellatedShell : public StepVisual_TessellatedItem
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedShell();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
                                                   theItems,
    const bool                                     theHasTopologicalLink,
    const occ::handle<StepShape_ConnectedFaceSet>& theTopologicalLink);

  //! Returns field Items
  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>
    Items() const;

  //! Sets field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
      theItems);

  //! Returns number of Items
  Standard_EXPORT int NbItems() const;

  //! Returns value of Items by its num
  Standard_EXPORT occ::handle<StepVisual_TessellatedStructuredItem> ItemsValue(
    const int theNum) const;

  //! Returns field TopologicalLink
  Standard_EXPORT occ::handle<StepShape_ConnectedFaceSet> TopologicalLink() const;

  //! Sets field TopologicalLink
  Standard_EXPORT void SetTopologicalLink(
    const occ::handle<StepShape_ConnectedFaceSet>& theTopologicalLink);

  //! Returns True if optional field TopologicalLink is defined
  Standard_EXPORT bool HasTopologicalLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedShell, StepVisual_TessellatedItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>> myItems;
  occ::handle<StepShape_ConnectedFaceSet> myTopologicalLink; //!< optional
  bool myHasTopologicalLink;                                 //!< flag "is TopologicalLink defined"
};

