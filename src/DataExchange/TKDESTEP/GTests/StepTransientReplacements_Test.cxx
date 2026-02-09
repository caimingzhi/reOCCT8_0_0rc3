

#include <gtest/gtest.h>

#include <Standard_Transient.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepRepr_ReprItemAndMeasureWithUnit.hpp>

#include <StepBasic_ConversionBasedUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_SiUnit.hpp>
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>

#include <StepDimTol_GeometricTolerance.hpp>
#include <StepRepr_MakeFromUsageOption.hpp>
#include <StepRepr_ParallelOffset.hpp>
#include <StepRepr_QuantifiedAssemblyComponentUsage.hpp>
#include <StepShape_MeasureQualification.hpp>
#include <StepData_Logical.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepDimTol_GeometricToleranceTarget.hpp>
#include <StepShape_ValueQualifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include <TCollection_HAsciiString.hpp>

namespace
{

  occ::handle<StepBasic_MeasureWithUnit> CreateMeasureWithUnit(const double theValue)
  {
    occ::handle<StepBasic_MeasureWithUnit> aMeasure = new StepBasic_MeasureWithUnit();

    occ::handle<StepBasic_MeasureValueMember> aValueMember = new StepBasic_MeasureValueMember();
    aValueMember->SetName("POSITIVE_LENGTH_MEASURE");
    aValueMember->SetReal(theValue);
    aMeasure->SetValueComponentMember(aValueMember);

    occ::handle<StepBasic_SiUnit> aSiUnit = new StepBasic_SiUnit();
    aSiUnit->Init(false,
                  StepBasic_SiPrefix::StepBasic_spMilli,
                  StepBasic_SiUnitName::StepBasic_sunMetre);
    StepBasic_Unit aUnit;
    aUnit.SetValue(aSiUnit);
    aMeasure->SetUnitComponent(aUnit);

    return aMeasure;
  }

  occ::handle<StepRepr_ReprItemAndMeasureWithUnit> CreateReprItemAndMeasureWithUnit(
    const double theValue)
  {
    occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasure =
      new StepRepr_ReprItemAndMeasureWithUnit();
    occ::handle<StepBasic_MeasureWithUnit> aMeasure = CreateMeasureWithUnit(theValue);
    aReprMeasure->SetMeasureWithUnit(aMeasure);

    occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("TestReprItem");
    aReprMeasure->SetName(aName);

    return aReprMeasure;
  }
} // namespace

class StepTransientReplacements : public ::testing::Test
{
protected:
  void SetUp() override
  {

    myMeasureWithUnit            = CreateMeasureWithUnit(5.0);
    myReprItemAndMeasureWithUnit = CreateReprItemAndMeasureWithUnit(10.0);

    myDimensionalExponents = new StepBasic_DimensionalExponents();
    myDimensionalExponents->Init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    myName = new TCollection_HAsciiString("TestName");

    myDescription = new TCollection_HAsciiString("TestDescription");

    myProductDefinition = new StepBasic_ProductDefinition();

    myProductDefinitionShape = new StepRepr_ProductDefinitionShape();

    myQualifiers = new NCollection_HArray1<StepShape_ValueQualifier>(1, 1);
  }

  occ::handle<StepBasic_MeasureWithUnit>                     myMeasureWithUnit;
  occ::handle<StepRepr_ReprItemAndMeasureWithUnit>           myReprItemAndMeasureWithUnit;
  occ::handle<StepBasic_DimensionalExponents>                myDimensionalExponents;
  occ::handle<TCollection_HAsciiString>                      myName;
  occ::handle<TCollection_HAsciiString>                      myDescription;
  occ::handle<StepBasic_ProductDefinition>                   myProductDefinition;
  occ::handle<StepRepr_ProductDefinitionShape>               myProductDefinitionShape;
  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> myQualifiers;
};

