#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_SelectInt.hpp>
#include <Standard_Integer.hpp>
// Created on: 1995-12-01
// Created by: EXPRESS->CDL V0.2 Translator
// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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


enum StepVisual_MarkerType
{
  StepVisual_mtDot,
  StepVisual_mtX,
  StepVisual_mtPlus,
  StepVisual_mtAsterisk,
  StepVisual_mtRing,
  StepVisual_mtSquare,
  StepVisual_mtTriangle
};



//! Defines MarkerType as unique member of MarkerSelect
//! Works with an EnumTool
class StepVisual_MarkerMember : public StepData_SelectInt
{

public:
  Standard_EXPORT StepVisual_MarkerMember();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  Standard_EXPORT const char* EnumText() const override;

  Standard_EXPORT void SetEnumText(const int val, const char* text) override;

  Standard_EXPORT void SetValue(const StepVisual_MarkerType val);

  Standard_EXPORT StepVisual_MarkerType Value() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_MarkerMember, StepData_SelectInt)
};

