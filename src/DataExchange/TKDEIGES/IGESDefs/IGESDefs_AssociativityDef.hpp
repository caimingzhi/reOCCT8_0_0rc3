#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESBasic_HArray1OfHArray1OfInteger;

class IGESDefs_AssociativityDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_AssociativityDef();

  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<int>>&            requirements,
                            const occ::handle<NCollection_HArray1<int>>&            orders,
                            const occ::handle<NCollection_HArray1<int>>&            numItems,
                            const occ::handle<IGESBasic_HArray1OfHArray1OfInteger>& items);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT int NbClassDefs() const;

  Standard_EXPORT bool IsBackPointerReq(const int ClassNum) const;

  Standard_EXPORT int BackPointerReq(const int ClassNum) const;

  Standard_EXPORT bool IsOrdered(const int ClassNum) const;

  Standard_EXPORT int ClassOrder(const int ClassNum) const;

  Standard_EXPORT int NbItemsPerClass(const int ClassNum) const;

  Standard_EXPORT int Item(const int ClassNum, const int ItemNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_AssociativityDef, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<int>>            theBackPointerReqs;
  occ::handle<NCollection_HArray1<int>>            theClassOrders;
  occ::handle<NCollection_HArray1<int>>            theNbItemsPerClass;
  occ::handle<IGESBasic_HArray1OfHArray1OfInteger> theItems;
};
