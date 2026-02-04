#pragma once


#include <TDataStd_Expression.hpp>

//! Relation attribute.
//! ==================
//!
//! * Data Structure of the Expression is stored in a
//! string and references to variables used by the string
//!
//! Warning: To be consistent, each Variable referenced by the
//! relation must have its equivalent in the string
class TDataStd_Relation : public TDataStd_Expression
{

public:
  //! class methods
  //! =============
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Find, or create, an Relation attribute.
  //! Real methods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_Relation> Set(const TDF_Label& label);

  Standard_EXPORT TDataStd_Relation();

  Standard_EXPORT void SetRelation(const TCollection_ExtendedString& E);

  Standard_EXPORT const TCollection_ExtendedString& GetRelation() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_Relation, TDataStd_Expression)
};

