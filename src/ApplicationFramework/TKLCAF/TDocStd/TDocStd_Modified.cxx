#include <TDocStd_Modified.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDocStd_Modified, TDF_Attribute)

//=================================================================================================

bool TDocStd_Modified::IsEmpty(const TDF_Label& access)
{
  occ::handle<TDocStd_Modified> MDF;
  if (!access.Root().FindAttribute(TDocStd_Modified::GetID(), MDF))
  {
    return true;
  }
  else
    return MDF->IsEmpty();
}

//=================================================================================================

bool TDocStd_Modified::Add(const TDF_Label& alabel)
{
  occ::handle<TDocStd_Modified> MDF;
  if (!alabel.Root().FindAttribute(TDocStd_Modified::GetID(), MDF))
  {
    MDF = new TDocStd_Modified();
    alabel.Root().AddAttribute(MDF);
  }
  return MDF->AddLabel(alabel);
}

//=================================================================================================

bool TDocStd_Modified::Remove(const TDF_Label& alabel)
{
  occ::handle<TDocStd_Modified> MDF;
  if (!alabel.Root().FindAttribute(TDocStd_Modified::GetID(), MDF))
  {
    return true;
  }
  else
    return MDF->RemoveLabel(alabel);
}

//=================================================================================================

bool TDocStd_Modified::Contains(const TDF_Label& alabel)
{
  occ::handle<TDocStd_Modified> MDF;
  if (!alabel.Root().FindAttribute(TDocStd_Modified::GetID(), MDF))
  {
    return false;
  }
  return (MDF->Get().Contains(alabel));
}

//=================================================================================================

const NCollection_Map<TDF_Label>& TDocStd_Modified::Get(const TDF_Label& access)
{
  occ::handle<TDocStd_Modified> MDF;
  if (!access.Root().FindAttribute(TDocStd_Modified::GetID(), MDF))
  {
    throw Standard_DomainError("TDocStd_Modified::Get : IsEmpty");
  }
  return MDF->Get();
}

//=================================================================================================

void TDocStd_Modified::Clear(const TDF_Label& access)
{
  occ::handle<TDocStd_Modified> MDF;
  if (!access.Root().FindAttribute(TDocStd_Modified::GetID(), MDF))
  {
    return;
  }
  else
    MDF->Clear();
}

//=================================================================================================

const Standard_GUID& TDocStd_Modified::GetID()
{
  static Standard_GUID TDocStd_ModifiedID("2a96b622-ec8b-11d0-bee7-080009dc3333");
  return TDocStd_ModifiedID;
}

//=================================================================================================

TDocStd_Modified::TDocStd_Modified() = default;

//=================================================================================================

bool TDocStd_Modified::AddLabel(const TDF_Label& L)
{
  Backup();
  return myModified.Add(L);
}

//=================================================================================================

bool TDocStd_Modified::RemoveLabel(const TDF_Label& L)
{
  Backup();
  return myModified.Remove(L);
}

//=================================================================================================

bool TDocStd_Modified::IsEmpty() const
{
  return myModified.IsEmpty();
}

//=================================================================================================

void TDocStd_Modified::Clear()
{
  Backup();
  myModified.Clear();
}

//=================================================================================================

const NCollection_Map<TDF_Label>& TDocStd_Modified::Get() const
{
  return myModified;
}

//=================================================================================================

const Standard_GUID& TDocStd_Modified::ID() const
{
  return GetID();
}

//=================================================================================================

occ::handle<TDF_Attribute> TDocStd_Modified::NewEmpty() const
{
  return new TDocStd_Modified();
}

//=================================================================================================

void TDocStd_Modified::Restore(const occ::handle<TDF_Attribute>& With)
{
  occ::handle<TDocStd_Modified> MDF = occ::down_cast<TDocStd_Modified>(With);
  myModified                        = MDF->myModified;
}

//=================================================================================================

void TDocStd_Modified::Paste(const occ::handle<TDF_Attribute>&,
                             const occ::handle<TDF_RelocationTable>&) const
{
}

//=================================================================================================

Standard_OStream& TDocStd_Modified::Dump(Standard_OStream& anOS) const
{
  anOS << "Modified";
  return anOS;
}
