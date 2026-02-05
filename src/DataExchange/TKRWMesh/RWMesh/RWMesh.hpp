#pragma once

#include <TDF_Label.hpp>
#include <RWMesh_NameFormat.hpp>

//! Auxiliary tools for RWMesh package.
class RWMesh
{
public:
  //! Read name attribute from label.
  Standard_EXPORT static TCollection_AsciiString ReadNameAttribute(const TDF_Label& theLabel);

  //! Generate name for specified labels.
  //! @param[in] theFormat   name format to apply
  //! @param[in] theLabel    instance label
  //! @param[in] theRefLabel product label
  Standard_EXPORT static TCollection_AsciiString FormatName(RWMesh_NameFormat theFormat,
                                                            const TDF_Label&  theLabel,
                                                            const TDF_Label&  theRefLabel);
};
