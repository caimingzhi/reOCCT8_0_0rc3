

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_CartesianPointReducer.hpp>

#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hpp>
#include <StepGeom_BSplineSurfaceWithKnots.hpp>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp>
#include <StepGeom_Line.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepShape_GeometricCurveSet.hpp>
#include <StepShape_VertexPoint.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_StyledItem.hpp>

class StepTidy_CartesianPointReducerTest : public StepTidy_BaseTestFixture
{
protected:
  NCollection_Map<occ::handle<Standard_Transient>> replaceDuplicateCartesianPoints()
  {
    StepTidy_CartesianPointReducer aReducer(myWS);
    for (int anIndex = 1; anIndex <= myWS->Model()->NbEntities(); ++anIndex)
    {
      aReducer.ProcessEntity(myWS->Model()->Value(anIndex));
    }

    NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities;
    aReducer.Perform(aRemovedEntities);
    return aRemovedEntities;
  }
};

TEST_F(StepTidy_CartesianPointReducerTest, DifferentNames)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint("FirstPt");
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint("SecondPt");

  occ::handle<NCollection_HArray1<double>> aDirCoords = new NCollection_HArray1<double>(1, 3);
  aDirCoords->SetValue(1, 0.);
  aDirCoords->SetValue(2, 0.);
  aDirCoords->SetValue(3, 1.);
  occ::handle<StepGeom_Direction> aDir = new StepGeom_Direction;
  aDir->Init(new TCollection_HAsciiString, aDirCoords);
  addToModel(aDir);

  occ::handle<StepGeom_Axis2Placement3d> aFirstAxis = new StepGeom_Axis2Placement3d;
  aFirstAxis->Init(new TCollection_HAsciiString, aPt1, true, aDir, false, nullptr);
  addToModel(aFirstAxis);

  occ::handle<StepGeom_Axis2Placement3d> aSecondAxis = new StepGeom_Axis2Placement3d;
  aSecondAxis->Init(new TCollection_HAsciiString, aPt2, true, aDir, false, nullptr);
  addToModel(aSecondAxis);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_TRUE(aRemovedEntities.IsEmpty());
}

