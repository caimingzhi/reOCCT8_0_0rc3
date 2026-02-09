#pragma once

#include <FSD_File.hpp>
#include <Storage_BaseDriver.hpp>
#include <Storage_Error.hpp>
#include <Storage_OpenMode.hpp>

class TCollection_AsciiString;
class TCollection_ExtendedString;

class FSD_CmpFile : public FSD_File
{
public:
  DEFINE_STANDARD_RTTIEXT(FSD_CmpFile, FSD_File)

public:
  Standard_EXPORT FSD_CmpFile();

  Standard_EXPORT Storage_Error Open(const TCollection_AsciiString& aName,
                                     const Storage_OpenMode         aMode) override;

  Standard_EXPORT static Storage_Error IsGoodFileType(const TCollection_AsciiString& aName);

  Standard_EXPORT Storage_Error BeginWriteInfoSection() override;

  Standard_EXPORT Storage_Error BeginReadInfoSection() override;

  Standard_EXPORT void WritePersistentObjectHeader(const int aRef, const int aType) override;

  Standard_EXPORT void BeginWritePersistentObjectData() override;

  Standard_EXPORT void BeginWriteObjectData() override;

  Standard_EXPORT void EndWriteObjectData() override;

  Standard_EXPORT void EndWritePersistentObjectData() override;

  Standard_EXPORT void ReadPersistentObjectHeader(int& aRef, int& aType) override;

  Standard_EXPORT void BeginReadPersistentObjectData() override;

  Standard_EXPORT void BeginReadObjectData() override;

  Standard_EXPORT void EndReadObjectData() override;

  Standard_EXPORT void EndReadPersistentObjectData() override;

  Standard_EXPORT void Destroy();

  ~FSD_CmpFile() override { Destroy(); }

  Standard_EXPORT static const char* MagicNumber();

protected:
  Standard_EXPORT void ReadLine(TCollection_AsciiString& buffer) override;

  Standard_EXPORT void ReadExtendedLine(TCollection_ExtendedString& buffer) override;

  Standard_EXPORT void WriteExtendedLine(const TCollection_ExtendedString& buffer) override;

  Standard_EXPORT void ReadString(TCollection_AsciiString& buffer) override;
};
