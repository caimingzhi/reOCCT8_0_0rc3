#include <Bnd_BoundSortBox.hpp>

#include <gp_Pln.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_MultiplyDefined.hpp>
#include <Standard_NullValue.hpp>

static int getBnd_VoxelGridResolution(const int theBoxesCount)
{
  if (theBoxesCount > 40000)
  {
    return 128;
  }
  if (theBoxesCount > 10000)
  {
    return 64;
  }
  if (theBoxesCount > 1000)
  {
    return 32;
  }
  if (theBoxesCount > 100)
  {
    return 16;
  }
  return 8;
}

class Bnd_VoxelGrid : public Standard_Transient
{
public:
  DEFINE_STANDARD_RTTIEXT(Bnd_VoxelGrid, Standard_Transient)

public:
  using VectorInt = NCollection_Vector<int>;

private:
  using SliceArray = NCollection_Array1<VectorInt>;

public:
  Bnd_VoxelGrid(const int theResolution, const int theExpectedBoxCount);

  void AddBox(const int theBoxIndex, const std::array<int, 6>& theVoxelBox);

  const VectorInt* GetSliceX(const int theVoxelIndex) const;

  const VectorInt* GetSliceY(const int theVoxelIndex) const;

  const VectorInt* GetSliceZ(const int theVoxelIndex) const;

private:
  void AppendSliceX(const int theVoxelIndexMin, const int theVoxelIndexMax, const int theBoxIndex);

  void AppendSliceY(const int theVoxelIndexMin, const int theVoxelIndexMax, const int theBoxIndex);

  void AppendSliceZ(const int theVoxelIndexMin, const int theVoxelIndexMax, const int theBoxIndex);

private:
  occ::handle<NCollection_IncAllocator> myAllocator;
  SliceArray                            mySlicesX;
  SliceArray                            mySlicesY;
  SliceArray                            mySlicesZ;
};

IMPLEMENT_STANDARD_RTTIEXT(Bnd_VoxelGrid, Standard_Transient)

Bnd_VoxelGrid::Bnd_VoxelGrid(const int theResolution, const int theExpectedBoxCount)
    : myAllocator(new NCollection_IncAllocator()),
      mySlicesX(0, theResolution - 1),
      mySlicesY(0, theResolution - 1),
      mySlicesZ(0, theResolution - 1)
{

  const int anIncrement = std::max(theExpectedBoxCount / theResolution, 16);
  for (int i = 0; i < theResolution; ++i)
  {

    mySlicesX[i] = VectorInt(anIncrement, myAllocator);
    mySlicesY[i] = VectorInt(anIncrement, myAllocator);
    mySlicesZ[i] = VectorInt(anIncrement, myAllocator);
  }
}

void Bnd_VoxelGrid::AddBox(const int theBoxIndex, const std::array<int, 6>& theVoxelBox)
{
  const int aMinVoxelX = theVoxelBox[0];
  const int aMinVoxelY = theVoxelBox[1];
  const int aMinVoxelZ = theVoxelBox[2];
  const int aMaxVoxelX = theVoxelBox[3];
  const int aMaxVoxelY = theVoxelBox[4];
  const int aMaxVoxelZ = theVoxelBox[5];

  AppendSliceX(aMinVoxelX, aMaxVoxelX, theBoxIndex);
  AppendSliceY(aMinVoxelY, aMaxVoxelY, theBoxIndex);
  AppendSliceZ(aMinVoxelZ, aMaxVoxelZ, theBoxIndex);
}

const Bnd_VoxelGrid::VectorInt* Bnd_VoxelGrid::GetSliceX(const int theVoxelIndex) const
{
  const VectorInt& aSlice = mySlicesX[theVoxelIndex];
  return aSlice.IsEmpty() ? nullptr : &aSlice;
}

const Bnd_VoxelGrid::VectorInt* Bnd_VoxelGrid::GetSliceY(const int theVoxelIndex) const
{
  const VectorInt& aSlice = mySlicesY[theVoxelIndex];
  return aSlice.IsEmpty() ? nullptr : &aSlice;
}

const Bnd_VoxelGrid::VectorInt* Bnd_VoxelGrid::GetSliceZ(const int theVoxelIndex) const
{
  const VectorInt& aSlice = mySlicesZ[theVoxelIndex];
  return aSlice.IsEmpty() ? nullptr : &aSlice;
}

void Bnd_VoxelGrid::AppendSliceX(const int theVoxelIndexMin,
                                 const int theVoxelIndexMax,
                                 const int theBoxIndex)
{
  for (int i = theVoxelIndexMin; i <= theVoxelIndexMax; ++i)
  {
    mySlicesX[i].Append(theBoxIndex);
  }
}

void Bnd_VoxelGrid::AppendSliceY(const int theVoxelIndexMin,
                                 const int theVoxelIndexMax,
                                 const int theBoxIndex)
{
  for (int i = theVoxelIndexMin; i <= theVoxelIndexMax; ++i)
  {
    mySlicesY[i].Append(theBoxIndex);
  }
}

