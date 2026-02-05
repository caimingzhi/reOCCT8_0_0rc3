#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <TDataStd_RealEnum.hpp>
#include <TDF_DerivedAttribute.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

//! The basis to define a real number attribute.
class TDataStd_Real : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  //! Returns the default GUID for real numbers.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds, or creates, a Real attribute with default GUID and sets <value>.
  //! The Real attribute is returned. The Real dimension is Scalar by default.
  //! Use SetDimension to overwrite.
  //! Real methods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_Real> Set(const TDF_Label& label, const double value);

  //! Finds, or creates, a Real attribute with explicit GUID and sets <value>.
  //! The Real attribute is returned.
  //! Real methods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_Real> Set(const TDF_Label&     label,
                                                        const Standard_GUID& guid,
                                                        const double         value);

  Standard_EXPORT TDataStd_Real();

  //! Obsolete method that will be removed in next versions.
  //! This field is not supported in the persistence mechanism.
  Standard_DEPRECATED(
    "TDataStd_Real::SetDimension() is deprecated. Please avoid usage of this method.")
  Standard_EXPORT void SetDimension(const TDataStd_RealEnum DIM);

  //! Obsolete method that will be removed in next versions.
  //! This field is not supported in the persistence mechanism.
  Standard_DEPRECATED(
    "TDataStd_Real::GetDimension() is deprecated. Please avoid usage of this method.")
  Standard_EXPORT TDataStd_RealEnum GetDimension() const;

  //! Sets the real number V.
  Standard_EXPORT void Set(const double V);

  //! Sets the explicit GUID for the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  //! Sets default GUID for the attribute.
  Standard_EXPORT void SetID() override;

  //! Returns the real number value contained in the attribute.
  Standard_EXPORT double Get() const;

  //! Returns True if there is a reference on the same label
  Standard_EXPORT bool IsCaptured() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_Real, TDF_Attribute)

protected:
  double myValue;
  //! An obsolete field that will be removed in next versions.
  TDataStd_RealEnum myDimension;
  Standard_GUID     myID;
};
