#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
class Standard_GUID;
class TDF_Label;
class XCAFDimTolObjects_DimensionObject;

// resolve name collisions with WinAPI headers
#ifdef GetObject
  #undef GetObject
#endif

//! Attribute that identifies a dimension in the GD&T table.
//! Its parent label is used as a container to store data provided
//! by XCAFDimTolObjects_DimensionObject.
class XCAFDoc_Dimension : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_Dimension();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_Dimension> Set(const TDF_Label& theLabel);

  Standard_EXPORT const Standard_GUID& ID() const override;

  //! Updates parent's label and its sub-labels with data taken from theDimensionObject.
  //! Old data associated with the label will be lost.
  Standard_EXPORT void SetObject(
    const occ::handle<XCAFDimTolObjects_DimensionObject>& theDimensionObject);

  //! Returns dimension object data taken from the parent's label and its sub-labels.
  Standard_EXPORT occ::handle<XCAFDimTolObjects_DimensionObject> GetObject() const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_Dimension, TDataStd_GenericEmpty)
};

