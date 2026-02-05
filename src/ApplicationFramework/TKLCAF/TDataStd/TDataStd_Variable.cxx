#include <TDataStd_Variable.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDataStd_Expression.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_Variable, TDF_Attribute)

//=================================================================================================

const Standard_GUID& TDataStd_Variable::GetID()
{
  static Standard_GUID TDataStd_VariableID("ce241469-8e57-11d1-8953-080009dc4425");
  return TDataStd_VariableID;
}

//=================================================================================================

occ::handle<TDataStd_Variable> TDataStd_Variable::Set(const TDF_Label& L)
{
  occ::handle<TDataStd_Variable> A;
  if (!L.FindAttribute(TDataStd_Variable::GetID(), A))
  {
    A = new TDataStd_Variable();
    L.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

TDataStd_Variable::TDataStd_Variable()
    : isConstant(false),
      myUnit("SCALAR")
{
}

//=================================================================================================

void TDataStd_Variable::Name(const TCollection_ExtendedString& string)
{
  TDataStd_Name::Set(Label(), string);
}

//=================================================================================================

const TCollection_ExtendedString& TDataStd_Variable::Name() const
{
  occ::handle<TDataStd_Name> N;
  if (!Label().FindAttribute(TDataStd_Name::GetID(), N))
  {
    throw Standard_DomainError("TDataStd_Variable::Name : invalid model");
  }
  return N->Get();
}

//=================================================================================================

bool TDataStd_Variable::IsValued() const
{
  return (Label().IsAttribute(TDataStd_Real::GetID()));
}

//=================================================================================================

occ::handle<TDataStd_Real> TDataStd_Variable::Real() const
{
  occ::handle<TDataStd_Real> R;
  if (!Label().FindAttribute(TDataStd_Real::GetID(), R))
  {
    throw Standard_DomainError("TDataStd_Variable::Real : invalid model");
  }
  return R;
}

//=================================================================================================

void TDataStd_Variable::Set(const double value) const
{
  occ::handle<TDataStd_Real> R = TDataStd_Real::Set(Label(), value);
}

//=================================================================================================

void TDataStd_Variable::Set(const double value, const TDataStd_RealEnum dimension) const
{
  if (!IsValued())
  {
    occ::handle<TDataStd_Real>            R = TDataStd_Real::Set(Label(), value);
    Standard_DISABLE_DEPRECATION_WARNINGS R->SetDimension(dimension);
    Standard_ENABLE_DEPRECATION_WARNINGS
  }
  else
  {
    occ::handle<TDataStd_Real> R = TDataStd_Real::Set(Label(), value);
  }
}

//=================================================================================================

double TDataStd_Variable::Get() const
{
  occ::handle<TDataStd_Real> R;
  if (!Label().FindAttribute(TDataStd_Real::GetID(), R))
  {
    throw Standard_DomainError("TDataStd_Variable::Get : invalid model");
  }
  return R->Get();
}

//=================================================================================================

bool TDataStd_Variable::IsAssigned() const
{
  return (Label().IsAttribute(TDataStd_Expression::GetID()));
}

//=================================================================================================

occ::handle<TDataStd_Expression> TDataStd_Variable::Assign() const
{
  occ::handle<TDataStd_Expression> E = TDataStd_Expression::Set(Label());
  return E;
}

//=================================================================================================

void TDataStd_Variable::Desassign() const
{
  occ::handle<TDataStd_Expression> E;
  if (!Label().FindAttribute(TDataStd_Expression::GetID(), E))
  {
    throw Standard_DomainError("TDataStd_Variable::Deassign");
  }
  Label().ForgetAttribute(E);
}

//=================================================================================================

occ::handle<TDataStd_Expression> TDataStd_Variable::Expression() const
{
  occ::handle<TDataStd_Expression> E;
  if (!Label().FindAttribute(TDataStd_Expression::GetID(), E))
  {
    throw Standard_DomainError("TDataStd_Variable::GetExpression");
  }
  return E;
}

//=================================================================================================

bool TDataStd_Variable::IsCaptured() const
{
  return Real()->IsCaptured();
}

//=================================================================================================

bool TDataStd_Variable::IsConstant() const
{
  return isConstant;
}

//=================================================================================================

void TDataStd_Variable::Constant(const bool status)
{
  // OCC2932 correction
  if (isConstant == status)
    return;

  Backup();
  isConstant = status;
}

//=================================================================================================

void TDataStd_Variable::Unit(const TCollection_AsciiString& unit)
{
  // OCC2932 correction
  if (myUnit == unit)
    return;

  Backup();
  myUnit = unit;
}

//=================================================================================================

const TCollection_AsciiString& TDataStd_Variable::Unit() const
{
  return myUnit;
}

//=================================================================================================

const Standard_GUID& TDataStd_Variable::ID() const
{
  return GetID();
}

//=================================================================================================

void TDataStd_Variable::Restore(const occ::handle<TDF_Attribute>& With)
{
  occ::handle<TDataStd_Variable> V = occ::down_cast<TDataStd_Variable>(With);
  isConstant                       = V->IsConstant();
  myUnit                           = V->Unit();
}

//=================================================================================================

occ::handle<TDF_Attribute> TDataStd_Variable::NewEmpty() const
{
  return new TDataStd_Variable();
}

//=================================================================================================

void TDataStd_Variable::Paste(const occ::handle<TDF_Attribute>& Into,
                              const occ::handle<TDF_RelocationTable>& /*RT*/) const
{
  occ::handle<TDataStd_Variable> V = occ::down_cast<TDataStd_Variable>(Into);
  V->Constant(isConstant);
  V->Unit(myUnit);
}

//=================================================================================================

void TDataStd_Variable::References(const occ::handle<TDF_DataSet>& DS) const
{
  occ::handle<TDataStd_Name> N;
  if (Label().FindAttribute(TDataStd_Name::GetID(), N))
  {
    DS->AddAttribute(N);
  }
}

//=================================================================================================

Standard_OStream& TDataStd_Variable::Dump(Standard_OStream& anOS) const
{
  anOS << "Variable";
  return anOS;
}

//=================================================================================================

void TDataStd_Variable::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, isConstant)
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myUnit)
}
