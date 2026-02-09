

#include <StdStorage_Data.hpp>
#include <StdStorage_HeaderData.hpp>
#include <StdStorage_TypeData.hpp>
#include <StdStorage_RootData.hpp>

StdStorage_Data::StdStorage_Data()
    : myHeaderData(new StdStorage_HeaderData),
      myTypeData(new StdStorage_TypeData),
      myRootData(new StdStorage_RootData)
{
}

void StdStorage_Data::Clear()
{
  myTypeData->Clear();
  myRootData->Clear();
}
