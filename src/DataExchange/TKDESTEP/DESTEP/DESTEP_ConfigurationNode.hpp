#pragma once

#include <DESTEP_Parameters.hpp>
#include <DE_ShapeFixConfigurationNode.hpp>
#include <Resource_FormatType.hpp>
#include <STEPControl_StepModelType.hpp>
#include <UnitsMethods_LengthUnit.hpp>

class DESTEP_ConfigurationNode : public DE_ShapeFixConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DESTEP_ConfigurationNode, DE_ShapeFixConfigurationNode)
public:
  Standard_EXPORT DESTEP_ConfigurationNode();

  Standard_EXPORT DESTEP_ConfigurationNode(const occ::handle<DESTEP_ConfigurationNode>& theNode);

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
  DESTEP_Parameters InternalParameters;
};
