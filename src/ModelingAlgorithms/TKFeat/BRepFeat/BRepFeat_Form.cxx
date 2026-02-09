#include <BRep_Builder.hpp>
#include <BRepAlgo.hpp>
#include <BRepAlgoAPI_Cut.hpp>
#include <BRepCheck_Analyzer.hpp>
#include <BRepFeat.hpp>
#include <BRepFeat_Builder.hpp>
#include <BRepFeat_Form.hpp>
#include <BRepLib.hpp>
#include <BRepTools_Modifier.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <ElCLib.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <LocOpe_CSIntersector.hpp>
#include <LocOpe_FindEdges.hpp>
#include <LocOpe_Gluer.hpp>
#include <LocOpe_PntFace.hpp>
#include <Precision.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Solid.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

#ifdef OCCT_DEBUG
extern bool BRepFeat_GettraceFEAT();
#endif

static void Descendants(const TopoDS_Shape&,
                        BRepFeat_Builder&,
                        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&);

void BRepFeat_Form::GlobalPerform()
{

#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
  if (trc)
    std::cout << "BRepFeat_Form::GlobalPerform ()" << std::endl;
#endif

  if (!mySbOK || !myGSOK || !mySFOK || !mySUOK || !myGFOK || !mySkOK || !myPSOK)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Fields not initialized in BRepFeat_Form" << std::endl;
#endif
    myStatusError = BRepFeat_NotInitialized;
    NotDone();
    return;
  }

  TopExp_Explorer                                                                    exp, exp2;
  int                                                                                theOpe = 2;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itm;

  if (myJustFeat && !myFuse)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Invalid option : myJustFeat + Cut" << std::endl;
#endif
    myStatusError = BRepFeat_InvOption;
    NotDone();
    return;
  }
  else if (myJustFeat)
  {
    theOpe = 2;
  }
  else if (!myGluedF.IsEmpty())
  {
    theOpe = 1;
  }
  else
  {
  }
  bool ChangeOpe = false;

  bool FromInShape  = false;
  bool UntilInShape = false;

  if (!mySFrom.IsNull())
  {
    FromInShape = true;
    for (exp2.Init(mySFrom, TopAbs_FACE); exp2.More(); exp2.Next())
    {
      const TopoDS_Shape& ffrom = exp2.Current();
      for (exp.Init(mySbase, TopAbs_FACE); exp.More(); exp.Next())
      {
        if (exp.Current().IsSame(ffrom))
        {
          break;
        }
      }
      if (!exp.More())
      {
        FromInShape = false;
#ifdef OCCT_DEBUG
        if (trc)
          std::cout << " From not in Shape" << std::endl;
#endif
        break;
      }
    }
  }

  if (!mySUntil.IsNull())
  {
    UntilInShape = true;
    for (exp2.Init(mySUntil, TopAbs_FACE); exp2.More(); exp2.Next())
    {
      const TopoDS_Shape& funtil = exp2.Current();
      for (exp.Init(mySbase, TopAbs_FACE); exp.More(); exp.Next())
      {
        if (exp.Current().IsSame(funtil))
        {
          break;
        }
      }
      if (!exp.More())
      {
        UntilInShape = false;
#ifdef OCCT_DEBUG
        if (trc)
          std::cout << " Until not in Shape" << std::endl;
#endif
        break;
      }
    }
  }

  NCollection_List<TopoDS_Shape>::Iterator it, it2;
  int                                      sens = 0;

  NCollection_Sequence<occ::handle<Geom_Curve>> scur;
  Curves(scur);

  double mf, Mf, mu, Mu;

  TopAbs_Orientation Orifuntil = TopAbs_INTERNAL;
  TopAbs_Orientation Oriffrom  = TopAbs_INTERNAL;
  TopoDS_Face        FFrom, FUntil;

  LocOpe_CSIntersector ASI1;
  LocOpe_CSIntersector ASI2;

  NCollection_List<TopoDS_Shape> IntList;
  IntList.Clear();

  if (!mySFrom.IsNull())
  {
    ASI1.Init(mySFrom);
    ASI1.Perform(scur);
  }

  if (!mySUntil.IsNull())
  {
    ASI2.Init(mySUntil);
    ASI2.Perform(scur);
  }

  {

    for (int jj = 1; jj <= scur.Length(); jj++)
    {
      if (ASI1.IsDone() && ASI2.IsDone())
      {
        if (ASI1.NbPoints(jj) <= 0)
        {
          continue;
        }
        mf = ASI1.Point(jj, 1).Parameter();
        Mf = ASI1.Point(jj, ASI1.NbPoints(jj)).Parameter();
        if (ASI2.NbPoints(jj) <= 0)
        {
          continue;
        }
        mu = ASI2.Point(jj, 1).Parameter();
        Mu = ASI2.Point(jj, ASI2.NbPoints(jj)).Parameter();
        if (!scur(jj)->IsPeriodic())
        {
          int ku, kf;
          if (mu <= Mf && mf <= Mu)
          {
            sens = 1;
            kf   = 1;
            ku   = ASI2.NbPoints(jj);
          }
          else if (mu > Mf)
          {
            if (sens == -1)
            {
              myStatusError = BRepFeat_IntervalOverlap;
              NotDone();
              return;
            }
            sens = 1;
            kf   = 1;
            ku   = ASI2.NbPoints(jj);
          }
          else
          {
            if (sens == 1)
            {
              myStatusError = BRepFeat_IntervalOverlap;
              NotDone();
              return;
            }
            sens = -1;
            kf   = ASI1.NbPoints(jj);
            ku   = 1;
          }
          if (Oriffrom == TopAbs_INTERNAL)
          {
            TopAbs_Orientation Oript = ASI1.Point(jj, kf).Orientation();
            if (Oript == TopAbs_FORWARD || Oript == TopAbs_REVERSED)
            {
              if (sens == -1)
              {
                Oript = TopAbs::Reverse(Oript);
              }
              Oriffrom = TopAbs::Reverse(Oript);
              FFrom    = ASI1.Point(jj, kf).Face();
            }
          }
          if (Orifuntil == TopAbs_INTERNAL)
          {
            TopAbs_Orientation Oript = ASI2.Point(jj, ku).Orientation();
            if (Oript == TopAbs_FORWARD || Oript == TopAbs_REVERSED)
            {
              if (sens == -1)
              {
                Oript = TopAbs::Reverse(Oript);
              }
              Orifuntil = Oript;
              FUntil    = ASI2.Point(jj, ku).Face();
            }
          }
        }
      }
      else if (ASI2.IsDone())
      {
        if (ASI2.NbPoints(jj) <= 0)
          continue;

        if (sens != 1)
        {
          if (ASI2.Point(jj, 1).Parameter() * ASI2.Point(jj, ASI2.NbPoints(jj)).Parameter() <= 0)
            sens = 1;
          else if (ASI2.Point(jj, 1).Parameter() < 0.)
            sens = -1;
          else
            sens = 1;
        }

        int ku;
        if (sens == -1)
        {
          ku = 1;
        }
        else
        {
          ku = ASI2.NbPoints(jj);
        }
        if (Orifuntil == TopAbs_INTERNAL && sens != 0)
        {
          TopAbs_Orientation Oript = ASI2.Point(jj, ku).Orientation();
          if (Oript == TopAbs_FORWARD || Oript == TopAbs_REVERSED)
          {
            if (sens == -1)
            {
              Oript = TopAbs::Reverse(Oript);
            }
            Orifuntil = Oript;
            FUntil    = ASI2.Point(jj, ku).Face();
          }
        }
      }
      else
      {
        sens = 1;
        break;
      }
    }
  }

  LocOpe_Gluer theGlue;

  if (theOpe == 1)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Gluer" << std::endl;
