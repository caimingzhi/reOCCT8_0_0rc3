#pragma once

#include <Standard.hpp>

#include <IGESSolid_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESSolid_Face;

class IGESSolid_Shell : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_Shell();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Face>>>& allFaces,
    const occ::handle<NCollection_HArray1<int>>&                         allOrient);

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT void SetClosed(const bool closed);

  Standard_EXPORT int NbFaces() const;

  Standard_EXPORT occ::handle<IGESSolid_Face> Face(const int Index) const;

  Standard_EXPORT bool Orientation(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_Shell, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_Face>>> theFaces;
  occ::handle<NCollection_HArray1<int>>                         theOrientation;
};
