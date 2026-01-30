// Created on: 1993-09-28
// Created by: Bruno DUMORTIER
// Copyright (c) 1993-1999 Matra Datavision
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

#include <GeomFill_AppSweep.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <GeomFill_SweepSectionGenerator.hpp>
#include <GeomFill_Line.hpp>

#define TheSectionGenerator GeomFill_SweepSectionGenerator
#define TheSectionGenerator_hxx <GeomFill_SweepSectionGenerator.hpp>
#define Handle_TheLine occ::handle<GeomFill_Line>
#define TheLine GeomFill_Line
#define TheLine_hxx <GeomFill_Line.hpp>
#define AppBlend_AppSurf GeomFill_AppSweep
#define AppBlend_AppSurf_hxx <GeomFill_AppSweep.hpp>
#include <AppBlend_AppSurf.hpp>