void Bnd_VoxelGrid::AppendSliceZ(const int theVoxelIndexMin,
                                 const int theVoxelIndexMax,
                                 const int theBoxIndex)
{
  for (int i = theVoxelIndexMin; i <= theVoxelIndexMax; ++i)
  {
    mySlicesZ[i].Append(theBoxIndex);
  }
}

Bnd_BoundSortBox::Bnd_BoundSortBox()
    : myBoxes(nullptr),
      myCoeffX(0.),
      myCoeffY(0.),
      myCoeffZ(0.),
      myResolution(0),

      myVoxelGrid(nullptr)
{
}

void Bnd_BoundSortBox::Initialize(const occ::handle<NCollection_HArray1<Bnd_Box>>& theSetOfBoxes)
{
  myBoxes = theSetOfBoxes;

  for (int aBoxIndex = myBoxes->Lower(); aBoxIndex <= myBoxes->Upper(); ++aBoxIndex)
  {
    const Bnd_Box& aBox = myBoxes->Value(aBoxIndex);
    if (!aBox.IsVoid())
    {
      myEnclosingBox.Add(aBox);
    }
  }

  myResolution = getBnd_VoxelGridResolution(myBoxes->Size());

  if (myEnclosingBox.IsVoid())
  {
    return;
  }

  calculateCoefficients();
  resetVoxelGrid();

  sortBoxes();
}

void Bnd_BoundSortBox::Initialize(const Bnd_Box&                                   theEnclosingBox,
                                  const occ::handle<NCollection_HArray1<Bnd_Box>>& theSetOfBoxes)
{
  myBoxes        = theSetOfBoxes;
  myEnclosingBox = theEnclosingBox;
  myResolution   = getBnd_VoxelGridResolution(myBoxes->Size());

  if (myEnclosingBox.IsVoid())
  {
    return;
  }

  calculateCoefficients();
  resetVoxelGrid();

  sortBoxes();
}

void Bnd_BoundSortBox::Initialize(const Bnd_Box& theEnclosingBox, const int theNbBoxes)
{
  Standard_NullValue_Raise_if(theNbBoxes <= 0, "Unexpected: theNbBoxes <= 0");
  myBoxes = new NCollection_HArray1<Bnd_Box>(1, theNbBoxes);

  Bnd_Box emptyBox;
  myBoxes->Init(emptyBox);

  myEnclosingBox = theEnclosingBox;
  myResolution   = getBnd_VoxelGridResolution(theNbBoxes);

  if (myEnclosingBox.IsVoid())
  {
    return;
  }

  calculateCoefficients();
  resetVoxelGrid();
}

void Bnd_BoundSortBox::Add(const Bnd_Box& theBox, const int theIndex)
{
  Standard_MultiplyDefined_Raise_if(!(myBoxes->Value(theIndex).IsVoid()),
                                    " This box is already defined !");
  if (theBox.IsVoid())
  {
    return;
  }

  myBoxes->SetValue(theIndex, theBox);

  addBox(theBox, theIndex);
}

const NCollection_List<int>& Bnd_BoundSortBox::Compare(const Bnd_Box& theBox)

{
  myLastResult.Clear();

  if (theBox.IsVoid() || theBox.IsOut(myEnclosingBox))
  {
    return myLastResult;
  }

  for (auto& aBoxIndex : myLargeBoxes)
  {
    const Bnd_Box& aBox = myBoxes->Value(aBoxIndex);
    if (!aBox.IsOut(theBox))
    {
      myLastResult.Append(aBoxIndex);
    }
  }

  auto&& [aMinVoxelX, aMinVoxelY, aMinVoxelZ, aMaxVoxelX, aMaxVoxelY, aMaxVoxelZ] =
    getBoundingVoxels(theBox);

  std::vector<uint8_t> aResultIndices(myBoxes->Upper() + 1, 0);
  constexpr uint8_t    anOccupiedX  = 0b01;
  constexpr uint8_t    anOccupiedY  = 0b10;
  constexpr uint8_t    anOccupiedXY = 0b11;

  for (int aVoxelX = aMinVoxelX; aVoxelX <= aMaxVoxelX; ++aVoxelX)
  {
    const Bnd_VoxelGrid::VectorInt* aBoxIndices = myVoxelGrid->GetSliceX(aVoxelX);
    if (aBoxIndices == nullptr)
    {
      continue;
    }
    for (const auto& aBoxIndex : *aBoxIndices)
    {

      aResultIndices[aBoxIndex] |= anOccupiedX;
    }
  }

  for (int aVoxelY = aMinVoxelY; aVoxelY <= aMaxVoxelY; ++aVoxelY)
  {
    const Bnd_VoxelGrid::VectorInt* aBoxIndices = myVoxelGrid->GetSliceY(aVoxelY);
    if (aBoxIndices == nullptr)
    {
      continue;
    }
    for (const auto& aBoxIndex : *aBoxIndices)
    {

      aResultIndices[aBoxIndex] |= anOccupiedY;
    }
  }

  for (int aVoxelZ = aMinVoxelZ; aVoxelZ <= aMaxVoxelZ; ++aVoxelZ)
  {
    const Bnd_VoxelGrid::VectorInt* aBoxIndices = myVoxelGrid->GetSliceZ(aVoxelZ);
    if (aBoxIndices == nullptr)
    {
      continue;
    }
    for (const auto& aBoxIndex : *aBoxIndices)
    {

      if (aResultIndices[aBoxIndex] == anOccupiedXY)
      {

        aResultIndices[aBoxIndex] = 0;

        if (!myBoxes->Value(aBoxIndex).IsOut(theBox))
        {

          myLastResult.Append(aBoxIndex);
        }
      }
    }
  }

  return myLastResult;
}

