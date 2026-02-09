#pragma once

#include <DE_ConfigurationNode.hpp>
#include <RWMesh_CoordinateSystem.hpp>

class DEOBJ_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DEOBJ_ConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DEOBJ_ConfigurationNode();

  Standard_EXPORT DEOBJ_ConfigurationNode(const occ::handle<DEOBJ_ConfigurationNode>& theNode);

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

public:
  struct RWObj_InternalSection
  {

    double                  FileLengthUnit = 1.;
    RWMesh_CoordinateSystem SystemCS       = RWMesh_CoordinateSystem_Zup;
    RWMesh_CoordinateSystem FileCS         = RWMesh_CoordinateSystem_Yup;

    bool                    ReadSinglePrecision = false;
    bool                    ReadCreateShapes    = false;
    TCollection_AsciiString ReadRootPrefix;
    bool                    ReadFillDoc        = true;
    bool                    ReadFillIncomplete = true;

    int ReadMemoryLimitMiB = -1;

    TCollection_AsciiString WriteComment;
    TCollection_AsciiString WriteAuthor;
  } InternalParameters;
};
