#pragma once

#include <TDataStd_GenericExtString.hpp>

class TDataStd_Comment : public TDataStd_GenericExtString
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_Comment> Set(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataStd_Comment> Set(
    const TDF_Label&                  label,
    const TCollection_ExtendedString& string);

  Standard_EXPORT TDataStd_Comment();

  Standard_EXPORT void Set(const TCollection_ExtendedString& S) override;

  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_Comment, TDataStd_GenericExtString)
};
