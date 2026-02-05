#pragma once

#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_List.hpp>
#include <TDF_DerivedAttribute.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;

//! Expression attribute.
//! ====================
//!
//! * Data Structure of the Expression is stored in a
//! string and references to variables used by the string
//!
//! Warning: To be consistent, each Variable referenced by the
//! expression must have its equivalent in the string
class TDataStd_Expression : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Find, or create, an Expression attribute.
  //! Expressionmethods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_Expression> Set(const TDF_Label& label);

  Standard_EXPORT TDataStd_Expression();

  //! build and return the expression name
  Standard_EXPORT TCollection_ExtendedString Name() const;

  Standard_EXPORT void SetExpression(const TCollection_ExtendedString& E);

  Standard_EXPORT const TCollection_ExtendedString& GetExpression() const;

  Standard_EXPORT NCollection_List<occ::handle<TDF_Attribute>>& GetVariables();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_Expression, TDF_Attribute)

protected:
  TCollection_ExtendedString                   myExpression;
  NCollection_List<occ::handle<TDF_Attribute>> myVariables;
};
