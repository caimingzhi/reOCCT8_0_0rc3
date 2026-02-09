

#include <Resource_Manager.hpp>

#include <OSD_Directory.hpp>
#include <OSD_Environment.hpp>
#include <OSD_File.hpp>
#include <OSD_Path.hpp>
#include <OSD_Protection.hpp>
#include <Resource_LexicalCompare.hpp>
#include <Resource_NoSuchResource.hpp>
#include <Resource_Unicode.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Type.hpp>
#include <Standard_TypeMismatch.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_Array1.hpp>

#include <algorithm>
#include <cerrno>

IMPLEMENT_STANDARD_RTTIEXT(Resource_Manager, Standard_Transient)

enum Resource_KindOfLine
{
  Resource_KOL_End,
  Resource_KOL_Empty,
  Resource_KOL_Comment,
  Resource_KOL_Resource,
  Resource_KOL_Error
};

static Resource_KindOfLine WhatKindOfLine(OSD_File&                aFile,
                                          TCollection_AsciiString& aToken1,
                                          TCollection_AsciiString& aToken2);

static int GetLine(OSD_File& aFile, TCollection_AsciiString& aLine);

static bool Debug;

Resource_Manager::Resource_Manager(const TCollection_AsciiString& theName,
                                   const TCollection_AsciiString& theDefaultsDirectory,
                                   const TCollection_AsciiString& theUserDefaultsDirectory,
                                   const bool                     theIsVerbose)
    : myName(theName),
      myVerbose(theIsVerbose),
      myInitialized(false)
{
  if (!theDefaultsDirectory.IsEmpty())
  {
    OSD_Path anOSDPath(theDefaultsDirectory);
    if (!anOSDPath.Name().IsEmpty())
    {
      anOSDPath.DownTrek(anOSDPath.Name() + anOSDPath.Extension());
    }
    anOSDPath.SetName(theName);
    anOSDPath.SetExtension("");
    TCollection_AsciiString aPath;
    anOSDPath.SystemName(aPath);
    Load(aPath, myRefMap);
  }
  else if (myVerbose)
  {
    std::cout << "Resource Manager Warning: aDefaultsDirectory is empty." << std::endl;
  }

  if (!theUserDefaultsDirectory.IsEmpty())
  {
    OSD_Path anOSDPath(theUserDefaultsDirectory);
    if (!anOSDPath.Name().IsEmpty())
    {
      anOSDPath.DownTrek(anOSDPath.Name() + anOSDPath.Extension());
    }
    anOSDPath.SetName(theName);
    anOSDPath.SetExtension("");
    TCollection_AsciiString aPath;
    anOSDPath.SystemName(aPath);
    Load(aPath, myRefMap);
  }
  else if (myVerbose)
  {
    std::cout << "Resource Manager Warning: anUserDefaultsDirectory is empty." << std::endl;
  }
}

Resource_Manager::Resource_Manager(const char* aName, const bool Verbose)
    : myName(aName),
      myVerbose(Verbose),
      myInitialized(false)
{
  OSD_Environment envDebug("ResourceDebug");
  Debug = (!envDebug.Value().IsEmpty());

  TCollection_AsciiString Directory;

  OSD_Environment envVerbose("CSF_ResourceVerbose");
  if (!envVerbose.Value().IsEmpty())
    myVerbose = true;

  TCollection_AsciiString aPath, aUserPath;
  GetResourcePath(aPath, aName, false);
  GetResourcePath(aUserPath, aName, true);

  if (!aPath.IsEmpty())
    Load(aPath, myRefMap);
  else if (myVerbose)
    std::cout << "Resource Manager Warning: Environment variable \"CSF_" << aName
              << "Defaults\" not set." << std::endl;

  if (!aUserPath.IsEmpty())
    Load(aUserPath, myRefMap);
  else if (myVerbose)
    std::cout << "Resource Manager Warning: Environment variable \"CSF_" << aName
              << "UserDefaults\" not set." << std::endl;
}

