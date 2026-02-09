#pragma once

#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>

class DE_ConfigurationContext;
class DE_Provider;
class DE_Wrapper;
class NCollection_Buffer;

class DE_ConfigurationNode : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(DE_ConfigurationNode, Standard_Transient)
public:
  Standard_EXPORT DE_ConfigurationNode();

  Standard_EXPORT DE_ConfigurationNode(
    const occ::handle<DE_ConfigurationNode>& theConfigurationNode);

  Standard_EXPORT virtual bool Load(const TCollection_AsciiString& theResourcePath = "");

  Standard_EXPORT virtual bool Load(const occ::handle<DE_ConfigurationContext>& theResource) = 0;

  Standard_EXPORT bool Save(const TCollection_AsciiString& theResourcePath) const;

  Standard_EXPORT virtual TCollection_AsciiString Save() const = 0;

  Standard_EXPORT virtual occ::handle<DE_Provider> BuildProvider() = 0;

  Standard_EXPORT virtual occ::handle<DE_ConfigurationNode> Copy() const = 0;

  Standard_EXPORT virtual bool UpdateLoad(const bool theToImport, const bool theToKeep);

public:
  Standard_EXPORT virtual bool IsImportSupported() const;

  Standard_EXPORT virtual bool IsExportSupported() const;

  Standard_EXPORT virtual bool IsStreamSupported() const;

  Standard_EXPORT virtual TCollection_AsciiString GetFormat() const = 0;

  Standard_EXPORT virtual TCollection_AsciiString GetVendor() const = 0;

  Standard_EXPORT virtual NCollection_List<TCollection_AsciiString> GetExtensions() const = 0;

  Standard_EXPORT virtual bool CheckExtension(const TCollection_AsciiString& theExtension) const;

  Standard_EXPORT virtual bool CheckContent(const occ::handle<NCollection_Buffer>& theBuffer) const;

public:
  bool IsEnabled() const { return myIsEnabled; }

  void SetEnabled(const bool theIsLoaded) { myIsEnabled = theIsLoaded; }

  Standard_EXPORT virtual void CustomActivation(const NCollection_List<TCollection_AsciiString>&) {
  };

public:
  struct DE_SectionGlobal
  {

    double LengthUnit = 1.0;
    double SystemUnit = 1.0;

  } GlobalParameters;

public:
  Standard_EXPORT virtual void Register(const occ::handle<DE_Wrapper>& theWrapper) const;

  Standard_EXPORT virtual void UnRegister(const occ::handle<DE_Wrapper>& theWrapper) const;

private:
  bool myIsEnabled;
};
