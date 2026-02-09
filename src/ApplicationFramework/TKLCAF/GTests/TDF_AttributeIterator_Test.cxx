

#include <TDF_AttributeIterator.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_Real.hpp>
#include <TDocStd_Application.hpp>
#include <TDocStd_Document.hpp>

#include <gtest/gtest.h>

TEST(TDF_AttributeIterator_Test, OCC24755_AttributeInsertionOrder)
{
  occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
  occ::handle<TDocStd_Document>    aDoc;
  anApp->NewDocument("BinOcaf", aDoc);
  TDF_Label aLab = aDoc->Main();

  TDataStd_Integer::Set(aLab, 0);

  TDataStd_Name::Set(aLab, "test");

  aLab.AddAttribute(new TDataStd_Real(), true);

  TDF_AttributeIterator anIter(aLab);

  ASSERT_TRUE(anIter.More()) << "Iterator should have first attribute";
  occ::handle<TDF_Attribute> anAttr = anIter.Value();
  EXPECT_TRUE(anAttr->IsKind(STANDARD_TYPE(TDataStd_Integer)))
    << "First attribute should be TDataStd_Integer";

  anIter.Next();
  ASSERT_TRUE(anIter.More()) << "Iterator should have second attribute";
  anAttr = anIter.Value();
  EXPECT_TRUE(anAttr->IsKind(STANDARD_TYPE(TDataStd_Name)))
    << "Second attribute should be TDataStd_Name";

  anIter.Next();
  ASSERT_TRUE(anIter.More()) << "Iterator should have third attribute";
  anAttr = anIter.Value();
  EXPECT_TRUE(anAttr->IsKind(STANDARD_TYPE(TDataStd_Real)))
    << "Third attribute should be TDataStd_Real";

  anIter.Next();
  EXPECT_FALSE(anIter.More()) << "Iterator should have no more attributes";
}
