

#include <IFSelect_ContextWrite.hpp>
#include <IFSelect_WorkLibrary.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_WorkLibrary, Standard_Transient)

IFSelect_WorkLibrary::IFSelect_WorkLibrary()
{
  thelevdef = 0;
}

bool IFSelect_WorkLibrary::CopyModel(const occ::handle<Interface_InterfaceModel>&,
                                     const occ::handle<Interface_InterfaceModel>& newmodel,
                                     const Interface_EntityIterator&              list,
                                     Interface_CopyTool&                          TC) const
{
  for (list.Start(); list.More(); list.Next())
    TC.TransferEntity(list.Value());

  TC.FillModel(newmodel);

  return true;
}

void IFSelect_WorkLibrary::DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                      const occ::handle<Interface_Protocol>&       protocol,
                                      const occ::handle<Standard_Transient>&       entity,
                                      Standard_OStream&                            S) const
{
  if (thelevhlp.IsNull())
    DumpEntity(model, protocol, entity, S, 0);
  else
    DumpEntity(model, protocol, entity, S, thelevdef);
}

void IFSelect_WorkLibrary::SetDumpLevels(const int def, const int max)
{
  thelevdef = def;
  thelevhlp.Nullify();
  if (max >= 0)
    thelevhlp = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(0, max);
}

void IFSelect_WorkLibrary::DumpLevels(int& def, int& max) const
{
  def = thelevdef;
  if (thelevhlp.IsNull())
  {
    def = 0;
    max = -1;
  }
  else
    max = thelevhlp->Upper();
}

void IFSelect_WorkLibrary::SetDumpHelp(const int level, const char* help)
{
  if (thelevhlp.IsNull())
    return;
  if (level < 0 || level > thelevhlp->Upper())
    return;
  occ::handle<TCollection_HAsciiString> str = new TCollection_HAsciiString(help);
  thelevhlp->SetValue(level, str);
}

const char* IFSelect_WorkLibrary::DumpHelp(const int level) const
{
  if (thelevhlp.IsNull())
    return "";
  if (level < 0 || level > thelevhlp->Upper())
    return "";
  occ::handle<TCollection_HAsciiString> str = thelevhlp->Value(level);
  if (str.IsNull())
    return "";
  return str->ToCString();
}

int IFSelect_WorkLibrary::ReadStream(const char*,
                                     std::istream&,
                                     occ::handle<Interface_InterfaceModel>&,
                                     const occ::handle<Interface_Protocol>&) const
{
  return 1;
}
