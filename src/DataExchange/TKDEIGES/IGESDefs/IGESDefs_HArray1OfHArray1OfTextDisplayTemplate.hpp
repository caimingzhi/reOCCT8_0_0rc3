#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

class IGESDefs_HArray1OfHArray1OfTextDisplayTemplate : public Standard_Transient
{

public:
  Standard_EXPORT IGESDefs_HArray1OfHArray1OfTextDisplayTemplate(const int low, const int up);

  Standard_EXPORT int Lower() const;

  Standard_EXPORT int Upper() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT void SetValue(
    const int                                                                           num,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>>& val);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>>
                  Value(const int num) const;

  DEFINE_STANDARD_RTTI_INLINE(IGESDefs_HArray1OfHArray1OfTextDisplayTemplate, Standard_Transient)

private:
  NCollection_Array1<occ::handle<Standard_Transient>> thelist;
};

