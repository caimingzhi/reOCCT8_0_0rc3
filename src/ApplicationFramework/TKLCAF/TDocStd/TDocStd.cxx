

#include <TDocStd.hpp>

#include <TDocStd_XLink.hpp>

void TDocStd::IDList(NCollection_List<Standard_GUID>& anIDList)
{
  anIDList.Append(TDocStd_XLink::GetID());
}
