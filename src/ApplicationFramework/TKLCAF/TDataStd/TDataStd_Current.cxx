#include <TDataStd_Current.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDataStd_Current, TDF_Attribute)

//=================================================================================================

const Standard_GUID& TDataStd_Current::GetID()
{
  static Standard_GUID TDataStd_CurrentID("2a96b623-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_CurrentID;
}

//=================================================================================================

void TDataStd_Current::Set(const TDF_Label& current)
{
  occ::handle<TDataStd_Current> A;
  occ::handle<TDF_Data>         D = current.Data();
  if (!D->Root().FindAttribute(TDataStd_Current::GetID(), A))
  {
    A = new TDataStd_Current();
    D->Root().AddAttribute(A);
  }
  A->SetLabel(current);
}

//=================================================================================================

TDF_Label TDataStd_Current::Get(const TDF_Label& access)
{
  //  TDF_Label current;
  occ::handle<TDataStd_Current> A;
  if (!access.Data()->Root().FindAttribute(TDataStd_Current::GetID(), A))
  {
    throw Standard_DomainError("TDataStd_Current::Get : not set");
  }
  return A->GetLabel();
}

//=================================================================================================

bool TDataStd_Current::Has(const TDF_Label& access)
{
  return (access.Data()->Root().IsAttribute(TDataStd_Current::GetID()));
}

//=================================================================================================

TDataStd_Current::TDataStd_Current() = default;

//=================================================================================================

void TDataStd_Current::SetLabel(const TDF_Label& current)
{
  // OCC2932 correction
  if (myLabel == current)
    return;

  Backup();
  myLabel = current;
}

//=================================================================================================

TDF_Label TDataStd_Current::GetLabel() const
{
  return myLabel;
}

//=================================================================================================

const Standard_GUID& TDataStd_Current::ID() const
{
  return GetID();
}

//=================================================================================================

occ::handle<TDF_Attribute> TDataStd_Current::NewEmpty() const
{
  return new TDataStd_Current();
}

//=================================================================================================

void TDataStd_Current::Restore(const occ::handle<TDF_Attribute>& With)
{
  myLabel = occ::down_cast<TDataStd_Current>(With)->GetLabel();
}

//=================================================================================================

void TDataStd_Current::Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const
{
  TDF_Label tLab;
  if (!myLabel.IsNull())
  {
    if (!RT->HasRelocation(myLabel, tLab))
      tLab = myLabel;
  }
  occ::down_cast<TDataStd_Current>(Into)->SetLabel(tLab);
}

//=================================================================================================

Standard_OStream& TDataStd_Current::Dump(Standard_OStream& anOS) const
{
  anOS << "Current";
  return anOS;
}

//=================================================================================================

void TDataStd_Current::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, TDF_Attribute)

  TCollection_AsciiString aLabel;
  TDF_Tool::Entry(myLabel, aLabel);
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aLabel)
}
