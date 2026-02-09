

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_Axis2Placement3dReducer.hpp>

#include <StepGeom_Plane.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepGeom_CylindricalSurface.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_ConstructiveGeometryRepresentation.hpp>
#include <StepGeom_Circle.hpp>
#include <StepVisual_PresentationLayerAssignment.hpp>
#include <StepVisual_StyledItem.hpp>
#include <StepGeom_Ellipse.hpp>
#include <StepGeom_ConicalSurface.hpp>
#include <StepGeom_ToroidalSurface.hpp>
#include <StepShape_AdvancedBrepShapeRepresentation.hpp>
#include <StepGeom_SphericalSurface.hpp>

class StepTidy_Axis2Placement3dReducerTest : public StepTidy_BaseTestFixture
{
protected:
  NCollection_Map<occ::handle<Standard_Transient>> replaceDuplicateAxis2Placement3ds()
  {
    StepTidy_Axis2Placement3dReducer aReducer(myWS);
    for (int anIndex = 1; anIndex <= myWS->Model()->NbEntities(); ++anIndex)
    {
      aReducer.ProcessEntity(myWS->Model()->Value(anIndex));
    }

    NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities;
    aReducer.Perform(aRemovedEntities);
    return aRemovedEntities;
  }
};

TEST_F(StepTidy_Axis2Placement3dReducerTest, DifferentNames)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d("Axis1");
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d("Axis2");

  occ::handle<StepGeom_Plane> aPlane1 = new StepGeom_Plane;
  aPlane1->Init(new TCollection_HAsciiString, anAxis1);
  addToModel(aPlane1);

  occ::handle<StepGeom_Plane> aPlane2 = new StepGeom_Plane;
  aPlane2->Init(new TCollection_HAsciiString, anAxis2);
  addToModel(aPlane2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_TRUE(aRemovedEntities.IsEmpty());
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepGeom_Plane)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<StepGeom_Plane> aPlane1 = new StepGeom_Plane;
  aPlane1->Init(new TCollection_HAsciiString, anAxis1);
  addToModel(aPlane1);

  occ::handle<StepGeom_Plane> aPlane2 = new StepGeom_Plane;
  aPlane2->Init(new TCollection_HAsciiString, anAxis2);
  addToModel(aPlane2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepRepr_ItemDefinedTransformation)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis3 = addAxis2Placement3d(nullptr, gp_XYZ(1., 1., 1.));

  occ::handle<StepRepr_ItemDefinedTransformation> aItem1 = new StepRepr_ItemDefinedTransformation;
  aItem1->Init(new TCollection_HAsciiString, new TCollection_HAsciiString, anAxis1, anAxis3);
  addToModel(aItem1);

  occ::handle<StepRepr_ItemDefinedTransformation> aItem2 = new StepRepr_ItemDefinedTransformation;
  aItem1->Init(new TCollection_HAsciiString, new TCollection_HAsciiString, anAxis2, anAxis3);
  addToModel(aItem2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepGeom_CylindricalSurface)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<StepGeom_CylindricalSurface> aCylindricalSurface1 = new StepGeom_CylindricalSurface;
  aCylindricalSurface1->Init(new TCollection_HAsciiString, anAxis1, 1.0);
  addToModel(aCylindricalSurface1);

  occ::handle<StepGeom_CylindricalSurface> aCylindricalSurface2 = new StepGeom_CylindricalSurface;
  aCylindricalSurface2->Init(new TCollection_HAsciiString, anAxis2, 1.0);
  addToModel(aCylindricalSurface2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepShape_ShapeRepresentation)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems1 =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aItems1->SetValue(1, anAxis1);
  occ::handle<StepShape_ShapeRepresentation> aShapeRepresentation1 =
    new StepShape_ShapeRepresentation;
  aShapeRepresentation1->Init(new TCollection_HAsciiString,
                              aItems1,
                              new StepRepr_RepresentationContext);
  addToModel(aShapeRepresentation1);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems2 =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aItems2->SetValue(1, anAxis2);
  occ::handle<StepShape_ShapeRepresentation> aShapeRepresentation2 =
    new StepShape_ShapeRepresentation;
  aShapeRepresentation2->Init(new TCollection_HAsciiString,
                              aItems2,
                              new StepRepr_RepresentationContext);
  addToModel(aShapeRepresentation2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepRepr_ConstructiveGeometryRepresentation)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems1 =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aItems1->SetValue(1, anAxis1);
  occ::handle<StepRepr_ConstructiveGeometryRepresentation> aConstructiveGeometryRepresentation1 =
    new StepRepr_ConstructiveGeometryRepresentation;
  aConstructiveGeometryRepresentation1->Init(new TCollection_HAsciiString,
                                             aItems1,
                                             new StepRepr_RepresentationContext);
  addToModel(aConstructiveGeometryRepresentation1);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems2 =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aItems2->SetValue(1, anAxis2);
  occ::handle<StepRepr_ConstructiveGeometryRepresentation> aConstructiveGeometryRepresentation2 =
    new StepRepr_ConstructiveGeometryRepresentation;
  aConstructiveGeometryRepresentation2->Init(new TCollection_HAsciiString,
                                             aItems2,
                                             new StepRepr_RepresentationContext);
  addToModel(aConstructiveGeometryRepresentation2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepGeom_Circle)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  StepGeom_Axis2Placement aSelector1;
  aSelector1.SetValue(anAxis1);
  occ::handle<StepGeom_Circle> aCircle1 = new StepGeom_Circle;
  aCircle1->Init(new TCollection_HAsciiString, aSelector1, 1.0);
  addToModel(aCircle1);

  StepGeom_Axis2Placement aSelector2;
  aSelector2.SetValue(anAxis2);
  occ::handle<StepGeom_Circle> aCircle2 = new StepGeom_Circle;
  aCircle2->Init(new TCollection_HAsciiString, aSelector2, 1.0);
  addToModel(aCircle2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepVisual_PresentationLayerAssignment)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> aAssignedItems1 =
    new NCollection_HArray1<StepVisual_LayeredItem>(1, 1);
  StepVisual_LayeredItem aLayeredItem1;
  aLayeredItem1.SetValue(anAxis1);
  aAssignedItems1->SetValue(1, aLayeredItem1);
  occ::handle<StepVisual_PresentationLayerAssignment> aPresentationLayerAssignment1 =
    new StepVisual_PresentationLayerAssignment;
  aPresentationLayerAssignment1->Init(new TCollection_HAsciiString,
                                      new TCollection_HAsciiString,
                                      aAssignedItems1);
  addToModel(aPresentationLayerAssignment1);

  occ::handle<NCollection_HArray1<StepVisual_LayeredItem>> aAssignedItems2 =
    new NCollection_HArray1<StepVisual_LayeredItem>(1, 1);
  StepVisual_LayeredItem aLayeredItem2;
  aLayeredItem2.SetValue(anAxis2);
  aAssignedItems2->SetValue(1, aLayeredItem2);
  occ::handle<StepVisual_PresentationLayerAssignment> aPresentationLayerAssignment2 =
    new StepVisual_PresentationLayerAssignment;
  aPresentationLayerAssignment2->Init(new TCollection_HAsciiString,
                                      new TCollection_HAsciiString,
                                      aAssignedItems2);
  addToModel(aPresentationLayerAssignment2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepVisual_StyledItem)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<StepVisual_StyledItem> aStiledItem1 = new StepVisual_StyledItem;
  aStiledItem1->Init(
    new TCollection_HAsciiString,
    new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, 1),
    anAxis1);
  addToModel(aStiledItem1);

  occ::handle<StepVisual_StyledItem> aStiledItem2 = new StepVisual_StyledItem;
  aStiledItem2->Init(
    new TCollection_HAsciiString,
    new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, 1),
    anAxis2);
  addToModel(aStiledItem2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepGeom_Ellipse)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  StepGeom_Axis2Placement aSelector1;
  aSelector1.SetValue(anAxis1);
  occ::handle<StepGeom_Ellipse> aEllipse1 = new StepGeom_Ellipse;
  aEllipse1->Init(new TCollection_HAsciiString, aSelector1, 1.0, 2.0);
  addToModel(aEllipse1);

  StepGeom_Axis2Placement aSelector2;
  aSelector2.SetValue(anAxis2);
  occ::handle<StepGeom_Ellipse> aEllipse2 = new StepGeom_Ellipse;
  aEllipse2->Init(new TCollection_HAsciiString, aSelector2, 1.0, 2.0);
  addToModel(aEllipse2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepGeom_ConicalSurface)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<StepGeom_ConicalSurface> aConicalSurface1 = new StepGeom_ConicalSurface;
  aConicalSurface1->Init(new TCollection_HAsciiString, anAxis1, 1.0, 1.0);
  addToModel(aConicalSurface1);

  occ::handle<StepGeom_ConicalSurface> aConicalSurface2 = new StepGeom_ConicalSurface;
  aConicalSurface2->Init(new TCollection_HAsciiString, anAxis2, 1.0, 1.0);
  addToModel(aConicalSurface2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepGeom_ToroidalSurface)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<StepGeom_ToroidalSurface> aToroidalSurface1 = new StepGeom_ToroidalSurface;
  aToroidalSurface1->Init(new TCollection_HAsciiString, anAxis1, 1.0, 1.0);
  addToModel(aToroidalSurface1);

  occ::handle<StepGeom_ToroidalSurface> aToroidalSurface2 = new StepGeom_ToroidalSurface;
  aToroidalSurface2->Init(new TCollection_HAsciiString, anAxis2, 1.0, 1.0);
  addToModel(aToroidalSurface2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepShape_AdvancedBrepShapeRepresentation)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems1 =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aItems1->SetValue(1, anAxis1);
  occ::handle<StepShape_AdvancedBrepShapeRepresentation> aShapeRepresentation1 =
    new StepShape_AdvancedBrepShapeRepresentation;
  aShapeRepresentation1->Init(new TCollection_HAsciiString,
                              aItems1,
                              new StepRepr_RepresentationContext);
  addToModel(aShapeRepresentation1);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems2 =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  aItems2->SetValue(1, anAxis2);
  occ::handle<StepShape_AdvancedBrepShapeRepresentation> aShapeRepresentation2 =
    new StepShape_AdvancedBrepShapeRepresentation;
  aShapeRepresentation2->Init(new TCollection_HAsciiString,
                              aItems2,
                              new StepRepr_RepresentationContext);
  addToModel(aShapeRepresentation2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}

TEST_F(StepTidy_Axis2Placement3dReducerTest, StepGeom_SphericalSurface)
{

  occ::handle<StepGeom_Axis2Placement3d> anAxis1 = addAxis2Placement3d();
  occ::handle<StepGeom_Axis2Placement3d> anAxis2 = addAxis2Placement3d();

  occ::handle<StepGeom_SphericalSurface> aSphericalSurface1 = new StepGeom_SphericalSurface;
  aSphericalSurface1->Init(new TCollection_HAsciiString, anAxis1, 1.0);
  addToModel(aSphericalSurface1);

  occ::handle<StepGeom_SphericalSurface> aSphericalSurface2 = new StepGeom_SphericalSurface;
  aSphericalSurface2->Init(new TCollection_HAsciiString, anAxis2, 1.0);
  addToModel(aSphericalSurface2);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities =
    replaceDuplicateAxis2Placement3ds();

  EXPECT_EQ(aRemovedEntities.Extent(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(anAxis1) || aRemovedEntities.Contains(anAxis2));
}
