#pragma once

#include <DE_ConfigurationNode.hpp>
#include <Precision.hpp>
#include <RWMesh_CoordinateSystem.hpp>

class DE_ConfigurationContext;

class DEPLY_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DEPLY_ConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DEPLY_ConfigurationNode();

  Standard_EXPORT DEPLY_ConfigurationNode(const occ::handle<DEPLY_ConfigurationNode>& theNode);

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
  struct RWPly_InternalSection
  {

    double                  FileLengthUnit = 1.;
    RWMesh_CoordinateSystem SystemCS       = RWMesh_CoordinateSystem_Zup;
    RWMesh_CoordinateSystem FileCS         = RWMesh_CoordinateSystem_Yup;

    bool WriteNormals   = true;
    bool WriteColors    = true;
    bool WriteTexCoords = false;
    bool WritePartId    = true;
    bool WriteFaceId    = false;

    TCollection_AsciiString WriteComment;
    TCollection_AsciiString WriteAuthor;
  } InternalParameters;
};
