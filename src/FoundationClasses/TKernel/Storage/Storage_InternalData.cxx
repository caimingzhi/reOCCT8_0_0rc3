

#include <Storage_InternalData.hpp>
#include <Storage_Schema.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_InternalData, Standard_Transient)

app::storage::Storage_InternalData::Storage_InternalData()
    : myObjId(1),
      myTypeId(1)
{
}

void app::storage::Storage_InternalData::Clear()
{
  myTypeId = 1;
  myObjId  = 1;
  myReadArray.Nullify();
  myPtoA.Clear();
  myTypeBinding.Clear();
}
