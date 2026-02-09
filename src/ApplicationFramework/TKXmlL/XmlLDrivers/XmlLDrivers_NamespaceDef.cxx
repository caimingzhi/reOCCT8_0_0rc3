#include <XmlLDrivers_NamespaceDef.hpp>

XmlLDrivers_NamespaceDef::XmlLDrivers_NamespaceDef() = default;

XmlLDrivers_NamespaceDef::XmlLDrivers_NamespaceDef(const TCollection_AsciiString& thePrefix,
                                                   const TCollection_AsciiString& theURI)
    : myPrefix(thePrefix),
      myURI(theURI)
{
}

const TCollection_AsciiString& XmlLDrivers_NamespaceDef::Prefix() const
{
  return myPrefix;
}

const TCollection_AsciiString& XmlLDrivers_NamespaceDef::URI() const
{
  return myURI;
}
