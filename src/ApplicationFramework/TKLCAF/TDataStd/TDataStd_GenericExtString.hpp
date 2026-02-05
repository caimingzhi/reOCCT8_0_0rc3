#pragma once

#include <TDF_DerivedAttribute.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Standard_GUID.hpp>

class TDF_RelocationTable;

//! An ancestor attribute for all attributes which have TCollection_ExtendedString field.
//! If an attribute inherits this one it should not have drivers for persistence.
//! Also this attribute provides functionality to have on the same label same attributes with
//! different IDs.
class TDataStd_GenericExtString : public TDF_Attribute
{

public:
  //! Sets <S> as name. Raises if <S> is not a valid name.
  Standard_EXPORT virtual void Set(const TCollection_ExtendedString& S);

  //! Sets the explicit user defined GUID to the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  //! Returns the name contained in this name attribute.
  Standard_EXPORT virtual const TCollection_ExtendedString& Get() const;

  //! Returns the ID of the attribute.
  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_GenericExtString, TDF_Attribute)

protected:
  //! A string field of the attribute, participated in persistence.
  TCollection_ExtendedString myString;
  //! A private GUID of the attribute.
  Standard_GUID myID;
};
