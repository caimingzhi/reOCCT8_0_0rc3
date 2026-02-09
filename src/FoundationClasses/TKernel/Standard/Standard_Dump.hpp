#pragma once

#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <Standard_SStream.hpp>
#include <TCollection_AsciiString.hpp>

#define OCCT_CLASS_NAME(theClass) #theClass

#define OCCT_DUMP_CLASS_BEGIN(theOStream, theField)                                                \
  {                                                                                                \
    const char* className = OCCT_CLASS_NAME(theField);                                             \
    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, className)                                            \
  }

#define OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)                                                \
  {                                                                                                \
    const char* className = get_type_name();                                                       \
    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, className)                                            \
  }

#define OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, theField)                                      \
  {                                                                                                \
    TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField);                     \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    theOStream << "\"" << aName << "\": " << theField;                                             \
  }

#define OCCT_DUMP_FIELD_VALUE_NUMERICAL_INC(theOStream, theField, theIncName)                      \
  {                                                                                                \
    TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField) + theIncName;        \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    theOStream << "\"" << aName << "\": " << theField;                                             \
  }

#define OCCT_INIT_FIELD_VALUE_REAL(theOStream, theStreamPos, theField)                             \
  {                                                                                                \
    int aStreamPos = theStreamPos;                                                                 \
    if (!Standard_Dump::ProcessFieldName(theOStream, #theField, aStreamPos))                       \
      return false;                                                                                \
    TCollection_AsciiString aValueText;                                                            \
    if (!Standard_Dump::InitValue(theOStream, aStreamPos, aValueText)                              \
        || !aValueText.IsRealValue())                                                              \
      return false;                                                                                \
    theField     = aValueText.RealValue();                                                         \
    theStreamPos = aStreamPos;                                                                     \
  }

#define OCCT_INIT_FIELD_VALUE_INTEGER(theOStream, theStreamPos, theField)                          \
  {                                                                                                \
    int aStreamPos = theStreamPos;                                                                 \
    if (!Standard_Dump::ProcessFieldName(theOStream, #theField, aStreamPos))                       \
      return false;                                                                                \
    TCollection_AsciiString aValueText;                                                            \
    if (!Standard_Dump::InitValue(theOStream, aStreamPos, aValueText)                              \
        || !aValueText.IsIntegerValue())                                                           \
      return false;                                                                                \
    theField     = aValueText.IntegerValue();                                                      \
    theStreamPos = aStreamPos;                                                                     \
  }

#define OCCT_DUMP_FIELD_VALUE_STRING(theOStream, theField)                                         \
  {                                                                                                \
    TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField);                     \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    theOStream << "\"" << aName << "\": \"" << theField << "\"";                                   \
  }

#define OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, theField)                                        \
  {                                                                                                \
    TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField);                     \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    theOStream << "\"" << aName << "\": \"" << Standard_Dump::GetPointerInfo(theField) << "\"";    \
  }

#define OCCT_DUMP_FIELD_VALUE_GUID(theOStream, theField)                                           \
  {                                                                                                \
    TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField);                     \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    char aStr[Standard_GUID_SIZE_ALLOC];                                                           \
    theField.ToCString(aStr);                                                                      \
    theOStream << "\"" << aName << "\": \"" << aStr << "\"";                                       \
  }

#define OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, theField)                              \
  {                                                                                                \
    if (theDepth != 0 && (void*)(theField) != NULL)                                                \
    {                                                                                              \
      Standard_SStream aFieldStream;                                                               \
      (theField)->DumpJson(aFieldStream, theDepth - 1);                                            \
      TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField);                   \
      Standard_Dump::DumpKeyToClass(theOStream, aName, Standard_Dump::Text(aFieldStream));         \
    }                                                                                              \
  }

#define OCCT_DUMP_FIELD_VALUES_DUMPED_INC(theOStream, theDepth, theField, theIncName)              \
  {                                                                                                \
    if (theDepth != 0 && (void*)(theField) != NULL)                                                \
    {                                                                                              \
      Standard_SStream aFieldStream;                                                               \
      (theField)->DumpJson(aFieldStream, theDepth - 1);                                            \
      TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField) + theIncName;      \
      Standard_Dump::DumpKeyToClass(theOStream, aName, Standard_Dump::Text(aFieldStream));         \
    }                                                                                              \
  }

#define OCCT_INIT_FIELD_VALUES_DUMPED(theSStream, theStreamPos, theField)                          \
  {                                                                                                \
    if ((theField) == NULL || !(theField)->InitFromJson(theSStream, theStreamPos))                 \
      return false;                                                                                \
  }

