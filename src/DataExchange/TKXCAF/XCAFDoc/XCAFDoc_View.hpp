#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
class Standard_GUID;
class TDF_Label;
class XCAFView_Object;

// resolve name collisions with WinAPI headers
#ifdef GetObject
  #undef GetObject
#endif

//! Attribute to store view
class XCAFDoc_View : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_View();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_View> Set(const TDF_Label& theLabel);

  Standard_EXPORT const Standard_GUID& ID() const override;

  //! Updates parent's label and its sub-labels with data taken from theViewObject.
  //! Old data associated with the label will be lost.
  Standard_EXPORT void SetObject(const occ::handle<XCAFView_Object>& theViewObject);

  //! Returns view object data taken from the paren's label and its sub-labels.
  Standard_EXPORT occ::handle<XCAFView_Object> GetObject() const;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_View, TDataStd_GenericEmpty)
};

