

#include <FSD_File.hpp>

#include <OSD.hpp>
#include <OSD_OpenFile.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_StreamExtCharParityError.hpp>
#include <Storage_StreamFormatError.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <Storage_StreamWriteError.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

static const char* MAGICNUMBER                 = "FSDFILE";
static const char* ENDOFNORMALEXTENDEDSECTION  = "BEGIN_REF_SECTION";
static const int   SIZEOFNORMALEXTENDEDSECTION = 16;

#define USEOSDREAL 1

IMPLEMENT_STANDARD_RTTIEXT(app::file::stream::FSD_File, app::storage::Storage_BaseDriver)

app::file::stream::FSD_File::FSD_File() = default;

Storage_Error app::file::stream::FSD_File::IsGoodFileType(const TCollection_AsciiString& aName)
{
  app::file::stream::FSD_File      f;
  Storage_Error s;

  s = f.Open(aName, Storage_VSRead);

  if (s == Storage_VSOk)
  {
    TCollection_AsciiString l;
    size_t                  len = strlen(app::file::stream::FSD_File::MagicNumber());

    f.ReadChar(l, len);

    f.Close();

    if (strncmp(app::file::stream::FSD_File::MagicNumber(), l.ToCString(), len) != 0)
    {
      s = Storage_VSFormatError;
    }
  }

  return s;
}

Storage_Error app::file::stream::FSD_File::Open(const TCollection_AsciiString& aName, const Storage_OpenMode aMode)
{
  Storage_Error result = Storage_VSOk;

  SetName(aName);

  if (OpenMode() == Storage_VSNone)
  {
    std::ios_base::openmode anOpenMode = std::ios_base::openmode{};
    switch (aMode)
    {
      case Storage_VSNone:
      {
        break;
      }
      case Storage_VSRead:
      {

        anOpenMode = std::ios::in;
        break;
      }
      case Storage_VSWrite:
      {
        anOpenMode = std::ios::out;
        break;
      }
      case Storage_VSReadWrite:
      {
        anOpenMode = std::ios::in | std::ios::out;
        break;
      }
    }
    if (anOpenMode != 0)
    {
      OSD_OpenStream(myStream, aName.ToCString(), anOpenMode);
    }
    if (myStream.fail())
    {
      result = Storage_VSOpenError;
    }
    else
    {
      myStream.precision(17);
      myStream.imbue(std::locale::classic());
      SetOpenMode(aMode);
    }
  }
  else
  {
    result = Storage_VSAlreadyOpen;
  }

  return result;
}

bool app::file::stream::FSD_File::IsEnd()
{
  return myStream.eof();
}

Storage_Error app::file::stream::FSD_File::Close()
{
  Storage_Error result = Storage_VSOk;

  if (OpenMode() != Storage_VSNone)
  {
    myStream.close();
    SetOpenMode(Storage_VSNone);
  }
  else
  {
    result = Storage_VSNotOpen;
  }

  return result;
}

const char* app::file::stream::FSD_File::MagicNumber()
{
  return MAGICNUMBER;
}

void app::file::stream::FSD_File::FlushEndOfLine()
{
  TCollection_AsciiString aDummy;
  ReadLine(aDummy);
}

void app::file::stream::FSD_File::ReadLine(TCollection_AsciiString& buffer)
{
  char Buffer[8193];
  bool IsEnd = false;

  buffer.Clear();

  while (!IsEnd && !app::file::stream::FSD_File::IsEnd())
  {
    Buffer[0] = '\0';
    myStream.getline(Buffer, 8192, '\n');

    buffer += Buffer;
    IsEnd = true;
  }
}

void app::file::stream::FSD_File::WriteExtendedLine(const TCollection_ExtendedString& buffer)
{
  const char16_t* extBuffer;
  int             i, c, d;

  extBuffer = buffer.ToExtString();

  for (i = 0; i < buffer.Length(); i++)
  {
    c = (extBuffer[i] & 0x0000FF00) >> 8;
    d = extBuffer[i] & 0x000000FF;

    myStream << (char)c << (char)d;
  }

  myStream << (char)0 << "\n";
}

