

#include <BRepPrimAPI_MakeBox.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESControl_Writer.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_FinderProcess.hpp>

#include <gtest/gtest.h>

TEST(IGESExportTest, SharedCurvesBRepMode)
{
  TopoDS_Shape aSolid = (TopoDS_Solid)BRepPrimAPI_MakeBox(gp_Pnt(0, 0, 0), 1, 1, 1);

  int                aBRepMode = 1;
  IGESControl_Writer aWriter("MM", aBRepMode);
  aWriter.AddShape(aSolid);

  const occ::handle<Transfer_FinderProcess>& aFP    = aWriter.TransferProcess();
  const occ::handle<IGESData_IGESModel>&     aModel = aWriter.Model();

  for (int i = 1; i <= aFP->NbMapped(); i++)
  {
    occ::handle<Transfer_SimpleBinderOfTransient> aBinder =
      occ::down_cast<Transfer_SimpleBinderOfTransient>(aFP->MapItem(i));
    if (aBinder.IsNull())
      continue;

    occ::handle<IGESData_IGESEntity> anEnt = occ::down_cast<IGESData_IGESEntity>(aBinder->Result());
    if (anEnt.IsNull())
      continue;

    occ::handle<IGESGeom_Line> aLine = occ::down_cast<IGESGeom_Line>(anEnt);
    if (aLine.IsNull())
      continue;

    EXPECT_TRUE(aModel->DNum(anEnt) != 0);
  }
}
