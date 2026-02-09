

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_LineReducer.hpp>

#include <StepShape_EdgeCurve.hpp>
#include <StepGeom_TrimmedCurve.hpp>
#include <StepGeom_SurfaceCurve.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>
#include <StepGeom_SeamCurve.hpp>
#include <StepRepr_RepresentationContext.hpp>

class StepTidy_LineReducerTest : public StepTidy_BaseTestFixture
{
protected:
  NCollection_Map<occ::handle<Standard_Transient>> replaceDuplicateLines()
  {
    StepTidy_LineReducer aReducer(myWS);
    for (int anIndex = 1; anIndex <= myWS->Model()->NbEntities(); ++anIndex)
    {
      aReducer.ProcessEntity(myWS->Model()->Value(anIndex));
    }

    NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities;
    aReducer.Perform(aRemovedEntities);
    return aRemovedEntities;
  }
};

TEST_F(StepTidy_LineReducerTest, DifferentNames)
{

  occ::handle<StepGeom_Line> aLine1 = addLine("Line1");
  occ::handle<StepGeom_Line> aLine2 = addLine("Line2");

  occ::handle<StepShape_EdgeCurve> aFirstEdgeCurve = new StepShape_EdgeCurve;
  aFirstEdgeCurve->Init(new TCollection_HAsciiString,
                        new StepShape_Vertex,
                        new StepShape_Vertex,
                        aLine1,
                        true);
  addToModel(aFirstEdgeCurve);

  occ::handle<StepShape_EdgeCurve> aSecondEdgeCurve = new StepShape_EdgeCurve;
  aSecondEdgeCurve->Init(new TCollection_HAsciiString,
                         new StepShape_Vertex,
                         new StepShape_Vertex,
                         aLine2,
                         true);
  addToModel(aSecondEdgeCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateLines();

  EXPECT_TRUE(aRemovedEntities.IsEmpty());
}

TEST_F(StepTidy_LineReducerTest, StepShape_EdgeCurve)
{

  occ::handle<StepGeom_Line> aLine1 = addLine();
  occ::handle<StepGeom_Line> aLine2 = addLine();

  occ::handle<StepShape_EdgeCurve> aFirstEdgeCurve = new StepShape_EdgeCurve;
  aFirstEdgeCurve->Init(new TCollection_HAsciiString,
                        new StepShape_Vertex,
                        new StepShape_Vertex,
                        aLine1,
                        true);
  addToModel(aFirstEdgeCurve);

  occ::handle<StepShape_EdgeCurve> aSecondEdgeCurve = new StepShape_EdgeCurve;
  aSecondEdgeCurve->Init(new TCollection_HAsciiString,
                         new StepShape_Vertex,
                         new StepShape_Vertex,
                         aLine2,
                         true);
  addToModel(aSecondEdgeCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateLines();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aLine1) || aRemovedEntities.Contains(aLine2));
}

TEST_F(StepTidy_LineReducerTest, StepGeom_TrimmedCurve)
{

  occ::handle<StepGeom_Line> aLine1 = addLine();
  occ::handle<StepGeom_Line> aLine2 = addLine();

  occ::handle<StepGeom_TrimmedCurve> aFirstTrimmedCurve = new StepGeom_TrimmedCurve;
  aFirstTrimmedCurve->Init(new TCollection_HAsciiString,
                           aLine1,
                           new NCollection_HArray1<StepGeom_TrimmingSelect>,
                           new NCollection_HArray1<StepGeom_TrimmingSelect>,
                           true,
                           StepGeom_tpUnspecified);
  addToModel(aFirstTrimmedCurve);

  occ::handle<StepGeom_TrimmedCurve> aSecondTrimmedCurve = new StepGeom_TrimmedCurve;
  aSecondTrimmedCurve->Init(new TCollection_HAsciiString,
                            aLine2,
                            new NCollection_HArray1<StepGeom_TrimmingSelect>,
                            new NCollection_HArray1<StepGeom_TrimmingSelect>,
                            true,
                            StepGeom_tpUnspecified);
  addToModel(aSecondTrimmedCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateLines();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aLine1) || aRemovedEntities.Contains(aLine2));
}

TEST_F(StepTidy_LineReducerTest, StepGeom_SurfaceCurve)
{

  occ::handle<StepGeom_Line> aLine1 = addLine();
  occ::handle<StepGeom_Line> aLine2 = addLine();

  occ::handle<StepGeom_SurfaceCurve> aFirstSurfaceCurve = new StepGeom_SurfaceCurve;
  aFirstSurfaceCurve->Init(new TCollection_HAsciiString,
                           aLine1,
                           new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                           StepGeom_pscrCurve3d);
  addToModel(aFirstSurfaceCurve);

  occ::handle<StepGeom_SurfaceCurve> aSecondSurfaceCurve = new StepGeom_SurfaceCurve;
  aSecondSurfaceCurve->Init(new TCollection_HAsciiString,
                            aLine2,
                            new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                            StepGeom_pscrCurve3d);
  addToModel(aSecondSurfaceCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateLines();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aLine1) || aRemovedEntities.Contains(aLine2));
}

TEST_F(StepTidy_LineReducerTest, StepRepr_DefinitionalRepresentation)
{

  occ::handle<StepGeom_Line> aLine1 = addLine();
  occ::handle<StepGeom_Line> aLine2 = addLine();

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aFirstItems =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aFirstItems->SetValue(1, aLine1);
  occ::handle<StepRepr_DefinitionalRepresentation> aFirstDefinitionalRepresentation =
    new StepRepr_DefinitionalRepresentation;
  aFirstDefinitionalRepresentation->Init(new TCollection_HAsciiString,
                                         aFirstItems,
                                         new StepRepr_RepresentationContext);
  addToModel(aFirstDefinitionalRepresentation);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aSecondItems =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aSecondItems->SetValue(1, aLine2);
  occ::handle<StepRepr_DefinitionalRepresentation> aSecondDefinitionalRepresentation =
    new StepRepr_DefinitionalRepresentation;
  aSecondDefinitionalRepresentation->Init(new TCollection_HAsciiString,
                                          aSecondItems,
                                          new StepRepr_RepresentationContext);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateLines();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aLine1) || aRemovedEntities.Contains(aLine2));
}

TEST_F(StepTidy_LineReducerTest, StepGeom_SeamCurve)
{

  occ::handle<StepGeom_Line> aLine1 = addLine();
  occ::handle<StepGeom_Line> aLine2 = addLine();

  occ::handle<StepGeom_SeamCurve> aFirstSeamCurve = new StepGeom_SeamCurve;
  aFirstSeamCurve->Init(new TCollection_HAsciiString,
                        aLine1,
                        new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                        StepGeom_pscrCurve3d);
  addToModel(aFirstSeamCurve);

  occ::handle<StepGeom_SeamCurve> aSecondSeamCurve = new StepGeom_SeamCurve;
  aSecondSeamCurve->Init(new TCollection_HAsciiString,
                         aLine2,
                         new NCollection_HArray1<StepGeom_PcurveOrSurface>,
                         StepGeom_pscrCurve3d);
  addToModel(aSecondSeamCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicateLines();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aLine1) || aRemovedEntities.Contains(aLine2));
}