Resource_Manager::Resource_Manager()
    : myName(""),
      myVerbose(false),
      myInitialized(false)
{
}

void Resource_Manager::Load(
  const TCollection_AsciiString&                                         thePath,
  NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>& aMap)
{
  Resource_KindOfLine     aKind;
  TCollection_AsciiString Token1, Token2;
  OSD_Path                Path(thePath);
  OSD_File                File     = Path;
  TCollection_AsciiString FileName = Path.Name();
  File.Open(OSD_ReadOnly, OSD_Protection());
  if (File.Failed())
  {
    if (myVerbose)
      std::cout << "Resource Manager Warning: Cannot read file \"" << FileName
                << "\". File not found or permission denied." << std::endl;
    return;
  }
  myInitialized  = true;
  int LineNumber = 1;
  while ((aKind = WhatKindOfLine(File, Token1, Token2)) != Resource_KOL_End)
  {
    switch (aKind)
    {
      case Resource_KOL_End:
      case Resource_KOL_Comment:
      case Resource_KOL_Empty:
        break;
      case Resource_KOL_Resource:
        if (!aMap.Bind(Token1, Token2))
          aMap(Token1) = Token2;
        break;
      case Resource_KOL_Error:
        if (myVerbose)
          std::cout << "Resource Manager: Syntax error at line " << LineNumber
                    << " in file : " << FileName << std::endl;
        break;
    }
    LineNumber++;
  }
  File.Close();
  if (myVerbose)
    std::cout << "Resource Manager: " << ((&aMap == &myUserMap) ? "User" : "Reference")
              << " file \"" << FileName << "\" loaded" << std::endl;
}

static Resource_KindOfLine WhatKindOfLine(OSD_File&                aFile,
                                          TCollection_AsciiString& aToken1,
                                          TCollection_AsciiString& aToken2)
{
  TCollection_AsciiString WhiteSpace = " \t";
  int                     Pos1, Pos2, Pos;
  TCollection_AsciiString Line;

  if (!GetLine(aFile, Line))
    return Resource_KOL_End;

  if (Line.Value(1) == '!')
    return Resource_KOL_Comment;

  Pos1 = Line.FirstLocationNotInSet(WhiteSpace, 1, Line.Length());
  if (Line.Value(Pos1) == '\n')
    return Resource_KOL_Empty;

  Pos2 = Line.Location(1, ':', Pos1, Line.Length());
  if (!Pos2 || Pos1 == Pos2)
    return Resource_KOL_Error;

  for (Pos = Pos2 - 1; Line.Value(Pos) == '\t' || Line.Value(Pos) == ' '; Pos--)
    ;
  aToken1 = Line.SubString(Pos1, Pos);

  if (Debug)
    std::cout << "Key = '" << aToken1 << std::flush;

  Pos = Line.FirstLocationNotInSet(WhiteSpace, Pos2 + 1, Line.Length());
  if (Pos)
  {
    if (Line.Value(Pos) == '\\')
      switch (Line.Value(Pos + 1))
      {
        case '\\':
        case ' ':
        case '\t':
          Pos++;
          break;
      }
  }
  if (Pos == Line.Length())
    aToken2.Clear();
  else
  {
    Line.Remove(1, Pos - 1);
    const int aLineLength = Line.Length();
    if (aLineLength >= 2)
    {
      if (Line.Value(aLineLength - 1) == '\r')
      {
        Line.Remove(aLineLength - 1);
      }
    }
    Line.Remove(Line.Length());
    aToken2 = Line;
  }
  if (Debug)
    std::cout << "'\t Value = '" << aToken2 << "'" << std::endl << std::flush;
  return Resource_KOL_Resource;
}

static int GetLine(OSD_File& aFile, TCollection_AsciiString& aLine)
{
  TCollection_AsciiString Buffer;
  int                     BufSize = 10;
  int                     Len;

  aLine.Clear();
  do
  {
    aFile.ReadLine(Buffer, BufSize, Len);
    aLine += Buffer;
    if (aFile.IsAtEnd())
    {
      if (!aLine.Length())
        return 0;
      else
        aLine += "\n";
    }
  } while (aLine.Value(aLine.Length()) != '\n');

  return 1;
}