#endif
    bool Collage = true;

    TopoDS_Shape Comp;
    BRep_Builder B;
    B.MakeCompound(TopoDS::Compound(Comp));
    if (!mySFrom.IsNull())
    {
      TopoDS_Solid S = BRepFeat::Tool(mySFrom, FFrom, Oriffrom);
      if (!S.IsNull())
      {
        B.Add(Comp, S);
      }
    }
    if (!mySUntil.IsNull())
    {
      TopoDS_Solid S = BRepFeat::Tool(mySUntil, FUntil, Orifuntil);
      if (!S.IsNull())
      {
        B.Add(Comp, S);
      }
    }

    LocOpe_FindEdges theFE;
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                    locmap;
    TopExp_Explorer expp(Comp, TopAbs_SOLID);
    if (expp.More() && !Comp.IsNull() && !myGShape.IsNull())
    {
      BRepAlgoAPI_Cut trP(myGShape, Comp);
      exp.Init(trP.Shape(), TopAbs_SOLID);
      if (exp.Current().IsNull())
      {
        theOpe    = 2;
        ChangeOpe = true;
        Collage   = false;
      }
      else
      {

        TopoDS_Shape theGShape;
        B.MakeCompound(TopoDS::Compound(theGShape));
        for (; exp.More(); exp.Next())
        {
          B.Add(theGShape, exp.Current());
        }
        if (!BRepAlgo::IsValid(theGShape))
        {
          theOpe    = 2;
          ChangeOpe = true;
          Collage   = false;
        }
        else
        {
          if (!mySFrom.IsNull())
          {
            TopExp_Explorer ex;
            ex.Init(mySFrom, TopAbs_FACE);
            for (; ex.More(); ex.Next())
            {
              const TopoDS_Face& fac = TopoDS::Face(ex.Current());
              if (!FromInShape)
              {
                NCollection_List<TopoDS_Shape> thelist;
                myMap.Bind(fac, thelist);
              }
              else
              {
                NCollection_List<TopoDS_Shape> thelist1;
                locmap.Bind(fac, thelist1);
              }
              if (trP.IsDeleted(fac))
              {
              }
              else if (!FromInShape)
              {
                myMap(fac) = trP.Modified(fac);
                if (myMap(fac).IsEmpty())
                  myMap(fac).Append(fac);
              }
              else
              {
                locmap(fac) = trP.Modified(fac);
                if (locmap(fac).IsEmpty())
                  locmap(fac).Append(fac);
              }
            }
          }

          if (!mySUntil.IsNull())
          {
            TopExp_Explorer ex;
            ex.Init(mySUntil, TopAbs_FACE);
            for (; ex.More(); ex.Next())
            {
              const TopoDS_Face& fac = TopoDS::Face(ex.Current());
              if (!UntilInShape)
              {
                NCollection_List<TopoDS_Shape> thelist2;
                myMap.Bind(fac, thelist2);
              }
              else
              {
                NCollection_List<TopoDS_Shape> thelist3;
                locmap.Bind(fac, thelist3);
              }
              if (trP.IsDeleted(fac))
              {
              }
              else if (!UntilInShape)
              {
                myMap(fac) = trP.Modified(fac);
                if (myMap(fac).IsEmpty())
                  myMap(fac).Append(fac);
              }
              else
              {
                locmap(fac) = trP.Modified(fac);
                if (locmap(fac).IsEmpty())
                  locmap(fac).Append(fac);
              }
            }
          }

          UpdateDescendants(trP, theGShape, true);

          theGlue.Init(mySbase, theGShape);
          for (itm.Initialize(myGluedF); itm.More(); itm.Next())
          {
            const TopoDS_Face&             gl = TopoDS::Face(itm.Key());
            NCollection_List<TopoDS_Shape> ldsc;
            if (trP.IsDeleted(gl))
            {
            }
            else
            {
              ldsc = trP.Modified(gl);
              if (ldsc.IsEmpty())
                ldsc.Append(gl);
            }
            const TopoDS_Face& glface = TopoDS::Face(itm.Value());
            for (it.Initialize(ldsc); it.More(); it.Next())
            {
              const TopoDS_Face& fac = TopoDS::Face(it.Value());
              Collage                = BRepFeat::IsInside(fac, glface);
              if (!Collage)
              {
                theOpe    = 2;
                ChangeOpe = true;
                break;
              }
              else
              {
                theGlue.Bind(fac, glface);
                theFE.Set(fac, glface);
                for (theFE.InitIterator(); theFE.More(); theFE.Next())
                {
                  theGlue.Bind(theFE.EdgeFrom(), theFE.EdgeTo());
                }
              }
            }
          }
        }
      }
    }
    else
    {
      theGlue.Init(mySbase, myGShape);
      for (itm.Initialize(myGluedF); itm.More(); itm.Next())
      {
        const TopoDS_Face& glface = TopoDS::Face(itm.Key());
        const TopoDS_Face& fac    = TopoDS::Face(myGluedF(glface));
        for (exp.Init(myGShape, TopAbs_FACE); exp.More(); exp.Next())
        {
          if (exp.Current().IsSame(glface))
          {
            break;
          }
        }
        if (exp.More())
        {
          Collage = BRepFeat::IsInside(glface, fac);
          if (!Collage)
          {
            theOpe    = 2;
            ChangeOpe = true;
            break;
          }
          else
          {
            theGlue.Bind(glface, fac);
            theFE.Set(glface, fac);
            for (theFE.InitIterator(); theFE.More(); theFE.Next())
            {
              theGlue.Bind(theFE.EdgeFrom(), theFE.EdgeTo());
            }
          }
        }
      }
    }

    if (FromInShape && Collage)
    {
      TopExp_Explorer ex(mySFrom, TopAbs_FACE);
      for (; ex.More(); ex.Next())
      {
        const TopoDS_Face& fac2 = TopoDS::Face(ex.Current());

        for (it.Initialize(locmap(fac2)); it.More(); it.Next())
        {
          const TopoDS_Face& fac1 = TopoDS::Face(it.Value());
          theFE.Set(fac1, fac2);
          theGlue.Bind(fac1, fac2);
          for (theFE.InitIterator(); theFE.More(); theFE.Next())
          {
            theGlue.Bind(theFE.EdgeFrom(), theFE.EdgeTo());
          }
        }
      }
    }

    if (UntilInShape && Collage)
    {
      TopExp_Explorer ex(mySUntil, TopAbs_FACE);
      for (; ex.More(); ex.Next())
      {
        const TopoDS_Face& fac2 = TopoDS::Face(ex.Current());

        for (it.Initialize(locmap(fac2)); it.More(); it.Next())
        {
          const TopoDS_Face& fac1 = TopoDS::Face(it.Value());
          theGlue.Bind(fac1, fac2);
          theFE.Set(fac1, fac2);
          for (theFE.InitIterator(); theFE.More(); theFE.Next())
          {
            theGlue.Bind(theFE.EdgeFrom(), theFE.EdgeTo());
          }
        }
      }
    }

    LocOpe_Operation ope = theGlue.OpeType();
    if (ope == LocOpe_INVALID || (myFuse && ope != LocOpe_FUSE) || (!myFuse && ope != LocOpe_CUT)
        || (!Collage))
    {
      theOpe    = 2;
      ChangeOpe = true;
    }
  }

  if (theOpe == 1)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " still Gluer" << std::endl;
