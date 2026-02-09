#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_Sewing.hpp>
#include <Geom2d_Curve.hpp>
#include <gp_Pnt.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeAnalysis_WireOrder.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeFix_Face.hpp>
#include <ShapeFix_FaceConnect.hpp>
#include <ShapeFix_Wire.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>

#ifdef OCCT_DEBUG
  #include <NCollection_Map.hpp>
#endif

ShapeFix_FaceConnect::ShapeFix_FaceConnect() = default;

bool ShapeFix_FaceConnect::Add(const TopoDS_Face& aFirst, const TopoDS_Face& aSecond)
{
  if (!aFirst.IsNull() && !aSecond.IsNull())
  {

    if (myConnected.IsBound(aFirst))
    {

      NCollection_List<TopoDS_Shape>& theFirstList = myConnected(aFirst);

      NCollection_List<TopoDS_Shape>::Iterator theIter;
      for (theIter.Initialize(theFirstList); theIter.More(); theIter.Next())
        if (theIter.Value().IsSame(aSecond))
          return true;
      theFirstList.Append(aSecond);
    }
    else
    {

      NCollection_List<TopoDS_Shape> theNewFirstList;
      theNewFirstList.Append(aSecond);
      myConnected.Bind(aFirst, theNewFirstList);
    }

    if (!aFirst.IsSame(aSecond))
    {
      if (myConnected.IsBound(aSecond))
      {

        myConnected(aSecond).Append(aFirst);
      }
      else
      {

        NCollection_List<TopoDS_Shape> theNewSecondList;
        theNewSecondList.Append(aFirst);
        myConnected.Bind(aSecond, theNewSecondList);
      }
    }

    return true;
  }

  return false;
}

TopoDS_Shell ShapeFix_FaceConnect::Build(const TopoDS_Shell& shell,
                                         const double        sewtoler,
                                         const double        fixtoler)
{
  TopoDS_Shell result = shell;

  myOriFreeEdges.Clear();
  myResFreeEdges.Clear();
  myResSharEdges.Clear();

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> theFreeEdges;
  TopoDS_Shape                                                             theEdge, theFace;

  for (TopoDS_Iterator itf(result); itf.More(); itf.Next())
  {
    theFace = itf.Value();
    for (TopExp_Explorer expe(theFace, TopAbs_EDGE); expe.More(); expe.Next())
    {
      theEdge = expe.Current();
      if (theFreeEdges.IsBound(theEdge))
        theFreeEdges.UnBind(theEdge);
      else
        theFreeEdges.Bind(theEdge, theFace);
    }
  }

  for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator theFEIter(
         theFreeEdges);
       theFEIter.More();
       theFEIter.Next())
  {

    theEdge = theFEIter.Key(), theFace = theFEIter.Value();

    if (myConnected.IsBound(theFace) && !BRep_Tool::Degenerated(TopoDS::Edge(theEdge)))
    {

      if (myOriFreeEdges.IsBound(theFace))
      {

        myOriFreeEdges(theFace).Append(theEdge);
      }
      else
      {

        NCollection_List<TopoDS_Shape> theNewList;
        theNewList.Append(theEdge);
        myOriFreeEdges.Bind(theFace, theNewList);
      }

      if (!myResFreeEdges.IsBound(theEdge))
      {
        NCollection_List<TopoDS_Shape> theFree, theShared;
        theFree.Append(theEdge);
        myResFreeEdges.Bind(theEdge, theFree);
        myResSharEdges.Bind(theEdge, theShared);
      }
    }
  }

  theFreeEdges.Clear();

#ifdef OCCT_DEBUG

  if (!myOriFreeEdges.IsEmpty())
  {
    std::cout << std::endl << "FACE CONNECT PREPARATION RESULTS:" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    int freenum = 0, facenum = 0;
    for (NCollection_DataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator theOFIter(myOriFreeEdges);
         theOFIter.More();
         theOFIter.Next())
    {
      freenum += theOFIter.Value().Extent();
      facenum++;
    }
    std::cout << "TOTAL: " << facenum << " faces containing " << freenum << " free edges"
              << std::endl;
  }

