

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_VectorReducer.hpp>

#include <StepGeom_Line.hpp>

class StepTidy_VectorReducerTest : public StepTidy_BaseTestFixture
{
protected:
  NCollection_Map<occ::handle<Standard_Transient>> replaceDuplicateVectors()
  {
    StepTidy_VectorReducer aReducer(myWS);
    for (int anIndex = 1; anIndex <= myWS->Model()->NbEntities(); ++anIndex)
    {
      aReducer.ProcessEntity(myWS->Model()->Value(anIndex));
    }

    NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities;
    aReducer.Perform(aRemovedEntities);
    return aRemovedEntities;
  }
};

TEST_F(StepTidy_VectorReducerTest, DifferentNames)
{

  occ::handle<StepGeom_Vector> aVec1 = addVector("vec1");
  occ::handle<StepGeom_Vector> aVec2 = addVector("vec2");

  occ::handle<StepGeom_CartesianPoint> aPnt = addCartesianPoint(nullptr, {0., 0., 0.});

  occ::handle<StepGeom_Line> aLine1 = new StepGeom_Line;
  aLine1->Init(new TCollection_HAsciiString, aPnt, aVec1);
  addToModel(aLine1);

  occ::handle<StepGeom_Line> aLine2 = new StepGeom_Line;
  aLine2->Init(new TCollection_HAsciiString, aPnt, aVec2);
  addToModel(aLine2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateVectors();

  EXPECT_TRUE(aRemovedEntities.IsEmpty());
}

TEST_F(StepTidy_VectorReducerTest, StepGeom_Line)
{

  occ::handle<StepGeom_Vector> aVec1 = addVector();
  occ::handle<StepGeom_Vector> aVec2 = addVector();

  occ::handle<StepGeom_CartesianPoint> aPnt = addCartesianPoint(nullptr, {0., 0., 0.});

  occ::handle<StepGeom_Line> aLine1 = new StepGeom_Line;
  aLine1->Init(new TCollection_HAsciiString, aPnt, aVec1);
  addToModel(aLine1);

  occ::handle<StepGeom_Line> aLine2 = new StepGeom_Line;
  aLine2->Init(new TCollection_HAsciiString, aPnt, aVec2);
  addToModel(aLine2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateVectors();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aVec1) || aRemovedEntities.Contains(aVec2));
}
