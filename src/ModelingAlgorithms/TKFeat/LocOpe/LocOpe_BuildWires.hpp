#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class LocOpe_WiresOnShape;

class LocOpe_BuildWires
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocOpe_BuildWires();

  Standard_EXPORT LocOpe_BuildWires(const NCollection_List<TopoDS_Shape>&   Ledges,
                                    const occ::handle<LocOpe_WiresOnShape>& PW);

  Standard_EXPORT void Perform(const NCollection_List<TopoDS_Shape>&   Ledges,
                               const occ::handle<LocOpe_WiresOnShape>& PW);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Result() const;

private:
  bool                           myDone;
  NCollection_List<TopoDS_Shape> myRes;
};