#endif
    theGlue.Perform();
    if (theGlue.IsDone())
    {
      const TopoDS_Shape& shshs = theGlue.ResultingShape();

      if (BRepAlgo::IsValid(shshs))
      {
        UpdateDescendants(theGlue);
        myNewEdges = theGlue.Edges();
        myTgtEdges = theGlue.TgtEdges();
#ifdef OCCT_DEBUG
        if (trc)
          std::cout << " Gluer result" << std::endl;
#endif
        Done();
        myShape = theGlue.ResultingShape();
      }
      else
      {
        theOpe    = 2;
        ChangeOpe = true;
      }
    }
    else
    {
      theOpe    = 2;
      ChangeOpe = true;
    }
  }

  if (theOpe == 2 && ChangeOpe && myJustGluer)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Gluer failure" << std::endl;
#endif
    myJustGluer = false;
    theOpe      = 0;
  }

  if (theOpe == 2)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " No Gluer" << std::endl;
#endif
    TopoDS_Shape theGShape = myGShape;
    if (ChangeOpe)
    {
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << " Passage to topological operations" << std::endl;
#endif
    }

    TopoDS_Shape Comp;
    BRep_Builder B;
    B.MakeCompound(TopoDS::Compound(Comp));
    if (!mySFrom.IsNull() || !mySUntil.IsNull())
    {
      if (!mySFrom.IsNull() && !FromInShape)
      {
        TopoDS_Solid S = BRepFeat::Tool(mySFrom, FFrom, Oriffrom);
        if (!S.IsNull())
        {
          B.Add(Comp, S);
        }
      }
      if (!mySUntil.IsNull() && !UntilInShape)
      {
        if (!mySFrom.IsNull())
        {
          if (!mySFrom.IsSame(mySUntil))
          {
            TopoDS_Solid S = BRepFeat::Tool(mySUntil, FUntil, Orifuntil);
            if (!S.IsNull())
            {
              B.Add(Comp, S);
            }
          }
        }
        else
        {
          TopoDS_Solid S = BRepFeat::Tool(mySUntil, FUntil, Orifuntil);
          if (!S.IsNull())
          {
            B.Add(Comp, S);
          }
        }
      }
    }

    if (myPerfSelection == BRepFeat_SelectionU && !UntilInShape)
    {
      myPerfSelection = BRepFeat_NoSelection;
    }
    else if (myPerfSelection == BRepFeat_SelectionFU && !FromInShape && !UntilInShape)
    {
      myPerfSelection = BRepFeat_NoSelection;
    }
    else if (myPerfSelection == BRepFeat_SelectionShU && !UntilInShape)
    {
      myPerfSelection = BRepFeat_NoSelection;
    }
    else
    {
    }

    TopExp_Explorer expp(Comp, TopAbs_SOLID);
    if (expp.More() && !Comp.IsNull() && !myGShape.IsNull())
    {
      BRepAlgoAPI_Cut trP(myGShape, Comp);

      exp.Init(trP.Shape(), TopAbs_SOLID);
      if (!exp.More())
      {
        myStatusError = BRepFeat_EmptyCutResult;
        NotDone();
        return;
      }

      theGShape.Nullify();
      B.MakeCompound(TopoDS::Compound(theGShape));
      for (; exp.More(); exp.Next())
      {
        B.Add(theGShape, exp.Current());
      }
      if (!BRepAlgo::IsValid(theGShape))
      {
        myStatusError = BRepFeat_InvShape;
        NotDone();
        return;
      }
      if (!mySFrom.IsNull())
      {
        if (!FromInShape)
        {
          TopExp_Explorer ex(mySFrom, TopAbs_FACE);
          for (; ex.More(); ex.Next())
          {
            const TopoDS_Face&             fac = TopoDS::Face(ex.Current());
            NCollection_List<TopoDS_Shape> thelist4;
            myMap.Bind(fac, thelist4);
            if (trP.IsDeleted(fac))
            {
            }
            else
            {
              myMap(fac) = trP.Modified(fac);
              if (myMap(fac).IsEmpty())
                myMap(fac).Append(fac);
            }
          }
        }
      }
      if (!mySUntil.IsNull())
      {
        if (!UntilInShape)
        {
          TopExp_Explorer ex(mySUntil, TopAbs_FACE);
          for (; ex.More(); ex.Next())
          {
            const TopoDS_Face&             fac = TopoDS::Face(ex.Current());
            NCollection_List<TopoDS_Shape> thelist5;
            myMap.Bind(fac, thelist5);
            if (trP.IsDeleted(fac))
            {
            }
            else
            {
              myMap(fac) = trP.Modified(fac);
              if (myMap.IsEmpty())
                myMap(fac).Append(fac);
            }
          }
        }
      }
      UpdateDescendants(trP, theGShape, true);
    }

    bool             bFlag = myPerfSelection != BRepFeat_NoSelection;
    BRepFeat_Builder theBuilder;
    theBuilder.Init(mySbase, theGShape);
    theBuilder.SetOperation(myFuse, bFlag);
    theBuilder.Perform();

    NCollection_List<TopoDS_Shape> lshape;
    theBuilder.PartsOfTool(lshape);

    double                  pbmin = RealLast(), pbmax = RealFirst();
    double                  prmin = RealLast() - 2 * Precision::Confusion();
    double                  prmax = RealFirst() + 2 * Precision::Confusion();
    bool                    flag1 = false;
    occ::handle<Geom_Curve> C;

    if (!lshape.IsEmpty() && myPerfSelection != BRepFeat_NoSelection)
    {

      C = BarycCurve();
      if (C.IsNull())
      {
        myStatusError = BRepFeat_EmptyBaryCurve;
        NotDone();
        return;
      }

      if (myPerfSelection == BRepFeat_SelectionSh)
      {
        BRepFeat::ParametricMinMax(mySbase, C, prmin, prmax, pbmin, pbmax, flag1);
      }
      else if (myPerfSelection == BRepFeat_SelectionFU)
      {
        double prmin1, prmax1, prmin2, prmax2;
        double prbmin1, prbmax1, prbmin2, prbmax2;

        BRepFeat::ParametricMinMax(mySFrom, C, prmin1, prmax1, prbmin1, prbmax1, flag1);
        BRepFeat::ParametricMinMax(mySUntil, C, prmin2, prmax2, prbmin2, prbmax2, flag1);

        if (C->IsPeriodic())
        {
          double period = C->Period();
          prmax         = prmax2;
          if (flag1)
          {
            prmin = ElCLib::InPeriod(prmin1, prmax - period, prmax);
          }
          else
          {
            prmin = std::min(prmin1, prmin2);
          }
          pbmax = prbmax2;
          pbmin = ElCLib::InPeriod(prbmin1, pbmax - period, pbmax);
        }
        else
        {
          prmin = std::min(prmin1, prmin2);
          prmax = std::max(prmax1, prmax2);
          pbmin = std::min(prbmin1, prbmin2);
          pbmax = std::max(prbmax1, prbmax2);
        }
      }
      else if (myPerfSelection == BRepFeat_SelectionShU)
      {
        double prmin1, prmax1, prmin2, prmax2;
        double prbmin1, prbmax1, prbmin2, prbmax2;

        if (!myJustFeat && sens == 0)
          sens = 1;
        if (sens == 0)
        {
          myStatusError = BRepFeat_IncDirection;
          NotDone();
          return;
        }

        BRepFeat::ParametricMinMax(mySUntil, C, prmin1, prmax1, prbmin1, prbmax1, flag1);

        BRepFeat::ParametricMinMax(mySbase, C, prmin2, prmax2, prbmin2, prbmax2, flag1);
        if (sens == 1)
        {
          prmin = prmin2;
          prmax = prmax1;
          pbmin = prbmin2;
          pbmax = prbmax1;
        }
        else if (sens == -1)
        {
          prmin = prmin1;
          prmax = prmax2;
          pbmin = prbmin1;
          pbmax = prbmax2;
        }
      }
      else if (myPerfSelection == BRepFeat_SelectionU)
      {
        double prmin1, prmax1, prbmin1, prbmax1;
        if (sens == 0)
        {
          myStatusError = BRepFeat_IncDirection;
          NotDone();
          return;
        }

        BRepFeat::ParametricMinMax(mySUntil, C, prmin1, prmax1, prbmin1, prbmax1, flag1);
        if (sens == 1)
        {
          prmin = RealFirst();
          prmax = prmax1;
          pbmin = RealFirst();
          pbmax = prbmax1;
        }
        else if (sens == -1)
        {
          prmin = prmin1;
          prmax = RealLast();
          pbmin = prbmin1;
          pbmax = RealLast();
        }
      }

      constexpr double delta = Precision::Confusion();

      if (myPerfSelection != BRepFeat_NoSelection)
      {

        if (!mySUntil.IsNull())
        {
          NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapFuntil;
          Descendants(mySUntil, theBuilder, mapFuntil);
          if (!mapFuntil.IsEmpty())
          {
            for (it.Initialize(lshape); it.More(); it.Next())
            {
              TopExp_Explorer expf;
              for (expf.Init(it.Value(), TopAbs_FACE); expf.More(); expf.Next())
              {
                if (mapFuntil.Contains(expf.Current()))
                {
                  bool   flag2, flag3;
                  double prmin1, prmax1, prbmin1, prbmax1;
                  double prmin2, prmax2, prbmin2, prbmax2;
                  BRepFeat::ParametricMinMax(expf.Current(),
                                             C,
                                             prmin1,
                                             prmax1,
                                             prbmin1,
                                             prbmax1,
                                             flag3);
                  BRepFeat::ParametricMinMax(it.Value(),
                                             C,
                                             prmin2,
                                             prmax2,
                                             prbmin2,
                                             prbmax2,
                                             flag2);
                  if (sens == 1)
                  {
                    bool testOK = !flag2;
                    if (flag2)
                    {
                      testOK = !flag1;
                      if (flag1 && prmax2 > prmin + delta)
                      {
                        testOK = !flag3;
                        if (flag3 && prmax1 == prmax2)
                        {
                          testOK = true;
                        }
                      }
                    }
                    if (prbmin1 < pbmax && testOK)
                    {
                      if (flag2)
                      {
                        flag1 = flag2;
                        prmax = prmax2;
                      }
                      pbmax = prbmin1;
                    }
                  }
                  else if (sens == -1)
                  {
                    bool testOK = !flag2;
                    if (flag2)
                    {
                      testOK = !flag1;
                      if (flag1 && prmin2 < prmax - delta)
                      {
                        testOK = !flag3;
                        if (flag3 && prmin1 == prmin2)
                        {
                          testOK = true;
                        }
                      }
                    }
                    if (prbmax1 > pbmin && testOK)
                    {
                      if (flag2)
                      {
                        flag1 = flag2;
                        prmin = prmin2;
                      }
                      pbmin = prbmax1;
                    }
                  }
                  break;
                }
              }
            }
            it.Initialize(lshape);
          }
        }
        if (!mySFrom.IsNull())
        {
          NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapFfrom;
          Descendants(mySFrom, theBuilder, mapFfrom);
          if (!mapFfrom.IsEmpty())
          {
            for (it.Initialize(lshape); it.More(); it.Next())
            {
              TopExp_Explorer expf;
              for (expf.Init(it.Value(), TopAbs_FACE); expf.More(); expf.Next())
              {
                if (mapFfrom.Contains(expf.Current()))
                {
                  bool   flag2, flag3;
                  double prmin1, prmax1, prbmin1, prbmax1;
                  double prmin2, prmax2, prbmin2, prbmax2;
                  BRepFeat::ParametricMinMax(expf.Current(),
                                             C,
                                             prmin1,
                                             prmax1,
                                             prbmin1,
                                             prbmax1,
                                             flag3);
                  BRepFeat::ParametricMinMax(it.Value(),
                                             C,
                                             prmin2,
                                             prmax2,
                                             prbmin2,
                                             prbmax2,
                                             flag2);
                  if (sens == 1)
                  {
                    bool testOK = !flag2;
                    if (flag2)
                    {
                      testOK = !flag1;
                      if (flag1 && prmin2 < prmax - delta)
                      {
                        testOK = !flag3;
                        if (flag3 && prmin1 == prmin2)
                        {
                          testOK = true;
                        }
                      }
                    }
                    if (prbmax1 > pbmin && testOK)
                    {
                      if (flag2)
                      {
                        flag1 = flag2;
                        prmin = prmin2;
                      }
                      pbmin = prbmax1;
                    }
                  }
                  else if (sens == -1)
                  {
                    bool testOK = !flag2;
                    if (flag2)
                    {
                      testOK = !flag1;
                      if (flag1 && prmax2 > prmin + delta)
                      {
                        testOK = !flag3;
                        if (flag3 && prmax1 == prmax2)
                        {
                          testOK = true;
                        }
                      }
                    }
                    if (prbmin1 < pbmax && testOK)
                    {
                      if (flag2)
                      {
                        flag1 = flag2;
                        prmax = prmax2;
                      }
                      pbmax = prbmin1;
                    }
                  }
                  break;
                }
              }
            }
            it.Initialize(lshape);
          }
        }
      }

      if (!myJustFeat)
      {
        bool   KeepParts = false;
        double prmin1, prmax1, prbmin1, prbmax1;
        double min, max, pmin, pmax;
        bool   flag2;
        for (it.Initialize(lshape); it.More(); it.Next())
        {
          if (C->IsPeriodic())
          {
            double period = C->Period();
            double pr, prb;
            BRepFeat::ParametricMinMax(it.Value(), C, pr, prmax1, prb, prbmax1, flag2, true);
            if (flag2)
            {
              prmin1 = ElCLib::InPeriod(pr, prmax1 - period, prmax1);
            }
            else
            {
              prmin1 = pr;
            }
            prbmin1 = ElCLib::InPeriod(prb, prbmax1 - period, prbmax1);
          }
          else
          {
            BRepFeat::ParametricMinMax(it.Value(), C, prmin1, prmax1, prbmin1, prbmax1, flag2);
          }
          if (!flag2 || !flag1)
          {
            pmin = pbmin;
            pmax = pbmax;
            min  = prbmin1;
            max  = prbmax1;
          }
          else
          {
            pmin = prmin;
            pmax = prmax;
            min  = prmin1;
            max  = prmax1;
          }
          if ((min <= pmax - delta) && (max >= pmin + delta))
          {
            KeepParts             = true;
            const TopoDS_Shape& S = it.Value();
            theBuilder.KeepPart(S);
          }
        }

        if (!KeepParts)
        {
#ifdef OCCT_DEBUG
          if (trc)
            std::cout << " No parts of tool kept" << std::endl;
#endif
          myStatusError = BRepFeat_NoParts;
          NotDone();
          return;
        }
      }
      else
      {

        double       prmin1, prmax1, prbmin1, prbmax1;
        double       min, max, pmin, pmax;
        bool         flag2;
        TopoDS_Shape Compo;
        B.MakeCompound(TopoDS::Compound(Compo));
        for (it.Initialize(lshape); it.More(); it.Next())
        {
          BRepFeat::ParametricMinMax(it.Value(), C, prmin1, prmax1, prbmin1, prbmax1, flag2);
          if (!flag2 || !flag1)
          {
            pmin = pbmin;
            pmax = pbmax;
            min  = prbmin1;
            max  = prbmax1;
          }
          else
          {
            pmin = prmin;
            pmax = prmax;
            min  = prmin1;
            max  = prmax1;
          }
          if ((min < pmax - delta) && (max > pmin + delta))
          {
            if (!it.Value().IsNull())
            {
              B.Add(Compo, it.Value());
            }
          }
        }
        myShape = Compo;
      }
    }

    if (!myJustFeat)
    {

      if (bFlag)
      {
        theBuilder.PerformResult();
        myShape = theBuilder.Shape();
      }
      else
      {
        myShape = theBuilder.Shape();
      }
      Done();
    }
    else
    {

      Done();
    }
  }

  myStatusError = BRepFeat_OK;
}

