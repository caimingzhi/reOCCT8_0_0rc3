#include <TDataStd_Relation.hpp>

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

IMPLEMENT_DERIVED_ATTRIBUTE(TDataStd_Relation, TDataStd_Expression)

//=================================================================================================

const Standard_GUID& TDataStd_Relation::GetID()
{
  static Standard_GUID TDataStd_RelationID("ce24146b-8e57-11d1-8953-080009dc4425");
  return TDataStd_RelationID;
}

//=================================================================================================

occ::handle<TDataStd_Relation> TDataStd_Relation::Set(const TDF_Label& L)
{
  occ::handle<TDataStd_Relation> A;
  if (!L.FindAttribute(TDataStd_Relation::GetID(), A))
  {
    A = new TDataStd_Relation();
    L.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

TDataStd_Relation::TDataStd_Relation() = default;

//=================================================================================================

void TDataStd_Relation::SetRelation(const TCollection_ExtendedString& R)
{
  SetExpression(R);
}

//=================================================================================================

const TCollection_ExtendedString& TDataStd_Relation::GetRelation() const
{
  return GetExpression();
}

//=================================================================================================

const Standard_GUID& TDataStd_Relation::ID() const
{
  return GetID();
}

//=================================================================================================

Standard_OStream& TDataStd_Relation::Dump(Standard_OStream& anOS) const
{
  anOS << "Relation";
  return anOS;
}

//=================================================================================================

void TDataStd_Relation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, GetRelation())

  for (NCollection_List<occ::handle<TDF_Attribute>>::Iterator aVariableIt(myVariables);
       aVariableIt.More();
       aVariableIt.Next())
  {
    const occ::handle<TDF_Attribute>& aVariable = aVariableIt.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aVariable.get())
  }
}
