#include <DDF_AttributeBrowser.hpp>
#include <DDF_Browser.hpp>
#include <Draw_Display.hpp>
#include <Draw_Drawable3D.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDataStd_Name.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DDF_Browser, Draw_Drawable3D)

#define TDF_BrowserSeparator1 '\\'
#define TDF_BrowserSeparator2 ' '
#define TDF_BrowserSeparator3 '#'
#define TDF_BrowserSeparator4 ','

DDF_Browser::DDF_Browser(const occ::handle<TDF_Data>& aDF)
    : myDF(aDF)
{
}

void DDF_Browser::DrawOn(Draw_Display&) const {}

occ::handle<Draw_Drawable3D> DDF_Browser::Copy() const
{
  return new DDF_Browser(myDF);
}

void DDF_Browser::Dump(Standard_OStream& S) const
{
  S << "DDF_Browser on a DF:" << std::endl;
  S << myDF;
}

void DDF_Browser::Whatis(Draw_Interpretor& I) const
{
  I << "Data Framework Browser";
}

void DDF_Browser::Data(const occ::handle<TDF_Data>& aDF)
{
  myDF = aDF;
}

occ::handle<TDF_Data> DDF_Browser::Data() const
{
  return myDF;
}

TCollection_AsciiString DDF_Browser::OpenRoot() const
{
  TCollection_AsciiString list;
  const TDF_Label&        root = myDF->Root();
  TDF_Tool::Entry(root, list);
  occ::handle<TDataStd_Name> name;
  list.AssignCat(TDF_BrowserSeparator2);
  list.AssignCat("\"");
  if (root.FindAttribute(TDataStd_Name::GetID(), name))
  {
    TCollection_AsciiString tmpStr(name->Get());
    tmpStr.ChangeAll(' ', '_');
    list.AssignCat(tmpStr);
  }
  list.AssignCat("\"");
  list.AssignCat(TDF_BrowserSeparator2);
  if (!root.MayBeModified())
    list.AssignCat("Not");
  list.AssignCat("Modified");
  list.AssignCat(TDF_BrowserSeparator2);
  list.AssignCat((root.HasAttribute() || root.HasChild()) ? "1" : "0");
  return list;
}

TCollection_AsciiString DDF_Browser::OpenLabel(const TDF_Label& aLab) const
{
  bool                    split = false;
  TCollection_AsciiString entry, list;
  if (aLab.HasAttribute() || aLab.AttributesModified())
  {
    list.AssignCat("AttributeList");
    list.AssignCat(TDF_BrowserSeparator2);
    if (!aLab.AttributesModified())
      list.AssignCat("Not");
    list.AssignCat("Modified");
    split = true;
  }
  occ::handle<TDataStd_Name> name;
  for (TDF_ChildIterator itr(aLab); itr.More(); itr.Next())
  {
    if (split)
      list.AssignCat(TDF_BrowserSeparator1);
    TDF_Tool::Entry(itr.Value(), entry);
    list.AssignCat(entry);
    list.AssignCat(TDF_BrowserSeparator2);
    list.AssignCat("\"");
    if (itr.Value().FindAttribute(TDataStd_Name::GetID(), name))
    {
      TCollection_AsciiString tmpStr(name->Get());
      tmpStr.ChangeAll(' ', '_');
      list.AssignCat(tmpStr);
    }
    list.AssignCat("\"");
    list.AssignCat(TDF_BrowserSeparator2);
    if (!itr.Value().MayBeModified())
      list.AssignCat("Not");
    list.AssignCat("Modified");
    list.AssignCat(TDF_BrowserSeparator2);

    list.AssignCat((itr.Value().HasAttribute() || itr.Value().HasChild()) ? "1" : "0");
    split = true;
  }
  return list;
}

TCollection_AsciiString DDF_Browser::OpenAttributeList(const TDF_Label& aLab)
{
  TCollection_AsciiString list;
  bool                    split1 = false;
  for (TDF_AttributeIterator itr(aLab, false); itr.More(); itr.Next())
  {
    if (split1)
      list.AssignCat(TDF_BrowserSeparator1);
    const occ::handle<TDF_Attribute>& att   = itr.Value();
    const int                         index = myAttMap.Add(att);
    TCollection_AsciiString           indexStr(index);
    list.AssignCat(att->DynamicType()->Name());
    list.AssignCat(TDF_BrowserSeparator3);
    list.AssignCat(indexStr);
    list.AssignCat(TDF_BrowserSeparator2);
    list.AssignCat(att->Transaction());

    list.AssignCat(TDF_BrowserSeparator2);
    if (!att->IsValid())
      list.AssignCat("Not");
    list.AssignCat("Valid");

    list.AssignCat(TDF_BrowserSeparator2);
    if (!att->IsForgotten())
      list.AssignCat("Not");
    list.AssignCat("Forgotten");

    list.AssignCat(TDF_BrowserSeparator2);
    if (!att->IsBackuped())
      list.AssignCat("Not");
    list.AssignCat("Backuped");

    list.AssignCat(TDF_BrowserSeparator2);
    DDF_AttributeBrowser* br = DDF_AttributeBrowser::FindBrowser(att);
    list.AssignCat(br ? "1" : "0");
    split1 = true;
  }
  return list;
}

TCollection_AsciiString DDF_Browser::OpenAttribute(const int anIndex)
{
  TCollection_AsciiString    list;
  occ::handle<TDF_Attribute> att = myAttMap.FindKey(anIndex);
  DDF_AttributeBrowser*      br  = DDF_AttributeBrowser::FindBrowser(att);
  if (br)
    list = br->Open(att);
  return list;
}

TCollection_AsciiString DDF_Browser::Information() const
{
  TCollection_AsciiString list;
  return list;
}

TCollection_AsciiString DDF_Browser::Information(const TDF_Label&) const
{
  TCollection_AsciiString list;
  return list;
}

TCollection_AsciiString DDF_Browser::Information(const int) const
{
  TCollection_AsciiString list;
  return list;
}
