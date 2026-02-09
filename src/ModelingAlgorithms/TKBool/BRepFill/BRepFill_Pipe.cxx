#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <BRepClass3d_SolidClassifier.hpp>
#include <BRepFill_Edge3DLaw.hpp>
#include <BRepFill_LocationLaw.hpp>
#include <BRepFill_Pipe.hpp>
#include <BRepFill_SectionPlacement.hpp>
#include <BRepFill_ShapeLaw.hpp>
#include <BRepFill_Sweep.hpp>
#include <BRepLib.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRepTools_Substitution.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomFill_CorrectedFrenet.hpp>
#include <GeomFill_CurveAndTrihedron.hpp>
#include <GeomFill_DiscreteTrihedron.hpp>
#include <GeomFill_Frenet.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <ShapeUpgrade_RemoveLocations.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NotImplemented.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>

static bool UpdateMap(
  const TopoDS_Shape& theKey,
  const TopoDS_Shape& theValue,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theMap)
{
  if (!theMap.IsBound(theKey))
  {
    NCollection_List<TopoDS_Shape> thelist;
    theMap.Bind(theKey, thelist);
  }
  NCollection_List<TopoDS_Shape>&          aList = theMap.ChangeFind(theKey);
  NCollection_List<TopoDS_Shape>::Iterator anIt(aList);
  bool                                     found = false;

  for (; anIt.More(); anIt.Next())
  {
    if (theValue.IsSame(anIt.Value()))
    {
      found = true;
      break;
    }
  }

  if (!found)
    aList.Append(theValue);

  return !found;
}

static void UpdateTolFromTopOrBottomPCurve(const TopoDS_Face& aFace, TopoDS_Edge& anEdge)
{
  double                    fpar, lpar;
  occ::handle<Geom2d_Curve> aPCurve = BRep_Tool::CurveOnSurface(anEdge, aFace, fpar, lpar);
  if (aPCurve.IsNull())
    return;

  occ::handle<Geom_Curve> aCurve = BRep_Tool::Curve(anEdge, fpar, lpar);
  if (aCurve.IsNull())
    return;

  occ::handle<Geom2dAdaptor_Curve> GAHC2d = new Geom2dAdaptor_Curve(aPCurve, fpar, lpar);
  occ::handle<Geom_Surface>        aSurf  = BRep_Tool::Surface(aFace);
  occ::handle<GeomAdaptor_Surface> GAHS   = new GeomAdaptor_Surface(aSurf);
  Adaptor3d_CurveOnSurface         ConS(GAHC2d, GAHS);

  double    Tol      = BRep_Tool::Tolerance(anEdge);
  double    InitTol  = Tol;
  double    TolTol   = Tol * Tol;
  const int NCONTROL = 22;
  double    delta    = (lpar - fpar) / NCONTROL;
  for (int i = 0; i <= NCONTROL; i++)
  {
    double par    = fpar + i * delta;
    gp_Pnt pnt    = aCurve->Value(par);
    gp_Pnt prj    = ConS.Value(par);
    double sqdist = pnt.SquareDistance(prj);
    if (sqdist > TolTol)
      TolTol = sqdist;
  }
  Tol = 1.00005 * std::sqrt(TolTol);
  if (Tol >= InitTol)
  {
    BRep_Builder BB;
    BB.UpdateEdge(anEdge, Tol);
    TopoDS_Iterator itv(anEdge);
    for (; itv.More(); itv.Next())
    {
      TopoDS_Vertex aVertex = TopoDS::Vertex(itv.Value());
      BB.UpdateVertex(aVertex, Tol);
    }
  }
}

BRepFill_Pipe::BRepFill_Pipe()
{
  myDegmax        = 11;
  mySegmax        = 100;
  myContinuity    = GeomAbs_C2;
  myMode          = GeomFill_IsCorrectedFrenet;
  myForceApproxC1 = false;

  myCurIndexOfSectionEdge = 1;
}

