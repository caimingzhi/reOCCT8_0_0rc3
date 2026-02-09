#include <TDataStd.hpp>

#include <TDataStd_ExtStringArray.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_IntegerArray.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_Real.hpp>
#include <TDataStd_RealArray.hpp>
#include <TDF_Attribute.hpp>
#include <NCollection_List.hpp>
#include <TDF_Reference.hpp>
#include <TDF_TagSource.hpp>

void TDataStd::IDList(NCollection_List<Standard_GUID>& anIDList)
{
  anIDList.Append(TDF_TagSource::GetID());
  anIDList.Append(TDF_Reference::GetID());
  anIDList.Append(TDataStd_Integer::GetID());
  anIDList.Append(TDataStd_Name::GetID());
  anIDList.Append(TDataStd_Real::GetID());
  anIDList.Append(TDataStd_IntegerArray::GetID());
  anIDList.Append(TDataStd_RealArray::GetID());
  anIDList.Append(TDataStd_ExtStringArray::GetID());
}

Standard_OStream& TDataStd::Print(const TDataStd_RealEnum C, Standard_OStream& s)
{
  switch (C)
  {
    case TDataStd_SCALAR:
    {
      s << "SCALAR";
      break;
    }
    case TDataStd_LENGTH:
    {
      s << "LENGTH";
      break;
    }
    case TDataStd_ANGULAR:
    {
      s << "ANGULAR";
      break;
    }
    default:
    {
      s << "UNKNOWN";
      break;
    }
  }
  return s;
}