TEST_F(StepTransientReplacements, ConversionBasedUnit_WorksWithBothTypes)
{

  occ::handle<StepBasic_ConversionBasedUnit> aUnit = new StepBasic_ConversionBasedUnit();

  aUnit->Init(myDimensionalExponents, myName, myMeasureWithUnit);
  EXPECT_FALSE(aUnit->ConversionFactor().IsNull());
  EXPECT_TRUE(aUnit->ConversionFactor()->IsKind(STANDARD_TYPE(StepBasic_MeasureWithUnit)));

  occ::handle<StepBasic_MeasureWithUnit> aMeasure =
    occ::down_cast<StepBasic_MeasureWithUnit>(aUnit->ConversionFactor());
  EXPECT_FALSE(aMeasure.IsNull());
  EXPECT_NEAR(aMeasure->ValueComponent(), 5.0, 1e-7);

  aUnit->SetConversionFactor(myReprItemAndMeasureWithUnit);
  EXPECT_FALSE(aUnit->ConversionFactor().IsNull());
  EXPECT_TRUE(
    aUnit->ConversionFactor()->IsKind(STANDARD_TYPE(StepRepr_ReprItemAndMeasureWithUnit)));

  occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasure =
    occ::down_cast<StepRepr_ReprItemAndMeasureWithUnit>(aUnit->ConversionFactor());
  EXPECT_FALSE(aReprMeasure.IsNull());
  occ::handle<StepBasic_MeasureWithUnit> aExtractedMeasure = aReprMeasure->GetMeasureWithUnit();
  EXPECT_NEAR(aExtractedMeasure->ValueComponent(), 10.0, 1e-7);
}

TEST_F(StepTransientReplacements, GeometricTolerance_WorksWithBothTypes)
{

  occ::handle<StepDimTol_GeometricTolerance> aTolerance = new StepDimTol_GeometricTolerance();

  StepDimTol_GeometricToleranceTarget aTarget;

  aTolerance->Init(myName, myDescription, myMeasureWithUnit, aTarget);
  EXPECT_FALSE(aTolerance->Magnitude().IsNull());
  EXPECT_TRUE(aTolerance->Magnitude()->IsKind(STANDARD_TYPE(StepBasic_MeasureWithUnit)));

  occ::handle<StepBasic_MeasureWithUnit> aMeasure =
    occ::down_cast<StepBasic_MeasureWithUnit>(aTolerance->Magnitude());
  EXPECT_FALSE(aMeasure.IsNull());
  EXPECT_NEAR(aMeasure->ValueComponent(), 5.0, 1e-7);

  aTolerance->SetMagnitude(myReprItemAndMeasureWithUnit);
  EXPECT_FALSE(aTolerance->Magnitude().IsNull());
  EXPECT_TRUE(aTolerance->Magnitude()->IsKind(STANDARD_TYPE(StepRepr_ReprItemAndMeasureWithUnit)));

  occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasure =
    occ::down_cast<StepRepr_ReprItemAndMeasureWithUnit>(aTolerance->Magnitude());
  EXPECT_FALSE(aReprMeasure.IsNull());
  occ::handle<StepBasic_MeasureWithUnit> aExtractedMeasure = aReprMeasure->GetMeasureWithUnit();
  EXPECT_NEAR(aExtractedMeasure->ValueComponent(), 10.0, 1e-7);
}

TEST_F(StepTransientReplacements, MakeFromUsageOption_WorksWithBothTypes)
{

  occ::handle<StepRepr_MakeFromUsageOption> aMakeFromUsage = new StepRepr_MakeFromUsageOption();

  bool hasDescription = true;
  aMakeFromUsage->Init(myName,
                       myName,
                       hasDescription,
                       myDescription,
                       myProductDefinition,
                       myProductDefinition,
                       1,
                       myDescription,
                       myMeasureWithUnit);

  EXPECT_FALSE(aMakeFromUsage->Quantity().IsNull());
  EXPECT_TRUE(aMakeFromUsage->Quantity()->IsKind(STANDARD_TYPE(StepBasic_MeasureWithUnit)));

  occ::handle<StepBasic_MeasureWithUnit> aMeasure =
    occ::down_cast<StepBasic_MeasureWithUnit>(aMakeFromUsage->Quantity());
  EXPECT_FALSE(aMeasure.IsNull());
  EXPECT_NEAR(aMeasure->ValueComponent(), 5.0, 1e-7);

  aMakeFromUsage->SetQuantity(myReprItemAndMeasureWithUnit);
  EXPECT_FALSE(aMakeFromUsage->Quantity().IsNull());
  EXPECT_TRUE(
    aMakeFromUsage->Quantity()->IsKind(STANDARD_TYPE(StepRepr_ReprItemAndMeasureWithUnit)));

  occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasure =
    occ::down_cast<StepRepr_ReprItemAndMeasureWithUnit>(aMakeFromUsage->Quantity());
  EXPECT_FALSE(aReprMeasure.IsNull());
  occ::handle<StepBasic_MeasureWithUnit> aExtractedMeasure = aReprMeasure->GetMeasureWithUnit();
  EXPECT_NEAR(aExtractedMeasure->ValueComponent(), 10.0, 1e-7);
}

