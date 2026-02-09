

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_CircleReducer.hpp>

#include <StepShape_EdgeCurve.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepGeom_SeamCurve.hpp>

class StepTidy_CircleReducerTest : public StepTidy_BaseTestFixture
{
protected:
  NCollection_Map<occ::handle<Standard_Transient>> replaceDuplicateCircles()
  {
    StepTidy_CircleReducer aReducer(myWS);
    for (int anIndex = 1; anIndex <= myWS->Model()->NbEntities(); ++anIndex)
    {
      aReducer.ProcessEntity(myWS->Model()->Value(anIndex));
    }

    NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities;
    aReducer.Perform(aRemovedEntities);
    return aRemovedEntities;
  }
};

TEST_F(StepTidy_CircleReducerTest, DifferentNames)
{

  occ::handle<StepGeom_Circle> aCircle1 = addCircle("Circle1");
  occ::handle<StepGeom_Circle> aCircle2 = addCircle("Circle2");

  occ::handle<StepShape_EdgeCurve> aFirstEdgeCurve = new StepShape_EdgeCurve;
  aFirstEdgeCurve->Init(new TCollection_HAsciiString,
                        new StepShape_Vertex,
                        new StepShape_Vertex,
                        aCircle1,
                        true);
  addToModel(aFirstEdgeCurve);

  occ::handle<StepShape_EdgeCurve> aSecondEdgeCurve = new StepShape_EdgeCurve;
  aSecondEdgeCurve->Init(new TCollection_HAsciiString,
                         new StepShape_Vertex,
                         new StepShape_Vertex,
                         aCircle2,
                         true);
  addToModel(aSecondEdgeCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateCircles();

  EXPECT_TRUE(aRemovedEntities.IsEmpty());
}

TEST_F(StepTidy_CircleReducerTest, StepShape_EdgeCurve)
{

  occ::handle<StepGeom_Circle> aCircle1 = addCircle();
  occ::handle<StepGeom_Circle> aCircle2 = addCircle();

  occ::handle<StepShape_EdgeCurve> aFirstEdgeCurve = new StepShape_EdgeCurve;
  aFirstEdgeCurve->Init(new TCollection_HAsciiString,
                        new StepShape_Vertex,
                        new StepShape_Vertex,
                        aCircle1,
                        true);
  addToModel(aFirstEdgeCurve);

  occ::handle<StepShape_EdgeCurve> aSecondEdgeCurve = new StepShape_EdgeCurve;
  aSecondEdgeCurve->Init(new TCollection_HAsciiString,
                         new StepShape_Vertex,
                         new StepShape_Vertex,
                         aCircle2,
                         true);
  addToModel(aSecondEdgeCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateCircles();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aCircle1) || aRemovedEntities.Contains(aCircle2));
}

TEST_F(StepTidy_CircleReducerTest, StepGeom_SurfaceCurve)
{

  occ::handle<StepGeom_Circle> aCircle1 = addCircle();
  occ::handle<StepGeom_Circle> aCircle2 = addCircle();

  occ::handle<StepGeom_SurfaceCurve> aFirstSurfaceCurve = new StepGeom_SurfaceCurve;
  aFirstSurfaceCurve->Init(new TCollection_HAsciiString,
                           aCircle1,
                           new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                           StepGeom_pscrCurve3d);
  addToModel(aFirstSurfaceCurve);

  occ::handle<StepGeom_SurfaceCurve> aSecondSurfaceCurve = new StepGeom_SurfaceCurve;
  aSecondSurfaceCurve->Init(new TCollection_HAsciiString,
                            aCircle2,
                            new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                            StepGeom_pscrCurve3d);
  addToModel(aSecondSurfaceCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateCircles();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aCircle1) || aRemovedEntities.Contains(aCircle2));
}

TEST_F(StepTidy_CircleReducerTest, StepGeom_SeamCurve)
{

  occ::handle<StepGeom_Circle> aCircle1 = addCircle();
  occ::handle<StepGeom_Circle> aCircle2 = addCircle();

  occ::handle<StepGeom_SeamCurve> aFirstSeamCurve = new StepGeom_SeamCurve;
  aFirstSeamCurve->Init(new TCollection_HAsciiString,
                        aCircle1,
                        new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                        StepGeom_pscrCurve3d);
  addToModel(aFirstSeamCurve);

  occ::handle<StepGeom_SeamCurve> aSecondSeamCurve = new StepGeom_SeamCurve;
  aSecondSeamCurve->Init(new TCollection_HAsciiString,
                         aCircle2,
                         new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                         StepGeom_pscrCurve3d);
  addToModel(aSecondSeamCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateCircles();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aCircle1) || aRemovedEntities.Contains(aCircle2));
}
