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

class TDataStd_NoteBook : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static bool Find(const TDF_Label& current, occ::handle<TDataStd_NoteBook>& N);

  Standard_EXPORT static occ::handle<TDataStd_NoteBook> New(const TDF_Label& label);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDataStd_NoteBook();

  Standard_EXPORT occ::handle<TDataStd_Real> Append(const double value,
                                                    const bool   isExported = false);

  Standard_EXPORT occ::handle<TDataStd_Integer> Append(const int  value,
                                                       const bool isExported = false);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_NoteBook, TDataStd_GenericEmpty)
};
