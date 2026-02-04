#pragma once


#include <RWMesh_CafReader.hpp>

//! The Vrml mesh reader into XDE document.
class VrmlAPI_CafReader : public RWMesh_CafReader
{
  DEFINE_STANDARD_RTTIEXT(VrmlAPI_CafReader, RWMesh_CafReader)

protected:
  //! Read the mesh data from specified file.
  //! @param theStream   input stream
  //! @param theFile     path of additional files
  //! @param theProgress progress indicator
  //! @param theToProbe  flag for probing file without complete reading. Not supported.
  //! @return false when theToProbe is set to true or reading has completed with error.
  Standard_EXPORT bool performMesh(std::istream&                  theStream,
                                   const TCollection_AsciiString& theFile,
                                   const Message_ProgressRange&   theProgress,
                                   const bool                     theToProbe) override;
};

