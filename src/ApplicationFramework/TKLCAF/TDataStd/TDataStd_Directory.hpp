#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;

class TDataStd_Directory : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static bool Find(const TDF_Label& current, occ::handle<TDataStd_Directory>& D);

  Standard_EXPORT static occ::handle<TDataStd_Directory> New(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataStd_Directory> AddDirectory(
    const occ::handle<TDataStd_Directory>& dir);

  Standard_EXPORT static TDF_Label MakeObjectLabel(const occ::handle<TDataStd_Directory>& dir);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDataStd_Directory();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_Directory, TDataStd_GenericEmpty)
};
