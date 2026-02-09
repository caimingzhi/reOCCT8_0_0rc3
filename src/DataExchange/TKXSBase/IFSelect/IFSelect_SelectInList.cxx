

#include <IFSelect_SelectInList.hpp>
#include <Interface_EntityIterator.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectInList, IFSelect_SelectAnyList)

void IFSelect_SelectInList::FillResult(const int                              n1,
                                       const int                              n2,
                                       const occ::handle<Standard_Transient>& ent,
                                       Interface_EntityIterator&              result) const
{
  for (int i = n1; i <= n2; i++)
    result.GetOneItem(ListedEntity(i, ent));
}