void app::file::stream::FSD_File::ReadExtendedLine(TCollection_ExtendedString& buffer)
{
  char        c = '\0';
  char16_t    i = 0, count = 0;
  bool        fin = false;
  const char* tg  = ENDOFNORMALEXTENDEDSECTION;

  buffer.Clear();

  while (!fin && !IsEnd())
  {
    myStream.get(c);

    if (c == tg[count])
      count++;
    else
      count = 0;
    if (count < SIZEOFNORMALEXTENDEDSECTION)
    {
      i = (char16_t)c;
      if (c == '\0')
        fin = true;
      i = (i << 8);

      myStream.get(c);
      if (c == tg[count])
        count++;
      else
        count = 0;
      if (count < SIZEOFNORMALEXTENDEDSECTION)
      {
        if (c != '\n')
        {
          fin = false;
          i |= (0x00FF & (char16_t)c);
          buffer += (char16_t)i;
        }
      }
      else
      {
        throw app::storage::Storage_StreamExtCharParityError();
      }
    }
    else
    {
      throw app::storage::Storage_StreamExtCharParityError();
    }
  }
}

void app::file::stream::FSD_File::ReadChar(TCollection_AsciiString& buffer, const size_t rsize)
{
  char   c      = '\0';
  size_t ccount = 0;

  buffer.Clear();

  while (!IsEnd() && (ccount < rsize))
  {
    myStream.get(c);
    buffer += c;
    ccount++;
  }
}

void app::file::stream::FSD_File::ReadString(TCollection_AsciiString& buffer)
{
  char  Buffer[8193];
  char* bpos;
  bool  IsEnd = false, isFirstTime = true;

  buffer.Clear();

  while (!IsEnd && !app::file::stream::FSD_File::IsEnd())
  {
    Buffer[0] = '\0';
    myStream.getline(Buffer, 8192, '\n');
    bpos = Buffer;

    if (isFirstTime)
    {
      isFirstTime = false;
      while (*bpos == '\n' || *bpos == ' ')
        bpos++;
    }

    buffer += bpos;
    IsEnd = true;
  }
}

void app::file::stream::FSD_File::ReadWord(TCollection_AsciiString& buffer)
{
  char c = '\0';
  char b[8193], *tmpb;
  bool IsEnd = false;
  int  i;

  tmpb = b;
  memset(b, '\0', 8193);
  buffer.Clear();

  while (!IsEnd && !app::file::stream::FSD_File::IsEnd())
  {
    myStream.get(c);
    if ((c != ' ') && (c != '\n'))
      IsEnd = true;
  }

  IsEnd = false;
  i     = 0;

  while (!IsEnd && !app::file::stream::FSD_File::IsEnd())
  {
    if (i == 8192)
    {
      buffer += b;
      tmpb = b;
      memset(b, '\0', 8193);
      i = 0;
    }
    *tmpb = c;
    tmpb++;
    i++;
    myStream.get(c);
    if ((c == '\n') || (c == ' '))
      IsEnd = true;
  }

  buffer += b;
}

Storage_Error app::file::stream::FSD_File::FindTag(const char* aTag)
{
  TCollection_AsciiString l;

  ReadString(l);

  while ((strcmp(l.ToCString(), aTag) != 0) && !IsEnd())
  {
    ReadString(l);
  }

  if (IsEnd())
  {
    return Storage_VSSectionNotFound;
  }
  else
  {
    return Storage_VSOk;
  }
}

