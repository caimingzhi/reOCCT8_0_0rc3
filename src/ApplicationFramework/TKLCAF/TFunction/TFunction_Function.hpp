#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_GUID.hpp>
#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TDF_RelocationTable;
class TDF_DataSet;

class TFunction_Function : public TDF_Attribute
{

public:
  Standard_EXPORT static occ::handle<TFunction_Function> Set(const TDF_Label& L);

  Standard_EXPORT static occ::handle<TFunction_Function> Set(const TDF_Label&     L,
                                                             const Standard_GUID& DriverID);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TFunction_Function();

  const Standard_GUID& GetDriverGUID() const { return myDriverGUID; }

  Standard_EXPORT void SetDriverGUID(const Standard_GUID& guid);

  bool Failed() const { return myFailure != 0; }

  Standard_EXPORT void SetFailure(const int mode = 0);

  int GetFailure() const { return myFailure; }

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TFunction_Function, TDF_Attribute)

private:
  Standard_GUID myDriverGUID;
  int           myFailure;
};