BRepFill_Pipe::BRepFill_Pipe(const TopoDS_Wire&       Spine,
                             const TopoDS_Shape&      Profile,
                             const GeomFill_Trihedron aMode,
                             const bool               ForceApproxC1,
                             const bool               KPart)

{
  myDegmax = 11;
  mySegmax = 100;

  myMode = GeomFill_IsCorrectedFrenet;
  if (aMode == GeomFill_IsFrenet || aMode == GeomFill_IsCorrectedFrenet
      || aMode == GeomFill_IsDiscreteTrihedron)
    myMode = aMode;

  myContinuity = GeomAbs_C2;
  if (myMode == GeomFill_IsDiscreteTrihedron)
    myContinuity = GeomAbs_C0;

  myForceApproxC1 = ForceApproxC1;

  myCurIndexOfSectionEdge = 1;

  Perform(Spine, Profile, KPart);
}

void BRepFill_Pipe::Perform(const TopoDS_Wire& Spine, const TopoDS_Shape& Profile, const bool)

{
  mySections.Nullify();
  myFaces.Nullify();
  myEdges.Nullify();

  mySpine   = Spine;
  myProfile = Profile;

  DefineRealSegmax();

  BRepTools_WireExplorer wexp;
  TopoDS_Shape           TheProf;

  occ::handle<GeomFill_TrihedronLaw> TLaw;
  switch (myMode)
  {
    case GeomFill_IsFrenet:
      TLaw = new GeomFill_Frenet();
      break;
    case GeomFill_IsCorrectedFrenet:
      TLaw = new GeomFill_CorrectedFrenet();
      break;
    case GeomFill_IsDiscreteTrihedron:
      TLaw = new GeomFill_DiscreteTrihedron();
      break;
    default:
      break;
  }
  occ::handle<GeomFill_CurveAndTrihedron> Loc = new (GeomFill_CurveAndTrihedron)(TLaw);
  myLoc                                       = new (BRepFill_Edge3DLaw)(mySpine, Loc);
  if (myLoc->NbLaw() == 0)
  {
    return;
  }
  myLoc->TransformInG0Law();

  BRepFill_SectionPlacement Place(myLoc, Profile);
  myTrsf = Place.Transformation();

  TopLoc_Location Loc2(myTrsf), Loc1;
  Loc1 = Profile.Location();
  TopoDS_Shape aux;
  TheProf = myProfile;
  TheProf.Location(Loc2.Multiplied(Loc1));

  occ::handle<GeomFill_LocationLaw> law;

  gp_Mat  M;
  gp_Vec  V;
  gp_Trsf fila;
  double  first, last;
  myLoc->Law(1)->GetDomain(first, last);
  myLoc->Law(1)->D0(first, M, V);
  fila.SetValues(M(1, 1),
                 M(1, 2),
                 M(1, 3),
                 V.X(),
                 M(2, 1),
                 M(2, 2),
                 M(2, 3),
                 V.Y(),
                 M(3, 1),
                 M(3, 2),
                 M(3, 3),
                 V.Z());

  fila.Multiply(myTrsf);
  TopLoc_Location LocFirst(fila);
  myFirst = myProfile;
  if (!LocFirst.IsIdentity())
  {

    myFirst = BRepBuilderAPI_Transform(myProfile, fila, true);
  }

  ShapeUpgrade_RemoveLocations RemLoc;
  RemLoc.SetRemoveLevel(TopAbs_COMPOUND);
  RemLoc.Remove(myFirst);
  myFirst = RemLoc.GetResult();

  myLoc->Law(myLoc->NbLaw())->GetDomain(first, last);
  myLoc->Law(myLoc->NbLaw())->D0(last, M, V);

  fila.SetValues(M(1, 1),
                 M(1, 2),
                 M(1, 3),
                 V.X(),
                 M(2, 1),
                 M(2, 2),
                 M(2, 3),
                 V.Y(),
                 M(3, 1),
                 M(3, 2),
                 M(3, 3),
                 V.Z());
  fila.Multiply(myTrsf);
  TopLoc_Location LocLast(fila);
  if (!myLoc->IsClosed() || LocFirst != LocLast)
  {
    myLast = myProfile;
    if (!LocLast.IsIdentity())
    {

      myLast = BRepBuilderAPI_Transform(myProfile, fila, true);
    }
  }
  else
  {
    myLast = myFirst;
  }

  RemLoc.Remove(myLast);
  myLast = RemLoc.GetResult();

  myShape = MakeShape(TheProf, myProfile, myFirst, myLast);
}

