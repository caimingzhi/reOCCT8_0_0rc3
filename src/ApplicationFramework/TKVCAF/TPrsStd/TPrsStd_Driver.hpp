#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TDF_Label;
class AIS_InteractiveObject;

//! Driver for AIS
//! ==============
//! An abstract class, which - in classes inheriting
//! from it - allows you to update an
//! AIS_InteractiveObject or create one if one does
//! not already exist.
//! For both creation and update, the interactive
//! object is filled with information contained in
//! attributes. These attributes are those found on
//! the label given as an argument in the method Update.
//! true is returned if the interactive object was modified by the update.
//! This class provide an algorithm to Build with its default
//! values (if Null) or Update (if !Null) an AIS_InteractiveObject.
//! Resources are found in attributes associated to a given
//! label.
class TPrsStd_Driver : public Standard_Transient
{

public:
  //! Updates the interactive object ais with
  //! information found on the attributes associated with the label L.
  Standard_EXPORT virtual bool Update(const TDF_Label&                    L,
                                      occ::handle<AIS_InteractiveObject>& ais) = 0;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_Driver, Standard_Transient)

protected:
  Standard_EXPORT TPrsStd_Driver();
};

