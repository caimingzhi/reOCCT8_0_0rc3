#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HelixGeom_BuilderHelixGen.hpp>

class HelixGeom_BuilderHelixCoil : public HelixGeom_BuilderHelixGen
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HelixGeom_BuilderHelixCoil();
  Standard_EXPORT ~HelixGeom_BuilderHelixCoil() override;

  Standard_EXPORT void Perform() override;
};
