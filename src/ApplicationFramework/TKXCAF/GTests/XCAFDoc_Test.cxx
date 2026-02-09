

#include <BRepPrimAPI_MakeBox.hpp>
#include <Standard_GUID.hpp>
#include <TDataStd_Name.hpp>
#include <TDocStd_Application.hpp>
#include <TDocStd_Document.hpp>
#include <XCAFDoc.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>

#include <gtest/gtest.h>

TEST(XCAFDoc_Test, OCC738_ShapeRefGUID)
{

  Standard_GUID aGUID;
  EXPECT_NO_THROW(aGUID = XCAFDoc::ShapeRefGUID());

  Standard_GUID aNullGUID("00000000-0000-0000-0000-000000000000");
  EXPECT_NE(aGUID, aNullGUID) << "ShapeRefGUID should not be null";
}

TEST(XCAFDoc_Test, OCC738_AssemblyGUID)
{

  Standard_GUID aGUID;
  EXPECT_NO_THROW(aGUID = XCAFDoc::AssemblyGUID());

  Standard_GUID aNullGUID("00000000-0000-0000-0000-000000000000");
  EXPECT_NE(aGUID, aNullGUID) << "AssemblyGUID should not be null";
}

class AutoNamingGuard
{
public:
  AutoNamingGuard()
      : mySavedValue(XCAFDoc_ShapeTool::AutoNaming())
  {
  }

  ~AutoNamingGuard() { XCAFDoc_ShapeTool::SetAutoNaming(mySavedValue); }

  AutoNamingGuard(const AutoNamingGuard&)            = delete;
  AutoNamingGuard& operator=(const AutoNamingGuard&) = delete;

private:
  bool mySavedValue;
};

TEST(XCAFDoc_Test, OCC23595_AutoNaming)
{

  AutoNamingGuard aGuard;

  occ::handle<TDocStd_Application> anApp = new TDocStd_Application();
  occ::handle<TDocStd_Document>    aDoc;
  anApp->NewDocument("XmlXCAF", aDoc);
  ASSERT_FALSE(aDoc.IsNull());

  occ::handle<XCAFDoc_ShapeTool> aShTool = XCAFDoc_DocumentTool::ShapeTool(aDoc->Main());

  bool aValue = XCAFDoc_ShapeTool::AutoNaming();
  EXPECT_TRUE(aValue) << "AutoNaming should be true by default";

  XCAFDoc_ShapeTool::SetAutoNaming(true);
  TopoDS_Shape               aShape1 = BRepPrimAPI_MakeBox(100., 200., 300.).Shape();
  TDF_Label                  aLabel1 = aShTool->AddShape(aShape1);
  occ::handle<TDataStd_Name> anAttr;
  EXPECT_TRUE(aLabel1.FindAttribute(TDataStd_Name::GetID(), anAttr))
    << "Shape should have a name attribute when AutoNaming is true";

  XCAFDoc_ShapeTool::SetAutoNaming(false);
  TopoDS_Shape aShape2 = BRepPrimAPI_MakeBox(300., 200., 100.).Shape();
  TDF_Label    aLabel2 = aShTool->AddShape(aShape2);
  EXPECT_FALSE(aLabel2.FindAttribute(TDataStd_Name::GetID(), anAttr))
    << "Shape should not have a name attribute when AutoNaming is false";
}