bool Resource_Manager::Save() const
{
  TCollection_AsciiString anEnvVar("CSF_");
  anEnvVar += myName;
  anEnvVar += "UserDefaults";

  TCollection_AsciiString dir;
  OSD_Environment         anEnv(anEnvVar);
  dir = anEnv.Value();
  if (dir.IsEmpty())
  {
    if (myVerbose)
      std::cout << "Resource Manager Warning: environment variable \"" << anEnvVar
                << "\" not set.  Cannot save resources." << std::endl;
    return false;
  }

  TCollection_AsciiString aFilePath(dir);
  OSD_Path                anOSDPath(aFilePath);
  OSD_Directory           Dir     = anOSDPath;
  bool                    aStatus = true;
  if (!Dir.Exists())
  {
    {
      try
      {
        OCC_CATCH_SIGNALS
        Dir.Build(OSD_Protection(OSD_RX, OSD_RWXD, OSD_RX, OSD_RX));
      }
      catch (Standard_Failure const&)
      {
        aStatus = false;
      }
    }
    aStatus = aStatus && !Dir.Failed();
    if (!aStatus)
    {
      if (myVerbose)
        std::cout << "Resource Manager: Error opening or creating directory \"" << aFilePath
                  << "\". Permission denied. Cannot save resources." << std::endl;
      return false;
    }
  }

  if (!anOSDPath.Name().IsEmpty())
  {
    anOSDPath.DownTrek(anOSDPath.Name() + anOSDPath.Extension());
  }
  anOSDPath.SetName(myName);
  anOSDPath.SetExtension("");
  anOSDPath.SystemName(aFilePath);

  OSD_File       File = anOSDPath;
  OSD_Protection theProt;
  aStatus = true;
  {
    try
    {
      OCC_CATCH_SIGNALS
      File.Build(OSD_ReadWrite, theProt);
    }
    catch (Standard_Failure const&)
    {
      aStatus = false;
    }
  }
  aStatus = aStatus && !File.Failed();
  if (!aStatus)
  {
    if (myVerbose)
      std::cout << "Resource Manager: Error opening or creating file \"" << aFilePath
                << "\". Permission denied. Cannot save resources." << std::endl;
    return false;
  }

  const int NbKey = myUserMap.Extent();
  if (NbKey)
  {
    NCollection_Array1<TCollection_AsciiString> KeyArray(1, NbKey);
    NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>::Iterator Iter(myUserMap);

    int Index;
    for (Index = 1; Iter.More(); Iter.Next())
      KeyArray(Index++) = Iter.Key();

    std::sort(KeyArray.begin(), KeyArray.end());

    TCollection_AsciiString Line, Value;
    for (Index = 1; Index <= NbKey; Index++)
    {
      Value = myUserMap(KeyArray(Index));
      if (!Value.IsEmpty())
        switch (Value.Value(1))
        {
          case '\\':
          case ' ':
          case '\t':
            Value.Insert(1, '\\');
            break;
        }
      Line = KeyArray(Index) + ":\t" + Value + "\n";

      if (Debug)
        std::cout << "Line = '" << Line << "'" << std::endl;

      File.Write(Line, Line.Length());
    }
    if (myVerbose)
      std::cout << "Resource Manager: Resources saved in file " << aFilePath << std::endl;
  }
  File.Close();
  return true;
}

int Resource_Manager::Integer(const char* aResourceName) const
{
  TCollection_AsciiString Result = Value(aResourceName);
  if (!Result.IsIntegerValue())
  {
    TCollection_AsciiString n("Value of resource `");
    n += aResourceName;
    n += "` is not an integer";
    throw Standard_TypeMismatch(n.ToCString());
  }
  return Result.IntegerValue();
}

