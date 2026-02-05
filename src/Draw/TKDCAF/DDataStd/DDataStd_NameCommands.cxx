#include <DDataStd.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_Appli.hpp>

#include <DDF.hpp>

#include <TDF_Data.hpp>
#include <TDF_Label.hpp>

// ATTRIBUTES

#include <TDataStd_Name.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_List.hpp>

//=======================================================================
// function : DDataStd_SetName
// purpose  : SetName (DF, entry, name [,guid])
//=======================================================================

static int DDataStd_SetName(Draw_Interpretor& di, int nb, const char** arg)
{

  if (nb == 4 || nb == 5)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    if (L.IsNull())
      di << "Label is not found" << "\n";
    if (nb == 4)
      TDataStd_Name::Set(L, TCollection_ExtendedString(arg[3], true));
    else
    {
      if (!Standard_GUID::CheckGUIDFormat(arg[4]))
      {
        di << "DDataStd_SetReal: The format of GUID is invalid\n";
        return 1;
      }
      Standard_GUID guid(arg[4]);
      TDataStd_Name::Set(L, guid, TCollection_ExtendedString(arg[3], true));
    }
    return 0;
  }
  di << "DDataStd_SetName : Error\n";
  return 1;
}

// #define DEB_DDataStd
//=======================================================================
// function : DDataStd_GetName
// purpose  : GetName (DF, entry [,guid])
//=======================================================================

static int DDataStd_GetName(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 3 || nb == 4)
  {
    occ::handle<TDF_Data> DF;
    if (!DDF::GetDF(arg[1], DF))
      return 1;
    TDF_Label L;
    DDF::FindLabel(DF, arg[2], L);
    if (L.IsNull())
      di << "Label is not found" << "\n";
    Standard_GUID aGuid(TDataStd_Name::GetID());
    if (nb == 4)
    {
      if (!Standard_GUID::CheckGUIDFormat(arg[3]))
      {
        di << "DDataStd_GetAsciiString: The format of GUID is invalid\n";
        return 1;
      }
      aGuid = Standard_GUID(arg[3]);
    }
    occ::handle<TDataStd_Name> N;
    if (!L.FindAttribute(aGuid, N))
    {
      di << "Name attribute is not found or not set";
      return 1;
    }
#ifdef DEB_DDataStd
    if (!N.IsNull())
      std::cout << "String = " << N->Get() << std::endl;
#endif
    di << N->Get();
    return 0;
  }
  di << "DDataStd_SetName : Error\n";
  return 1;
}

//=================================================================================================

void DDataStd::NameCommands(Draw_Interpretor& theCommands)
{

  static bool done = false;
  if (done)
    return;
  done = true;

  const char* g = "DDataStd : Name attribute commands";

  theCommands.Add("SetName", "SetName (DF, entry, name [,guid])", __FILE__, DDataStd_SetName, g);

  theCommands.Add("GetName", "GetNmae (DF, entry [,guid])", __FILE__, DDataStd_GetName, g);
}
