#include <DDF.hpp>
#include <DDF_Data.hpp>
#include <Draw.hpp>
#include <Standard_GUID.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

//=================================================================================================

bool DDF::AddLabel

  (const occ::handle<TDF_Data>& DF, const char* Entry, TDF_Label& Label)
{
  TDF_Tool::Label(DF, Entry, Label, true);
  return true;
}

//=================================================================================================

bool DDF::FindLabel(const occ::handle<TDF_Data>& DF,
                    const char*                  Entry,
                    TDF_Label&                   Label,
                    const bool                   Complain)
{
  Label.Nullify();
  TDF_Tool::Label(DF, Entry, Label, false);
  if (Label.IsNull() && Complain)
    std::cout << "No label for entry " << Entry << std::endl;
  return !Label.IsNull();
}

//=================================================================================================

bool DDF::GetDF(const char*& Name, occ::handle<TDF_Data>& DF, const bool Complain)
{
  occ::handle<Standard_Transient> t   = Draw::Get(Name);
  occ::handle<DDF_Data>           DDF = occ::down_cast<DDF_Data>(t);
  // occ::handle<DDF_Data> DDF = Handle(DDF_Data)::DownCast (Draw::Get(Name, Complain));
  if (!DDF.IsNull())
  {
    DF = DDF->DataFramework();
    return true;
  }
  if (Complain)
    std::cout << "framework " << Name << " not found " << std::endl;
  return false;
}

//=================================================================================================

bool DDF::Find(const occ::handle<TDF_Data>& DF,
               const char*                  Entry,
               const Standard_GUID&         ID,
               occ::handle<TDF_Attribute>&  A,
               const bool                   Complain)
{
  TDF_Label L;
  if (FindLabel(DF, Entry, L, Complain))
  {
    if (L.FindAttribute(ID, A))
      return true;
    if (Complain)
      std::cout << "attribute not found for entry : " << Entry << std::endl;
  }
  return false;
}

//=================================================================================================

Draw_Interpretor& DDF::ReturnLabel(Draw_Interpretor& di, const TDF_Label& L)
{
  TCollection_AsciiString S;
  TDF_Tool::Entry(L, S);
  di << S.ToCString();
  return di;
}

//=================================================================================================

void DDF::AllCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  DDF::BasicCommands(theCommands);
  DDF::DataCommands(theCommands);
  DDF::TransactionCommands(theCommands);
  DDF::BrowserCommands(theCommands);
  // define the TCL variable DDF
  const char* com = "set DDF";
  theCommands.Eval(com);
}
