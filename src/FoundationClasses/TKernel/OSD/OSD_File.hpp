#pragma once

#include <OSD_FileNode.hpp>

enum OSD_FromWhere
{
  OSD_FromBeginning,
  OSD_FromHere,
  OSD_FromEnd
};

enum OSD_KindFile
{
  OSD_FILE,
  OSD_DIRECTORY,
  OSD_LINK,
  OSD_SOCKET,
  OSD_UNKNOWN
};

enum OSD_LockType
{
  OSD_NoLock,
  OSD_ReadLock,
  OSD_WriteLock,
  OSD_ExclusiveLock
};

#include <OSD_OpenMode.hpp>

class OSD_Path;
class OSD_Protection;

class OSD_File : public OSD_FileNode
{
public:
  Standard_EXPORT OSD_File();

  Standard_EXPORT OSD_File(const OSD_Path& Name);

  Standard_EXPORT ~OSD_File();

  Standard_EXPORT void Build(const OSD_OpenMode Mode, const OSD_Protection& Protect);

  Standard_EXPORT void Open(const OSD_OpenMode Mode, const OSD_Protection& Protect);

  Standard_EXPORT void Append(const OSD_OpenMode Mode, const OSD_Protection& Protect);

  Standard_EXPORT void Read(TCollection_AsciiString& Buffer, const int Nbyte);

  Standard_EXPORT void ReadLine(TCollection_AsciiString& Buffer, const int NByte, int& NbyteRead);

  inline int ReadLine(TCollection_AsciiString& Buffer, const int NByte)
  {
    int NbyteRead;
    ReadLine(Buffer, NByte, NbyteRead);
    return NbyteRead;
  }

  Standard_EXPORT void Read(void* const Buffer, const int Nbyte, int& Readbyte);

  void Write(const TCollection_AsciiString& theBuffer, const int theNbBytes)
  {
    Write((void*)theBuffer.ToCString(), theNbBytes);
  }

  Standard_EXPORT void Write(void* const theBuffer, const int theNbBytes);

  Standard_EXPORT void Seek(const int Offset, const OSD_FromWhere Whence);

  Standard_EXPORT void Close();

  Standard_EXPORT bool IsAtEnd();

  Standard_EXPORT OSD_KindFile KindOfFile() const;

  Standard_EXPORT void BuildTemporary();

  Standard_EXPORT void SetLock(const OSD_LockType Lock);

  Standard_EXPORT void UnLock();

  OSD_LockType GetLock() const { return myLock; }

  bool IsLocked() const
  {
#ifdef _WIN32
    return ImperativeFlag;
#else
    return myLock != OSD_NoLock;
#endif
  }

  Standard_EXPORT size_t Size();

  Standard_EXPORT bool IsOpen() const;

  Standard_EXPORT bool IsReadable();

  Standard_EXPORT bool IsWriteable();

  Standard_EXPORT bool IsExecutable();

  Standard_EXPORT bool ReadLastLine(TCollection_AsciiString& aLine,
                                    const int                aDelay,
                                    const int                aNbTries);

  Standard_EXPORT bool Edit();

  Standard_EXPORT void Rewind();

protected:
#ifdef _WIN32
  void* myFileHandle;
#else
  int   myFileChannel;
  void* myFILE;
#endif
  int myIO;

private:
  OSD_LockType myLock;
  OSD_OpenMode myMode;
  bool         ImperativeFlag;
};
