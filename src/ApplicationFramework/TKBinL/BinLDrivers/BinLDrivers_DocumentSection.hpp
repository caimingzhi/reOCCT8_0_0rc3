#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <Message_ProgressIndicator.hpp>
#include <TDocStd_FormatVersion.hpp>

class BinLDrivers_DocumentSection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinLDrivers_DocumentSection();

  Standard_EXPORT BinLDrivers_DocumentSection(const TCollection_AsciiString& theName,
                                              const bool                     isPostRead);

  Standard_EXPORT const TCollection_AsciiString& Name() const;

  Standard_EXPORT bool IsPostRead() const;

  Standard_EXPORT uint64_t Offset() const;

  Standard_EXPORT void SetOffset(const uint64_t theOffset);

  Standard_EXPORT uint64_t Length() const;

  Standard_EXPORT void SetLength(const uint64_t theLength);

  Standard_EXPORT void WriteTOC(Standard_OStream&           theOS,
                                const TDocStd_FormatVersion theDocFormatVersion);

  Standard_EXPORT void Write(Standard_OStream&           theOS,
                             const uint64_t              theOffset,
                             const TDocStd_FormatVersion theDocFormatVersion);

  Standard_EXPORT static bool ReadTOC(BinLDrivers_DocumentSection& theSection,
                                      Standard_IStream&            theIS,
                                      const TDocStd_FormatVersion  theDocFormatVersion);

private:
  TCollection_AsciiString myName;
  uint64_t                myValue[2];
  bool                    myIsPostRead;
};