const TopoDS_Shape& BRepFill_Pipe::Spine() const
{
  return mySpine;
}

const TopoDS_Shape& BRepFill_Pipe::Profile() const
{
  return myProfile;
}

const TopoDS_Shape& BRepFill_Pipe::Shape() const
{
  return myShape;
}

double BRepFill_Pipe::ErrorOnSurface() const
{
  return myErrorOnSurf;
}

const TopoDS_Shape& BRepFill_Pipe::FirstShape() const
{
  return myFirst;
}

const TopoDS_Shape& BRepFill_Pipe::LastShape() const
{
  return myLast;
}

void BRepFill_Pipe::Generated(const TopoDS_Shape& theShape, NCollection_List<TopoDS_Shape>& theList)
{
  theList.Clear();

  if (myGenMap.IsBound(theShape))
  {
    theList = myGenMap.Find(theShape);
  }
}

TopoDS_Face BRepFill_Pipe::Face(const TopoDS_Edge& ESpine, const TopoDS_Edge& EProfile)
{
  TopoDS_Face theFace;

  if (BRep_Tool::Degenerated(EProfile))
    return theFace;

  int ii, ispin = 0, iprof = 0, count = 0;

  iprof = FindEdge(myProfile, EProfile, count);

  if (!iprof)
    throw Standard_DomainError("BRepFill_Pipe::Face : Edge not in the Profile");

  for (ii = 1; ii <= myLoc->NbLaw() && (!ispin); ii++)
    if (ESpine.IsSame(myLoc->Edge(ii)))
      ispin = ii;

  if (!ispin)
    throw Standard_DomainError("BRepFill_Pipe::Edge  : Edge not in the Spine");

  theFace = TopoDS::Face(myFaces->Value(iprof, ispin));
  return theFace;
}

TopoDS_Edge BRepFill_Pipe::Edge(const TopoDS_Edge& ESpine, const TopoDS_Vertex& VProfile)
{
  int ii, ispin = 0, iprof = 0, count = 0;

  iprof = FindVertex(myProfile, VProfile, count);
  if (!iprof)
    throw Standard_DomainError("BRepFill_Pipe::Edge : Vertex not in the Profile");

  for (ii = 1; ii <= myLoc->NbLaw() && (!ispin); ii++)
    if (ESpine.IsSame(myLoc->Edge(ii)))
      ispin = ii;

  if (!ispin)
    throw Standard_DomainError("BRepFill_Pipe::Edge  : Edge not in the Spine");

  TopoDS_Edge theEdge;
  theEdge = TopoDS::Edge(myEdges->Value(iprof, ispin));

  return theEdge;
}

TopoDS_Shape BRepFill_Pipe::Section(const TopoDS_Vertex& VSpine) const
{
  TopoDS_Iterator it, itv;

  int ii, ispin = 0;

  TopoDS_Shape curSect = myProfile;

  for (ii = 1; ii <= myLoc->NbLaw() + 1 && (!ispin); ii++)
    if (VSpine.IsSame(myLoc->Vertex(ii)))
      ispin = ii;

  if (!ispin)
    throw Standard_DomainError("BRepFill_Pipe::Section  : Vertex not in the Spine");

  BRep_Builder    B;
  TopoDS_Compound Comp;
  B.MakeCompound(Comp);
  for (ii = 1; ii <= mySections->ColLength(); ii++)
    B.Add(Comp, mySections->Value(ii, ispin));

  return Comp;
}