TEST_F(StepTransientReplacements, ParallelOffset_WorksWithBothTypes)
{

  occ::handle<StepRepr_ParallelOffset> aParallelOffset = new StepRepr_ParallelOffset();

  aParallelOffset->Init(myName,
                        myDescription,
                        myProductDefinitionShape,
                        StepData_LTrue,
                        myMeasureWithUnit);

  EXPECT_FALSE(aParallelOffset->Offset().IsNull());
  EXPECT_TRUE(aParallelOffset->Offset()->IsKind(STANDARD_TYPE(StepBasic_MeasureWithUnit)));

  occ::handle<StepBasic_MeasureWithUnit> aMeasure =
    occ::down_cast<StepBasic_MeasureWithUnit>(aParallelOffset->Offset());
  EXPECT_FALSE(aMeasure.IsNull());
  EXPECT_NEAR(aMeasure->ValueComponent(), 5.0, 1e-7);

  aParallelOffset->SetOffset(myReprItemAndMeasureWithUnit);
  EXPECT_FALSE(aParallelOffset->Offset().IsNull());
  EXPECT_TRUE(
    aParallelOffset->Offset()->IsKind(STANDARD_TYPE(StepRepr_ReprItemAndMeasureWithUnit)));

  occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasure =
    occ::down_cast<StepRepr_ReprItemAndMeasureWithUnit>(aParallelOffset->Offset());
  EXPECT_FALSE(aReprMeasure.IsNull());
  occ::handle<StepBasic_MeasureWithUnit> aExtractedMeasure = aReprMeasure->GetMeasureWithUnit();
  EXPECT_NEAR(aExtractedMeasure->ValueComponent(), 10.0, 1e-7);
}

TEST_F(StepTransientReplacements, QuantifiedAssemblyComponentUsage_WorksWithBothTypes)
{

  occ::handle<StepRepr_QuantifiedAssemblyComponentUsage> aUsage =
    new StepRepr_QuantifiedAssemblyComponentUsage();

  bool hasDescription         = true;
  bool hasReferenceDesignator = true;
  aUsage->Init(myName,
               myName,
               hasDescription,
               myDescription,
               myProductDefinition,
               myProductDefinition,
               hasReferenceDesignator,
               myName,
               myMeasureWithUnit);

  EXPECT_FALSE(aUsage->Quantity().IsNull());
  EXPECT_TRUE(aUsage->Quantity()->IsKind(STANDARD_TYPE(StepBasic_MeasureWithUnit)));

  occ::handle<StepBasic_MeasureWithUnit> aMeasure =
    occ::down_cast<StepBasic_MeasureWithUnit>(aUsage->Quantity());
  EXPECT_FALSE(aMeasure.IsNull());
  EXPECT_NEAR(aMeasure->ValueComponent(), 5.0, 1e-7);

  aUsage->SetQuantity(myReprItemAndMeasureWithUnit);
  EXPECT_FALSE(aUsage->Quantity().IsNull());
  EXPECT_TRUE(aUsage->Quantity()->IsKind(STANDARD_TYPE(StepRepr_ReprItemAndMeasureWithUnit)));

  occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasure =
    occ::down_cast<StepRepr_ReprItemAndMeasureWithUnit>(aUsage->Quantity());
  EXPECT_FALSE(aReprMeasure.IsNull());
  occ::handle<StepBasic_MeasureWithUnit> aExtractedMeasure = aReprMeasure->GetMeasureWithUnit();
  EXPECT_NEAR(aExtractedMeasure->ValueComponent(), 10.0, 1e-7);
}

