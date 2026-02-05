#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;
class TDataStd_Real;
class TDataStd_Integer;

//! NoteBook Object attribute
class TDataStd_NoteBook : public TDataStd_GenericEmpty
{

public:
  //! class methods
  //! =============
  //! try to retrieve a NoteBook attribute at <current> label
  //! or in fathers label of <current>. Returns True if
  //! found and set <N>.
  Standard_EXPORT static bool Find(const TDF_Label& current, occ::handle<TDataStd_NoteBook>& N);

  //! Create an enpty NoteBook attribute, located at
  //! <label>. Raises if <label> has attribute
  Standard_EXPORT static occ::handle<TDataStd_NoteBook> New(const TDF_Label& label);

  //! NoteBook methods
  //! ===============
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDataStd_NoteBook();

  //! Tool to Create an Integer attribute from <value>,
  //! Insert it in a new son label of <me>. The Real
  //! attribute is returned.
  Standard_EXPORT occ::handle<TDataStd_Real> Append(const double value,
                                                    const bool   isExported = false);

  //! Tool to Create an Real attribute from <value>, Insert
  //! it in a new son label of <me>. The Integer attribute
  //! is returned.
  Standard_EXPORT occ::handle<TDataStd_Integer> Append(const int  value,
                                                       const bool isExported = false);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_NoteBook, TDataStd_GenericEmpty)
};
