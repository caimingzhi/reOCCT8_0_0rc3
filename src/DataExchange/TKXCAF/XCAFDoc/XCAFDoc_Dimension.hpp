#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
class Standard_GUID;
class TDF_Label;
class XCAFDimTolObjects_DimensionObject;

#ifdef GetObject
  #undef GetObject
#endif

class XCAFDoc_Dimension : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_Dimension();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_Dimension> Set(const TDF_Label& theLabel);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void SetObject(
    const occ::handle<XCAFDimTolObjects_DimensionObject>& theDimensionObject);

  Standard_EXPORT occ::handle<XCAFDimTolObjects_DimensionObject> GetObject() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_Dimension, TDataStd_GenericEmpty)
};
