

#include <TopLoc_Location.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <BRep_Tool.hpp>
#include <gp.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <OSD_Parallel.hpp>

#include <gtest/gtest.h>

#include <atomic>
#include <vector>

namespace
{

  struct TopLocTransformFunctor
  {
    TopLocTransformFunctor(const std::vector<TopoDS_Shape>& theShapeVec)
        : myShapeVec(&theShapeVec),
          myIsRaceDetected(0)
    {
    }

    void operator()(size_t i) const
    {
      if (!myIsRaceDetected)
      {
        const TopoDS_Vertex& aVertex = TopoDS::Vertex(myShapeVec->at(i));
        gp_Pnt               aPoint  = BRep_Tool::Pnt(aVertex);
        if (aPoint.X() != static_cast<double>(i))
        {
          ++myIsRaceDetected;
        }
      }
    }

    const std::vector<TopoDS_Shape>* myShapeVec;
    mutable std::atomic<int>         myIsRaceDetected;
  };
} // namespace

TEST(TopLoc_Location_Test, OCC25545_ConcurrentTransformationAccess)
{

  int                          n = 1000;
  std::vector<TopoDS_Shape>    aShapeVec(n);
  std::vector<TopLoc_Location> aLocVec(n);
  TopoDS_Shape                 aShape = BRepBuilderAPI_MakeVertex(gp::Origin());
  aShapeVec[0]                        = aShape;

  for (int i = 1; i < n; ++i)
  {
    gp_Trsf aTrsf;
    aTrsf.SetTranslation(gp_Vec(1, 0, 0));
    aLocVec[i]   = aLocVec[i - 1] * aTrsf;
    aShapeVec[i] = aShape.Moved(aLocVec[i]);
  }

  TopLocTransformFunctor aFunc(aShapeVec);

  OSD_Parallel::For(0, n, aFunc);

  EXPECT_EQ(aFunc.myIsRaceDetected, 0)
    << "Data race detected in concurrent TopLoc_Location::Transformation() access";
}
