// Created on: 1994-12-16
// Created by: Frederic MAUPAS
// Copyright (c) 1994-1999 Matra Datavision
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

#ifndef _StepToTopoDS_TranslateVertex_HeaderFile
#define _StepToTopoDS_TranslateVertex_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_TranslateVertexError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
class StepShape_Vertex;
class StepToTopoDS_Tool;
class StepToTopoDS_NMTool;

class StepToTopoDS_TranslateVertex : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_TranslateVertex();

  Standard_EXPORT StepToTopoDS_TranslateVertex(
    const occ::handle<StepShape_Vertex>& V,
    StepToTopoDS_Tool&                   T,
    StepToTopoDS_NMTool&                 NMTool,
    const StepData_Factors&              theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_Vertex>& V,
                            StepToTopoDS_Tool&                   T,
                            StepToTopoDS_NMTool&                 NMTool,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_TranslateVertexError Error() const;

private:
  StepToTopoDS_TranslateVertexError myError;
  TopoDS_Shape                      myResult;
};

#endif // _StepToTopoDS_TranslateVertex_HeaderFile
