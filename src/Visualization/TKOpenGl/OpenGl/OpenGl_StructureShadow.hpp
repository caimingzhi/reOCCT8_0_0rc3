#pragma once

#include <OpenGl_Structure.hpp>

//! Dummy structure which just redirects to groups of another structure.
class OpenGl_StructureShadow : public OpenGl_Structure
{

public:
  //! Create empty structure
  Standard_EXPORT OpenGl_StructureShadow(const occ::handle<Graphic3d_StructureManager>& theManager,
                                         const occ::handle<OpenGl_Structure>& theStructure);

public:
  //! Raise exception on API misuse.
  Standard_EXPORT void Connect(Graphic3d_CStructure&) override;

  //! Raise exception on API misuse.
  Standard_EXPORT void Disconnect(Graphic3d_CStructure&) override;

private:
  occ::handle<OpenGl_Structure> myParent;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_StructureShadow, OpenGl_Structure) // Type definition
};