#endif

  if (!myOriFreeEdges.IsEmpty())
  {

    TopoDS_Shape                     theFirstFace, theSecondFace;
    NCollection_Array1<TopoDS_Shape> theFacesToSew(1, 2);
    int                              theNumOfFacesToSew = 0;
    bool                             skip_pair          = false;

    NCollection_List<TopoDS_Shape>::Iterator theOriginalIter, theResultsIter;
    TopoDS_Shape                             theAuxE, theOrigE, theAuxF;

    BRep_Builder theBuilder;

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
      theProcessed;

    for (NCollection_DataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator theConnectedIter(myConnected);
         theConnectedIter.More();
         theConnectedIter.Next())
    {

      theFirstFace = theConnectedIter.Key();
      if (myOriFreeEdges.IsBound(theFirstFace))
      {

        theFacesToSew.SetValue(1, theFirstFace);
        theNumOfFacesToSew = 1;

        NCollection_List<TopoDS_Shape> theProcessedList;

        const NCollection_List<TopoDS_Shape>&    theConnectedList = theConnectedIter.Value();
        NCollection_List<TopoDS_Shape>::Iterator theConnectedListIter;
        for (theConnectedListIter.Initialize(theConnectedList); theConnectedListIter.More();
             theConnectedListIter.Next())
        {

          theSecondFace = theConnectedListIter.Value();
          if (myOriFreeEdges.IsBound(theSecondFace))
          {

            theFacesToSew.SetValue(2, theSecondFace);

            theProcessedList.Append(theSecondFace);

            skip_pair = false;
            if (theProcessed.IsBound(theSecondFace))
            {
              NCollection_List<TopoDS_Shape>&          theProcCnxList = theProcessed(theSecondFace);
              NCollection_List<TopoDS_Shape>::Iterator theProcCnxListIter;
              for (theProcCnxListIter.Initialize(theProcCnxList);
                   theProcCnxListIter.More() && !skip_pair;
                   theProcCnxListIter.Next())
                if (theFirstFace.IsSame(theProcCnxListIter.Value()))
                  skip_pair = true;
            }
            if (!skip_pair)
            {

              if (theFirstFace.IsSame(theSecondFace))
              {
#ifdef OCCT_DEBUG
                std::cout << "Warning: ShapeFix_FaceConnect::Build: Self-connected face"
                          << std::endl;
#endif
              }
              else
                theNumOfFacesToSew = 2;

              NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>
                                    theSewerWires;
              BRepBuilderAPI_Sewing theSewer(sewtoler);

              int i = 1;
              for (i = 1; i <= theNumOfFacesToSew; i++)
              {

                TopoDS_Shape theFaceToSew = theFacesToSew(i);
                theAuxF                   = theFaceToSew.EmptyCopied();

                for (theOriginalIter.Initialize(myOriFreeEdges(theFaceToSew));
                     theOriginalIter.More();
                     theOriginalIter.Next())
                {
                  for (theResultsIter.Initialize(myResFreeEdges(theOriginalIter.Value()));
                       theResultsIter.More();
                       theResultsIter.Next())
                  {

                    theAuxE = theResultsIter.Value();
                    TopoDS_Wire theAuxW;
                    theBuilder.MakeWire(theAuxW);
                    theBuilder.Add(theAuxW, theAuxE);
                    theBuilder.Add(theAuxF, theAuxW);
                    theSewerWires.Bind(theAuxE, theAuxW);
                    theSewer.Add(theAuxW);
                  }
                }

                theSewer.Add(theAuxF);
              }

              bool sewing_ok = true;
              {
                try
                {
                  OCC_CATCH_SIGNALS
                  theSewer.Perform();
                }
                catch (Standard_Failure const&)
                {
                  sewing_ok = false;
                }
              }
              if (sewing_ok)
                if (theSewer.SewedShape().IsNull())
                  sewing_ok = false;

              if (sewing_ok)
              {
                NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>
                  theResultEdges;

                for (i = 1; i <= theNumOfFacesToSew; i++)
                {
                  for (theOriginalIter.Initialize(myOriFreeEdges(theFacesToSew(i)));
                       theOriginalIter.More();
                       theOriginalIter.Next())
                  {

                    theOrigE                                       = theOriginalIter.Value();
                    NCollection_List<TopoDS_Shape>& theOldFreeList = myResFreeEdges(theOrigE);
                    theResultsIter.Initialize(theOldFreeList);
                    while (theResultsIter.More())
                    {
                      theAuxE = theSewerWires(theResultsIter.Value());

                      if (theSewer.IsModified(theAuxE))
                      {

                        for (TopExp_Explorer expe(theSewer.Modified(theAuxE), TopAbs_EDGE);
                             expe.More();
                             expe.Next())
                        {
                          theAuxE = expe.Current();

                          if (theResultEdges.IsBound(theAuxE))
                          {

                            myResSharEdges(theResultEdges(theAuxE)).Append(theAuxE);
                            myResSharEdges(theOrigE).Append(theAuxE);
                            theResultEdges.UnBind(theAuxE);
                          }
                          else
                            theResultEdges.Bind(theAuxE, theOrigE);
                        }

                        theOldFreeList.Remove(theResultsIter);
                      }
                      else
                        theResultsIter.Next();
                    }
                  }
                }

                for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::
                       Iterator theResIter(theResultEdges);
                     theResIter.More();
                     theResIter.Next())
                {
                  theAuxE = theResIter.Key();
                  myResFreeEdges(theResIter.Value()).Append(theAuxE);
                }
              }
            }
          }
        }

        theProcessed.Bind(theFirstFace, theProcessedList);
      }
    }

    theProcessed.Clear();

