#include <DDF_AttributeBrowser.hpp>

static DDF_AttributeBrowser* DDF_FirstBrowser = nullptr;

//=================================================================================================

DDF_AttributeBrowser::DDF_AttributeBrowser(
  bool (*test)(const occ::handle<TDF_Attribute>&),
  TCollection_AsciiString (*open)(const occ::handle<TDF_Attribute>&),
  TCollection_AsciiString (*text)(const occ::handle<TDF_Attribute>&))
    : myTest(test),
      myOpen(open),
      myText(text),
      myNext(DDF_FirstBrowser)
{
  DDF_FirstBrowser = this;
}

//=================================================================================================

bool DDF_AttributeBrowser::Test(const occ::handle<TDF_Attribute>& anAtt) const
{
  return (*myTest)(anAtt);
}

//=================================================================================================

TCollection_AsciiString DDF_AttributeBrowser::Open(const occ::handle<TDF_Attribute>& anAtt) const
{
  return (*myOpen)(anAtt);
}

//=================================================================================================

TCollection_AsciiString DDF_AttributeBrowser::Text(const occ::handle<TDF_Attribute>& anAtt) const
{
  return (*myText)(anAtt);
}

//=================================================================================================

DDF_AttributeBrowser* DDF_AttributeBrowser::FindBrowser(const occ::handle<TDF_Attribute>& anAtt)
{
  DDF_AttributeBrowser* browser = DDF_FirstBrowser;
  while (browser)
  {
    if (browser->Test(anAtt))
      break;
    browser = browser->Next();
  }
  return browser;
}
