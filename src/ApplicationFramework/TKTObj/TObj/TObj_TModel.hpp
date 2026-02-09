#pragma once

#include <TDF_Attribute.hpp>

class TObj_Model;

class TObj_TModel : public TDF_Attribute
{
public:
  Standard_EXPORT TObj_TModel();

  static Standard_EXPORT const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  Standard_EXPORT void Set(const occ::handle<TObj_Model>& theModel);

  Standard_EXPORT occ::handle<TObj_Model> Model() const;

public:
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

private:
  occ::handle<TObj_Model> myModel;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_TModel, TDF_Attribute)
};

#ifdef _MSC_VER
  #pragma once
#endif
