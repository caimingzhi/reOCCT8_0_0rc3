#pragma once

#include <TDF_DerivedAttribute.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Standard_GUID.hpp>

class TDF_RelocationTable;

class TDataStd_GenericExtString : public TDF_Attribute
{

public:
  Standard_EXPORT virtual void Set(const TCollection_ExtendedString& S);

  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  Standard_EXPORT virtual const TCollection_ExtendedString& Get() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_GenericExtString, TDF_Attribute)

protected:
  TCollection_ExtendedString myString;

  Standard_GUID myID;
};
