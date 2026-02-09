

#include <TCollection_AsciiString.hpp>
#include <Resource_LexicalCompare.hpp>

Resource_LexicalCompare::Resource_LexicalCompare() = default;

bool Resource_LexicalCompare::IsLower(const TCollection_AsciiString& Left,
                                      const TCollection_AsciiString& Right) const
{
  return Left.IsLess(Right);
}
