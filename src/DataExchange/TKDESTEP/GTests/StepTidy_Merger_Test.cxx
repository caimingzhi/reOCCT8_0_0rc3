

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_DuplicateCleaner.hpp>

#include <StepGeom_Axis1Placement.hpp>

class StepTidy_DuplicateCleanerTest : public StepTidy_BaseTestFixture
{
protected:
  int getEntitiesCount(const occ::handle<Standard_Type>& theType) const
  {
    int aCount = 0;
    for (int i = 1; i <= myWS->Model()->NbEntities(); i++)
    {
      if (myWS->Model()->Value(i)->IsKind(theType))
      {
        aCount++;
      }
    }
    return aCount;
  }

  void performRemoval()
  {
    StepTidy_DuplicateCleaner aMerger(myWS);
    aMerger.Perform();
  }
};

TEST_F(StepTidy_DuplicateCleanerTest, DifferentEntities)
{

  occ::handle<StepGeom_Direction> aDir1 = addDirection("dir1");
  occ::handle<StepGeom_Direction> aDir2 = addDirection("dir2");

  occ::handle<StepGeom_Vector> aFirstVector = new StepGeom_Vector;
  aFirstVector->Init(new TCollection_HAsciiString, aDir1, 1.);
  addToModel(aFirstVector);

  occ::handle<StepGeom_Vector> aSecondVector = new StepGeom_Vector;
  aSecondVector->Init(new TCollection_HAsciiString, aDir2, 1.);
  addToModel(aSecondVector);

  const int aDirectionCountBefore = getEntitiesCount(STANDARD_TYPE(StepGeom_Direction));

  performRemoval();

  const int aDirectionCountAfter = getEntitiesCount(STANDARD_TYPE(StepGeom_Direction));

  EXPECT_EQ(aDirectionCountBefore, 2);
  EXPECT_EQ(aDirectionCountBefore, aDirectionCountAfter);
}

TEST_F(StepTidy_DuplicateCleanerTest, EqualEntities)
{

  occ::handle<StepGeom_Direction> aDir1 = addDirection();
  occ::handle<StepGeom_Direction> aDir2 = addDirection();

  occ::handle<StepGeom_CartesianPoint>     aLocation       = new StepGeom_CartesianPoint;
  occ::handle<NCollection_HArray1<double>> aLocationCoords = new NCollection_HArray1<double>(1, 3);
  aLocationCoords->SetValue(1, 0.);
  aLocationCoords->SetValue(2, 0.);
  aLocationCoords->SetValue(3, 0.);
  aLocation->Init(new TCollection_HAsciiString, aLocationCoords);
  addToModel(aLocation);

  occ::handle<StepGeom_Axis1Placement> aFirstAxis = new StepGeom_Axis1Placement;
  aFirstAxis->Init(new TCollection_HAsciiString, aLocation, true, aDir1);
  addToModel(aFirstAxis);

  occ::handle<StepGeom_Axis1Placement> aSecondAxis = new StepGeom_Axis1Placement;
  aSecondAxis->Init(new TCollection_HAsciiString, aLocation, true, aDir2);
  addToModel(aSecondAxis);

  const int aDirectionCountBefore = getEntitiesCount(STANDARD_TYPE(StepGeom_Direction));

  performRemoval();

  const int aDirectionCountAfter = getEntitiesCount(STANDARD_TYPE(StepGeom_Direction));

  EXPECT_EQ(aDirectionCountBefore, 2);
  EXPECT_EQ(aDirectionCountAfter, 1);
}
