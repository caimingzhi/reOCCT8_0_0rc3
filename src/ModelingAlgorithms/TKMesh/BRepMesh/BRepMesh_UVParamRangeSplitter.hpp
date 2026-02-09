#pragma once

#include <BRepMesh_DefaultRangeSplitter.hpp>
#include <IMeshData_Types.hpp>

class BRepMesh_UVParamRangeSplitter : public BRepMesh_DefaultRangeSplitter
{
public:
  BRepMesh_UVParamRangeSplitter()
      : myAllocator(new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE)),
        myUParams(1, myAllocator),
        myVParams(1, myAllocator)
  {
  }

  ~BRepMesh_UVParamRangeSplitter() override = default;

  void Reset(const IMeshData::IFaceHandle& theDFace,
             const IMeshTools_Parameters&  theParameters) override
  {
    BRepMesh_DefaultRangeSplitter::Reset(theDFace, theParameters);
    myUParams.Clear();
    myVParams.Clear();
    myAllocator->Reset(false);
  }

public:
  const IMeshData::IMapOfReal& GetParametersU() const { return myUParams; }

  IMeshData::IMapOfReal& GetParametersU() { return myUParams; }

  const IMeshData::IMapOfReal& GetParametersV() const { return myVParams; }

  IMeshData::IMapOfReal& GetParametersV() { return myVParams; }

private:
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::IMapOfReal                 myUParams;
  IMeshData::IMapOfReal                 myVParams;
};