TEST_F(StepTransientReplacements, MeasureQualification_WorksWithBothTypes)
{

  occ::handle<StepShape_MeasureQualification> aQualification = new StepShape_MeasureQualification();

  aQualification->Init(myName, myDescription, myMeasureWithUnit, myQualifiers);

  EXPECT_FALSE(aQualification->QualifiedMeasure().IsNull());
  EXPECT_TRUE(aQualification->QualifiedMeasure()->IsKind(STANDARD_TYPE(StepBasic_MeasureWithUnit)));

  occ::handle<StepBasic_MeasureWithUnit> aMeasure =
    occ::down_cast<StepBasic_MeasureWithUnit>(aQualification->QualifiedMeasure());
  EXPECT_FALSE(aMeasure.IsNull());
  EXPECT_NEAR(aMeasure->ValueComponent(), 5.0, 1e-7);

  aQualification->SetQualifiedMeasure(myReprItemAndMeasureWithUnit);
  EXPECT_FALSE(aQualification->QualifiedMeasure().IsNull());
  EXPECT_TRUE(
    aQualification->QualifiedMeasure()->IsKind(STANDARD_TYPE(StepRepr_ReprItemAndMeasureWithUnit)));

  occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasure =
    occ::down_cast<StepRepr_ReprItemAndMeasureWithUnit>(aQualification->QualifiedMeasure());
  EXPECT_FALSE(aReprMeasure.IsNull());
  occ::handle<StepBasic_MeasureWithUnit> aExtractedMeasure = aReprMeasure->GetMeasureWithUnit();
  EXPECT_NEAR(aExtractedMeasure->ValueComponent(), 10.0, 1e-7);
}

TEST_F(StepTransientReplacements, GetMeasureWithUnit_ExtractsCorrectly)
{

  auto GetMeasureWithUnit =
    [](const occ::handle<Standard_Transient>& theMeasure) -> occ::handle<StepBasic_MeasureWithUnit>
  {
    if (theMeasure.IsNull())
    {
      return nullptr;
    }

    occ::handle<StepBasic_MeasureWithUnit> aMeasureWithUnit;
    if (theMeasure->IsKind(STANDARD_TYPE(StepBasic_MeasureWithUnit)))
    {
      aMeasureWithUnit = occ::down_cast<StepBasic_MeasureWithUnit>(theMeasure);
    }
    else if (theMeasure->IsKind(STANDARD_TYPE(StepRepr_ReprItemAndMeasureWithUnit)))
    {
      occ::handle<StepRepr_ReprItemAndMeasureWithUnit> aReprMeasureItem =
        occ::down_cast<StepRepr_ReprItemAndMeasureWithUnit>(theMeasure);
      aMeasureWithUnit = aReprMeasureItem->GetMeasureWithUnit();
    }
    return aMeasureWithUnit;
  };

  occ::handle<Standard_Transient>        aNullTransient;
  occ::handle<StepBasic_MeasureWithUnit> aExtracted = GetMeasureWithUnit(aNullTransient);
  EXPECT_TRUE(aExtracted.IsNull());

  aExtracted = GetMeasureWithUnit(myMeasureWithUnit);
  EXPECT_FALSE(aExtracted.IsNull());
  EXPECT_NEAR(aExtracted->ValueComponent(), 5.0, 1e-7);

  aExtracted = GetMeasureWithUnit(myReprItemAndMeasureWithUnit);
  EXPECT_FALSE(aExtracted.IsNull());
  EXPECT_NEAR(aExtracted->ValueComponent(), 10.0, 1e-7);

  occ::handle<Standard_Transient> anUnrelatedTransient = myName;
  aExtracted                                           = GetMeasureWithUnit(anUnrelatedTransient);
  EXPECT_TRUE(aExtracted.IsNull());
}