bool BRepFeat_Form::IsDeleted(const TopoDS_Shape& F)
{
  if (myMap.IsBound(F))
  {
    return (myMap(F).IsEmpty());
  }
  return false;
}

const NCollection_List<TopoDS_Shape>& BRepFeat_Form::Modified(const TopoDS_Shape& F)
{
  myGenerated.Clear();
  if (!IsDone())
    return myGenerated;

  if (mySbase.IsEqual(F))
  {
    myGenerated.Append(myShape);
    return myGenerated;
  }

  if (myMap.IsBound(F))
  {
    NCollection_List<TopoDS_Shape>::Iterator ite(myMap(F));
    for (; ite.More(); ite.Next())
    {
      const TopoDS_Shape& sh = ite.Value();
      if (!sh.IsSame(F) && sh.ShapeType() == F.ShapeType())
        myGenerated.Append(sh);
    }
  }
  return myGenerated;
}

const NCollection_List<TopoDS_Shape>& BRepFeat_Form::Generated(const TopoDS_Shape& S)
{
  myGenerated.Clear();
  if (!IsDone())
    return myGenerated;
  if (myMap.IsBound(S) && S.ShapeType() != TopAbs_FACE)
  {
    NCollection_List<TopoDS_Shape>::Iterator ite(myMap(S));
    for (; ite.More(); ite.Next())
    {
      const TopoDS_Shape& sh = ite.Value();
      if (!sh.IsSame(S))
        myGenerated.Append(sh);
    }
    return myGenerated;
  }
  return myGenerated;
}

