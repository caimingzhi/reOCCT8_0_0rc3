#pragma once

#include <DE_ConfigurationNode.hpp>
#include <PCDM_ReaderFilter.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>

class DEXCAF_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DEXCAF_ConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DEXCAF_ConfigurationNode();

  Standard_EXPORT DEXCAF_ConfigurationNode(const occ::handle<DEXCAF_ConfigurationNode>& theNode);

  Standard_EXPORT bool Load(const occ::handle<DE_ConfigurationContext>& theResource) override;

  Standard_EXPORT TCollection_AsciiString Save() const override;

  Standard_EXPORT occ::handle<DE_ConfigurationNode> Copy() const override;

  Standard_EXPORT occ::handle<DE_Provider> BuildProvider() override;

public:
  Standard_EXPORT bool IsImportSupported() const override;

  Standard_EXPORT bool IsExportSupported() const override;

  Standard_EXPORT TCollection_AsciiString GetFormat() const override;

  Standard_EXPORT TCollection_AsciiString GetVendor() const override;

  Standard_EXPORT NCollection_List<TCollection_AsciiString> GetExtensions() const override;

  Standard_EXPORT bool CheckContent(
    const occ::handle<NCollection_Buffer>& theBuffer) const override;

public:
  struct XCAFDoc_InternalSection
  {

    PCDM_ReaderFilter::AppendMode ReadAppendMode = PCDM_ReaderFilter::AppendMode::AppendMode_Forbid;
    NCollection_List<TCollection_AsciiString> ReadSkipValues;
    NCollection_List<TCollection_AsciiString> ReadValues;

  } InternalParameters;
};