void app::file::stream::FSD_File::SkipObject()
{
  FlushEndOfLine();
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::PutReference(const int aValue)
{
  myStream << aValue << " ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::PutCharacter(const char aValue)
{
  unsigned short i;

  i = aValue;
  myStream << i << " ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::PutExtCharacter(const char16_t aValue)
{
  myStream << (short)aValue << " ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::PutInteger(const int aValue)
{
  myStream << aValue << " ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::PutBoolean(const bool aValue)
{
  myStream << ((int)aValue) << " ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::PutReal(const double aValue)
{
  myStream << ((double)aValue) << " ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::PutShortReal(const float aValue)
{
  myStream << aValue << " ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::GetReference(int& aValue)
{
  if (!(myStream >> aValue))
    throw app::storage::Storage_StreamTypeMismatchError();

  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::GetCharacter(char& aValue)
{
  unsigned short i = 0;
  if (!(myStream >> i))
  {

    if (i == 0)
      throw app::storage::Storage_StreamTypeMismatchError();
    myStream.clear(std::ios::goodbit);
  }
  aValue = (char)i;

  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::GetExtCharacter(char16_t& aValue)
{
  short aChar = 0;
  if (!(myStream >> aChar))
    throw app::storage::Storage_StreamTypeMismatchError();
  aValue = aChar;
  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::GetInteger(int& aValue)
{
  if (!(myStream >> aValue))
    throw app::storage::Storage_StreamTypeMismatchError();

  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::GetBoolean(bool& aValue)
{
  if (!(myStream >> aValue))
    throw app::storage::Storage_StreamTypeMismatchError();

  return *this;
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::GetReal(double& aValue)
{
#ifdef USEOSDREAL
  char realbuffer[100];

  realbuffer[0] = '\0';
  if (!(myStream >> realbuffer))
    throw app::storage::Storage_StreamTypeMismatchError();
  if (!System::os::OSD::CStringToReal(realbuffer, aValue))
    throw app::storage::Storage_StreamTypeMismatchError();

  return *this;
#else
  if (!(myStream >> aValue))
    throw app::storage::Storage_StreamTypeMismatchError();

  return *this;
#endif
}

app::storage::Storage_BaseDriver& app::file::stream::FSD_File::GetShortReal(float& aValue)
{
#ifdef USEOSDREAL
  char   realbuffer[100];
  double r = 0.0;

  realbuffer[0] = '\0';
  if (!(myStream >> realbuffer))
    throw app::storage::Storage_StreamTypeMismatchError();
  if (!System::os::OSD::CStringToReal(realbuffer, r))
    throw app::storage::Storage_StreamTypeMismatchError();

  aValue = (float)r;

  return *this;
#else
  if (!(myStream >> aValue))
    throw app::storage::Storage_StreamTypeMismatchError();
  return *this;
#endif
}

void app::file::stream::FSD_File::Destroy()
{
  if (OpenMode() != Storage_VSNone)
  {
    Close();
  }
}

Storage_Error app::file::stream::FSD_File::BeginWriteInfoSection()
{
  myStream << app::file::stream::FSD_File::MagicNumber() << '\n';
  myStream << "BEGIN_INFO_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();

  return Storage_VSOk;
}

void app::file::stream::FSD_File::WriteInfo(const int                                            nbObj,
                         const TCollection_AsciiString&                       dbVersion,
                         const TCollection_AsciiString&                       date,
                         const TCollection_AsciiString&                       schemaName,
                         const TCollection_AsciiString&                       schemaVersion,
                         const TCollection_ExtendedString&                    appName,
                         const TCollection_AsciiString&                       appVersion,
                         const TCollection_ExtendedString&                    dataType,
                         const NCollection_Sequence<TCollection_AsciiString>& userInfo)
{
  int i;

  myStream << nbObj;
  myStream << "\n";
  myStream << dbVersion.ToCString() << "\n";
  myStream << date.ToCString() << "\n";
  myStream << schemaName.ToCString() << "\n";
  myStream << schemaVersion.ToCString() << "\n";
  WriteExtendedLine(appName);
  myStream << appVersion.ToCString() << "\n";
  WriteExtendedLine(dataType);
  myStream << userInfo.Length() << "\n";

  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();

  for (i = 1; i <= userInfo.Length(); i++)
  {
    myStream << userInfo.Value(i).ToCString() << "\n";
    if (myStream.bad())
      throw app::storage::Storage_StreamWriteError();
  }
}

Storage_Error app::file::stream::FSD_File::EndWriteInfoSection()
{
  myStream << "END_INFO_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

Storage_Error app::file::stream::FSD_File::BeginReadInfoSection()
{
  Storage_Error           s;
  TCollection_AsciiString l;
  size_t                  len = strlen(app::file::stream::FSD_File::MagicNumber());

  ReadChar(l, len);

  if (strncmp(app::file::stream::FSD_File::MagicNumber(), l.ToCString(), len) != 0)
  {
    s = Storage_VSFormatError;
  }
  else
  {
    s = FindTag("BEGIN_INFO_SECTION");
  }

  return s;
}

void app::file::stream::FSD_File::ReadInfo(int&                                           nbObj,
                        TCollection_AsciiString&                       dbVersion,
                        TCollection_AsciiString&                       date,
                        TCollection_AsciiString&                       schemaName,
                        TCollection_AsciiString&                       schemaVersion,
                        TCollection_ExtendedString&                    appName,
                        TCollection_AsciiString&                       appVersion,
                        TCollection_ExtendedString&                    dataType,
                        NCollection_Sequence<TCollection_AsciiString>& userInfo)
{
  if (!(myStream >> nbObj))
    throw app::storage::Storage_StreamTypeMismatchError();

  FlushEndOfLine();

  ReadLine(dbVersion);
  ReadLine(date);
  ReadLine(schemaName);
  ReadLine(schemaVersion);
  ReadExtendedLine(appName);
  ReadLine(appVersion);
  ReadExtendedLine(dataType);

  int i, len = 0;

  if (!(myStream >> len))
    throw app::storage::Storage_StreamTypeMismatchError();

  FlushEndOfLine();

  TCollection_AsciiString line;

  for (i = 1; i <= len && !IsEnd(); i++)
  {
    ReadLine(line);
    userInfo.Append(line);
    line.Clear();
  }
}

void app::file::stream::FSD_File::ReadCompleteInfo(Standard_IStream&, occ::handle<app::storage::Storage_Data>&) {}

Storage_Error app::file::stream::FSD_File::EndReadInfoSection()
{
  return FindTag("END_INFO_SECTION");
}

Storage_Error app::file::stream::FSD_File::BeginWriteCommentSection()
{
  myStream << "BEGIN_COMMENT_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

void app::file::stream::FSD_File::WriteComment(const NCollection_Sequence<TCollection_ExtendedString>& aCom)
{
  int i, aSize;

  aSize = aCom.Length();
  myStream << aSize << "\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();

  for (i = 1; i <= aSize; i++)
  {
    WriteExtendedLine(aCom.Value(i));
    if (myStream.bad())
      throw app::storage::Storage_StreamWriteError();
  }
}

Storage_Error app::file::stream::FSD_File::EndWriteCommentSection()
{
  myStream << "END_COMMENT_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

Storage_Error app::file::stream::FSD_File::BeginReadCommentSection()
{
  return FindTag("BEGIN_COMMENT_SECTION");
}

void app::file::stream::FSD_File::ReadComment(NCollection_Sequence<TCollection_ExtendedString>& aCom)
{
  TCollection_ExtendedString line;
  int                        len, i;

  if (!(myStream >> len))
    throw app::storage::Storage_StreamTypeMismatchError();

  FlushEndOfLine();

  for (i = 1; i <= len && !IsEnd(); i++)
  {
    ReadExtendedLine(line);
    aCom.Append(line);
    line.Clear();
  }
}

Storage_Error app::file::stream::FSD_File::EndReadCommentSection()
{
  return FindTag("END_COMMENT_SECTION");
}

Storage_Error app::file::stream::FSD_File::BeginWriteTypeSection()
{
  myStream << "BEGIN_TYPE_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

void app::file::stream::FSD_File::SetTypeSectionSize(const int aSize)
{
  myStream << aSize << "\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

void app::file::stream::FSD_File::WriteTypeInformations(const int typeNum, const TCollection_AsciiString& typeName)
{
  myStream << typeNum << " " << typeName.ToCString() << "\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

Storage_Error app::file::stream::FSD_File::EndWriteTypeSection()
{
  myStream << "END_TYPE_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

Storage_Error app::file::stream::FSD_File::BeginReadTypeSection()
{
  return FindTag("BEGIN_TYPE_SECTION");
}

int app::file::stream::FSD_File::TypeSectionSize()
{
  int i;

  if (!(myStream >> i))
    throw app::storage::Storage_StreamTypeMismatchError();

  FlushEndOfLine();

  return i;
}

void app::file::stream::FSD_File::ReadTypeInformations(int& typeNum, TCollection_AsciiString& typeName)
{
  if (!(myStream >> typeNum))
    throw app::storage::Storage_StreamTypeMismatchError();
  if (!(myStream >> typeName))
    throw app::storage::Storage_StreamTypeMismatchError();
  FlushEndOfLine();
}

Storage_Error app::file::stream::FSD_File::EndReadTypeSection()
{
  return FindTag("END_TYPE_SECTION");
}

Storage_Error app::file::stream::FSD_File::BeginWriteRootSection()
{
  myStream << "BEGIN_ROOT_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

void app::file::stream::FSD_File::SetRootSectionSize(const int aSize)
{
  myStream << aSize << "\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

void app::file::stream::FSD_File::WriteRoot(const TCollection_AsciiString& rootName,
                         const int                      aRef,
                         const TCollection_AsciiString& rootType)
{
  myStream << aRef << " " << rootName.ToCString() << " " << rootType.ToCString() << "\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

Storage_Error app::file::stream::FSD_File::EndWriteRootSection()
{
  myStream << "END_ROOT_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

Storage_Error app::file::stream::FSD_File::BeginReadRootSection()
{
  return FindTag("BEGIN_ROOT_SECTION");
}

int app::file::stream::FSD_File::RootSectionSize()
{
  int i;

  if (!(myStream >> i))
    throw app::storage::Storage_StreamTypeMismatchError();

  FlushEndOfLine();

  return i;
}

void app::file::stream::FSD_File::ReadRoot(TCollection_AsciiString& rootName,
                        int&                     aRef,
                        TCollection_AsciiString& rootType)
{
  if (!(myStream >> aRef))
    throw app::storage::Storage_StreamTypeMismatchError();
  ReadWord(rootName);
  ReadWord(rootType);
}

Storage_Error app::file::stream::FSD_File::EndReadRootSection()
{
  return FindTag("END_ROOT_SECTION");
}

Storage_Error app::file::stream::FSD_File::BeginWriteRefSection()
{
  myStream << "BEGIN_REF_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

void app::file::stream::FSD_File::SetRefSectionSize(const int aSize)
{
  myStream << aSize << "\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

void app::file::stream::FSD_File::WriteReferenceType(const int reference, const int typeNum)
{
  myStream << reference << " " << typeNum << "\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

Storage_Error app::file::stream::FSD_File::EndWriteRefSection()
{
  myStream << "END_REF_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

Storage_Error app::file::stream::FSD_File::BeginReadRefSection()
{
  return FindTag("BEGIN_REF_SECTION");
}

int app::file::stream::FSD_File::RefSectionSize()
{
  int i;

  if (!(myStream >> i))
    throw app::storage::Storage_StreamTypeMismatchError();
  FlushEndOfLine();

  return i;
}

void app::file::stream::FSD_File::ReadReferenceType(int& reference, int& typeNum)
{
  if (!(myStream >> reference))
    throw app::storage::Storage_StreamTypeMismatchError();
  if (!(myStream >> typeNum))
    throw app::storage::Storage_StreamTypeMismatchError();
  FlushEndOfLine();
}

Storage_Error app::file::stream::FSD_File::EndReadRefSection()
{
  return FindTag("END_REF_SECTION");
}

Storage_Error app::file::stream::FSD_File::BeginWriteDataSection()
{
  myStream << "BEGIN_DATA_SECTION";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

void app::file::stream::FSD_File::WritePersistentObjectHeader(const int aRef, const int aType)
{
  myStream << "\n#" << aRef << "=%" << aType;
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

void app::file::stream::FSD_File::BeginWritePersistentObjectData()
{
  myStream << "( ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

void app::file::stream::FSD_File::BeginWriteObjectData()
{
  myStream << "( ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

void app::file::stream::FSD_File::EndWriteObjectData()
{
  myStream << ") ";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

void app::file::stream::FSD_File::EndWritePersistentObjectData()
{
  myStream << ")";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
}

Storage_Error app::file::stream::FSD_File::EndWriteDataSection()
{
  myStream << "\nEND_DATA_SECTION\n";
  if (myStream.bad())
    throw app::storage::Storage_StreamWriteError();
  return Storage_VSOk;
}

Storage_Error app::file::stream::FSD_File::BeginReadDataSection()
{
  return FindTag("BEGIN_DATA_SECTION");
}

void app::file::stream::FSD_File::ReadPersistentObjectHeader(int& aRef, int& aType)
{
  char c = '\0';

  myStream.get(c);

  while (c != '#')
  {
    if (IsEnd() || (c != ' ') || (c == '\n'))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }

  if (!(myStream >> aRef))
    throw app::storage::Storage_StreamTypeMismatchError();

  myStream.get(c);

  while (c != '=')
  {
    if (IsEnd() || (c != ' ') || (c == '\n'))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }

  myStream.get(c);

  while (c != '%')
  {
    if (IsEnd() || (c != ' ') || (c == '\n'))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }

  if (!(myStream >> aType))
    throw app::storage::Storage_StreamTypeMismatchError();
}

void app::file::stream::FSD_File::BeginReadPersistentObjectData()
{
  char c = '\0';
  myStream.get(c);
  while (c != '(')
  {
    if (IsEnd() || (c != ' ') || (c == '\n'))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }
}

void app::file::stream::FSD_File::BeginReadObjectData()
{
  char c = '\0';
  myStream.get(c);
  while (c != '(')
  {
    if (IsEnd() || (c != ' ') || (c == '\n'))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }
}

void app::file::stream::FSD_File::EndReadObjectData()
{
  char c = '\0';
  myStream.get(c);
  while (c != ')')
  {
    if (IsEnd() || (c != ' ') || (c == '\n'))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }
}

void app::file::stream::FSD_File::EndReadPersistentObjectData()
{
  char c = '\0';

  myStream.get(c);
  while (c != ')')
  {
    if (IsEnd() || (c != ' ') || (c == '\n'))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }

  myStream.get(c);
  while (c != '\n')
  {
    if (IsEnd() || (c != ' '))
    {
      throw app::storage::Storage_StreamFormatError();
    }
    myStream.get(c);
  }
}

Storage_Error app::file::stream::FSD_File::EndReadDataSection()
{
  return FindTag("END_DATA_SECTION");
}

Storage_Position app::file::stream::FSD_File::Tell()
{
  switch (OpenMode())
  {
    case Storage_VSRead:
      return (Storage_Position)myStream.tellp();
    case Storage_VSWrite:
      return (Storage_Position)myStream.tellg();
    case Storage_VSReadWrite:
    {
      Storage_Position aPosR = (Storage_Position)myStream.tellp();
      Storage_Position aPosW = (Storage_Position)myStream.tellg();
      if (aPosR < aPosW)
        return aPosW;
      else
        return aPosR;
    }
    default:
      return -1;
  }
}