TEST_F(StepTidy_CartesianPointReducerTest, StepGeom_Axis2Placement3d)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray1<double>> aDirCoords = new NCollection_HArray1<double>(1, 3);
  aDirCoords->SetValue(1, 0.);
  aDirCoords->SetValue(2, 0.);
  aDirCoords->SetValue(3, 1.);
  occ::handle<StepGeom_Direction> aDir = new StepGeom_Direction;
  aDir->Init(new TCollection_HAsciiString, aDirCoords);
  addToModel(aDir);

  occ::handle<StepGeom_Axis2Placement3d> aFirstAxis = new StepGeom_Axis2Placement3d;
  aFirstAxis->Init(new TCollection_HAsciiString, aPt1, true, aDir, false, nullptr);
  addToModel(aFirstAxis);

  occ::handle<StepGeom_Axis2Placement3d> aSecondAxis = new StepGeom_Axis2Placement3d;
  aSecondAxis->Init(new TCollection_HAsciiString, aPt2, true, aDir, false, nullptr);
  addToModel(aSecondAxis);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepShape_VertexPoint)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<StepShape_VertexPoint> aFirstVertex = new StepShape_VertexPoint;
  aFirstVertex->Init(new TCollection_HAsciiString, aPt1);
  addToModel(aFirstVertex);

  occ::handle<StepShape_VertexPoint> aSecondVertex = new StepShape_VertexPoint;
  aSecondVertex->Init(new TCollection_HAsciiString, aPt2);
  addToModel(aSecondVertex);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepShape_GeometricCurveSet)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> aFirstElements =
    new NCollection_HArray1<StepShape_GeometricSetSelect>(1, 1);
  StepShape_GeometricSetSelect aFirstSelect;
  aFirstSelect.SetValue(aPt1);
  aFirstElements->SetValue(1, aFirstSelect);
  addToModel(aFirstElements);
  occ::handle<StepShape_GeometricCurveSet> aFirstCurveSet = new StepShape_GeometricCurveSet;
  aFirstCurveSet->Init(new TCollection_HAsciiString, aFirstElements);
  addToModel(aFirstCurveSet);

  occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> aSecondElements =
    new NCollection_HArray1<StepShape_GeometricSetSelect>(1, 1);
  StepShape_GeometricSetSelect aSecondSelect;
  aSecondSelect.SetValue(aPt2);
  aSecondElements->SetValue(1, aSecondSelect);
  addToModel(aSecondElements);
  occ::handle<StepShape_GeometricCurveSet> aSecondCurveSet = new StepShape_GeometricCurveSet;
  aSecondCurveSet->Init(new TCollection_HAsciiString, aSecondElements);
  addToModel(aSecondCurveSet);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepVisual_PresentationLayerAssignment)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> aFirstAssignedItems =
    new NCollection_HArray1<StepVisual_LayeredItem>(1, 1);
  StepVisual_LayeredItem aFirstLayeredItem;
  aFirstLayeredItem.SetValue(aPt1);
  aFirstAssignedItems->SetValue(1, aFirstLayeredItem);
  addToModel(aFirstAssignedItems);
  occ::handle<StepVisual_PresentationLayerAssignment> aFirstAssignment =
    new StepVisual_PresentationLayerAssignment;
  aFirstAssignment->Init(new TCollection_HAsciiString,
                         new TCollection_HAsciiString,
                         aFirstAssignedItems);
  addToModel(aFirstAssignment);

  occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> aSecondAssignedItems =
    new NCollection_HArray1<StepVisual_LayeredItem>(1, 1);
  StepVisual_LayeredItem aSecondLayeredItem;
  aSecondLayeredItem.SetValue(aPt2);
  aSecondAssignedItems->SetValue(1, aSecondLayeredItem);
  addToModel(aSecondAssignedItems);
  occ::handle<StepVisual_PresentationLayerAssignment> aSecondAssignment =
    new StepVisual_PresentationLayerAssignment;
  aSecondAssignment->Init(new TCollection_HAsciiString,
                          new TCollection_HAsciiString,
                          aSecondAssignedItems);
  addToModel(aSecondAssignment);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepVisual_StyledItem)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>
    aFirstAssignedItems =
      new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, 1);
  occ::handle<StepVisual_StyledItem> aFirstStyledItem = new StepVisual_StyledItem;
  aFirstStyledItem->Init(new TCollection_HAsciiString, aFirstAssignedItems, aPt1);
  addToModel(aFirstStyledItem);

  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>
    aSecondAssignedItems =
      new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, 1);
  occ::handle<StepVisual_StyledItem> aSecondStyledItem = new StepVisual_StyledItem;
  aSecondStyledItem->Init(new TCollection_HAsciiString, aSecondAssignedItems, aPt2);
  addToModel(aSecondStyledItem);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepGeom_BSplineCurveWithKnots)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aFirstControlPoints =
    new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, 1);
  aFirstControlPoints->SetValue(1, aPt1);
  occ::handle<StepGeom_BSplineCurveWithKnots> aFirstCurve = new StepGeom_BSplineCurveWithKnots;
  aFirstCurve->Init(new TCollection_HAsciiString,
                    1,
                    aFirstControlPoints,
                    StepGeom_bscfUnspecified,
                    StepData_LUnknown,
                    StepData_LUnknown,
                    new NCollection_HArray1<int>,
                    new NCollection_HArray1<double>,
                    StepGeom_ktUnspecified);
  addToModel(aFirstCurve);

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aSecondControlPoints =
    new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, 1);
  aSecondControlPoints->SetValue(1, aPt2);
  occ::handle<StepGeom_BSplineCurveWithKnots> aSecondCurve = new StepGeom_BSplineCurveWithKnots;
  aSecondCurve->Init(new TCollection_HAsciiString,
                     1,
                     aSecondControlPoints,
                     StepGeom_bscfUnspecified,
                     StepData_LUnknown,
                     StepData_LUnknown,
                     new NCollection_HArray1<int>,
                     new NCollection_HArray1<double>,
                     StepGeom_ktUnspecified);
  addToModel(aSecondCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepGeom_Line)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<StepGeom_Line> aFirstLine = new StepGeom_Line;
  aFirstLine->Init(new TCollection_HAsciiString, aPt1, new StepGeom_Vector);
  addToModel(aFirstLine);

  occ::handle<StepGeom_Line> aSecondLine = new StepGeom_Line;
  aSecondLine->Init(new TCollection_HAsciiString, aPt2, new StepGeom_Vector);
  addToModel(aSecondLine);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepGeom_BSplineSurfaceWithKnots)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>> aFirstControlPoints =
    new NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>(1, 1, 1, 1);
  aFirstControlPoints->SetValue(1, 1, aPt1);
  occ::handle<StepGeom_BSplineSurfaceWithKnots> aFirstSurface =
    new StepGeom_BSplineSurfaceWithKnots;
  aFirstSurface->Init(new TCollection_HAsciiString,
                      1,
                      1,
                      aFirstControlPoints,
                      StepGeom_bssfUnspecified,
                      StepData_LUnknown,
                      StepData_LUnknown,
                      StepData_LUnknown,
                      new NCollection_HArray1<int>,
                      new NCollection_HArray1<int>,
                      new NCollection_HArray1<double>,
                      new NCollection_HArray1<double>,
                      StepGeom_ktUnspecified);
  addToModel(aFirstSurface);

  occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>> aSecondControlPoints =
    new NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>(1, 1, 1, 1);
  aSecondControlPoints->SetValue(1, 1, aPt2);
  occ::handle<StepGeom_BSplineSurfaceWithKnots> aSecondSurface =
    new StepGeom_BSplineSurfaceWithKnots;
  aSecondSurface->Init(new TCollection_HAsciiString,
                       1,
                       1,
                       aSecondControlPoints,
                       StepGeom_bssfUnspecified,
                       StepData_LUnknown,
                       StepData_LUnknown,
                       StepData_LUnknown,
                       new NCollection_HArray1<int>,
                       new NCollection_HArray1<int>,
                       new NCollection_HArray1<double>,
                       new NCollection_HArray1<double>,
                       StepGeom_ktUnspecified);
  addToModel(aSecondSurface);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepGeom_Axis1Placement)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<StepGeom_Axis1Placement> aFirstAxis = new StepGeom_Axis1Placement;
  aFirstAxis->Init(new TCollection_HAsciiString, aPt1, false, new StepGeom_Direction);
  addToModel(aFirstAxis);

  occ::handle<StepGeom_Axis1Placement> aSecondAxis = new StepGeom_Axis1Placement;
  aSecondAxis->Init(new TCollection_HAsciiString, aPt2, false, new StepGeom_Direction);
  addToModel(aSecondAxis);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepRepr_Representation)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aFirstItems =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aFirstItems->SetValue(1, aPt1);
  occ::handle<StepRepr_Representation> aFirstRepresentation = new StepRepr_Representation;
  aFirstRepresentation->Init(new TCollection_HAsciiString,
                             aFirstItems,
                             new StepRepr_RepresentationContext);
  addToModel(aFirstRepresentation);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aSecondItems =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aSecondItems->SetValue(1, aPt2);
  occ::handle<StepRepr_Representation> aSecondRepresentation = new StepRepr_Representation;
  aSecondRepresentation->Init(new TCollection_HAsciiString,
                              aSecondItems,
                              new StepRepr_RepresentationContext);
  addToModel(aSecondRepresentation);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest, StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aFirstControlPoints =
    new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, 1);
  aFirstControlPoints->SetValue(1, aPt1);
  occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> aFirstCurve =
    new StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve;
  aFirstCurve->Init(new TCollection_HAsciiString,
                    1,
                    aFirstControlPoints,
                    StepGeom_bscfUnspecified,
                    StepData_LUnknown,
                    StepData_LUnknown,
                    new NCollection_HArray1<int>,
                    new NCollection_HArray1<double>,
                    StepGeom_ktUnspecified,
                    new NCollection_HArray1<double>);
  addToModel(aFirstCurve);

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aSecondControlPoints =
    new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, 1);
  aSecondControlPoints->SetValue(1, aPt2);
  occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve> aSecondCurve =
    new StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve;
  aSecondCurve->Init(new TCollection_HAsciiString,
                     1,
                     aSecondControlPoints,
                     StepGeom_bscfUnspecified,
                     StepData_LUnknown,
                     StepData_LUnknown,
                     new NCollection_HArray1<int>,
                     new NCollection_HArray1<double>,
                     StepGeom_ktUnspecified,
                     new NCollection_HArray1<double>);
  addToModel(aSecondCurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}

