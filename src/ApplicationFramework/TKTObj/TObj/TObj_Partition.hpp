#pragma once

#include <TObj_Object.hpp>
#include <TObj_Persistence.hpp>

class TObj_Partition : public TObj_Object
{
protected:
  enum DataTag
  {
    DataTag_First = TObj_Object::DataTag_Last,
    DataTag_LastIndex,
    DataTag_Last = DataTag_First + 100
  };

protected:
  Standard_EXPORT TObj_Partition(const TDF_Label& theLabel, const bool theSetName = true);

public:
  static Standard_EXPORT occ::handle<TObj_Partition> Create(const TDF_Label& theLabel,
                                                            const bool       theSetName = true);

public:
  Standard_EXPORT bool SetName(
    const occ::handle<TCollection_HExtendedString>& theName) const override;

public:
  Standard_EXPORT void AfterRetrieval() override;

public:
  Standard_EXPORT TDF_Label NewLabel() const;

  Standard_EXPORT void SetNamePrefix(const occ::handle<TCollection_HExtendedString>& thePrefix);

  occ::handle<TCollection_HExtendedString> GetNamePrefix() const { return myPrefix; }

  Standard_EXPORT occ::handle<TCollection_HExtendedString> GetNewName(
    const bool theIsToChangeCount = true);

  Standard_EXPORT int GetLastIndex() const;

  Standard_EXPORT void SetLastIndex(const int theIndex);

public:
  static Standard_EXPORT occ::handle<TObj_Partition> GetPartition(
    const occ::handle<TObj_Object>& theObject);

public:
  virtual bool Update() { return true; }

protected:
  Standard_EXPORT bool copyData(const occ::handle<TObj_Object>& theTargetObject) override;

private:
  occ::handle<TCollection_HExtendedString> myPrefix;

protected:
  DECLARE_TOBJOCAF_PERSISTENCE(TObj_Partition, TObj_Object)

public:
  DEFINE_STANDARD_RTTIEXT(TObj_Partition, TObj_Object)

public:
  friend class TObj_Model;
};

#ifdef _MSC_VER
  #pragma once
#endif
