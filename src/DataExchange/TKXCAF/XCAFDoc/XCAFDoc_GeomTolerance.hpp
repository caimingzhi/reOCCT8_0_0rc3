#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
class Standard_GUID;
class TDF_Label;
class XCAFDimTolObjects_GeomToleranceObject;

// resolve name collisions with WinAPI headers
#ifdef GetObject
  #undef GetObject
#endif

//! Attribute to store dimension and tolerance
class XCAFDoc_GeomTolerance : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_GeomTolerance();

  Standard_EXPORT XCAFDoc_GeomTolerance(const occ::handle<XCAFDoc_GeomTolerance>& theObj);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_GeomTolerance> Set(const TDF_Label& theLabel);

  //! Updates parent's label and its sub-labels with data taken from theGeomToleranceObject.
  //! Old data associated with the label will be lost.
  Standard_EXPORT void SetObject(
    const occ::handle<XCAFDimTolObjects_GeomToleranceObject>& theGeomToleranceObject);

  //! Returns geometry tolerance object data taken from the paren's label and its sub-labels.
  Standard_EXPORT occ::handle<XCAFDimTolObjects_GeomToleranceObject> GetObject() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_GeomTolerance, TDataStd_GenericEmpty)
};

