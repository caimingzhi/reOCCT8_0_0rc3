#pragma once

#include <Prs3d_Presentation.hpp>

//! Defines a "shadow" of existing presentation object with custom aspects.
class Prs3d_PresentationShadow : public Graphic3d_Structure
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_PresentationShadow, Graphic3d_Structure)
public:
  //! Constructs a shadow of existing presentation object.
  Standard_EXPORT Prs3d_PresentationShadow(const occ::handle<Graphic3d_StructureManager>& theViewer,
                                           const occ::handle<Graphic3d_Structure>&        thePrs);

  //! Returns the id of the parent presentation
  inline int ParentId() const { return myParentStructId; }

  //! Returns view affinity of the parent presentation
  inline const occ::handle<Graphic3d_ViewAffinity>& ParentAffinity() const
  {
    return myParentAffinity;
  }

  //! Do nothing - axis-aligned bounding box should be initialized from parent structure.
  Standard_EXPORT void CalculateBoundBox() override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  occ::handle<Graphic3d_ViewAffinity> myParentAffinity;
  int                                 myParentStructId;
};
