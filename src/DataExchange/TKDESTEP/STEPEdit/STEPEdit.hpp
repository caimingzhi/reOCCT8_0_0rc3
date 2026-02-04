#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Interface_Protocol;
class StepData_StepModel;
class IFSelect_Signature;
class IFSelect_SelectSignature;

//! Provides tools to exploit and edit a set of STEP data :
//! editors, selections ..
class STEPEdit
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a Protocol fit for STEP (creates the first time)
  Standard_EXPORT static occ::handle<Interface_Protocol> Protocol();

  //! Returns a new empty StepModel fit for STEP
  //! i.e. with its header determined from Protocol
  Standard_EXPORT static occ::handle<StepData_StepModel> NewModel();

  //! Returns a SignType fit for STEP (creates the first time)
  Standard_EXPORT static occ::handle<IFSelect_Signature> SignType();

  //! Creates a Selection for ShapeDefinitionRepresentation
  //! By default searches among root entities
  Standard_EXPORT static occ::handle<IFSelect_SelectSignature> NewSelectSDR();

  //! Creates a Selection for Placed Items, i.e. MappedItem or
  //! ContextDependentShapeRepresentation, which itself refers to a
  //! RepresentationRelationship with possible subtypes (Shape...
  //! and/or ...WithTransformation)
  //! By default in the whole StepModel
  Standard_EXPORT static occ::handle<IFSelect_SelectSignature> NewSelectPlacedItem();

  //! Creates a Selection for ShapeRepresentation and its sub-types,
  //! plus ContextDependentShapeRepresentation (which is not a
  //! sub-type of ShapeRepresentation)
  //! By default in the whole StepModel
  Standard_EXPORT static occ::handle<IFSelect_SelectSignature> NewSelectShapeRepr();
};

