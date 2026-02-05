#include <TDataStd_Expression.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDataStd_Variable.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_Expression, TDF_Attribute)

//=================================================================================================

const Standard_GUID& TDataStd_Expression::GetID()
{
  static Standard_GUID TDataStd_ExpressionID("ce24146a-8e57-11d1-8953-080009dc4425");
  return TDataStd_ExpressionID;
}

//=================================================================================================

occ::handle<TDataStd_Expression> TDataStd_Expression::Set(const TDF_Label& L)
{
  occ::handle<TDataStd_Expression> A;
  if (!L.FindAttribute(TDataStd_Expression::GetID(), A))
  {
    A = new TDataStd_Expression();
    L.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

TDataStd_Expression::TDataStd_Expression() = default;

//=================================================================================================

TCollection_ExtendedString TDataStd_Expression::Name() const
{
  return myExpression; // ->String();
}

//=================================================================================================

void TDataStd_Expression::SetExpression(const TCollection_ExtendedString& E)
{
  // OCC2932 correction
  if (myExpression == E)
    return;

  Backup();
  myExpression = E;
}

//=================================================================================================

const TCollection_ExtendedString& TDataStd_Expression::GetExpression() const
{
  return myExpression;
}

//=================================================================================================

NCollection_List<occ::handle<TDF_Attribute>>& TDataStd_Expression::GetVariables()
{
  return myVariables;
}

//=================================================================================================

const Standard_GUID& TDataStd_Expression::ID() const
{
  return GetID();
}

//=================================================================================================

void TDataStd_Expression::Restore(const occ::handle<TDF_Attribute>& With)
{
  occ::handle<TDataStd_Expression> EXPR = occ::down_cast<TDataStd_Expression>(With);
  myExpression                          = EXPR->GetExpression();

  occ::handle<TDataStd_Variable> V;
  myVariables.Clear();
  for (NCollection_List<occ::handle<TDF_Attribute>>::Iterator it(EXPR->GetVariables()); it.More();
       it.Next())
  {
    V = occ::down_cast<TDataStd_Variable>(it.Value());
    myVariables.Append(V);
  }
}

//=================================================================================================

occ::handle<TDF_Attribute> TDataStd_Expression::NewEmpty() const
{
  return new TDataStd_Expression();
}

//=================================================================================================

void TDataStd_Expression::Paste(const occ::handle<TDF_Attribute>&       Into,
                                const occ::handle<TDF_RelocationTable>& RT) const
{
  occ::handle<TDataStd_Expression> EXPR = occ::down_cast<TDataStd_Expression>(Into);
  EXPR->SetExpression(myExpression);
  occ::handle<TDataStd_Variable> V1;
  for (NCollection_List<occ::handle<TDF_Attribute>>::Iterator it(myVariables); it.More(); it.Next())
  {
    V1 = occ::down_cast<TDataStd_Variable>(it.Value());
    occ::handle<TDF_Attribute> V2;
    RT->HasRelocation(V1, V2);
    EXPR->GetVariables().Append(V2);
  }
}

//=================================================================================================

Standard_OStream& TDataStd_Expression::Dump(Standard_OStream& anOS) const
{
  anOS << "Expression";
  return anOS;
}

//=================================================================================================

void TDataStd_Expression::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myExpression)

  for (NCollection_List<occ::handle<TDF_Attribute>>::Iterator aVariableIt(myVariables);
       aVariableIt.More();
       aVariableIt.Next())
  {
    const occ::handle<TDF_Attribute>& anAttribute = aVariableIt.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, anAttribute.get())
  }
}