#ifdef OCCT_DEBUG

    std::cout << std::endl << "FACE CONNECT SEWING RESULTS:" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Sewing tolerance was set to " << sewtoler << std::endl;
    int totfree = 0, totshared = 0;
    for (NCollection_DataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator theOF2Iter(myOriFreeEdges);
         theOF2Iter.More();
         theOF2Iter.Next())
    {
      NCollection_List<TopoDS_Shape>::Iterator theOFL2Iter;
      for (theOFL2Iter.Initialize(theOF2Iter.Value()); theOFL2Iter.More(); theOFL2Iter.Next())
      {
        totfree += myResFreeEdges(theOFL2Iter.Value()).Extent();
        totshared += myResSharEdges(theOFL2Iter.Value()).Extent();
      }
    }
    std::cout << "TOTAL: " << totfree << " free, " << totshared << " shared edges" << std::endl;

#endif

    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> theRepEdges;
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                             theRepVertices;
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> theOldVertices;
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
      theNewVertices;

    TopoDS_Wire   theNewW;
    TopoDS_Vertex theOldV1, theOldV2, theNewV1, theNewV2, theNewV;
    gp_Pnt        theOldP1, theOldP2;
    double        dist1, dist2, curdist1, curdist2;
    for (NCollection_DataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator theOEIter(myOriFreeEdges);
         theOEIter.More();
         theOEIter.Next())
    {

      for (theOriginalIter.Initialize(theOEIter.Value()); theOriginalIter.More();
           theOriginalIter.Next())
      {
        TopoDS_Edge theOldE = TopoDS::Edge(theOriginalIter.Value());

        theBuilder.MakeWire(theNewW);

        bool emptywire = true;
        for (int i = 1; i <= 2; i++)
        {

          if (i == 1)
            theResultsIter.Initialize(myResFreeEdges(theOldE));
          else
            theResultsIter.Initialize(myResSharEdges(theOldE));

          for (; theResultsIter.More(); theResultsIter.Next())
          {
            theAuxE = theResultsIter.Value();
            if (!theAuxE.IsSame(theOldE))
            {

              theBuilder.Add(theNewW, theAuxE);
              emptywire = false;
            }
          }
        }

        if (!emptywire)
        {

          TopExp::Vertices(theOldE, theOldV1, theOldV2);
          theOldP1 = BRep_Tool::Pnt(theOldV1);
          theOldP2 = BRep_Tool::Pnt(theOldV2);

          dist1 = -1.;
          dist2 = -1.;
          for (TopExp_Explorer expv(theNewW, TopAbs_VERTEX); expv.More(); expv.Next())
          {
            TopoDS_Vertex theNewVtx = TopoDS::Vertex(expv.Current());
            gp_Pnt        theNewPt  = BRep_Tool::Pnt(theNewVtx);
            curdist1                = theOldP1.Distance(theNewPt);
            curdist2                = theOldP2.Distance(theNewPt);
            if (dist1 < 0 || curdist1 < dist1)
            {
              dist1    = curdist1;
              theNewV1 = theNewVtx;
            }
            if (dist2 < 0 || curdist2 < dist2)
            {
              dist2    = curdist2;
              theNewV2 = theNewVtx;
            }
          }

          if (!theOldV1.IsSame(theNewV1))
          {
            if (theRepVertices.IsBound(theOldV1))
            {
              NCollection_List<TopoDS_Shape>&          theList1 = theRepVertices(theOldV1);
              NCollection_List<TopoDS_Shape>::Iterator theIter1;
              bool                                     found = false;
              for (theIter1.Initialize(theList1); theIter1.More(); theIter1.Next())
                if (theIter1.Value().IsSame(theNewV1))
                {
                  found = true;
                  break;
                }
              if (!found)
                theList1.Append(theNewV1);
            }
            else
            {
              NCollection_List<TopoDS_Shape> theNewList1;
              theNewList1.Append(theNewV1);
              theRepVertices.Bind(theOldV1, theNewList1);
            }
          }
          if (!theOldV2.IsSame(theNewV2))
          {
            if (theRepVertices.IsBound(theOldV2))
            {
              NCollection_List<TopoDS_Shape>&          theList2 = theRepVertices(theOldV2);
              NCollection_List<TopoDS_Shape>::Iterator theIter2;
              bool                                     found = false;
              for (theIter2.Initialize(theList2); theIter2.More(); theIter2.Next())
                if (theIter2.Value().IsSame(theNewV2))
                {
                  found = true;
                  break;
                }
              if (!found)
                theList2.Append(theNewV2);
            }
            else
            {
              NCollection_List<TopoDS_Shape> theNewList2;
              theNewList2.Append(theNewV2);
              theRepVertices.Bind(theOldV2, theNewList2);
            }
          }

          theRepEdges.Bind(theOldE, theNewW);
        }
      }
    }

    if (!theRepEdges.IsEmpty())
    {

      occ::handle<ShapeBuild_ReShape> theReShape = new ShapeBuild_ReShape;

      for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
             theREIter(theRepEdges);
           theREIter.More();
           theREIter.Next())
      {
        theReShape->Replace(theREIter.Key(), theREIter.Value());
      }

      TopoDS_Shape tmpReShape = theReShape->Apply(result);
      result                  = TopoDS::Shell(tmpReShape);
      if (theReShape->Status(ShapeExtend_OK))
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning: ShapeFix_FaceConnect::Build: Edges not replaced by ReShape"
                  << std::endl;
