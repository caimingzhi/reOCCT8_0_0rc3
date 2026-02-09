

#include <FSD_CmpFile.hpp>
#include <OSD_OpenFile.hpp>
#include <Storage_StreamFormatError.hpp>
#include <Storage_StreamTypeMismatchError.hpp>
#include <Storage_StreamWriteError.hpp>

static const char* MAGICNUMBER = "CMPFILE";

IMPLEMENT_STANDARD_RTTIEXT(FSD_CmpFile, FSD_File)

FSD_CmpFile::FSD_CmpFile() = default;

Storage_Error FSD_CmpFile::IsGoodFileType(const TCollection_AsciiString& aName)
{
  FSD_CmpFile   f;
  Storage_Error s;

  s = f.Open(aName, Storage_VSRead);

  if (s == Storage_VSOk)
  {
    TCollection_AsciiString l;
    size_t                  len = strlen(FSD_CmpFile::MagicNumber());

    f.ReadChar(l, len);

    f.Close();

    if (strncmp(FSD_CmpFile::MagicNumber(), l.ToCString(), len) != 0)
    {
      s = Storage_VSFormatError;
    }
  }

  return s;
}

Storage_Error FSD_CmpFile::Open(const TCollection_AsciiString& aName, const Storage_OpenMode aMode)
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

#if !defined(IRIX) && !defined(DECOSF1)
        anOpenMode = std::ios::in | std::ios::binary;
#else
        anOpenMode = std::ios::in;
#endif
        break;
      }
      case Storage_VSWrite:
      {
#if !defined(IRIX) && !defined(DECOSF1)
        anOpenMode = std::ios::out | std::ios::binary;
#else
        anOpenMode = std::ios::out;
#endif
        break;
      }
      case Storage_VSReadWrite:
      {
#if !defined(IRIX) && !defined(DECOSF1)
        anOpenMode = std::ios::in | std::ios::out | std::ios::binary;
#else
        anOpenMode = std::ios::in | std::ios::out;
#endif
        break;
      }
    }
    if (anOpenMode != 0)
    {
      OSD_OpenStream(myStream, aName, anOpenMode);
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

const char* FSD_CmpFile::MagicNumber()
{
  return MAGICNUMBER;
}

void FSD_CmpFile::ReadLine(TCollection_AsciiString& buffer)
{
  buffer.Clear();
  TCollection_AsciiString aBuf('\0');
  FSD_File::ReadLine(aBuf);
  for (int lv = aBuf.Length(); lv >= 1 && (aBuf.Value(lv) == '\r' || (aBuf.Value(lv) == '\n'));
       lv--)
  {
    aBuf.Trunc(lv - 1);
  }
  buffer = aBuf;
}

void FSD_CmpFile::WriteExtendedLine(const TCollection_ExtendedString& buffer)
{
  const char16_t* extBuffer;
  int             i;

  extBuffer = buffer.ToExtString();
  PutInteger(buffer.Length());
  for (i = 0; i < buffer.Length(); i++)
  {
    PutExtCharacter(extBuffer[i]);
  }

  myStream << "\n";
}

void FSD_CmpFile::ReadExtendedLine(TCollection_ExtendedString& buffer)
{
  char16_t c;
  int      i;

  GetInteger(i);

  for (i = 0; i < buffer.Length(); i++)
  {
    GetExtCharacter(c);
    buffer += c;
  }

  FlushEndOfLine();
}

void FSD_CmpFile::ReadString(TCollection_AsciiString& buffer)
{
  buffer.Clear();
  TCollection_AsciiString aBuf('\0');
  FSD_File::ReadString(aBuf);
  for (int lv = aBuf.Length(); lv >= 1 && (aBuf.Value(lv) == '\r' || (aBuf.Value(lv) == '\n'));
       lv--)
  {
    aBuf.Trunc(lv - 1);
  }
  buffer = aBuf;
}

void FSD_CmpFile::Destroy()
{
  if (OpenMode() != Storage_VSNone)
  {
    Close();
  }
}

Storage_Error FSD_CmpFile::BeginWriteInfoSection()
{
  myStream << FSD_CmpFile::MagicNumber() << '\n';
  myStream << "BEGIN_INFO_SECTION\n";
  if (myStream.bad())
    throw Storage_StreamWriteError();

  return Storage_VSOk;
}

Storage_Error FSD_CmpFile::BeginReadInfoSection()
{
  Storage_Error           s;
  TCollection_AsciiString l;
  size_t                  len = strlen(FSD_CmpFile::MagicNumber());

  ReadChar(l, len);

  if (strncmp(FSD_CmpFile::MagicNumber(), l.ToCString(), len) != 0)
  {
    s = Storage_VSFormatError;
  }
  else
  {
    s = FindTag("BEGIN_INFO_SECTION");
  }

  return s;
}

void FSD_CmpFile::WritePersistentObjectHeader(const int aRef, const int aType)
{
  myStream << "\n#" << aRef << "%" << aType << " ";
  if (myStream.bad())
    throw Storage_StreamWriteError();
}

void FSD_CmpFile::BeginWritePersistentObjectData()
{
  if (myStream.bad())
    throw Storage_StreamWriteError();
}

void FSD_CmpFile::BeginWriteObjectData()
{
  if (myStream.bad())
    throw Storage_StreamWriteError();
}

void FSD_CmpFile::EndWriteObjectData()
{
  if (myStream.bad())
    throw Storage_StreamWriteError();
}

void FSD_CmpFile::EndWritePersistentObjectData()
{
  if (myStream.bad())
    throw Storage_StreamWriteError();
}

void FSD_CmpFile::ReadPersistentObjectHeader(int& aRef, int& aType)
{
  char c = '\0';

  myStream.get(c);

  while (c != '#')
  {
    if (IsEnd() || (c != ' ') || (c == '\r') || (c == '\n'))
    {
      throw Storage_StreamFormatError();
    }
    myStream.get(c);
  }

  if (!(myStream >> aRef))
    throw Storage_StreamTypeMismatchError();

  myStream.get(c);

  while (c != '%')
  {
    if (IsEnd() || (c != ' ') || (c == '\r') || (c == '\n'))
    {
      throw Storage_StreamFormatError();
    }
    myStream.get(c);
  }

  if (!(myStream >> aType))
    throw Storage_StreamTypeMismatchError();
}

void FSD_CmpFile::BeginReadPersistentObjectData() {}

void FSD_CmpFile::BeginReadObjectData() {}

void FSD_CmpFile::EndReadObjectData() {}

void FSD_CmpFile::EndReadPersistentObjectData()
{
  char c = '\0';

  myStream.get(c);
  while (c != '\n' && (c != '\r'))
  {
    if (IsEnd() || (c != ' '))
    {
      throw Storage_StreamFormatError();
    }
    myStream.get(c);
  }
  if (c == '\r')
  {
    myStream.get(c);
  }
}
