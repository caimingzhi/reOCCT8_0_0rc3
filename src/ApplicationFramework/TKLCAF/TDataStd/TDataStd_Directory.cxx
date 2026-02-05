#include <TDataStd_Directory.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>
#include <TDataStd.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TDF_TagSource.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataStd_Directory, TDataStd_GenericEmpty)

//=================================================================================================

bool TDataStd_Directory::Find(const TDF_Label& current, occ::handle<TDataStd_Directory>& D)
{
  TDF_Label                       L = current;
  occ::handle<TDataStd_Directory> dir;
  if (L.IsNull())
    return false;

  for (;;)
  {
    if (L.FindAttribute(TDataStd_Directory::GetID(), dir))
      break;
    L = L.Father();
    if (L.IsNull())
      break;
  }

  if (!dir.IsNull())
  {
    D = dir;
    return true;
  }
  return false;
}

//=================================================================================================

const Standard_GUID& TDataStd_Directory::GetID()
{
  static Standard_GUID TDataStd_DirectoryID("2a96b61f-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_DirectoryID;
}

//=================================================================================================

occ::handle<TDataStd_Directory> TDataStd_Directory::New(const TDF_Label& L)
{
  if (L.HasAttribute())
  {
    throw Standard_DomainError("TDataStd_Directory::New : not an empty label");
  }
  occ::handle<TDataStd_Directory> A = new TDataStd_Directory();
  L.AddAttribute(A);
  TDF_TagSource::Set(L);
  return A;
}

//=================================================================================================

occ::handle<TDataStd_Directory> TDataStd_Directory::AddDirectory(
  const occ::handle<TDataStd_Directory>& dir)
{
  TDF_Label                       newLabel = TDF_TagSource::NewChild(dir->Label());
  occ::handle<TDataStd_Directory> A        = TDataStd_Directory::New(newLabel);
  return A;
}

//=================================================================================================

TDF_Label TDataStd_Directory::MakeObjectLabel(const occ::handle<TDataStd_Directory>& dir)
{
  return TDF_TagSource::NewChild(dir->Label());
}

//=================================================================================================

TDataStd_Directory::TDataStd_Directory() = default;

//=================================================================================================

const Standard_GUID& TDataStd_Directory::ID() const
{
  return GetID();
}

//=================================================================================================

// occ::handle<TDF_Attribute> TDataStd_Directory::NewEmpty () const
//{
//   return new TDataStd_Directory();
// }

//=================================================================================================

Standard_OStream& TDataStd_Directory::Dump(Standard_OStream& anOS) const
{
  anOS << "Directory";
  return anOS;
}