TopoDS_Wire BRepFill_Pipe::PipeLine(const gp_Pnt& Point)
{

  gp_Pnt P;
  P = Point;
  P.Transform(myTrsf);

  TopoDS_Vertex                  VertexSection = BRepLib_MakeVertex(P);
  occ::handle<BRepFill_ShapeLaw> Section       = new (BRepFill_ShapeLaw)(VertexSection);

  BRepFill_Sweep MkSw(Section, myLoc, true);
  MkSw.SetForceApproxC1(myForceApproxC1);
  MkSw.Build(myReversedEdges,
             myTapes,
             myRails,
             BRepFill_Modified,
             myContinuity,
             GeomFill_Location,
             myDegmax,
             mySegmax);
  TopoDS_Shape aLocalShape = MkSw.Shape();
  myErrorOnSurf            = MkSw.ErrorOnSurface();
  BuildHistory(MkSw, VertexSection);
  return TopoDS::Wire(aLocalShape);
}

TopoDS_Shape BRepFill_Pipe::MakeShape(const TopoDS_Shape& S,
                                      const TopoDS_Shape& theOriginalS,
                                      const TopoDS_Shape& FirstShape,
                                      const TopoDS_Shape& LastShape)
{
  TopoDS_Shape result;
  BRep_Builder B;
  bool         explode = false;
  TopoDS_Shape TheS, TheFirst, TheLast;
  int          InitialLength = 0;
  TheS                       = S;
  TheFirst                   = FirstShape;
  TheLast                    = LastShape;
  if (!myFaces.IsNull())
    InitialLength = myFaces->ColLength();

  TopLoc_Location BackLoc(myTrsf.Inverted());

  switch (S.ShapeType())
  {

    case TopAbs_VERTEX:
    {
      B.MakeWire(TopoDS::Wire(result));
      break;
    }

    case TopAbs_EDGE:
    {
      TopoDS_Wire W;
      B.MakeShell(TopoDS::Shell(result));
      B.MakeWire(W);
      B.Add(W, S);
      W.Closed(BRep_Tool::IsClosed(S));
      TheS = W;
      if (!FirstShape.IsNull())
      {
        B.MakeWire(W);
        B.Add(W, FirstShape);
        W.Closed(BRep_Tool::IsClosed(FirstShape));
        TheFirst = W;
      }
      if (!LastShape.IsNull())
      {
        B.MakeWire(W);
        B.Add(W, LastShape);
        W.Closed(BRep_Tool::IsClosed(LastShape));
        TheLast = W;
      }
      result.Closed(BRep_Tool::IsClosed(result));
      break;
    }

    case TopAbs_WIRE:
      B.MakeShell(TopoDS::Shell(result));
      break;

    case TopAbs_FACE:
    {
      B.MakeShell(TopoDS::Shell(result));
      explode = true;
      if (!mySpine.Closed() && !TheFirst.IsNull())
      {
        B.Add(result, TheFirst.Reversed());
      }
      result.Closed(BRep_Tool::IsClosed(result));
      break;
    }

    case TopAbs_SHELL:
    {
      B.MakeCompSolid(TopoDS::CompSolid(result));
      explode = true;
      break;
    }

    case TopAbs_SOLID:
    case TopAbs_COMPSOLID:
      throw Standard_DomainError("BRepFill_Pipe::profile contains solids");
      break;

    case TopAbs_COMPOUND:
    {
      B.MakeCompound(TopoDS::Compound(result));
      explode = true;
      break;
    }
    default:
      break;
  }

  if (explode)
  {

    TopoDS_Iterator itFirst, itLast;
    TopoDS_Shape    first, last;
    if (!TheFirst.IsNull())
      itFirst.Initialize(TheFirst);
    if (!TheLast.IsNull())
      itLast.Initialize(TheLast);

    TopoDS_Iterator it(S);
    TopoDS_Iterator itorig(theOriginalS);
    for (; it.More(); it.Next(), itorig.Next())
    {
      if (!TheFirst.IsNull())
        first = itFirst.Value();
      if (!TheLast.IsNull())
        last = itLast.Value();
      if (TheS.ShapeType() == TopAbs_FACE)
        MakeShape(it.Value(), itorig.Value(), first, last);
      else
        B.Add(result, MakeShape(it.Value(), itorig.Value(), first, last));

      if (!TheFirst.IsNull())
        itFirst.Next();
      if (!TheLast.IsNull())
        itLast.Next();
    }
  }

  else
  {
    if (TheS.ShapeType() == TopAbs_VERTEX)
    {
      occ::handle<BRepFill_ShapeLaw> Section = new (BRepFill_ShapeLaw)(TopoDS::Vertex(TheS));
      BRepFill_Sweep                 MkSw(Section, myLoc, true);
      MkSw.SetForceApproxC1(myForceApproxC1);
      MkSw.Build(myReversedEdges,
                 myTapes,
                 myRails,
                 BRepFill_Modified,
                 myContinuity,
                 GeomFill_Location,
                 myDegmax,
                 mySegmax);
      result = MkSw.Shape();
      UpdateMap(theOriginalS, result, myGenMap);
      myErrorOnSurf = MkSw.ErrorOnSurface();

      occ::handle<NCollection_HArray2<TopoDS_Shape>> aSections = MkSw.Sections();

      if (!aSections.IsNull())
      {
        const int aVLast = aSections->UpperCol();

        myFirst = aSections->Value(1, 1);
        myLast  = aSections->Value(1, aVLast);
      }

      BuildHistory(MkSw, theOriginalS);
    }

    if (TheS.ShapeType() == TopAbs_WIRE)
    {
      occ::handle<BRepFill_ShapeLaw> Section = new (BRepFill_ShapeLaw)(TopoDS::Wire(TheS));
      BRepFill_Sweep                 MkSw(Section, myLoc, true);
      MkSw.SetBounds(TopoDS::Wire(TheFirst), TopoDS::Wire(TheLast));
      MkSw.SetForceApproxC1(myForceApproxC1);
      MkSw.Build(myReversedEdges,
                 myTapes,
                 myRails,
                 BRepFill_Modified,
                 myContinuity,
                 GeomFill_Location,
                 myDegmax,
                 mySegmax);
      result        = MkSw.Shape();
      myErrorOnSurf = MkSw.ErrorOnSurface();

      if (mySections.IsNull())
      {
        myFaces    = MkSw.SubShape();
        mySections = MkSw.Sections();
        myEdges    = MkSw.InterFaces();
      }
      else
      {
        occ::handle<NCollection_HArray2<TopoDS_Shape>> Aux, Somme;
        int                                            length;
        int                                            ii, jj, kk;

        Aux    = MkSw.SubShape();
        length = Aux->ColLength() + myFaces->ColLength();
        Somme  = new (NCollection_HArray2<TopoDS_Shape>)(1, length, 1, Aux->RowLength());
        for (jj = 1; jj <= myFaces->RowLength(); jj++)
        {
          for (ii = 1; ii <= myFaces->ColLength(); ii++)
            Somme->SetValue(ii, jj, myFaces->Value(ii, jj));

          for (kk = 1, ii = myFaces->ColLength() + 1; kk <= Aux->ColLength(); kk++, ii++)
            Somme->SetValue(ii, jj, Aux->Value(kk, jj));
        }
        myFaces = Somme;

        Aux    = MkSw.Sections();
        length = Aux->ColLength() + mySections->ColLength();
        Somme  = new (NCollection_HArray2<TopoDS_Shape>)(1, length, 1, Aux->RowLength());
        for (jj = 1; jj <= mySections->RowLength(); jj++)
        {
          for (ii = 1; ii <= mySections->ColLength(); ii++)
            Somme->SetValue(ii, jj, mySections->Value(ii, jj));

          myCurIndexOfSectionEdge = mySections->ColLength() + 1;

          for (kk = 1, ii = mySections->ColLength() + 1; kk <= Aux->ColLength(); kk++, ii++)
            Somme->SetValue(ii, jj, Aux->Value(kk, jj));
        }
        mySections = Somme;

        Aux    = MkSw.InterFaces();
        length = Aux->ColLength() + myEdges->ColLength();
        Somme  = new (NCollection_HArray2<TopoDS_Shape>)(1, length, 1, Aux->RowLength());
        for (jj = 1; jj <= myEdges->RowLength(); jj++)
        {
          for (ii = 1; ii <= myEdges->ColLength(); ii++)
            Somme->SetValue(ii, jj, myEdges->Value(ii, jj));

          for (kk = 1, ii = myEdges->ColLength() + 1; kk <= Aux->ColLength(); kk++, ii++)
            Somme->SetValue(ii, jj, Aux->Value(kk, jj));
        }

        myEdges = Somme;
      }

      BuildHistory(MkSw, theOriginalS);
    }
  }

  if (TheS.ShapeType() == TopAbs_FACE)
  {
    int ii, jj;

    TopExp_Explorer Explo(result, TopAbs_FACE);
    for (; Explo.More(); Explo.Next())
    {
      const TopoDS_Shape& aFace = Explo.Current();
      RebuildTopOrBottomFace(aFace.Reversed(), true);
    }

    TopoDS_Face F;
    for (ii = InitialLength + 1; ii <= myFaces->ColLength(); ii++)
    {
      for (jj = 1; jj <= myFaces->RowLength(); jj++)
      {
        if (myFaces->Value(ii, jj).ShapeType() == TopAbs_FACE)
        {
          F = TopoDS::Face(myFaces->Value(ii, jj));
          if (!F.IsNull())
            B.Add(result, F);
        }
      }
    }

    if (!mySpine.Closed())
    {

      RebuildTopOrBottomFace(TheLast, false);

      B.Add(result, TopoDS::Face(TheLast));
    }

    TopoDS_Solid solid;
    BRep_Builder BS;
    BS.MakeSolid(solid);

    result.Closed(true);
    BS.Add(solid, TopoDS::Shell(result));

    BRepClass3d_SolidClassifier SC(solid);
    SC.PerformInfinitePoint(Precision::Confusion());
    if (SC.State() == TopAbs_IN)
    {
      BS.MakeSolid(solid);
      TopoDS_Shape aLocalShape = result.Reversed();
      BS.Add(solid, TopoDS::Shell(aLocalShape));
    }
    UpdateMap(theOriginalS, solid, myGenMap);
    return solid;
  }
  else
  {
    return result;
  }
}