#endif
      }
      else if (theReShape->Status(ShapeExtend_FAIL1))
      {
#ifdef OCCT_DEBUG
        std::cout << "Error: ShapeFix_FaceConnect::Build: ReShape failed on edges" << std::endl;
#endif
      }
      else
      {

        occ::handle<ShapeFix_Wire>        SFW = new ShapeFix_Wire;
        occ::handle<ShapeFix_Face>        SFF = new ShapeFix_Face;
        ShapeAnalysis_Edge                SAE;
        double                            f, l;
        occ::handle<Geom2d_Curve>         c2d;
        occ::handle<ShapeExtend_WireData> sewd;

        TopoDS_Shape emptyCopiedShell = result.EmptyCopied();
        TopoDS_Shell theShell         = TopoDS::Shell(emptyCopiedShell);
        for (TopoDS_Iterator itf1(result); itf1.More(); itf1.Next())
        {
          TopoDS_Face newface = TopoDS::Face(itf1.Value());

          TopoDS_Shape emptyCopiedFace = newface.EmptyCopied();
          TopoDS_Face  EmpFace         = TopoDS::Face(emptyCopiedFace);
          for (TopoDS_Iterator itw(newface); itw.More(); itw.Next())
          {
            if (itw.Value().ShapeType() != TopAbs_WIRE)
              continue;
            TopoDS_Wire theWire = TopoDS::Wire(itw.Value());

            sewd = new ShapeExtend_WireData(theWire);
            ShapeAnalysis_WireOrder SAWO(false, 0);
            for (int i = 1; i <= sewd->NbEdges(); i++)
            {

              TopoDS_Shape tmpFace = EmpFace.Oriented(TopAbs_FORWARD);
              if (!SAE.PCurve(sewd->Edge(i), TopoDS::Face(tmpFace), c2d, f, l))
                continue;
              SAWO.Add(c2d->Value(f).XY(), c2d->Value(l).XY());
            }
            SAWO.Perform();

            SFW->Load(sewd);
            SFW->FixReorder(SAWO);
            SFW->FixReorder();

            SFW->SetFace(EmpFace);
            SFW->SetPrecision(fixtoler);
            SFW->SetMaxTolerance(sewtoler);

            SFW->FixEdgeCurves();
            SFW->FixSelfIntersection();
            theWire = SFW->Wire();
            theBuilder.Add(EmpFace, theWire);
          }

          SFF->Init(EmpFace);

          NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
            MapWires;
          MapWires.Clear();
          if (SFF->FixOrientation(MapWires))
            EmpFace = SFF->Face();
          theBuilder.Add(theShell, EmpFace);
        }
        theShell.Closed(BRep_Tool::IsClosed(theShell));
        result = theShell;

        if (!theRepVertices.IsEmpty())
        {

          TopoDS_Shape theOld, theNew, theRep, theAux;
          for (NCollection_DataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>::Iterator theRV1Iter(theRepVertices);
               theRV1Iter.More();
               theRV1Iter.Next())
          {

            theOld = theRV1Iter.Key();
            NCollection_List<TopoDS_Shape> theNewList;

            NCollection_List<TopoDS_Shape>::Iterator theN1Iter;
            for (theN1Iter.Initialize(theRV1Iter.Value()); theN1Iter.More(); theN1Iter.Next())
            {
              theNew = theN1Iter.Value();
              if (theOldVertices.IsBound(theNew))
              {

                theRep = theOldVertices(theNew);
                if (!theRep.IsSame(theOld))
                {

                  theOldVertices.Bind(theRep, theOld);
                  theNewList.Append(theRep);
                  NCollection_List<TopoDS_Shape>::Iterator theN3Iter;
                  for (theN3Iter.Initialize(theNewVertices(theRep)); theN3Iter.More();
                       theN3Iter.Next())
                  {
                    theAux                 = theN3Iter.Value();
                    theOldVertices(theAux) = theOld;
                    theNewList.Append(theAux);
                  }
                  theNewVertices.UnBind(theRep);
                }
              }
              else
              {
                theOldVertices.Bind(theNew, theOld);
                theNewList.Append(theNew);
              }
            }
            theNewVertices.Bind(theOld, theNewList);
          }

          TopoDS_Vertex theNewVert, theOldVert;
          for (NCollection_DataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>::Iterator theRV2Iter(theNewVertices);
               theRV2Iter.More();
               theRV2Iter.Next())
          {
            theNewVert = TopoDS::Vertex(theRV2Iter.Key());

            gp_Pnt theLBound, theRBound, thePosition;
            theLBound = theRBound = BRep_Tool::Pnt(theNewVert);
            NCollection_List<TopoDS_Shape>::Iterator theN2Iter;
            for (theN2Iter.Initialize(theRV2Iter.Value()); theN2Iter.More(); theN2Iter.Next())
            {
              thePosition = BRep_Tool::Pnt(TopoDS::Vertex(theN2Iter.Value()));
              double val  = thePosition.X();
              if (val < theLBound.X())
                theLBound.SetX(val);
              else if (val > theRBound.X())
                theRBound.SetX(val);
              val = thePosition.Y();
              if (val < theLBound.Y())
                theLBound.SetY(val);
              else if (val > theRBound.Y())
                theRBound.SetY(val);
              val = thePosition.Z();
              if (val < theLBound.Z())
                theLBound.SetZ(val);
              else if (val > theRBound.Z())
                theRBound.SetZ(val);
            }
            thePosition         = gp_Pnt((theLBound.XYZ() + theRBound.XYZ()) / 2.);
            double theTolerance = 0., curtoler;

            for (theN2Iter.Initialize(theRV2Iter.Value()); theN2Iter.More(); theN2Iter.Next())
            {
              theOldVert = TopoDS::Vertex(theN2Iter.Value());
              curtoler =
                thePosition.Distance(BRep_Tool::Pnt(theOldVert)) + BRep_Tool::Tolerance(theOldVert);
              if (curtoler > theTolerance)
                theTolerance = curtoler;
            }
            curtoler =
              thePosition.Distance(BRep_Tool::Pnt(theNewVert)) + BRep_Tool::Tolerance(theNewVert);
            if (curtoler > theTolerance)
              theTolerance = curtoler;
            theBuilder.UpdateVertex(theNewVert, thePosition, theTolerance);
          }

          theReShape->Clear();
          for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
                 theNVIter(theOldVertices);
               theNVIter.More();
               theNVIter.Next())
            theReShape->Replace(theNVIter.Key().Oriented(TopAbs_FORWARD),
                                theNVIter.Value().Oriented(TopAbs_FORWARD));

          TopoDS_Shape tmpshape = theReShape->Apply(result);
          result                = TopoDS::Shell(tmpshape);

          if (theReShape->Status(ShapeExtend_FAIL1))
          {
#ifdef OCCT_DEBUG
            std::cout << "Error: ShapeFix_FaceConnect::Build: ReShape failed on vertices"
                      << std::endl;
#endif
          }
        }

