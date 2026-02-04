#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

class TopOpeBRepDS_Marker : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepDS_Marker();

  Standard_EXPORT void Reset();

  Standard_EXPORT void Set(const int i, const bool b);

  Standard_EXPORT void Set(const bool b, const int n, void* const a);

  Standard_EXPORT bool GetI(const int i) const;

  Standard_EXPORT void Allocate(const int n);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_Marker, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<bool>> myhe;
  int                                    myne;
};

