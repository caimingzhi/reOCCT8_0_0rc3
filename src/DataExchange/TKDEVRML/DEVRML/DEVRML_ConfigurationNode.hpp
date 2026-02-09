#pragma once

#include <DE_ConfigurationNode.hpp>
#include <RWMesh_CoordinateSystem.hpp>

class DEVRML_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DEVRML_ConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DEVRML_ConfigurationNode();

  Standard_EXPORT DEVRML_ConfigurationNode(const occ::handle<DEVRML_ConfigurationNode>& theNode);

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

public:
  enum WriteMode_WriterVersion
  {
    WriteMode_WriterVersion_1 = 1,
    WriteMode_WriterVersion_2
  };

  enum WriteMode_RepresentationType
  {
    WriteMode_RepresentationType_Shaded = 0,
    WriteMode_RepresentationType_Wireframe,
    WriteMode_RepresentationType_Both
  };

  struct Vrml_InternalSection
  {

    double                  ReadFileUnit            = 1.;
    RWMesh_CoordinateSystem ReadFileCoordinateSys   = RWMesh_CoordinateSystem_Yup;
    RWMesh_CoordinateSystem ReadSystemCoordinateSys = RWMesh_CoordinateSystem_Zup;
    bool                    ReadFillIncomplete      = true;

    WriteMode_WriterVersion      WriterVersion           = WriteMode_WriterVersion_2;
    WriteMode_RepresentationType WriteRepresentationType = WriteMode_RepresentationType_Wireframe;

  } InternalParameters;
};