#ifdef OCCT_DEBUG

        std::cout << std::endl << "FACE CONNECT REPLACEMENT RESULTS:" << std::endl;
        std::cout << "---------------------------------" << std::endl;
        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> theTmpMap;
        int                                                    toteold = 0, totenew = 0;
        for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
               theR1Iter(theRepEdges);
             theR1Iter.More();
             theR1Iter.Next())
        {
          toteold++;
          if (!theTmpMap.Contains(theR1Iter.Value()))
          {
            theTmpMap.Add(theR1Iter.Value());
            for (TopoDS_Iterator itw(TopoDS::Wire(theR1Iter.Value())); itw.More(); itw.Next())
              totenew++;
          }
        }
        int totvold = 0, totvnew = 0;
        for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
               theR2Iter(theOldVertices);
             theR2Iter.More();
             theR2Iter.Next())
        {
          totvold++;
          if (!theTmpMap.Contains(theR2Iter.Value()))
          {
            theTmpMap.Add(theR2Iter.Value());
            totvnew++;
          }
        }
        std::cout << "TOTAL: " << toteold << " edges, " << totvold << " vertices replaced by "
                  << totenew << " edges, " << totvnew << " vertices" << std::endl
                  << std::endl;

#endif
      }
    }
  }

  return result;
}

void ShapeFix_FaceConnect::Clear()
{
  myConnected.Clear();
  myOriFreeEdges.Clear();
  myResFreeEdges.Clear();
  myResSharEdges.Clear();
}