int BRepFill_Pipe::FindEdge(const TopoDS_Shape& S, const TopoDS_Edge& E, int& InitialLength) const
{
  int result = 0;

  switch (S.ShapeType())
  {

    case TopAbs_EDGE:
    {
      InitialLength++;
      if (S.IsSame(E))
        result = InitialLength;
      break;
    }

    case TopAbs_WIRE:
    {
      occ::handle<BRepFill_ShapeLaw> Section = new (BRepFill_ShapeLaw)(TopoDS::Wire(S), false);
      int                            NbLaw   = Section->NbLaw();

      for (int ii = 1; (ii <= NbLaw) && (!result); ii++)
      {
        if (E.IsSame(Section->Edge(ii)))
          result = InitialLength + ii;
      }
      InitialLength += NbLaw;
      break;
    }

    case TopAbs_FACE:
    case TopAbs_SHELL:
    case TopAbs_COMPOUND:
    {
      for (TopoDS_Iterator it(S); it.More() && (!result); it.Next())
        result = FindEdge(it.Value(), E, InitialLength);
      break;
    }

    case TopAbs_SOLID:
    case TopAbs_COMPSOLID:
      throw Standard_DomainError("BRepFill_Pipe::SOLID or COMPSOLID");
      break;
    default:
      break;
  }

  return result;
}

