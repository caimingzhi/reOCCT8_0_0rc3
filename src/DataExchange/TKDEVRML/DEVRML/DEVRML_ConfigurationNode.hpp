#pragma once

#include <DE_ConfigurationNode.hpp>
#include <RWMesh_CoordinateSystem.hpp>

//! The purpose of this class is to configure the transfer process for VRML format
//! Stores the necessary settings for DEVRML_Provider.
//! Configures and creates special provider to transfer VRML files.
//!
//! Nodes grouped by Vendor name and Format type.
//! The Vendor name is "OCC"
//! The Format type is "VRML"
//! The supported CAD extensions are ".vrml", ".wrl"
//! The import process is supported.
//! The export process is supported.
class DEVRML_ConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DEVRML_ConfigurationNode, DE_ConfigurationNode)
public:
  //! Initializes all field by default
  Standard_EXPORT DEVRML_ConfigurationNode();

  //! Copies values of all fields
  //! @param[in] theNode object to copy
  Standard_EXPORT DEVRML_ConfigurationNode(const occ::handle<DEVRML_ConfigurationNode>& theNode);

  //! Updates values according the resource
  //! @param[in] theResource input resource to use
  //! @return true if theResource loading has ended correctly
  Standard_EXPORT bool Load(const occ::handle<DE_ConfigurationContext>& theResource) override;

  //! Writes configuration to the string
  //! @return result resource string
  Standard_EXPORT TCollection_AsciiString Save() const override;

  //! Copies values of all fields
  //! @return new object with the same field values
  Standard_EXPORT occ::handle<DE_ConfigurationNode> Copy() const override;

  //! Creates new provider for the own format
  //! @return new created provider
  Standard_EXPORT occ::handle<DE_Provider> BuildProvider() override;

public:
  //! Checks the import supporting
  //! @return true if import is supported
  Standard_EXPORT bool IsImportSupported() const override;

  //! Checks the export supporting
  //! @return true if export is supported
  Standard_EXPORT bool IsExportSupported() const override;

  //! Checks for stream support.
  //! @return true if streams are supported
  Standard_EXPORT bool IsStreamSupported() const override;

  //! Gets CAD format name of associated provider
  //! @return provider CAD format
  Standard_EXPORT TCollection_AsciiString GetFormat() const override;

  //! Gets provider's vendor name of associated provider
  //! @return provider's vendor name
  Standard_EXPORT TCollection_AsciiString GetVendor() const override;

  //! Gets list of supported file extensions
  //! @return list of extensions
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
    // Read
    // clang-format off
    double ReadFileUnit = 1.; //<! file length units to convert from while reading the file, defined as scale factor for meters
    RWMesh_CoordinateSystem ReadFileCoordinateSys = RWMesh_CoordinateSystem_Yup; //<! coordinate system defined by Vrml file
    RWMesh_CoordinateSystem ReadSystemCoordinateSys = RWMesh_CoordinateSystem_Zup; //<! result coordinate system 
    bool ReadFillIncomplete = true; //<! fill the document with partially retrieved data even if reader has failed with error

    // Write
    WriteMode_WriterVersion WriterVersion = WriteMode_WriterVersion_2; //!< Setting up writer version (1/2)
    WriteMode_RepresentationType WriteRepresentationType = WriteMode_RepresentationType_Wireframe; //!< Setting up representation (shaded/wireframe/both)
    // clang-format on

  } InternalParameters;
};
