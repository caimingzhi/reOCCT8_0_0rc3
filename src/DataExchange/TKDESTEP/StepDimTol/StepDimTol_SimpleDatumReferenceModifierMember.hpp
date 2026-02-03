// Created on: 2015-07-16
// Created by: Irina KRYLOVA
// Copyright (c) 2015 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _StepDimTol_SimpleDatumReferenceModifierMember_HeaderFile
#define _StepDimTol_SimpleDatumReferenceModifierMember_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_SelectInt.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
// Created on: 2015-07-14
// Created by: Irina KRYLOVA
// Copyright (c) 2015 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _StepDimTol_SimpleDatumReferenceModifier_HeaderFile
#define _StepDimTol_SimpleDatumReferenceModifier_HeaderFile

enum StepDimTol_SimpleDatumReferenceModifier
{
  StepDimTol_SDRMAnyCrossSection,
  StepDimTol_SDRMAnyLongitudinalSection,
  StepDimTol_SDRMBasic,
  StepDimTol_SDRMContactingFeature,
  StepDimTol_SDRMDegreeOfFreedomConstraintU,
  StepDimTol_SDRMDegreeOfFreedomConstraintV,
  StepDimTol_SDRMDegreeOfFreedomConstraintW,
  StepDimTol_SDRMDegreeOfFreedomConstraintX,
  StepDimTol_SDRMDegreeOfFreedomConstraintY,
  StepDimTol_SDRMDegreeOfFreedomConstraintZ,
  StepDimTol_SDRMDistanceVariable,
  StepDimTol_SDRMFreeState,
  StepDimTol_SDRMLeastMaterialRequirement,
  StepDimTol_SDRMLine,
  StepDimTol_SDRMMajorDiameter,
  StepDimTol_SDRMMaximumMaterialRequirement,
  StepDimTol_SDRMMinorDiameter,
  StepDimTol_SDRMOrientation,
  StepDimTol_SDRMPitchDiameter,
  StepDimTol_SDRMPlane,
  StepDimTol_SDRMPoint,
  StepDimTol_SDRMTranslation
};

#endif


//! Defines SimpleDatumReferenceModifier as unique member of DatumReferenceModifier
//! Works with an EnumTool
class StepDimTol_SimpleDatumReferenceModifierMember : public StepData_SelectInt
{

public:
  Standard_EXPORT StepDimTol_SimpleDatumReferenceModifierMember();

  bool HasName() const override { return true; }

  const char* Name() const override { return "SIMPLE_DATUM_REFERENCE_MODIFIER"; }

  bool SetName(const char* /*theName*/) override { return true; }

  int Kind() const override { return 4; }

  Standard_EXPORT const char* EnumText() const override;

  Standard_EXPORT void SetEnumText(const int theValue, const char* theText) override;

  Standard_EXPORT void SetValue(const StepDimTol_SimpleDatumReferenceModifier theValue);

  Standard_EXPORT StepDimTol_SimpleDatumReferenceModifier Value() const;

  DEFINE_STANDARD_RTTIEXT(StepDimTol_SimpleDatumReferenceModifierMember, StepData_SelectInt)
};
#endif // _StepDimTol_SimpleDatumReferenceModifierMember_HeaderFile
