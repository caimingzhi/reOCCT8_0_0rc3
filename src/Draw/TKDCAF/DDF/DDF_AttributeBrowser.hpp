#pragma once

#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>

class DDF_AttributeBrowser
{

public:
  Standard_EXPORT DDF_AttributeBrowser(
    bool (*test)(const occ::handle<TDF_Attribute>&),
    TCollection_AsciiString (*open)(const occ::handle<TDF_Attribute>&),
    TCollection_AsciiString (*text)(const occ::handle<TDF_Attribute>&));

  bool                    Test(const occ::handle<TDF_Attribute>& anAtt) const;
  TCollection_AsciiString Open(const occ::handle<TDF_Attribute>& anAtt) const;
  TCollection_AsciiString Text(const occ::handle<TDF_Attribute>& anAtt) const;

  inline DDF_AttributeBrowser* Next() { return myNext; }

  static DDF_AttributeBrowser* FindBrowser(const occ::handle<TDF_Attribute>& anAtt);

private:
  bool (*myTest)(const occ::handle<TDF_Attribute>&);

  TCollection_AsciiString (*myOpen)(const occ::handle<TDF_Attribute>&);

  TCollection_AsciiString (*myText)(const occ::handle<TDF_Attribute>&);

  DDF_AttributeBrowser* myNext;
};
