#pragma once

#include <TObj_Object.hpp>

#include <TDF_Attribute.hpp>

class Standard_GUID;
class TDF_Label;

class TObj_TObject : public TDF_Attribute
{
public:
  Standard_EXPORT TObj_TObject();

  static Standard_EXPORT const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  static Standard_EXPORT occ::handle<TObj_TObject> Set(const TDF_Label&                theLabel,
                                                       const occ::handle<TObj_Object>& theElem);

public:
  Standard_EXPORT void Set(const occ::handle<TObj_Object>& theElem);

  Standard_EXPORT occ::handle<TObj_Object> Get() const;

public:
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  Standard_EXPORT void BeforeForget() override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt) override;

private:
  occ::handle<TObj_Object> myElem;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_TObject, TDF_Attribute)
};

#ifdef _MSC_VER
  #pragma once
#endif
