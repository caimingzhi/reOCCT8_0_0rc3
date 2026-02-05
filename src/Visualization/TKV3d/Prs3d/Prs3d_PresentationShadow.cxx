#include <Prs3d_PresentationShadow.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Prs3d_PresentationShadow, Graphic3d_Structure)

//=================================================================================================

Prs3d_PresentationShadow::Prs3d_PresentationShadow(
  const occ::handle<Graphic3d_StructureManager>& theViewer,
  const occ::handle<Graphic3d_Structure>&        thePrs)
    : Graphic3d_Structure(theViewer, thePrs),
      myParentAffinity(thePrs->CStructure()->ViewAffinity),
      myParentStructId(thePrs->Identification())
{
}

//=================================================================================================

void Prs3d_PresentationShadow::CalculateBoundBox() {}

//=================================================================================================

void Prs3d_PresentationShadow::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Graphic3d_Structure)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myParentAffinity.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myParentStructId)
}
