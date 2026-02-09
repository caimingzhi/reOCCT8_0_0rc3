#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt;

class IGESSolid_VertexList : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_VertexList();

  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<gp_XYZ>>& vertices);

  Standard_EXPORT int NbVertices() const;

  Standard_EXPORT gp_Pnt Vertex(const int num) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_VertexList, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<gp_XYZ>> theVertices;
};
