

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_DirectionReducer.hpp>

#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Axis2Placement3d.hpp>

class StepTidy_DirectionReducerTest : public StepTidy_BaseTestFixture
{
protected:
  NCollection_Map<occ::handle<Standard_Transient>> replaceDuplicateDirections()
  {
    StepTidy_DirectionReducer aReducer(myWS);
    for (int anIndex = 1; anIndex <= myWS->Model()->NbEntities(); ++anIndex)
    {
      aReducer.ProcessEntity(myWS->Model()->Value(anIndex));
    }

    NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities;
    aReducer.Perform(aRemovedEntities);
    return aRemovedEntities;
  }
};

TEST_F(StepTidy_DirectionReducerTest, DifferentNames)
{

  occ::handle<StepGeom_Direction> aDir1 = addDirection("dir1");
  occ::handle<StepGeom_Direction> aDir2 = addDirection("dir2");

  occ::handle<StepGeom_Vector> aFirstVector = new StepGeom_Vector;
  aFirstVector->Init(new TCollection_HAsciiString, aDir1, 1.);
  addToModel(aFirstVector);

  occ::handle<StepGeom_Vector> aSecondVector = new StepGeom_Vector;
  aSecondVector->Init(new TCollection_HAsciiString, aDir2, 1.);
  addToModel(aSecondVector);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateDirections();

  EXPECT_TRUE(aRemovedEntities.IsEmpty());
}

TEST_F(StepTidy_DirectionReducerTest, StepGeom_Axis1Placement)
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

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateDirections();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aDir1) || aRemovedEntities.Contains(aDir2));
}

TEST_F(StepTidy_DirectionReducerTest, StepGeom_Axis2Placement)
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

  occ::handle<StepGeom_Axis2Placement3d> aFirstAxis = new StepGeom_Axis2Placement3d;
  aFirstAxis->Init(new TCollection_HAsciiString, aLocation, true, aDir1, false, nullptr);
  addToModel(aFirstAxis);

  occ::handle<StepGeom_Axis2Placement3d> aSecondAxis = new StepGeom_Axis2Placement3d;
  aSecondAxis->Init(new TCollection_HAsciiString, aLocation, true, aDir2, false, nullptr);
  addToModel(aSecondAxis);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateDirections();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aDir1) || aRemovedEntities.Contains(aDir2));
}

TEST_F(StepTidy_DirectionReducerTest, StepGeom_Vector)
{

  occ::handle<StepGeom_Direction> aDir1 = addDirection();
  occ::handle<StepGeom_Direction> aDir2 = addDirection();

  occ::handle<StepGeom_Vector> aFirstVector = new StepGeom_Vector;
  aFirstVector->Init(new TCollection_HAsciiString, aDir1, 1.);
  addToModel(aFirstVector);

  occ::handle<StepGeom_Vector> aSecondVector = new StepGeom_Vector;
  aSecondVector->Init(new TCollection_HAsciiString, aDir2, 1.);
  addToModel(aSecondVector);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateDirections();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aDir1) || aRemovedEntities.Contains(aDir2));
}
