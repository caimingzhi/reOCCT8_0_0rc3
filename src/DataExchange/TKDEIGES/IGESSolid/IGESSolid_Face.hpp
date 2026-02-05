#pragma once

#include <Standard.hpp>

#include <IGESSolid_Loop.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESSolid_Loop;

//! defines Face, Type <510> Form Number <1>
//! in package IGESSolid
//! Face entity is a bound (partial) which has finite area
class IGESSolid_Face : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Face();

  //! This method is used to set the fields of the class Face
  //! - aSurface      : Pointer to the underlying surface
  //! - outerLoopFlag : True means the first loop is the outer loop
  //! - loops         : Array of loops bounding the face
  Standard_EXPORT void Init(
    const occ::handle<IGESData_IGESEntity>&                              aSurface,
    const bool                                                           outerLoopFlag,
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Loop>>>& loops);

  //! returns the underlying surface of the face
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  //! returns the number of the loops bounding the face
  Standard_EXPORT int NbLoops() const;

  //! checks whether there is an outer loop or not
  Standard_EXPORT bool HasOuterLoop() const;

  //! returns the Index'th loop that bounds the face
  //! raises exception if Index < 0 or Index >= NbLoops
  Standard_EXPORT occ::handle<IGESSolid_Loop> Loop(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Face, IGESData_IGESEntity)

private:
  occ::handle<IGESData_IGESEntity>                              theSurface;
  bool                                                          hasOuterLoop;
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Loop>>> theLoops;
};
