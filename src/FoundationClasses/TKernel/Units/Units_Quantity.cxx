#include <Units_Operators.hpp>
#include <Units_Quantity.hpp>
#include <Units_Unit.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Units_Quantity, Standard_Transient)

bool Units_Quantity::IsEqual(const char* astring) const
{
  return (Name() == astring);
}

void Units_Quantity::Dump(const int ashift, const int alevel) const
{
  int index;
  std::cout << std::endl;
  for (int i = 0; i < ashift; i++)
    std::cout << "  ";
  std::cout << Name() << std::endl;

  if (alevel > 0)
  {
    for (index = 1; index <= theunitssequence->Length(); index++)
      theunitssequence->Value(index)->Dump(ashift + 1, 0);
  }
}

bool operator==(const occ::handle<Units_Quantity>& aquantity, const char* astring)
{
  return aquantity->IsEqual(astring);
}
