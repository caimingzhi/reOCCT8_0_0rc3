

#include <DDocStd_DrawDocument.hpp>
#include <Draw_Display.hpp>
#include <Draw_Drawable3D.hpp>
#include <Standard_Type.hpp>
#include <TDF_Data.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd_Document.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DDocStd_DrawDocument, DDF_Data)

occ::handle<DDocStd_DrawDocument> DDocStd_DrawDocument::Find(const occ::handle<TDocStd_Document>&)
{
  occ::handle<DDocStd_DrawDocument> adoc;
  return adoc;
}

DDocStd_DrawDocument::DDocStd_DrawDocument(const occ::handle<TDocStd_Document>& Doc)
    : DDF_Data(new TDF_Data),
      myDocument(Doc)
{
  DataFramework(Doc->GetData());
}

occ::handle<TDocStd_Document> DDocStd_DrawDocument::GetDocument() const
{
  return myDocument;
}

void DDocStd_DrawDocument::DrawOn(Draw_Display&) const {}

occ::handle<Draw_Drawable3D> DDocStd_DrawDocument::Copy() const
{
  occ::handle<DDocStd_DrawDocument> D = new DDocStd_DrawDocument(myDocument);
  return D;
}

void DDocStd_DrawDocument::Dump(Standard_OStream& S) const
{
  occ::handle<TDocStd_Document> STDDOC = myDocument;
  if (!STDDOC.IsNull())
  {
    S << "TDocStd_Document\n";
    DDF_Data::Dump(S);
  }
  else
  {
    S << myDocument->DynamicType()->Name() << " is not a CAF document" << std::endl;
  }
}

void DDocStd_DrawDocument::Whatis(Draw_Interpretor& I) const
{
  I << myDocument->DynamicType()->Name();
}