TEST_F(StepTidy_CartesianPointReducerTest,
       StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface)
{

  occ::handle<StepGeom_CartesianPoint> aPt1 = addCartesianPoint();
  occ::handle<StepGeom_CartesianPoint> aPt2 = addCartesianPoint();

  occ::handle<StepGeom_RationalBSplineSurface> aRationalBSplineSurface =
    new StepGeom_RationalBSplineSurface;
  aRationalBSplineSurface->Init(
    new TCollection_HAsciiString,
    1,
    1,
    new NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>(1, 1, 1, 1),
    StepGeom_bssfUnspecified,
    StepData_LUnknown,
    StepData_LUnknown,
    StepData_LUnknown,
    new NCollection_HArray2<double>(1, 1, 1, 1));

  occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>> aFirstControlPoints =
    new NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>(1, 1, 1, 1);
  aFirstControlPoints->SetValue(1, 1, aPt1);
  occ::handle<StepGeom_BSplineSurfaceWithKnots> aFirstBSSWN = new StepGeom_BSplineSurfaceWithKnots;
  aFirstBSSWN->Init(new TCollection_HAsciiString,
                    1,
                    1,
                    aFirstControlPoints,
                    StepGeom_bssfUnspecified,
                    StepData_LUnknown,
                    StepData_LUnknown,
                    StepData_LUnknown,
                    new NCollection_HArray1<int>,
                    new NCollection_HArray1<int>,
                    new NCollection_HArray1<double>,
                    new NCollection_HArray1<double>,
                    StepGeom_ktUnspecified);
  addToModel(aFirstBSSWN);
  occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface> aFirstSurface =
    new StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface;
  aFirstSurface->Init(new TCollection_HAsciiString,
                      1,
                      1,
                      aFirstControlPoints,
                      StepGeom_bssfUnspecified,
                      StepData_LUnknown,
                      StepData_LUnknown,
                      StepData_LUnknown,
                      aFirstBSSWN,
                      aRationalBSplineSurface);
  addToModel(aFirstSurface);

  occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>> aSecondControlPoints =
    new NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>(1, 1, 1, 1);
  aSecondControlPoints->SetValue(1, 1, aPt2);
  occ::handle<StepGeom_BSplineSurfaceWithKnots> aSecondBSSWN = new StepGeom_BSplineSurfaceWithKnots;
  aSecondBSSWN->Init(new TCollection_HAsciiString,
                     1,
                     1,
                     aSecondControlPoints,
                     StepGeom_bssfUnspecified,
                     StepData_LUnknown,
                     StepData_LUnknown,
                     StepData_LUnknown,
                     new NCollection_HArray1<int>,
                     new NCollection_HArray1<int>,
                     new NCollection_HArray1<double>,
                     new NCollection_HArray1<double>,
                     StepGeom_ktUnspecified);
  addToModel(aSecondBSSWN);
  occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface> aSecondSurface =
    new StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface;
  aSecondSurface->Init(new TCollection_HAsciiString,
                       1,
                       1,
                       aSecondControlPoints,
                       StepGeom_bssfUnspecified,
                       StepData_LUnknown,
                       StepData_LUnknown,
                       StepData_LUnknown,
                       aSecondBSSWN,
                       aRationalBSplineSurface);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateCartesianPoints();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPt1) || aRemovedEntities.Contains(aPt2));
}
