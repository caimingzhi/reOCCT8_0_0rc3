#pragma once

#include <DE_ConfigurationNode.hpp>

class DESTL_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DESTL_ConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DESTL_ConfigurationNode();

  Standard_EXPORT DESTL_ConfigurationNode(const occ::handle<DESTL_ConfigurationNode>& theNode);

  Standard_EXPORT bool Load(const occ::handle<DE_ConfigurationContext>& theResource) override;

  Standard_EXPORT TCollection_AsciiString Save() const override;

  Standard_EXPORT occ::handle<DE_ConfigurationNode> Copy() const override;

  Standard_EXPORT occ::handle<DE_Provider> BuildProvider() override;

public:
  Standard_EXPORT bool IsImportSupported() const override;

  Standard_EXPORT bool IsExportSupported() const override;

  Standard_EXPORT bool IsStreamSupported() const override;

  Standard_EXPORT TCollection_AsciiString GetFormat() const override;

  Standard_EXPORT TCollection_AsciiString GetVendor() const override;

  Standard_EXPORT NCollection_List<TCollection_AsciiString> GetExtensions() const override;

  Standard_EXPORT bool CheckContent(
    const occ::handle<NCollection_Buffer>& theBuffer) const override;

public:
  struct RWStl_InternalSection
  {

    double ReadMergeAngle = 90.;
    bool   ReadBRep       = false;

    bool WriteAscii = true;

  } InternalParameters;
};
