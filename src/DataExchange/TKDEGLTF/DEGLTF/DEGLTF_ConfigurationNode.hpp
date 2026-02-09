#pragma once

#include <DE_ConfigurationNode.hpp>
#include <RWGltf_WriterTrsfFormat.hpp>
#include <RWMesh_CoordinateSystem.hpp>
#include <RWMesh_NameFormat.hpp>

class DEGLTF_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DEGLTF_ConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DEGLTF_ConfigurationNode();

  Standard_EXPORT DEGLTF_ConfigurationNode(const occ::handle<DEGLTF_ConfigurationNode>& theNode);

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
  struct RWGltf_InternalSection
  {

    double                  FileLengthUnit = 1.;
    RWMesh_CoordinateSystem SystemCS       = RWMesh_CoordinateSystem_Zup;
    RWMesh_CoordinateSystem FileCS         = RWMesh_CoordinateSystem_Yup;

    bool                    ReadSinglePrecision = true;
    bool                    ReadCreateShapes    = false;
    TCollection_AsciiString ReadRootPrefix;
    bool                    ReadFillDoc               = true;
    bool                    ReadFillIncomplete        = true;
    int                     ReadMemoryLimitMiB        = -1;
    bool                    ReadParallel              = false;
    bool                    ReadSkipEmptyNodes        = true;
    bool                    ReadLoadAllScenes         = false;
    bool                    ReadUseMeshNameAsFallback = true;
    bool                    ReadSkipLateDataLoading   = false;
    bool                    ReadKeepLateData          = true;
    bool                    ReadPrintDebugMessages    = false;
    bool                    ReadApplyScale            = true;

    TCollection_AsciiString WriteComment;
    TCollection_AsciiString WriteAuthor;
    RWGltf_WriterTrsfFormat WriteTrsfFormat         = RWGltf_WriterTrsfFormat_Compact;
    RWMesh_NameFormat       WriteNodeNameFormat     = RWMesh_NameFormat_InstanceOrProduct;
    RWMesh_NameFormat       WriteMeshNameFormat     = RWMesh_NameFormat_Product;
    bool                    WriteForcedUVExport     = false;
    bool                    WriteEmbedTexturesInGlb = true;
    bool                    WriteMergeFaces         = false;
    bool                    WriteSplitIndices16     = false;

  } InternalParameters;
};
