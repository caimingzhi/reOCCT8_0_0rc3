#pragma once

#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>

class TObj_Object;
class Standard_GUID;

class TObj_TReference : public TDF_Attribute
{
public:
  Standard_EXPORT TObj_TReference();

  static Standard_EXPORT const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  static Standard_EXPORT occ::handle<TObj_TReference> Set(
    const TDF_Label&                theLabel,
    const occ::handle<TObj_Object>& theObject,
    const occ::handle<TObj_Object>& theMaster);

public:
  Standard_EXPORT void Set(const occ::handle<TObj_Object>& theObject,
                           const TDF_Label&                theMasterLabel);

  Standard_EXPORT void Set(const TDF_Label& theLabel, const TDF_Label& theMasterLabel);

  Standard_EXPORT occ::handle<TObj_Object> Get() const;

  TDF_Label GetMasterLabel() const { return myMasterLabel; }

  TDF_Label GetLabel() const { return myLabel; }

public:
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  Standard_EXPORT void BeforeForget() override;

  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& theDelta,
                                  const bool                             isForced = false) override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& theDelta,
                                 const bool                             isForced = false) override;

  Standard_EXPORT void AfterResume() override;

  Standard_EXPORT bool AfterRetrieval(const bool forceIt = false) override;

private:
  TDF_Label myLabel;
  TDF_Label myMasterLabel;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_TReference, TDF_Attribute)
};

#ifdef _MSC_VER
  #pragma once
#endif
