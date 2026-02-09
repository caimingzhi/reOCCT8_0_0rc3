#pragma once

#include <OpenGl_Structure.hpp>

class OpenGl_StructureShadow : public OpenGl_Structure
{

public:
  Standard_EXPORT OpenGl_StructureShadow(const occ::handle<Graphic3d_StructureManager>& theManager,
                                         const occ::handle<OpenGl_Structure>& theStructure);

public:
  Standard_EXPORT void Connect(Graphic3d_CStructure&) override;

  Standard_EXPORT void Disconnect(Graphic3d_CStructure&) override;

private:
  occ::handle<OpenGl_Structure> myParent;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_StructureShadow, OpenGl_Structure)
};
