#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_DataMap.hpp>
#include <MeshVS_DataSource.hpp>

class MeshVS_DataSource3D : public MeshVS_DataSource
{

public:
  Standard_EXPORT occ::handle<NCollection_HArray1<NCollection_Sequence<int>>> GetPrismTopology(
    const int BasePoints) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<NCollection_Sequence<int>>> GetPyramidTopology(
    const int BasePoints) const;

  Standard_EXPORT static occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>
    CreatePrismTopology(const int BasePoints);

  Standard_EXPORT static occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>
    CreatePyramidTopology(const int BasePoints);

  DEFINE_STANDARD_RTTIEXT(MeshVS_DataSource3D, MeshVS_DataSource)

private:
  NCollection_DataMap<int, occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>>
    myPrismTopos;
  NCollection_DataMap<int, occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>>
    myPyramidTopos;
};
