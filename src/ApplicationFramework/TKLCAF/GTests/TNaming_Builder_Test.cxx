

#include <gtest/gtest.h>

#include <BRepPrimAPI_MakeBox.hpp>
#include <TDocStd_Document.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopoDS_Shape.hpp>
#include <gp_Pnt.hpp>

TEST(TNaming_Builder_Test, OCC361_ShapeOrientationPreservation)
{

  occ::handle<TDocStd_Document> aDoc = new TDocStd_Document("BinOcaf");

  BRepPrimAPI_MakeBox aBoxMaker(gp_Pnt(0, 0, 0), 100, 100, 100);
  TopoDS_Shape        aBox = aBoxMaker.Shape();
  aBox.Orientation(TopAbs_FORWARD);

  TDF_Label aTestLabel = aDoc->Main();

  TNaming_Builder aBuilder(aTestLabel);
  aBuilder.Generated(aBox);

  TopoDS_Shape aBox1 = aBox;
  aBox1.Orientation(TopAbs_REVERSED);

  aTestLabel.ForgetAllAttributes();

  TNaming_Builder aBuilder2(aTestLabel);
  aBuilder2.Generated(aBox1);

  aBox = aBuilder2.NamedShape()->Get();

  EXPECT_EQ(TopAbs_REVERSED, aBox.Orientation())
    << "Shape orientation should be preserved as REVERSED after TNaming_Builder operations";
}
