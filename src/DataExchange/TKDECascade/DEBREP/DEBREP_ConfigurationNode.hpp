#pragma once

#include <DE_ConfigurationNode.hpp>

#include <BinTools_FormatVersion.hpp>
#include <TopTools_FormatVersion.hpp>

class DEBREP_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DEBREP_ConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DEBREP_ConfigurationNode();

  Standard_EXPORT DEBREP_ConfigurationNode(const occ::handle<DEBREP_ConfigurationNode>& theNode);

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
  struct DEBRep_InternalSection
  {

    bool WriteBinary = true;

    BinTools_FormatVersion WriteVersionBin   = BinTools_FormatVersion_CURRENT;
    TopTools_FormatVersion WriteVersionAscii = TopTools_FormatVersion_CURRENT;

    bool WriteTriangles = true;
    bool WriteNormals   = true;

  } InternalParameters;
};
