

#include <TCollection_AsciiString.hpp>
#include <Resource_LexicalCompare.hpp>

System::resource::Resource_LexicalCompare::Resource_LexicalCompare() = default;

bool System::resource::Resource_LexicalCompare::IsLower(const TCollection_AsciiString& Left,
                                      const TCollection_AsciiString& Right) const
{
  return Left.IsLess(Right);
}
