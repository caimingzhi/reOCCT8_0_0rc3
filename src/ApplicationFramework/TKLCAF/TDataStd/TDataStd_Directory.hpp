#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;

//! Associates a directory in the data framework with
//! a TDataStd_TagSource attribute.
//! You can create a new directory label and add
//! sub-directory or object labels to it,
class TDataStd_Directory : public TDataStd_GenericEmpty
{

public:
  //! class methods
  //! =============
  //! Searches for a directory attribute on the label
  //! current, or on one of the father labels of current.
  //! If a directory attribute is found, true is returned,
  //! and the attribute found is set as D.
  Standard_EXPORT static bool Find(const TDF_Label& current, occ::handle<TDataStd_Directory>& D);

  //! Creates an empty Directory attribute, located at
  //! <label>. Raises if <label> has attribute
  Standard_EXPORT static occ::handle<TDataStd_Directory> New(const TDF_Label& label);

  //! Creates a new sub-label and sets the
  //! sub-directory dir on that label.
  Standard_EXPORT static occ::handle<TDataStd_Directory> AddDirectory(
    const occ::handle<TDataStd_Directory>& dir);

  //! Makes new label and returns it to insert
  //! other object attributes (sketch,part...etc...)
  Standard_EXPORT static TDF_Label MakeObjectLabel(const occ::handle<TDataStd_Directory>& dir);

  //! Directory methods
  //! ===============
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDataStd_Directory();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_Directory, TDataStd_GenericEmpty)
};