int BRepFill_Pipe::FindVertex(const TopoDS_Shape&  S,
                              const TopoDS_Vertex& V,
                              int&                 InitialLength) const
{
  int result = 0;

  switch (S.ShapeType())
  {
    case TopAbs_VERTEX:
    {
      InitialLength++;
      if (S.IsSame(V))
        result = InitialLength;
      break;
    }

    case TopAbs_EDGE:
    {
      TopoDS_Vertex VF, VL;
      TopExp::Vertices(TopoDS::Edge(S), VF, VL);
      if (S.Orientation() == TopAbs_REVERSED)
      {
        TopoDS_Vertex aux;
        aux = VF;
        VF  = VL;
        VL  = aux;
      }
      if (VF.IsSame(V))
        result = InitialLength + 1;
      else if (VL.IsSame(V))
        result = InitialLength + 2;
      InitialLength += 2;
      break;
    }

    case TopAbs_WIRE:
    {
      int                            ii      = InitialLength + 1;
      occ::handle<BRepFill_ShapeLaw> Section = new (BRepFill_ShapeLaw)(TopoDS::Wire(S), false);
      InitialLength += Section->NbLaw() + 1;

      for (; (ii <= InitialLength) && (!result); ii++)
      {
        if (V.IsSame(Section->Vertex(ii, 0.)))
          result = ii;
      }
      break;
    }

    case TopAbs_FACE:
    case TopAbs_SHELL:
    case TopAbs_COMPOUND:
    {
      for (TopoDS_Iterator it(S); it.More() && (!result); it.Next())
        result = FindVertex(it.Value(), V, InitialLength);
      break;
    }

    case TopAbs_SOLID:
    case TopAbs_COMPSOLID:
      throw Standard_DomainError("BRepFill_Pipe::SOLID or COMPSOLID");
      break;
    default:
      break;
  }

  return result;
}

