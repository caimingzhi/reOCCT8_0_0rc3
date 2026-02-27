

#include <Storage.hpp>

#include <TCollection_AsciiString.hpp>

TCollection_AsciiString app::storage::Storage::Version()
{
  TCollection_AsciiString v("1.3");

  return v;
}
