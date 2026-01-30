// Created on: 1992-04-06
// Created by: Christian CAILLET
// Copyright (c) 1992-1999 Matra Datavision
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

#include <IGESData_FileRecognizer.hpp>

#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_NoSuchObject.hpp>
#include <IGESData_IGESType.hpp>

#define TheKey IGESData_IGESType
#define TheKey_hxx <IGESData_IGESType.hpp>
#define Handle_TheResul occ::handle<IGESData_IGESEntity>
#define TheResul IGESData_IGESEntity
#define TheResul_hxx <IGESData_IGESEntity.hpp>
#define Interface_Recognizer IGESData_FileRecognizer
#define Interface_Recognizer_hxx <IGESData_FileRecognizer.hpp>
#define Handle_Interface_Recognizer occ::handle<IGESData_FileRecognizer>
#include <Interface_Recognizer.hpp>