void BRepFill_Pipe::DefineRealSegmax()
{
  int RealSegmax = 0;

  TopoDS_Iterator iter(mySpine);
  for (; iter.More(); iter.Next())
  {
    TopoDS_Edge             E = TopoDS::Edge(iter.Value());
    double                  first, last;
    occ::handle<Geom_Curve> C = BRep_Tool::Curve(E, first, last);
    if (C.IsNull())
      continue;
    while (C->DynamicType() == STANDARD_TYPE(Geom_TrimmedCurve)
           || C->DynamicType() == STANDARD_TYPE(Geom_OffsetCurve))
    {
      if (C->DynamicType() == STANDARD_TYPE(Geom_TrimmedCurve))
        C = occ::down_cast<Geom_TrimmedCurve>(C)->BasisCurve();
      if (C->DynamicType() == STANDARD_TYPE(Geom_OffsetCurve))
        C = occ::down_cast<Geom_OffsetCurve>(C)->BasisCurve();
    }
    if (C->DynamicType() == STANDARD_TYPE(Geom_BSplineCurve))
    {
      occ::handle<Geom_BSplineCurve> BC(occ::down_cast<Geom_BSplineCurve>(C));
      int                            NbKnots     = BC->NbKnots();
      int                            RealNbKnots = NbKnots;
      if (first > BC->FirstParameter())
      {
        int I1, I2;
        BC->LocateU(first, Precision::PConfusion(), I1, I2);
        RealNbKnots -= I1 - 1;
      }
      if (last < BC->LastParameter())
      {
        int I1, I2;
        BC->LocateU(last, Precision::PConfusion(), I1, I2);
        RealNbKnots -= NbKnots - I2;
      }
      RealSegmax += RealNbKnots - 1;
    }
  }

  if (mySegmax < RealSegmax)
    mySegmax = RealSegmax;
}

void BRepFill_Pipe::RebuildTopOrBottomFace(const TopoDS_Shape& aFace, const bool IsTop) const
{
  int IndexOfSection = (IsTop) ? 1 : mySections->RowLength();

  int             ii;
  BRep_Builder    BB;
  TopoDS_Iterator itf(aFace);
  for (; itf.More(); itf.Next())
  {
    TopoDS_Shape                       aWire = itf.Value();
    NCollection_Sequence<TopoDS_Shape> InitEdges;
    NCollection_Sequence<TopoDS_Shape> ResEdges;
    TopoDS_Iterator                    itw(aWire);
    for (; itw.More(); itw.Next())
    {
      const TopoDS_Shape& anEdge = itw.Value();
      for (ii = myCurIndexOfSectionEdge; ii <= mySections->ColLength(); ii++)
      {
        TopoDS_Shape aVisoEdge = mySections->Value(ii, IndexOfSection);
        if (anEdge.IsSame(aVisoEdge))
        {
          InitEdges.Append(anEdge);
          ResEdges.Append(aVisoEdge);
          break;
        }
      }
    }
    aWire.Free(true);
    for (ii = 1; ii <= InitEdges.Length(); ii++)
    {
      BB.Remove(aWire, InitEdges(ii));
      UpdateTolFromTopOrBottomPCurve(TopoDS::Face(aFace), TopoDS::Edge(ResEdges(ii)));
      BB.Add(aWire, ResEdges(ii));
    }
  }
}

