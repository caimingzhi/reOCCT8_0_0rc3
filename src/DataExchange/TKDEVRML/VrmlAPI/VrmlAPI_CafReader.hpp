#pragma once

#include <RWMesh_CafReader.hpp>

class VrmlAPI_CafReader : public RWMesh_CafReader
{
  DEFINE_STANDARD_RTTIEXT(VrmlAPI_CafReader, RWMesh_CafReader)

protected:
  Standard_EXPORT bool performMesh(std::istream&                  theStream,
                                   const TCollection_AsciiString& theFile,
                                   const Message_ProgressRange&   theProgress,
                                   const bool                     theToProbe) override;
};
