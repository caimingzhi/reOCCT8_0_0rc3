#pragma once

#include <TDF_Label.hpp>
#include <RWMesh_NameFormat.hpp>

class RWMesh
{
public:
  Standard_EXPORT static TCollection_AsciiString ReadNameAttribute(const TDF_Label& theLabel);

  Standard_EXPORT static TCollection_AsciiString FormatName(RWMesh_NameFormat theFormat,
                                                            const TDF_Label&  theLabel,
                                                            const TDF_Label&  theRefLabel);
};
