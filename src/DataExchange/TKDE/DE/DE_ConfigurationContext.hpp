#pragma once

#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>

class DE_ConfigurationContext : public Standard_Transient
{
public:
  DEFINE_STANDARD_RTTIEXT(DE_ConfigurationContext, Standard_Transient)

  Standard_EXPORT DE_ConfigurationContext();

  Standard_EXPORT bool Load(const TCollection_AsciiString& theConfiguration);

  Standard_EXPORT bool LoadFile(const TCollection_AsciiString& theFile);

  Standard_EXPORT bool LoadStr(const TCollection_AsciiString& theResource);

  Standard_EXPORT bool IsParamSet(const TCollection_AsciiString& theParam,
                                  const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT bool GetReal(const TCollection_AsciiString& theParam,
                               double&                        theValue,
                               const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT bool GetInteger(const TCollection_AsciiString& theParam,
                                  int&                           theValue,
                                  const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT bool GetBoolean(const TCollection_AsciiString& theParam,
                                  bool&                          theValue,
                                  const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT bool GetString(const TCollection_AsciiString& theParam,
                                 TCollection_AsciiString&       theValue,
                                 const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT bool GetStringSeq(const TCollection_AsciiString&             theParam,
                                    NCollection_List<TCollection_AsciiString>& theValue,
                                    const TCollection_AsciiString&             theScope = "") const;

  Standard_EXPORT double RealVal(const TCollection_AsciiString& theParam,
                                 const double                   theDefValue,
                                 const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT int IntegerVal(const TCollection_AsciiString& theParam,
                                 const int                      theDefValue,
                                 const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT bool BooleanVal(const TCollection_AsciiString& theParam,
                                  const bool                     theDefValue,
                                  const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT TCollection_AsciiString
    StringVal(const TCollection_AsciiString& theParam,
              const TCollection_AsciiString& theDefValue,
              const TCollection_AsciiString& theScope = "") const;

  Standard_EXPORT const NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>&
                        GetInternalMap() const
  {
    return myResource;
  }

protected:
  bool load(const TCollection_AsciiString& theResourceLine);

private:
  NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString> myResource;
};