void BRepFeat_Form::UpdateDescendants(const LocOpe_Gluer& G)
{
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator                                                       itdm;
  NCollection_List<TopoDS_Shape>::Iterator                         it, it2;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itm;

  for (itdm.Initialize(myMap); itdm.More(); itdm.Next())
  {
    const TopoDS_Shape&                                    orig = itdm.Key();
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> newdsc;
    for (it.Initialize(itdm.Value()); it.More(); it.Next())
    {
      const TopoDS_Face& fdsc = TopoDS::Face(it.Value());
      for (it2.Initialize(G.DescendantFaces(fdsc)); it2.More(); it2.Next())
      {
        newdsc.Add(it2.Value());
      }
    }
    myMap.ChangeFind(orig).Clear();
    for (itm.Initialize(newdsc); itm.More(); itm.Next())
    {
      myMap.ChangeFind(orig).Append(itm.Key());
    }
  }
}

const NCollection_List<TopoDS_Shape>& BRepFeat_Form::FirstShape() const
{
  if (!myFShape.IsNull())
  {
    return myMap(myFShape);
  }
  return myGenerated;
}

const NCollection_List<TopoDS_Shape>& BRepFeat_Form::LastShape() const
{
  if (!myLShape.IsNull())
  {
    return myMap(myLShape);
  }
  return myGenerated;
}

