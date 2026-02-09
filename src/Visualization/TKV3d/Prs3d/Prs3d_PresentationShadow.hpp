#pragma once

#include <Prs3d_Presentation.hpp>

class Prs3d_PresentationShadow : public Graphic3d_Structure
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_PresentationShadow, Graphic3d_Structure)
public:
  Standard_EXPORT Prs3d_PresentationShadow(const occ::handle<Graphic3d_StructureManager>& theViewer,
                                           const occ::handle<Graphic3d_Structure>&        thePrs);

  inline int ParentId() const { return myParentStructId; }

  inline const occ::handle<Graphic3d_ViewAffinity>& ParentAffinity() const
  {
    return myParentAffinity;
  }

  Standard_EXPORT void CalculateBoundBox() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  occ::handle<Graphic3d_ViewAffinity> myParentAffinity;
  int                                 myParentStructId;
};
