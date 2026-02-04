#pragma once


#include <TDataStd_GenericExtString.hpp>

//! Comment attribute. may be associated to any label
//! to store user comment.
class TDataStd_Comment : public TDataStd_GenericExtString
{

public:
  //! class methods
  //! =============
  //! Returns the GUID for comments.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Find, or create a Comment attribute. the Comment
  //! attribute is returned.
  Standard_EXPORT static occ::handle<TDataStd_Comment> Set(const TDF_Label& label);

  //! Finds, or creates a Comment attribute and sets the string.
  //! the Comment attribute is returned.
  //! Comment methods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_Comment> Set(
    const TDF_Label&                  label,
    const TCollection_ExtendedString& string);

  Standard_EXPORT TDataStd_Comment();

  Standard_EXPORT void Set(const TCollection_ExtendedString& S) override;

  //! Sets the explicit user defined GUID to the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  //! Sets default GUID for the attribute.
  Standard_EXPORT void SetID() override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_Comment, TDataStd_GenericExtString)
};