const NCollection_List<TopoDS_Shape>& BRepFeat_Form::NewEdges() const
{
  return myNewEdges;
}

const NCollection_List<TopoDS_Shape>& BRepFeat_Form::TgtEdges() const
{
  return myTgtEdges;
}

bool BRepFeat_Form::TransformShapeFU(const int flag)
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
#endif
  bool Trf = false;

  TopoDS_Shape shapefu;
  if (flag == 0)
    shapefu = mySFrom;
  else if (flag == 1)
    shapefu = mySUntil;
  else
    return Trf;

  TopExp_Explorer exp(shapefu, TopAbs_FACE);
  if (!exp.More())
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " BRepFeat_Form::TransformShapeFU : invalid Shape" << std::endl;
#endif
    return Trf;
  }

  exp.Next();
  if (!exp.More())
  {
    exp.ReInit();
    TopoDS_Face fac = TopoDS::Face(exp.Current());

    occ::handle<Geom_Surface>  S    = BRep_Tool::Surface(fac);
    occ::handle<Standard_Type> styp = S->DynamicType();
    if (styp == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
    {
      S    = occ::down_cast<Geom_RectangularTrimmedSurface>(S)->BasisSurface();
      styp = S->DynamicType();
    }

    if (styp == STANDARD_TYPE(Geom_Plane) || styp == STANDARD_TYPE(Geom_CylindricalSurface)
        || styp == STANDARD_TYPE(Geom_ConicalSurface))
    {
      TopExp_Explorer exp1(fac, TopAbs_WIRE);
      if (!exp1.More())
      {
        Trf = true;
      }
      else
      {
        Trf = BRep_Tool::NaturalRestriction(fac);
      }
    }
    if (Trf)
    {
      BRepFeat::FaceUntil(mySbase, fac);
    }

    if (flag == 0)
    {
      NCollection_List<TopoDS_Shape> thelist6;
      myMap.Bind(mySFrom, thelist6);
      myMap(mySFrom).Append(fac);
      mySFrom = fac;
    }
    else if (flag == 1)
    {
      NCollection_List<TopoDS_Shape> thelist7;
      myMap.Bind(mySUntil, thelist7);
      myMap(mySUntil).Append(fac);
      mySUntil = fac;
    }
    else
    {
    }
  }
  else
  {
    for (exp.ReInit(); exp.More(); exp.Next())
    {
      const TopoDS_Shape&            fac = exp.Current();
      NCollection_List<TopoDS_Shape> thelist8;
      myMap.Bind(fac, thelist8);
      myMap(fac).Append(fac);
    }
  }
#ifdef OCCT_DEBUG
  if (trc)
  {
    if (Trf && (flag == 0))
      std::cout << " TransformShapeFU From" << std::endl;
    if (Trf && (flag == 1))
      std::cout << " TransformShapeFU Until" << std::endl;
  }
#endif
  return Trf;
}

