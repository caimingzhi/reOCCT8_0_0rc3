#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_DerivedAttribute.hpp>

class TDF_RelocationTable;

//! An ancestor attribute for all attributes which have no fields.
//! If an attribute inherits this one it should not have drivers for persistence.
class TDataStd_GenericEmpty : public TDF_Attribute
{

public:
  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>&) override {};

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&,
                             const occ::handle<TDF_RelocationTable>&) const override
  {
  }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_GenericEmpty, TDF_Attribute)
};
