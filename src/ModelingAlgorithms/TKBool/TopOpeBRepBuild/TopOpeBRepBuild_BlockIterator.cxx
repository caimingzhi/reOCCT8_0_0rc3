#include <TopOpeBRepBuild_BlockIterator.hpp>

//=================================================================================================

TopOpeBRepBuild_BlockIterator::TopOpeBRepBuild_BlockIterator()
    : myLower(0),
      myUpper(0),
      myValue(1)
{
}

//=================================================================================================

TopOpeBRepBuild_BlockIterator::TopOpeBRepBuild_BlockIterator(const int Lower, const int Upper)
    : myLower(Lower),
      myUpper(Upper),
      myValue(Lower)
{
}
