

#include <gtest/gtest.h>

#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TNaming_Name.hpp>
#include <TNaming_NamedShape.hpp>

TEST(TNaming_Name_Test, BUC60925_SolveWithEmptyNamedShape)
{

  occ::handle<TDF_Data> aDF = new TDF_Data();

  TDF_Label aLabel = aDF->Root().FindChild(2, true);

  NCollection_Map<TDF_Label> aLabelMap;
  aLabelMap.Add(aLabel);

  occ::handle<TNaming_NamedShape> aNS = new TNaming_NamedShape;

  TNaming_Name aNN;
  aNN.Type(TNaming_IDENTITY);
  aNN.Append(aNS);

  bool aResult = aNN.Solve(aLabel, aLabelMap);

  EXPECT_FALSE(aResult) << "Solve should return false for empty NamedShape";
}
