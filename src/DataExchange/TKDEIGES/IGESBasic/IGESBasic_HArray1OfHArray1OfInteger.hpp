#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_HArray1.hpp>

class IGESBasic_HArray1OfHArray1OfInteger : public Standard_Transient
{

public:
  Standard_EXPORT IGESBasic_HArray1OfHArray1OfInteger(const int low, const int up);

  Standard_EXPORT int Lower() const;

  Standard_EXPORT int Upper() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT void SetValue(const int num, const occ::handle<NCollection_HArray1<int>>& val);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> Value(const int num) const;

  DEFINE_STANDARD_RTTI_INLINE(IGESBasic_HArray1OfHArray1OfInteger, Standard_Transient)

private:
  NCollection_Array1<occ::handle<Standard_Transient>> thelist;
};