void BRepFill_Pipe::BuildHistory(const BRepFill_Sweep& theSweep, const TopoDS_Shape& theSection)
{

  const occ::handle<NCollection_HArray2<TopoDS_Shape>>& anUEdges = theSweep.InterFaces();

  int             inde;
  TopoDS_Iterator itw;

  if (theSection.ShapeType() == TopAbs_WIRE)
  {
    TopoDS_Wire            aSection = TopoDS::Wire(theSection);
    BRepTools_WireExplorer wexp_sec(aSection);
    for (inde = 0; wexp_sec.More(); wexp_sec.Next())
    {
      inde++;
      const TopoDS_Edge& anEdge = TopoDS::Edge(wexp_sec.Current());
      if (BRep_Tool::Degenerated(anEdge))
        continue;
      if (myGenMap.IsBound(anEdge))
        continue;

      TopoDS_Vertex aVertex[2];
      TopExp::Vertices(anEdge, aVertex[0], aVertex[1]);

      TopoDS_Shell aTape = TopoDS::Shell(theSweep.Tape(inde));

      int UIndex[2];
      UIndex[0] = inde;
      UIndex[1] = inde + 1;

      if (anEdge.Orientation() == TopAbs_REVERSED)
      {
        int Tmp   = UIndex[0];
        UIndex[0] = UIndex[1];
        UIndex[1] = Tmp;
      }

      for (int kk = 0; kk < 2; kk++)
      {
        if (myGenMap.IsBound(aVertex[kk]))
          continue;

        NCollection_List<TopoDS_Shape>* Elist =
          myGenMap.Bound(aVertex[kk], NCollection_List<TopoDS_Shape>());
        int jj;
        for (jj = 1; jj <= anUEdges->UpperCol(); jj++)
        {
          const TopoDS_Shape& anUedge = anUEdges->Value(UIndex[kk], jj);
          if (!anUedge.IsNull())
            Elist->Append(anUedge);
        }
      }

      NCollection_List<TopoDS_Shape>* Flist =
        myGenMap.Bound(anEdge, NCollection_List<TopoDS_Shape>());
      TopoDS_Iterator itsh(aTape);
      for (; itsh.More(); itsh.Next())
        Flist->Append(itsh.Value());
    }
  }

  const occ::handle<NCollection_HArray2<TopoDS_Shape>>& aFaces  = theSweep.SubShape();
  const occ::handle<NCollection_HArray2<TopoDS_Shape>>& aVEdges = theSweep.Sections();

  BRepTools_WireExplorer wexp(mySpine);
  inde        = 0;
  bool ToExit = false;
  for (;;)
  {
    if (!wexp.More())
      ToExit = true;

    inde++;

    if (!ToExit)
    {
      const TopoDS_Edge& anEdgeOfSpine = wexp.Current();
      for (int i = 1; i <= aFaces->UpperRow(); i++)
      {
        const TopoDS_Shape& aFace = aFaces->Value(i, inde);
        UpdateMap(anEdgeOfSpine, aFace, myGenMap);
      }
    }

    const TopoDS_Vertex& aVertexOfSpine = wexp.CurrentVertex();
    for (int i = 1; i <= aVEdges->UpperRow(); i++)
    {
      const TopoDS_Shape& aVedge = aVEdges->Value(i, inde);
      UpdateMap(aVertexOfSpine, aVedge, myGenMap);
    }

    if (ToExit)
      break;

    if (wexp.More())
      wexp.Next();
  }
}
