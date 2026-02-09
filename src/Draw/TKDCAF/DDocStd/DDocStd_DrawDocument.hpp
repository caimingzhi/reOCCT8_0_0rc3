#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <DDF_Data.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>
class TDocStd_Document;
class Draw_Display;
class Draw_Drawable3D;

class DDocStd_DrawDocument : public DDF_Data
{

public:
  Standard_EXPORT static occ::handle<DDocStd_DrawDocument> Find(
    const occ::handle<TDocStd_Document>& Doc);

  Standard_EXPORT DDocStd_DrawDocument(const occ::handle<TDocStd_Document>& Doc);

  Standard_EXPORT occ::handle<TDocStd_Document> GetDocument() const;

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  DEFINE_STANDARD_RTTIEXT(DDocStd_DrawDocument, DDF_Data)

private:
  occ::handle<TDocStd_Document> myDocument;
};