double Resource_Manager::Real(const char* aResourceName) const
{
  TCollection_AsciiString Result = Value(aResourceName);
  if (!Result.IsRealValue())
  {
    TCollection_AsciiString n("Value of resource `");
    n += aResourceName;
    n += "` is not a real";
    throw Standard_TypeMismatch(n.ToCString());
  }
  return Result.RealValue();
}

const char* Resource_Manager::Value(const char* aResource) const
{
  TCollection_AsciiString Resource(aResource);
  if (myUserMap.IsBound(Resource))
    return myUserMap(Resource).ToCString();
  if (myRefMap.IsBound(Resource))
    return myRefMap(Resource).ToCString();
  throw Resource_NoSuchResource(aResource);
}

const char16_t* Resource_Manager::ExtValue(const char* aResource)
{
  TCollection_AsciiString Resource(aResource);
  if (myExtStrMap.IsBound(Resource))
    return myExtStrMap(Resource).ToExtString();

  TCollection_AsciiString    Result = Value(aResource);
  TCollection_ExtendedString ExtResult;

  Resource_Unicode::ConvertFormatToUnicode(Result.ToCString(), ExtResult);

  myExtStrMap.Bind(Resource, ExtResult);
  return myExtStrMap(Resource).ToExtString();
}

void Resource_Manager::SetResource(const char* aResourceName, const int aValue)
{
  SetResource(aResourceName, TCollection_AsciiString(aValue).ToCString());
}

void Resource_Manager::SetResource(const char* aResourceName, const double aValue)
{
  SetResource(aResourceName, TCollection_AsciiString(aValue).ToCString());
}

void Resource_Manager::SetResource(const char* aResource, const char16_t* aValue)
{
  Standard_PCharacter        pStr;
  TCollection_AsciiString    Resource = aResource;
  TCollection_ExtendedString ExtValue = aValue;
  TCollection_AsciiString    FormatStr(ExtValue.Length() * 3 + 10, ' ');

  if (!myExtStrMap.Bind(Resource, ExtValue))
  {
    myExtStrMap(Resource) = ExtValue;
  }

  pStr = (Standard_PCharacter)FormatStr.ToCString();

  Resource_Unicode::ConvertUnicodeToFormat(ExtValue, pStr, FormatStr.Length());
  SetResource(aResource, FormatStr.ToCString());
}

void Resource_Manager::SetResource(const char* aResource, const char* aValue)
{
  TCollection_AsciiString Resource = aResource;
  TCollection_AsciiString Value    = aValue;
  if (!myUserMap.Bind(Resource, Value))
    myUserMap(Resource) = Value;
}

bool Resource_Manager::Find(const char* aResource) const
{
  TCollection_AsciiString Resource(aResource);
  return myUserMap.IsBound(Resource) || myRefMap.IsBound(Resource);
}

bool Resource_Manager::Find(const TCollection_AsciiString& theResource,
                            TCollection_AsciiString&       theValue) const
{
  return myUserMap.Find(theResource, theValue) || myRefMap.Find(theResource, theValue);
}

void Resource_Manager::GetResourcePath(TCollection_AsciiString& aPath,
                                       const char*              aName,
                                       const bool               isUserDefaults)
{
  aPath.Clear();

  TCollection_AsciiString anEnvVar("CSF_");
  anEnvVar += aName;
  anEnvVar += isUserDefaults ? "UserDefaults" : "Defaults";

  TCollection_AsciiString dir;
  OSD_Environment         anEnv(anEnvVar);
  dir = anEnv.Value();
  if (dir.IsEmpty())
    return;

  TCollection_AsciiString aResPath(dir);

  OSD_Path anOSDPath(aResPath);

  if (!anOSDPath.Name().IsEmpty())
  {
    anOSDPath.DownTrek(anOSDPath.Name() + anOSDPath.Extension());
  }
  anOSDPath.SetName(aName);
  anOSDPath.SetExtension("");

  anOSDPath.SystemName(aPath);
}

NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>& Resource_Manager::GetMap(
  bool theRefMap)
{
  return theRefMap ? myRefMap : myUserMap;
}
