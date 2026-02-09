#include <BRepMesh_FaceChecker.hpp>
#include <IMeshData_Wire.hpp>
#include <IMeshData_Edge.hpp>
#include <OSD_Parallel.hpp>
#include <BRepMesh_GeomTool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_FaceChecker, Standard_Transient)

namespace
{
  const double MaxTangentAngle = 5. * M_PI / 180.;

  class SegmentsFiller
  {
  public:
    SegmentsFiller(const IMeshData::IFaceHandle&                    theDFace,
                   Handle(BRepMesh_FaceChecker::ArrayOfSegments)&   theWiresSegments,
                   Handle(BRepMesh_FaceChecker::ArrayOfBndBoxTree)& theWiresBndBoxTree)
        : myDFace(theDFace),
          myWiresSegments(theWiresSegments),
          myWiresBndBoxTree(theWiresBndBoxTree)
    {
      myWiresSegments   = new BRepMesh_FaceChecker::ArrayOfSegments(0, myDFace->WiresNb() - 1);
      myWiresBndBoxTree = new BRepMesh_FaceChecker::ArrayOfBndBoxTree(0, myDFace->WiresNb() - 1);
    }

    void operator()(const int theWireIndex) const
    {
      const IMeshData::IWireHandle& aDWire = myDFace->GetWire(theWireIndex);

      occ::handle<NCollection_IncAllocator> aTmpAlloc1 = new NCollection_IncAllocator();

      Handle(BRepMesh_FaceChecker::Segments) aSegments =
        new BRepMesh_FaceChecker::Segments(aDWire->EdgesNb(), aTmpAlloc1);
      Handle(IMeshData::BndBox2dTree) aBndBoxTree = new IMeshData::BndBox2dTree(aTmpAlloc1);

      myWiresSegments->ChangeValue(theWireIndex)   = aSegments;
      myWiresBndBoxTree->ChangeValue(theWireIndex) = aBndBoxTree;

      occ::handle<NCollection_IncAllocator> aTmpAlloc2 = new NCollection_IncAllocator();
      IMeshData::BndBox2dTreeFiller         aBndBoxTreeFiller(*aBndBoxTree, aTmpAlloc2);

      for (int aEdgeIt = 0; aEdgeIt < aDWire->EdgesNb(); ++aEdgeIt)
      {

        const IMeshData::IEdgePtr&      aDEdge = aDWire->GetEdge(aEdgeIt);
        const IMeshData::IPCurveHandle& aPCurve =
          aDEdge->GetPCurve(myDFace.get(), aDWire->GetEdgeOrientation(aEdgeIt));

        for (int aPointIt = 1; aPointIt < aPCurve->ParametersNb(); ++aPointIt)
        {
          gp_Pnt2d& aPnt1 = aPCurve->GetPoint(aPointIt - 1);
          gp_Pnt2d& aPnt2 = aPCurve->GetPoint(aPointIt);

          Bnd_Box2d aBox;
          aBox.Add(aPnt1);
          aBox.Add(aPnt2);
          aBox.Enlarge(Precision::Confusion());

          aBndBoxTreeFiller.Add(aSegments->Size(), aBox);
          aSegments->Append(BRepMesh_FaceChecker::Segment(aDEdge, &aPnt1, &aPnt2));
        }
      }

      aBndBoxTreeFiller.Fill();
    }

  private:
    SegmentsFiller(const SegmentsFiller& theOther) = delete;

    void operator=(const SegmentsFiller& theOther) = delete;

  private:
    const IMeshData::IFaceHandle&                    myDFace;
    Handle(BRepMesh_FaceChecker::ArrayOfSegments)&   myWiresSegments;
    Handle(BRepMesh_FaceChecker::ArrayOfBndBoxTree)& myWiresBndBoxTree;
  };

  class BndBox2dTreeSelector : public IMeshData::BndBox2dTree::Selector
  {
  public:
    BndBox2dTreeSelector(const double theTolerance)
        : myMaxLoopSize(M_PI * theTolerance * theTolerance),
          mySelfSegmentIndex(-1),
          mySegment(nullptr),
          myIndices(256, new NCollection_IncAllocator(IMeshData::MEMORY_BLOCK_SIZE_HUGE))
    {
    }

    void SetSegments(const Handle(BRepMesh_FaceChecker::Segments)& theSegments)
    {
      mySegments = theSegments;
    }

    void Reset(const BRepMesh_FaceChecker::Segment* theSegment, const int theSelfSegmentIndex)
    {
      myIndices.Clear();

      mySelfSegmentIndex = theSelfSegmentIndex;
      mySegment          = theSegment;

      myBox.SetVoid();
      myBox.Add(*mySegment->Point1);
      myBox.Add(*mySegment->Point2);
      myBox.Enlarge(Precision::Confusion());
    }

    bool Reject(const Bnd_Box2d& theBox) const override { return myBox.IsOut(theBox); }