#define OCCT_DUMP_STREAM_VALUE_DUMPED(theOStream, theField)                                        \
  {                                                                                                \
    TCollection_AsciiString aName = Standard_Dump::DumpFieldToName(#theField);                     \
    Standard_Dump::DumpKeyToClass(theOStream, aName, Standard_Dump::Text(theField));               \
  }

#define OCCT_DUMP_FIELD_VALUES_NUMERICAL(theOStream, theName, theCount, ...)                       \
  {                                                                                                \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    theOStream << "\"" << theName << "\": [";                                                      \
    Standard_Dump::DumpRealValues(theOStream, theCount, __VA_ARGS__);                              \
    theOStream << "]";                                                                             \
  }

#define OCCT_DUMP_FIELD_VALUES_STRING(theOStream, theName, theCount, ...)                          \
  {                                                                                                \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    theOStream << "\"" << theName << "\": [";                                                      \
    Standard_Dump::DumpCharacterValues(theOStream, theCount, __VA_ARGS__);                         \
    theOStream << "]";                                                                             \
  }

#define OCCT_DUMP_BASE_CLASS(theOStream, theDepth, theField)                                       \
  {                                                                                                \
    if (theDepth != 0)                                                                             \
    {                                                                                              \
      Standard_Dump::AddValuesSeparator(theOStream);                                               \
      theField::DumpJson(theOStream, theDepth - 1);                                                \
    }                                                                                              \
  }

#define OCCT_DUMP_VECTOR_CLASS(theOStream, theName, theCount, ...)                                 \
  {                                                                                                \
    Standard_Dump::AddValuesSeparator(theOStream);                                                 \
    theOStream << "\"" << theName << "\": [";                                                      \
    Standard_Dump::DumpRealValues(theOStream, theCount, __VA_ARGS__);                              \
    theOStream << "]";                                                                             \
  }

#define OCCT_INIT_VECTOR_CLASS(theOStream, theName, theStreamPos, theCount, ...)                   \
  {                                                                                                \
    int aStreamPos = theStreamPos;                                                                 \
    if (!Standard_Dump::ProcessStreamName(theOStream, theName, aStreamPos))                        \
      return false;                                                                                \
    if (!Standard_Dump::InitRealValues(theOStream, aStreamPos, theCount, __VA_ARGS__))             \
      return false;                                                                                \
    theStreamPos = aStreamPos;                                                                     \
  }

enum Standard_JsonKey
{
  Standard_JsonKey_None,
  Standard_JsonKey_OpenChild,
  Standard_JsonKey_CloseChild,
  Standard_JsonKey_OpenContainer,
  Standard_JsonKey_CloseContainer,
  Standard_JsonKey_Quote,
  Standard_JsonKey_SeparatorKeyToValue,
  Standard_JsonKey_SeparatorValueToValue
};

struct Standard_DumpValue
{
  Standard_DumpValue()
      : myStartPosition(0)
  {
  }

  Standard_DumpValue(const TCollection_AsciiString& theValue, const int theStartPos)
      : myValue(theValue),
        myStartPosition(theStartPos)
  {
  }

  TCollection_AsciiString myValue;
  int                     myStartPosition;
};

class Standard_Dump
{
public:
  Standard_EXPORT static TCollection_AsciiString Text(const Standard_SStream& theStream);

  Standard_EXPORT static TCollection_AsciiString FormatJson(const Standard_SStream& theStream,
                                                            const int               theIndent = 3);

  Standard_EXPORT static bool SplitJson(
    const TCollection_AsciiString&                                           theStreamStr,
    NCollection_IndexedDataMap<TCollection_AsciiString, Standard_DumpValue>& theKeyToValues);

  Standard_EXPORT static NCollection_List<int> HierarchicalValueIndices(
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theValues);

  Standard_EXPORT static bool HasChildKey(const TCollection_AsciiString& theSourceValue);

  Standard_EXPORT static const char* JsonKeyToString(const Standard_JsonKey theKey);

  Standard_EXPORT static int JsonKeyLength(const Standard_JsonKey theKey);

  static Standard_EXPORT void AddValuesSeparator(Standard_OStream& theOStream);

  static TCollection_AsciiString GetPointerPrefix() { return "0x"; }

  Standard_EXPORT static TCollection_AsciiString GetPointerInfo(
    const occ::handle<Standard_Transient>& thePointer,
    const bool                             isShortInfo = true);

  Standard_EXPORT static TCollection_AsciiString GetPointerInfo(const void* thePointer,
                                                                const bool  isShortInfo = true);

  Standard_EXPORT static void DumpKeyToClass(Standard_OStream&              theOStream,
                                             const TCollection_AsciiString& theKey,
                                             const TCollection_AsciiString& theField);

  Standard_EXPORT static void DumpCharacterValues(Standard_OStream& theOStream, int theCount, ...);

  Standard_EXPORT static void DumpRealValues(Standard_OStream& theOStream, int theCount, ...);

  Standard_EXPORT static bool ProcessStreamName(const TCollection_AsciiString& theStreamStr,
                                                const TCollection_AsciiString& theName,
                                                int&                           theStreamPos);

  Standard_EXPORT static bool ProcessFieldName(const TCollection_AsciiString& theStreamStr,
                                               const TCollection_AsciiString& theName,
                                               int&                           theStreamPos);

  Standard_EXPORT static bool InitRealValues(const TCollection_AsciiString& theStreamStr,
                                             int&                           theStreamPos,
                                             int                            theCount,
                                             ...);

  Standard_EXPORT static bool InitValue(const TCollection_AsciiString& theStreamStr,
                                        int&                           theStreamPos,
                                        TCollection_AsciiString&       theValue);

  Standard_EXPORT static TCollection_AsciiString DumpFieldToName(
    const TCollection_AsciiString& theField);

private:
  Standard_EXPORT static bool splitKeyToValue(
    const TCollection_AsciiString&                                           theStreamStr,
    int                                                                      theStartIndex,
    int&                                                                     theNextIndex,
    NCollection_IndexedDataMap<TCollection_AsciiString, Standard_DumpValue>& theValues);

  Standard_EXPORT static bool jsonKey(const TCollection_AsciiString& theStreamStr,
                                      int                            theStartIndex,
                                      int&                           theNextIndex,
                                      Standard_JsonKey&              theKey);

  Standard_EXPORT static int nextClosePosition(const TCollection_AsciiString& theSourceValue,
                                               const int                      theStartPosition,
                                               const Standard_JsonKey         theCloseKey,
                                               const Standard_JsonKey         theOpenKey);
};
