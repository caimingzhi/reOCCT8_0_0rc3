

#include <TDataStd_AsciiString.hpp>
#include <TDataStd_BooleanArray.hpp>
#include <TDataStd_BooleanList.hpp>
#include <TDataStd_ByteArray.hpp>
#include <TDataStd_ExtStringArray.hpp>
#include <TDataStd_ExtStringList.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_IntegerArray.hpp>
#include <TDataStd_IntegerList.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_Real.hpp>
#include <TDataStd_RealArray.hpp>
#include <TDataStd_RealList.hpp>
#include <TDataStd_ReferenceArray.hpp>
#include <TDataStd_ReferenceList.hpp>
#include <TDocStd_Application.hpp>
#include <TDocStd_Document.hpp>
#include <TDF_Label.hpp>
#include <Standard_GUID.hpp>

#include <gtest/gtest.h>

TEST(TDataStd_Attribute_Test, OCC29371_AttributeGUIDsNotNull)
{

  occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
  occ::handle<TDocStd_Document>    aDoc;
  anApp->NewDocument("BinOcaf", aDoc);
  TDF_Label aLab = aDoc->Main();

  Standard_GUID aNullGuid("00000000-0000-0000-0000-000000000000");

  occ::handle<TDataStd_AsciiString> aStrAtt = new TDataStd_AsciiString();
  aLab.AddAttribute(aStrAtt);
  EXPECT_NE(aNullGuid, aStrAtt->ID());

  occ::handle<TDataStd_BooleanArray> aBArAtt = new TDataStd_BooleanArray();
  aLab.AddAttribute(aBArAtt);
  EXPECT_NE(aNullGuid, aBArAtt->ID());

  occ::handle<TDataStd_BooleanList> aBListAtt = new TDataStd_BooleanList();
  aLab.AddAttribute(aBListAtt);
  EXPECT_NE(aNullGuid, aBListAtt->ID());

  occ::handle<TDataStd_ByteArray> aByteArAtt = new TDataStd_ByteArray();
  aLab.AddAttribute(aByteArAtt);
  EXPECT_NE(aNullGuid, aByteArAtt->ID());

  occ::handle<TDataStd_ExtStringArray> anExtStrArAtt = new TDataStd_ExtStringArray();
  aLab.AddAttribute(anExtStrArAtt);
  EXPECT_NE(aNullGuid, anExtStrArAtt->ID());

  occ::handle<TDataStd_ExtStringList> anExtStrListAtt = new TDataStd_ExtStringList();
  aLab.AddAttribute(anExtStrListAtt);
  EXPECT_NE(aNullGuid, anExtStrListAtt->ID());

  occ::handle<TDataStd_Integer> anIntAtt = new TDataStd_Integer();
  aLab.AddAttribute(anIntAtt);
  EXPECT_NE(aNullGuid, anIntAtt->ID());

  occ::handle<TDataStd_IntegerArray> anIntArrAtt = new TDataStd_IntegerArray();
  aLab.AddAttribute(anIntArrAtt);
  EXPECT_NE(aNullGuid, anIntArrAtt->ID());

  occ::handle<TDataStd_IntegerList> anIntListAtt = new TDataStd_IntegerList();
  aLab.AddAttribute(anIntListAtt);
  EXPECT_NE(aNullGuid, anIntListAtt->ID());

  occ::handle<TDataStd_Name> aNameAtt = new TDataStd_Name();
  aLab.AddAttribute(aNameAtt);
  EXPECT_NE(aNullGuid, aNameAtt->ID());

  occ::handle<TDataStd_Real> aRealAtt = new TDataStd_Real();
  aLab.AddAttribute(aRealAtt);
  EXPECT_NE(aNullGuid, aRealAtt->ID());

  occ::handle<TDataStd_RealArray> aRealArrAtt = new TDataStd_RealArray();
  aLab.AddAttribute(aRealArrAtt);
  EXPECT_NE(aNullGuid, aRealArrAtt->ID());

  occ::handle<TDataStd_RealList> aRealListAtt = new TDataStd_RealList();
  aLab.AddAttribute(aRealListAtt);
  EXPECT_NE(aNullGuid, aRealListAtt->ID());

  occ::handle<TDataStd_ReferenceArray> aRefArrAtt = new TDataStd_ReferenceArray();
  aLab.AddAttribute(aRefArrAtt);
  EXPECT_NE(aNullGuid, aRefArrAtt->ID());

  occ::handle<TDataStd_ReferenceList> aRefListAtt = new TDataStd_ReferenceList();
  aLab.AddAttribute(aRefListAtt);
  EXPECT_NE(aNullGuid, aRefListAtt->ID());

  anApp->Close(aDoc);
}