BRepFeat_StatusError BRepFeat_Form::CurrentStatusError() const
{
  return myStatusError;
}

static void Descendants(const TopoDS_Shape&                                     S,
                        BRepFeat_Builder&                                       theFB,
                        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& mapF)
{
  mapF.Clear();
  NCollection_List<TopoDS_Shape>::Iterator it;
  TopExp_Explorer                          exp;
  for (exp.Init(S, TopAbs_FACE); exp.More(); exp.Next())
  {

    const TopoDS_Face&                    fdsc = TopoDS::Face(exp.Current());
    const NCollection_List<TopoDS_Shape>& aLM  = theFB.Modified(fdsc);
    it.Initialize(aLM);
    for (; it.More(); it.Next())
    {
      mapF.Add(it.Value());
    }
  }
}

void BRepFeat_Form::UpdateDescendants(const BRepAlgoAPI_BooleanOperation& aBOP,
                                      const TopoDS_Shape&                 S,
                                      const bool                          SkipFace)
{
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator                                                       itdm;
  NCollection_List<TopoDS_Shape>::Iterator                         it, it2;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itm;
  TopExp_Explorer                                                  exp;

  for (itdm.Initialize(myMap); itdm.More(); itdm.Next())
  {
    const TopoDS_Shape& orig = itdm.Key();
    if (SkipFace && orig.ShapeType() == TopAbs_FACE)
    {
      continue;
    }
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> newdsc;

    if (itdm.Value().IsEmpty())
    {
      myMap.ChangeFind(orig).Append(orig);
    }

    for (it.Initialize(itdm.Value()); it.More(); it.Next())
    {
      const TopoDS_Shape& sh = it.Value();
      if (sh.ShapeType() != TopAbs_FACE)
        continue;
      const TopoDS_Face& fdsc = TopoDS::Face(it.Value());
      for (exp.Init(S, TopAbs_FACE); exp.More(); exp.Next())
      {
        if (exp.Current().IsSame(fdsc))
        {
          newdsc.Add(fdsc);
          break;
        }
      }
      if (!exp.More())
      {
        BRepAlgoAPI_BooleanOperation*         pBOP = (BRepAlgoAPI_BooleanOperation*)&aBOP;
        const NCollection_List<TopoDS_Shape>& aLM  = pBOP->Modified(fdsc);
        it2.Initialize(aLM);
        for (; it2.More(); it2.Next())
        {
          const TopoDS_Shape& aS = it2.Value();
          newdsc.Add(aS);
        }
      }
    }
    myMap.ChangeFind(orig).Clear();
    for (itm.Initialize(newdsc); itm.More(); itm.Next())
    {

      for (exp.Init(S, TopAbs_FACE); exp.More(); exp.Next())
      {
        if (exp.Current().IsSame(itm.Key()))
        {

          myMap.ChangeFind(orig).Append(itm.Key());
          break;
        }
      }
    }
  }
}
