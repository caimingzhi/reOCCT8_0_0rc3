#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HelixGeom_BuilderHelixGen.hpp>

//! Implementation of algorithm for building helix coil with
//! axis OZ
class HelixGeom_BuilderHelixCoil : public HelixGeom_BuilderHelixGen
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT HelixGeom_BuilderHelixCoil();
  Standard_EXPORT ~HelixGeom_BuilderHelixCoil() override;

  //! Performs calculations
  Standard_EXPORT void Perform() override;
};

