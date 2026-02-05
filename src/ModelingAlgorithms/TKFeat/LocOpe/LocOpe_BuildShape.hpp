#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

class LocOpe_BuildShape
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_BuildShape();

  //! Builds shape(s) from the list <L>. Uses only the
  //! faces of <L>.
  LocOpe_BuildShape(const NCollection_List<TopoDS_Shape>& L);

  //! Builds shape(s) from the list <L>. Uses only the
  //! faces of <L>.
  Standard_EXPORT void Perform(const NCollection_List<TopoDS_Shape>& L);

  const TopoDS_Shape& Shape() const;

private:
  TopoDS_Shape myRes;
};

inline LocOpe_BuildShape::LocOpe_BuildShape() = default;

//=================================================================================================

inline LocOpe_BuildShape::LocOpe_BuildShape(const NCollection_List<TopoDS_Shape>& L)
{
  Perform(L);
}

//=================================================================================================

inline const TopoDS_Shape& LocOpe_BuildShape::Shape() const
{
  return myRes;
}
