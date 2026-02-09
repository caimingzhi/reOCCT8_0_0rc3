

#include "StepTidy_BaseTestFixture.hpp"

#include <StepTidy_PlaneReducer.hpp>

#include <StepShape_AdvancedFace.hpp>
#include <StepGeom_Pcurve.hpp>
#include <StepRepr_DefinitionalRepresentation.hpp>

class StepTidy_PlaneReducerTest : public StepTidy_BaseTestFixture
{
protected:
  NCollection_Map<occ::handle<Standard_Transient>> replaceDuplicatePlanes()
  {
    StepTidy_PlaneReducer aReducer(myWS);
    for (int anIndex = 1; anIndex <= myWS->Model()->NbEntities(); ++anIndex)
    {
      aReducer.ProcessEntity(myWS->Model()->Value(anIndex));
    }

    NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities;
    aReducer.Perform(aRemovedEntities);
    return aRemovedEntities;
  }
};

TEST_F(StepTidy_PlaneReducerTest, DifferentNames)
{

  occ::handle<StepGeom_Plane> aPlane1 = addPlane("Plane1");
  occ::handle<StepGeom_Plane> aPlane2 = addPlane("Plane2");

  occ::handle<StepShape_AdvancedFace> aFirstAdvancedFace = new StepShape_AdvancedFace;
  aFirstAdvancedFace->Init(new TCollection_HAsciiString,
                           new NCollection_HArray1<occ::handle<StepShape_FaceBound>>,
                           aPlane1,
                           true);
  addToModel(aFirstAdvancedFace);

  occ::handle<StepShape_AdvancedFace> aSecondAdvancedFace = new StepShape_AdvancedFace;
  aSecondAdvancedFace->Init(new TCollection_HAsciiString,
                            new NCollection_HArray1<occ::handle<StepShape_FaceBound>>,
                            aPlane2,
                            true);
  addToModel(aSecondAdvancedFace);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicatePlanes();

  EXPECT_TRUE(aRemovedEntities.IsEmpty());
}

TEST_F(StepTidy_PlaneReducerTest, StepShape_AdvancedFace)
{

  occ::handle<StepGeom_Plane> aPlane1 = addPlane();
  occ::handle<StepGeom_Plane> aPlane2 = addPlane();

  occ::handle<StepShape_AdvancedFace> aFirstAdvancedFace = new StepShape_AdvancedFace;
  aFirstAdvancedFace->Init(new TCollection_HAsciiString,
                           new NCollection_HArray1<occ::handle<StepShape_FaceBound>>,
                           aPlane1,
                           true);
  addToModel(aFirstAdvancedFace);

  occ::handle<StepShape_AdvancedFace> aSecondAdvancedFace = new StepShape_AdvancedFace;
  aSecondAdvancedFace->Init(new TCollection_HAsciiString,
                            new NCollection_HArray1<occ::handle<StepShape_FaceBound>>,
                            aPlane2,
                            true);
  addToModel(aSecondAdvancedFace);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicatePlanes();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPlane1) || aRemovedEntities.Contains(aPlane2));
}

TEST_F(StepTidy_PlaneReducerTest, StepGeom_Pcurve)
{

  occ::handle<StepGeom_Plane> aPlane1 = addPlane();
  occ::handle<StepGeom_Plane> aPlane2 = addPlane();

  occ::handle<StepGeom_Pcurve> aFirstPcurve = new StepGeom_Pcurve;
  aFirstPcurve->Init(new TCollection_HAsciiString,
                     aPlane1,
                     new StepRepr_DefinitionalRepresentation);
  addToModel(aFirstPcurve);

  occ::handle<StepGeom_Pcurve> aSecondPcurve = new StepGeom_Pcurve;
  aSecondPcurve->Init(new TCollection_HAsciiString,
                      aPlane2,
                      new StepRepr_DefinitionalRepresentation);
  addToModel(aSecondPcurve);

  NCollection_Map<occ::handle<Standard_Transient>> aRemovedEntities = replaceDuplicatePlanes();

  EXPECT_EQ(aRemovedEntities.Size(), 1);
  EXPECT_TRUE(aRemovedEntities.Contains(aPlane1) || aRemovedEntities.Contains(aPlane2));
}
