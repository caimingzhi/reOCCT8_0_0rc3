// Created on: 2002-12-12
// Created by: data exchange team
// Copyright (c) 2002-2014 OPEN CASCADE SAS
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

#ifndef _StepBasic_EulerAngles_HeaderFile
#define _StepBasic_EulerAngles_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity EulerAngles
class StepBasic_EulerAngles : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_EulerAngles();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<double>>& aAngles);

  //! Returns field Angles
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Angles() const;

  //! Set field Angles
  Standard_EXPORT void SetAngles(const occ::handle<NCollection_HArray1<double>>& Angles);

  DEFINE_STANDARD_RTTIEXT(StepBasic_EulerAngles, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<double>> theAngles;
};

#endif // _StepBasic_EulerAngles_HeaderFile
