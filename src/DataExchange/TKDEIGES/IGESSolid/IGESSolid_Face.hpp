#pragma once

#include <Standard.hpp>

#include <IGESSolid_Loop.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESSolid_Loop;

class IGESSolid_Face : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Face();

  Standard_EXPORT void Init(
    const occ::handle<IGESData_IGESEntity>&                              aSurface,
    const bool                                                           outerLoopFlag,
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Loop>>>& loops);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  Standard_EXPORT int NbLoops() const;

  Standard_EXPORT bool HasOuterLoop() const;

  Standard_EXPORT occ::handle<IGESSolid_Loop> Loop(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Face, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity>                              theSurface;
  bool                                                          hasOuterLoop;
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Loop>>> theLoops;
};
