#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Interface_Protocol;
class StepData_StepModel;
class IFSelect_Signature;
class IFSelect_SelectSignature;

class STEPEdit
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Interface_Protocol> Protocol();

  Standard_EXPORT static occ::handle<StepData_StepModel> NewModel();

  Standard_EXPORT static occ::handle<IFSelect_Signature> SignType();

  Standard_EXPORT static occ::handle<IFSelect_SelectSignature> NewSelectSDR();

  Standard_EXPORT static occ::handle<IFSelect_SelectSignature> NewSelectPlacedItem();

  Standard_EXPORT static occ::handle<IFSelect_SelectSignature> NewSelectShapeRepr();
};