const NCollection_List<int>& Bnd_BoundSortBox::Compare(const gp_Pln& thePlane)

{
  myLastResult.Clear();
  for (int aBoxIndex = myBoxes->Lower(); aBoxIndex <= myBoxes->Upper(); ++aBoxIndex)
  {
    const Bnd_Box& aBox = myBoxes->Value(aBoxIndex);
    if (!aBox.IsOut(thePlane))
    {
      myLastResult.Append(aBoxIndex);
    }
  }
  return myLastResult;
}

void Bnd_BoundSortBox::calculateCoefficients()
{
  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  myEnclosingBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
  myCoeffX = (aXmax - aXmin == 0. ? 0. : myResolution / (aXmax - aXmin));
  myCoeffY = (aYmax - aYmin == 0. ? 0. : myResolution / (aYmax - aYmin));
  myCoeffZ = (aZmax - aZmin == 0. ? 0. : myResolution / (aZmax - aZmin));
}

void Bnd_BoundSortBox::resetVoxelGrid()
{
  myVoxelGrid = new Bnd_VoxelGrid(myResolution, myBoxes->Length());
  myLargeBoxes.Clear();

  myLargeBoxes.SetIncrement(std::max(myBoxes->Length() / 16, 16));
}

void Bnd_BoundSortBox::sortBoxes()
{
  for (int aBoxIndex = myBoxes->Lower(); aBoxIndex <= myBoxes->Upper(); ++aBoxIndex)
  {
    addBox(myBoxes->Value(aBoxIndex), aBoxIndex);
  }
}

std::array<int, 6> Bnd_BoundSortBox::getBoundingVoxels(const Bnd_Box& theBox) const
{

  const gp_Pnt aGridStart = myEnclosingBox.CornerMin();

  double aXMin, aYMin, aZMin, aXMax, aYMax, aZmax;
  theBox.Get(aXMin, aYMin, aZMin, aXMax, aYMax, aZmax);

  const int aXMinIndex =
    std::clamp(static_cast<int>((aXMin - aGridStart.X()) * myCoeffX) - 1, 0, myResolution - 1);
  const int aYMinIndex =
    std::clamp(static_cast<int>((aYMin - aGridStart.Y()) * myCoeffY) - 1, 0, myResolution - 1);
  const int aZMinIndex =
    std::clamp(static_cast<int>((aZMin - aGridStart.Z()) * myCoeffZ) - 1, 0, myResolution - 1);
  const int aXMaxIndex =
    std::clamp(static_cast<int>((aXMax - aGridStart.X()) * myCoeffX) + 1, 0, myResolution - 1);
  const int aYMaxIndex =
    std::clamp(static_cast<int>((aYMax - aGridStart.Y()) * myCoeffY) + 1, 0, myResolution - 1);
  const int aZMaxIndex =
    std::clamp(static_cast<int>((aZmax - aGridStart.Z()) * myCoeffZ) + 1, 0, myResolution - 1);

  return {aXMinIndex, aYMinIndex, aZMinIndex, aXMaxIndex, aYMaxIndex, aZMaxIndex};
}

void Bnd_BoundSortBox::addBox(const Bnd_Box& theBox, const int theIndex)
{
  if (theBox.IsVoid())
  {
    return;
  }

  auto&& [aMinVoxelX, aMinVoxelY, aMinVoxelZ, aMaxVoxelX, aMaxVoxelY, aMaxVoxelZ] =
    getBoundingVoxels(theBox);

  const int aBoxMinSide =
    std::min({aMaxVoxelX - aMinVoxelX, aMaxVoxelY - aMinVoxelY, aMaxVoxelZ - aMinVoxelZ});

  if (aBoxMinSide * 4 > myResolution)
  {
    myLargeBoxes.Append(theIndex);
  }
  else
  {
    myVoxelGrid->AddBox(theIndex,
                        {aMinVoxelX, aMinVoxelY, aMinVoxelZ, aMaxVoxelX, aMaxVoxelY, aMaxVoxelZ});
  }
}
