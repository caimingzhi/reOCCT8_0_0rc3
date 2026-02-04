#pragma once


#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
class TFunction_Logbook;

//! This driver class provide services around function
//! execution. One instance of this class is built for
//! the whole session. The driver is bound to the
//! DriverGUID in the DriverTable class.
//! It allows you to create classes which inherit from
//! this abstract class.
//! These subclasses identify the various algorithms
//! which can be applied to the data contained in the
//! attributes of sub-labels of a model.
//! A single instance of this class and each of its
//! subclasses is built for the whole session.
class TFunction_Driver : public Standard_Transient
{

public:
  //! Initializes the label L for this function prior to its execution.
  Standard_EXPORT void Init(const TDF_Label& L);

  //! Returns the label of the driver for this function.
  TDF_Label Label() const;

  //! Validates labels of a function in <log>.
  //! This function is the one initialized in this function driver.
  //! Warning
  //! In regeneration mode, the solver must call this
  //! method even if the function is not executed.
  //! execution of function
  //! =====================
  Standard_EXPORT virtual void Validate(occ::handle<TFunction_Logbook>& log) const;

  //! Analyzes the labels in the logbook log.
  //! Returns true if attributes have been modified.
  //! If the function label itself has been modified, the function must be executed.
  Standard_EXPORT virtual bool MustExecute(const occ::handle<TFunction_Logbook>& log) const;

  //! Executes the function in this function driver and
  //! puts the impacted labels in the logbook log.
  //! arguments & results of functions
  //! ================================
  Standard_EXPORT virtual int Execute(occ::handle<TFunction_Logbook>& log) const = 0;

  //! The method fills-in the list by labels,
  //! where the arguments of the function are located.
  Standard_EXPORT virtual void Arguments(NCollection_List<TDF_Label>& args) const;

  //! The method fills-in the list by labels,
  //! where the results of the function are located.
  Standard_EXPORT virtual void Results(NCollection_List<TDF_Label>& res) const;

  DEFINE_STANDARD_RTTIEXT(TFunction_Driver, Standard_Transient)

protected:
  //! initialisation of the driver
  //! ============================
  Standard_EXPORT TFunction_Driver();

private:
  TDF_Label myLabel;
};
// Created on: 1999-09-28
// Created by: Vladislav ROMASHKO
// Copyright (c) 1999-1999 Matra Datavision
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

//=======================================================================
// function : Label
// purpose  : Returns the initialized label
//=======================================================================

inline TDF_Label TFunction_Driver::Label() const
{
  return myLabel;
}


