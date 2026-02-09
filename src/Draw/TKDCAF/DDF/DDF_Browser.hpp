#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_IndexedMap.hpp>
#include <Draw_Drawable3D.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>
#include <Standard_Integer.hpp>

class TDF_Attribute;
class TDF_Data;
class Draw_Display;
class TCollection_AsciiString;
class TDF_Label;

class DDF_Browser : public Draw_Drawable3D
{

public:
  Standard_EXPORT DDF_Browser(const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  Standard_EXPORT void Data(const occ::handle<TDF_Data>& aDF);

  Standard_EXPORT occ::handle<TDF_Data> Data() const;

  Standard_EXPORT TCollection_AsciiString OpenRoot() const;

  Standard_EXPORT TCollection_AsciiString OpenLabel(const TDF_Label& aLab) const;

  Standard_EXPORT TCollection_AsciiString OpenAttributeList(const TDF_Label& aLab);

  Standard_EXPORT TCollection_AsciiString OpenAttribute(const int anIndex = 0);

  Standard_EXPORT TCollection_AsciiString Information() const;

  Standard_EXPORT TCollection_AsciiString Information(const TDF_Label& aLab) const;

  Standard_EXPORT TCollection_AsciiString Information(const int anIndex = 0) const;

  DEFINE_STANDARD_RTTIEXT(DDF_Browser, Draw_Drawable3D)

private:
  occ::handle<TDF_Data>                              myDF;
  NCollection_IndexedMap<occ::handle<TDF_Attribute>> myAttMap;
};
