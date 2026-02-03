// Created on: 2016-03-09
// Created by: Irina KRYLOVA
// Copyright (c) 2016 OPEN CASCADE SAS
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

#ifndef _StepVisual_NullStyleMember_HeaderFile
#define _StepVisual_NullStyleMember_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_SelectInt.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
// Created on: 2016-03-09
// Created by: Irina KRYLOVA
// Copyright (c) 2016 OPEN CASCADE SAS
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

#ifndef _StepVisual_NullStyle_HeaderFile
#define _StepVisual_NullStyle_HeaderFile

enum StepVisual_NullStyle
{
  StepVisual_Null
};

#endif


//! Defines NullStyle as unique member of PresentationStyleSelect
//! Works with an EnumTool
class StepVisual_NullStyleMember : public StepData_SelectInt
{

public:
  Standard_EXPORT StepVisual_NullStyleMember();

  bool HasName() const override { return true; }

  const char* Name() const override { return "NULL_STYLE"; }

  bool SetName(const char* /*theName*/) override { return true; }

  int Kind() const override { return 4; }

  Standard_EXPORT const char* EnumText() const override;

  Standard_EXPORT void SetEnumText(const int theValue, const char* theText) override;

  Standard_EXPORT void SetValue(const StepVisual_NullStyle theValue);

  Standard_EXPORT StepVisual_NullStyle Value() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_NullStyleMember, StepData_SelectInt)
};
#endif // _StepVisual_NullStyleMember_HeaderFile
