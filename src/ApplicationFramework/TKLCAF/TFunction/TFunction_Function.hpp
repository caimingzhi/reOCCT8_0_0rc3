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

//! Provides the following two services
//! -   a link to an evaluation driver
//! -   the means of providing a link between a
//! function and an evaluation driver.
class TFunction_Function : public TDF_Attribute
{

public:
  //! Static methods:
  //! ==============
  //! Finds or Creates a function attribute on the label <L>.
  //! Returns the function attribute.
  Standard_EXPORT static occ::handle<TFunction_Function> Set(const TDF_Label& L);

  //! Finds or Creates a function attribute on the label <L>.
  //! Sets a driver ID to the function.
  //! Returns the function attribute.
  Standard_EXPORT static occ::handle<TFunction_Function> Set(const TDF_Label&     L,
                                                             const Standard_GUID& DriverID);

  //! Returns the GUID for functions.
  //! Returns a function found on the label.
  //! Instance methods:
  //! ================
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TFunction_Function();

  //! Returns the GUID for this function's driver.
  const Standard_GUID& GetDriverGUID() const { return myDriverGUID; }

  //! Sets the driver for this function as that
  //! identified by the GUID guid.
  Standard_EXPORT void SetDriverGUID(const Standard_GUID& guid);

  //! Returns true if the execution failed
  bool Failed() const { return myFailure != 0; }

  //! Sets the failed index.
  Standard_EXPORT void SetFailure(const int mode = 0);

  //! Returns an index of failure if the execution of this function failed.
  //! If this integer value is 0, no failure has occurred.
  //! Implementation of Attribute methods:
  //! ===================================
  int GetFailure() const { return myFailure; }

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TFunction_Function, TDF_Attribute)

private:
  Standard_GUID myDriverGUID;
  int           myFailure;
};
