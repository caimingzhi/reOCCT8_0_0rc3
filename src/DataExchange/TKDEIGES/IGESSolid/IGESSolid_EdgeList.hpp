#pragma once

#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESSolid_VertexList.hpp>
#include <Standard_Integer.hpp>
class IGESSolid_VertexList;

class IGESSolid_EdgeList : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESSolid_EdgeList();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&  curves,
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_VertexList>>>& startVertexList,
    const occ::handle<NCollection_HArray1<int>>&                               startVertexIndex,
    const occ::handle<NCollection_HArray1<occ::handle<IGESSolid_VertexList>>>& endVertexList,
    const occ::handle<NCollection_HArray1<int>>&                               endVertexIndex);

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Curve(const int num) const;

  Standard_EXPORT occ::handle<IGESSolid_VertexList> StartVertexList(const int num) const;

  Standard_EXPORT int StartVertexIndex(const int num) const;

  Standard_EXPORT occ::handle<IGESSolid_VertexList> EndVertexList(const int num) const;

  Standard_EXPORT int EndVertexIndex(const int num) const;

  DEFINE_STANDARD_RTTIEXT(IGESSolid_EdgeList, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>  theCurves;
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_VertexList>>> theStartVertexList;
  occ::handle<NCollection_HArray1<int>>                               theStartVertexIndex;
  occ::handle<NCollection_HArray1<occ::handle<IGESSolid_VertexList>>> theEndVertexList;
  occ::handle<NCollection_HArray1<int>>                               theEndVertexIndex;
};