    bool Accept(const int& theSegmentIndex) override
    {
      const BRepMesh_FaceChecker::Segment& aSegment = mySegments->Value(theSegmentIndex);

      gp_Pnt2d                         aIntPnt;
      const BRepMesh_GeomTool::IntFlag aIntStatus =
        BRepMesh_GeomTool::IntSegSeg(mySegment->Point1->XY(),
                                     mySegment->Point2->XY(),
                                     aSegment.Point1->XY(),
                                     aSegment.Point2->XY(),
                                     false,
                                     false,
                                     aIntPnt);

      if (aIntStatus == BRepMesh_GeomTool::Cross)
      {
        const double aAngle = gp_Vec2d(mySegment->Point1->XY(), mySegment->Point2->XY())
                                .Angle(gp_Vec2d(aSegment.Point1->XY(), aSegment.Point2->XY()));

        if (std::abs(aAngle) < MaxTangentAngle)
        {
          return false;
        }

        if (mySelfSegmentIndex != -1)
        {
          gp_XY        aPrevVec;
          double       aSumS   = 0.;
          const gp_XY& aRefPnt = aIntPnt.Coord();
          for (int i = mySelfSegmentIndex; i < theSegmentIndex; ++i)
          {
            const BRepMesh_FaceChecker::Segment& aCurrSegment = mySegments->Value(i);
            gp_XY                                aCurVec      = aCurrSegment.Point2->XY() - aRefPnt;

            if (aCurVec.SquareModulus() < gp::Resolution())
              continue;

            if (aPrevVec.SquareModulus() > gp::Resolution())
              aSumS += aPrevVec ^ aCurVec;

            aPrevVec = aCurVec;
          }

          if (std::abs(aSumS / 2.) < myMaxLoopSize)
          {
            return false;
          }
        }

        myIndices.Append(theSegmentIndex);
        return true;
      }

      return false;
    }

    const IMeshData::VectorOfInteger& Indices() const { return myIndices; }

  private:
    double                                 myMaxLoopSize;
    int                                    mySelfSegmentIndex;
    Handle(BRepMesh_FaceChecker::Segments) mySegments;
    const BRepMesh_FaceChecker::Segment*   mySegment;
    Bnd_Box2d                              myBox;
    IMeshData::VectorOfInteger             myIndices;
  };
} // namespace

BRepMesh_FaceChecker::BRepMesh_FaceChecker(const IMeshData::IFaceHandle& theFace,
                                           const IMeshTools_Parameters&  theParameters)
    : myDFace(theFace),
      myParameters(theParameters)
{
}

BRepMesh_FaceChecker::~BRepMesh_FaceChecker() = default;

bool BRepMesh_FaceChecker::Perform()
{
  myIntersectingEdges = new IMeshData::MapOfIEdgePtr;
  collectSegments();

  OSD_Parallel::For(0, myDFace->WiresNb(), *this, !isParallel());
  collectResult();

  myWiresBndBoxTree.Nullify();
  myWiresSegments.Nullify();
  myWiresIntersectingEdges.Nullify();
  return myIntersectingEdges->IsEmpty();
}

void BRepMesh_FaceChecker::collectSegments()
{
  SegmentsFiller aSegmentsFiller(myDFace, myWiresSegments, myWiresBndBoxTree);
  OSD_Parallel::For(0, myDFace->WiresNb(), aSegmentsFiller, !isParallel());

  myWiresIntersectingEdges = new ArrayOfMapOfIEdgePtr(0, myDFace->WiresNb() - 1);
}

void BRepMesh_FaceChecker::perform(const int theWireIndex) const
{
  const occ::handle<Segments>&      aSegments1 = myWiresSegments->Value(theWireIndex);
  Handle(IMeshData::MapOfIEdgePtr)& aIntersections =
    myWiresIntersectingEdges->ChangeValue(theWireIndex);

  BndBox2dTreeSelector aSelector(2 * myDFace->GetDeflection());
  for (int aWireIt = theWireIndex; aWireIt < myDFace->WiresNb(); ++aWireIt)
  {
    const Handle(IMeshData::BndBox2dTree)& aBndBoxTree2 = myWiresBndBoxTree->Value(aWireIt);
    const occ::handle<Segments>&           aSegments2   = myWiresSegments->Value(aWireIt);

    aSelector.SetSegments(aSegments2);
    for (int aSegmentIt = 0; aSegmentIt < aSegments1->Size(); ++aSegmentIt)
    {
      const BRepMesh_FaceChecker::Segment& aSegment1 = aSegments1->Value(aSegmentIt);
      aSelector.Reset(&aSegment1, (aWireIt == theWireIndex) ? aSegmentIt : -1);
      if (aBndBoxTree2->Select(aSelector) != 0)
      {
        if (aIntersections.IsNull())
        {
          aIntersections = new IMeshData::MapOfIEdgePtr;
        }

        aIntersections->Add(aSegment1.EdgePtr);

        const IMeshData::VectorOfInteger& aSegments = aSelector.Indices();
        for (int aSelIt = 0; aSelIt < aSegments.Size(); ++aSelIt)
        {
          const BRepMesh_FaceChecker::Segment& aSegment2 = aSegments2->Value(aSegments(aSelIt));
          aIntersections->Add(aSegment2.EdgePtr);
        }
      }
    }
  }
}

void BRepMesh_FaceChecker::collectResult()
{
  for (int aWireIt = 0; aWireIt < myDFace->WiresNb(); ++aWireIt)
  {
    const Handle(IMeshData::MapOfIEdgePtr)& aEdges = myWiresIntersectingEdges->Value(aWireIt);
    if (!aEdges.IsNull())
    {
      NCollection_MapAlgo::Unite(*myIntersectingEdges, *aEdges);
    }
  }
}
