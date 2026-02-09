#pragma once

#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Real.hpp>
#include <TDataStd_RealEnum.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Label;
class TCollection_ExtendedString;
class TDataStd_Real;
class TDataStd_Expression;
class TDF_RelocationTable;
class TDF_DataSet;

class TDataStd_Variable : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_Variable> Set(const TDF_Label& label);

  Standard_EXPORT TDataStd_Variable();

  Standard_EXPORT void Name(const TCollection_ExtendedString& string);

  Standard_EXPORT const TCollection_ExtendedString& Name() const;

  Standard_EXPORT void Set(const double value) const;

  Standard_DEPRECATED("TDataStd_Variable::Set(value, dimension) is deprecated. Please use "
                      "TDataStd_Variable::Set(value) instead.")
  Standard_EXPORT void Set(const double value, const TDataStd_RealEnum dimension) const;

  Standard_EXPORT bool IsValued() const;

  Standard_EXPORT double Get() const;

  Standard_EXPORT occ::handle<TDataStd_Real> Real() const;

  Standard_EXPORT bool IsAssigned() const;

  Standard_EXPORT occ::handle<TDataStd_Expression> Assign() const;

  Standard_EXPORT void Desassign() const;

  Standard_EXPORT occ::handle<TDataStd_Expression> Expression() const;

  Standard_EXPORT bool IsCaptured() const;

  Standard_EXPORT bool IsConstant() const;

  Standard_EXPORT void Unit(const TCollection_AsciiString& unit);

  Standard_EXPORT const TCollection_AsciiString& Unit() const;

  Standard_EXPORT void Constant(const bool status);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_Variable, TDF_Attribute)

private:
  bool                    isConstant;
  TCollection_AsciiString myUnit;
};
