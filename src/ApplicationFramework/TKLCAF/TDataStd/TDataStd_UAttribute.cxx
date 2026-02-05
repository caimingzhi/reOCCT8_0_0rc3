#include <TDataStd_UAttribute.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDataStd.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_UAttribute, TDF_Attribute)

//=================================================================================================

occ::handle<TDataStd_UAttribute> TDataStd_UAttribute::Set(const TDF_Label&     label,
                                                          const Standard_GUID& guid)
{
  occ::handle<TDataStd_UAttribute> A;
  if (!label.FindAttribute(guid, A))
  {
    A = new TDataStd_UAttribute();
    A->SetID(guid);
    label.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

TDataStd_UAttribute::TDataStd_UAttribute() = default;

//=================================================================================================

const Standard_GUID& TDataStd_UAttribute::ID() const
{
  return myID;
}

//=================================================================================================

void TDataStd_UAttribute::SetID(const Standard_GUID& guid)
{
  // OCC2932 correction
  if (myID == guid)
    return;

  Backup();
  myID = guid;
}

//=================================================================================================

occ::handle<TDF_Attribute> TDataStd_UAttribute::NewEmpty() const
{
  occ::handle<TDataStd_UAttribute> A = new TDataStd_UAttribute();
  A->SetID(myID);
  return A;
}

//=================================================================================================

void TDataStd_UAttribute::Restore(const occ::handle<TDF_Attribute>& with)
{
  occ::handle<TDataStd_UAttribute> A = occ::down_cast<TDataStd_UAttribute>(with);
  SetID(A->ID());
}

//=================================================================================================

void TDataStd_UAttribute::Paste(const occ::handle<TDF_Attribute>& into,
                                const occ::handle<TDF_RelocationTable>& /*RT*/) const
{
  occ::handle<TDataStd_UAttribute> A = occ::down_cast<TDataStd_UAttribute>(into);
  A->SetID(myID);
}

//=================================================================================================

void TDataStd_UAttribute::References(const occ::handle<TDF_DataSet>& /*DS*/) const {}

//=================================================================================================

Standard_OStream& TDataStd_UAttribute::Dump(Standard_OStream& anOS) const
{
  anOS << "UAttribute";
  TDF_Attribute::Dump(anOS);
  return anOS;
}

//=================================================================================================

void TDataStd_UAttribute::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_GUID(theOStream, myID)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)
}
