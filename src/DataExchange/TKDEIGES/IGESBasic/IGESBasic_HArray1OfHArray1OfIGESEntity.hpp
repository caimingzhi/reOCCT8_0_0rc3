#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

class IGESBasic_HArray1OfHArray1OfIGESEntity : public Standard_Transient
{

public:
  Standard_EXPORT IGESBasic_HArray1OfHArray1OfIGESEntity(const int low, const int up);

  Standard_EXPORT int Lower() const;

  Standard_EXPORT int Upper() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT void SetValue(
    const int                                                                 num,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& val);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Value(
    const int num) const;

  DEFINE_STANDARD_RTTI_INLINE(IGESBasic_HArray1OfHArray1OfIGESEntity, Standard_Transient)

private:
  NCollection_Array1<occ::handle<Standard_Transient>> thelist;
};
