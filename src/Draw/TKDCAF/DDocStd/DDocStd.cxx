#include <DDocStd.hpp>

#include <DDocStd_DrawDocument.hpp>
#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <Standard_GUID.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd_Application.hpp>
#include <TDocStd_Document.hpp>

#include <StdLDrivers.hpp>
#include <BinLDrivers.hpp>
#include <XmlLDrivers.hpp>
#include <StdDrivers.hpp>
#include <BinDrivers.hpp>
#include <XmlDrivers.hpp>

const occ::handle<TDocStd_Application>& DDocStd::GetApplication()
{
  static occ::handle<TDocStd_Application> anApp;
  if (anApp.IsNull())
  {
    anApp = new TDocStd_Application;

    StdLDrivers::DefineFormat(anApp);
    BinLDrivers::DefineFormat(anApp);
    XmlLDrivers::DefineFormat(anApp);
    StdDrivers::DefineFormat(anApp);
    BinDrivers::DefineFormat(anApp);
    XmlDrivers::DefineFormat(anApp);
  }
  return anApp;
}

bool DDocStd::GetDocument(const char*&                   Name,
                          occ::handle<TDocStd_Document>& DOC,
                          const bool                     Complain)
{
  occ::handle<DDocStd_DrawDocument> DD =
    occ::down_cast<DDocStd_DrawDocument>(Draw::GetExisting(Name));
  if (DD.IsNull())
  {
    if (Complain)
      std::cout << Name << " is not a Document" << std::endl;
    return false;
  }
  occ::handle<TDocStd_Document> STDDOC = DD->GetDocument();
  if (!STDDOC.IsNull())
  {
    DOC = STDDOC;
    return true;
  }
  if (Complain)
    std::cout << Name << " is not a CAF Document" << std::endl;
  return false;
}

bool DDocStd::Find(const occ::handle<TDocStd_Document>& D,
                   const char*                          Entry,
                   TDF_Label&                           Label,
                   const bool                           Complain)
{
  Label.Nullify();
  TDF_Tool::Label(D->GetData(), Entry, Label, false);
  if (Label.IsNull() && Complain)
    std::cout << "No label for entry " << Entry << std::endl;
  return !Label.IsNull();
}

bool DDocStd::Find(const occ::handle<TDocStd_Document>& D,
                   const char*                          Entry,
                   const Standard_GUID&                 ID,
                   occ::handle<TDF_Attribute>&          A,
                   const bool                           Complain)
{
  TDF_Label L;
  if (Find(D, Entry, L, Complain))
  {
    if (L.FindAttribute(ID, A))
      return true;
    if (Complain)
      std::cout << "attribute not found for entry : " << Entry << std::endl;
  }
  return false;
}

Draw_Interpretor& DDocStd::ReturnLabel(Draw_Interpretor& di, const TDF_Label& L)
{
  TCollection_AsciiString S;
  TDF_Tool::Entry(L, S);
  di << S.ToCString();
  return di;
}

void DDocStd::AllCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  DDocStd::ApplicationCommands(theCommands);
  DDocStd::DocumentCommands(theCommands);
  DDocStd::ToolsCommands(theCommands);
  DDocStd::MTMCommands(theCommands);
  DDocStd::ShapeSchemaCommands(theCommands);
}
