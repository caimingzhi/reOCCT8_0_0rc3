#include <BRepTest.hpp>

#include <BRepTest_Objects.hpp>

#include <DBRep.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_Appli.hpp>

#include <BRepFill.hpp>
#include <BRepFill_Generator.hpp>
#include <BRepPrimAPI_MakePrism.hpp>
#include <BRepPrimAPI_MakeRevol.hpp>
#include <BRepOffsetAPI_MakePipe.hpp>
#include <BRepOffsetAPI_MakeEvolved.hpp>
#include <BRepOffsetAPI_ThruSections.hpp>
#include <BRepOffsetAPI_MakePipeShell.hpp>
#include <BRepOffsetAPI_MiddlePath.hpp>

#include <BRepLib_MakeWire.hpp>
#include <TopoDS.hpp>
#include <TopExp_Explorer.hpp>

#include <Precision.hpp>
#include <Law_Interpol.hpp>
#include <gp_Ax1.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>

static BRepOffsetAPI_MakePipeShell* Sweep     = nullptr;
static BRepOffsetAPI_ThruSections*  Generator = nullptr;

#include <cstdio>
#include <Geom_Curve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomFill_Pipe.hpp>
#include <Geom_Surface.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Geom_Circle.hpp>
#include <gp_Ax2.hpp>
#include <Message.hpp>
#include <ShapeUpgrade_UnifySameDomain.hpp>

static int prism(Draw_Interpretor&, int n, const char** a)
{
  if (n < 6)
    return 1;

  TopoDS_Shape base = DBRep::Get(a[2]);
  if (base.IsNull())
    return 1;

  gp_Vec V(Draw::Atof(a[3]), Draw::Atof(a[4]), Draw::Atof(a[5]));

  bool copy = false;
  bool inf  = false;
  bool sinf = false;

  if (n > 6)
  {
    copy = (*a[6] == 'c') || (*a[6] == 'C');
    inf  = (*a[6] == 'i') || (*a[6] == 'I');
    sinf = (*a[6] == 's') || (*a[6] == 'S');
  }

  TopoDS_Shape res;

  BRepPrimAPI_MakePrism* Prism;
  if (inf || sinf)
  {
    Prism = new BRepPrimAPI_MakePrism(base, gp_Dir(V), inf);
  }
  else
  {
    Prism = new BRepPrimAPI_MakePrism(base, V, copy);
  }

  res = Prism->Shape();

  DBRep::Set(a[1], res);

  NCollection_List<TopoDS_Shape> anArgs;
  anArgs.Append(base);
  BRepTest_Objects::SetHistory(anArgs, *Prism);

  delete Prism;

  return 0;
}

static int revol(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 10)
    return 1;

  TopoDS_Shape base = DBRep::Get(a[2]);
  if (base.IsNull())
    return 1;

  gp_Pnt P(Draw::Atof(a[3]), Draw::Atof(a[4]), Draw::Atof(a[5]));
  gp_Dir D(Draw::Atof(a[6]), Draw::Atof(a[7]), Draw::Atof(a[8]));
  gp_Ax1 A(P, D);

  double angle = Draw::Atof(a[9]) * (M_PI / 180.0);

  bool copy = n > 10;

  BRepPrimAPI_MakeRevol Revol(base, A, angle, copy);

  if (Revol.IsDone())
  {
    TopoDS_Shape res = Revol.Shape();

    DBRep::Set(a[1], res);

    NCollection_List<TopoDS_Shape> anArgs;
    anArgs.Append(base);
    BRepTest_Objects::SetHistory(anArgs, Revol);
  }
  else
  {
    di << "Revol not done \n";
  }

  return 0;
}

static int pipe(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 1)
  {
    di << "pipe result Wire_spine Profile [Mode [Approx]]\n";
    di << "Mode = 0 - CorrectedFrenet,\n";
    di << "     = 1 - Frenet,\n";
    di << "     = 2 - DiscreteTrihedron\n";
    di << "Approx - force C1-approximation if result is C0\n";
    return 0;
  }

  if (n > 1 && n < 4)
    return 1;

  TopoDS_Shape Spine = DBRep::Get(a[2], TopAbs_WIRE);
  if (Spine.IsNull())
    return 1;

  TopoDS_Shape Profile = DBRep::Get(a[3]);
  if (Profile.IsNull())
    return 1;

  GeomFill_Trihedron Mode = GeomFill_IsCorrectedFrenet;
  if (n >= 5)
  {
    int iMode = atoi(a[4]);
    if (iMode == 1)
      Mode = GeomFill_IsFrenet;
    else if (iMode == 2)
      Mode = GeomFill_IsDiscreteTrihedron;
  }

  bool ForceApproxC1 = false;
  if (n >= 6)
    ForceApproxC1 = true;

  BRepOffsetAPI_MakePipe PipeBuilder(TopoDS::Wire(Spine), Profile, Mode, ForceApproxC1);
  TopoDS_Shape           S = PipeBuilder.Shape();

  DBRep::Set(a[1], S);

  if (BRepTest_Objects::IsHistoryNeeded())
  {
    NCollection_List<TopoDS_Shape> aList;
    aList.Append(Profile);
    aList.Append(Spine);
    BRepTest_Objects::SetHistory(aList, PipeBuilder);
  }

  return 0;
}

static int geompipe(Draw_Interpretor&, int n, const char** a)
{
  TopoDS_Shape Spine = DBRep::Get(a[2], TopAbs_EDGE);
  if (Spine.IsNull())
    return 1;
  if (n < 5)
    return 1;
  TopoDS_Shape Profile = DBRep::Get(a[3], TopAbs_EDGE);
  if (Profile.IsNull())
    return 1;
  double                  aSpFirst, aSpLast, aPrFirst, aPrLast;
  occ::handle<Geom_Curve> SpineCurve   = BRep_Tool::Curve(TopoDS::Edge(Spine), aSpFirst, aSpLast);
  occ::handle<Geom_Curve> ProfileCurve = BRep_Tool::Curve(TopoDS::Edge(Profile), aPrFirst, aPrLast);
  occ::handle<GeomAdaptor_Curve> aAdaptCurve = new GeomAdaptor_Curve(SpineCurve, aSpFirst, aSpLast);
  bool                           ByACR       = false;
  bool                           rotate      = false;
  double                         Radius      = Draw::Atof(a[4]);
  gp_Pnt                         ctr;
  gp_Vec                         norm;
  ProfileCurve->D1(aSpFirst, ctr, norm);
  gp_Vec                   xAxisStart(ctr, SpineCurve->Value(aSpFirst));
  gp_Ax2                   aAx2Start(ctr, norm, xAxisStart);
  occ::handle<Geom_Circle> cStart = new Geom_Circle(aAx2Start, Radius);
  int                      k      = 5;
  if (n > k)
    ByACR = (Draw::Atoi(a[k++]) == 1);
  if (n > k)
    rotate = (Draw::Atoi(a[k++]) == 1);
  GeomFill_Pipe aPipe(ProfileCurve, aAdaptCurve, cStart, ByACR, rotate);
  aPipe.Perform(true);
  if (!aPipe.IsDone())
  {
    Message::SendFail() << "GeomFill_Pipe cannot make a surface";
    return 1;
  }

  double Accuracy = aPipe.ErrorOnSurf();
  std::cout << "Accuracy of approximation = " << Accuracy << std::endl;

  occ::handle<Geom_Surface> Sur = aPipe.Surface();
  TopoDS_Face               F;
  if (!Sur.IsNull())
    F = BRepBuilderAPI_MakeFace(Sur, Precision::Confusion());
  DBRep::Set(a[1], F);
  return 0;
}

int evolved(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 1)
  {
    di << " evolved result -s spine -p profile [-solid] [-v] [-a] [-t toler] [-parallel] : \n";
    di << "   Make evolved profile on spine.\n";
    di << "   -solid means make closed solid.\n";
    di << "   -v means use alternative algorithm (volume mode).\n";
    di << "   -a means referential CS is automatically computed, otherwise global CS is used. \n";
    di << "   -t sets the tolerance.\n";
    di << "   -parallel turns on parallel execution.\n";
    return 0;
  }

  if (n < 4)
    return 1;
  bool         Solid            = false;
  bool         isVolume         = false;
  bool         hasToComputeAxes = false;
  double       aTolerance       = 0.0;
  TopoDS_Shape Base;
  TopoDS_Wire  Prof;
  bool         isParallel = true;

  for (int i = 2; i < n; i++)
  {
    if (a[i][0] != '-')
    {
      di << "Error: wrong option!\n";
      return 1;
    }

    if (!Solid && !strcmp(a[i], "-solid"))
    {
      Solid = true;
      continue;
    }

    if (!strcmp(a[i], "-stm"))
    {
      isParallel = false;
      continue;
    }

    switch (a[i][1])
    {
      case 's':
      {
        Base = DBRep::Get(a[++i], TopAbs_WIRE, false);
        if (Base.IsNull())
        {
          Base = DBRep::Get(a[i], TopAbs_FACE, false);
        }
      }
      break;

      case 'p':
      {
        Prof = TopoDS::Wire(DBRep::Get(a[++i], TopAbs_WIRE, false));
      }
      break;

      case 'v':
      {
        isVolume = true;
      }
      break;

      case 'a':
      {
        hasToComputeAxes = true;
      }
      break;

      case 't':
      {
        aTolerance = Draw::Atof(a[++i]);
      }
      break;

      default:
        di << "Error: Unknown option!\n";
        break;
    }
  }

  if (Base.IsNull() || Prof.IsNull())
  {
    di << "spine (face or wire) and profile (wire) are expected\n";
    return 1;
  }

  TopoDS_Shape Volevo = BRepOffsetAPI_MakeEvolved(Base,
                                                  Prof,
                                                  GeomAbs_Arc,
                                                  !hasToComputeAxes,
                                                  Solid,
                                                  false,
                                                  aTolerance,
                                                  isVolume,
                                                  isParallel);

  DBRep::Set(a[1], Volevo);

  return 0;
}

static int pruled(Draw_Interpretor&, int n, const char** a)
{
  if (n != 4)
    return 1;

  bool         YaWIRE = false;
  TopoDS_Shape S1     = DBRep::Get(a[2], TopAbs_EDGE);
  if (S1.IsNull())
  {
    S1 = DBRep::Get(a[2], TopAbs_WIRE);
    if (S1.IsNull())
      return 1;
    YaWIRE = true;
  }

  TopoDS_Shape S2 = DBRep::Get(a[3], TopAbs_EDGE);
  if (S2.IsNull())
  {
    S2 = DBRep::Get(a[3], TopAbs_WIRE);
    if (S2.IsNull())
      return 1;
    if (!YaWIRE)
    {
      S1     = BRepLib_MakeWire(TopoDS::Edge(S1));
      YaWIRE = true;
    }
  }
  else if (YaWIRE)
  {
    S2 = BRepLib_MakeWire(TopoDS::Edge(S2));
  }

  TopoDS_Shape Result;
  if (YaWIRE)
  {
    Result = BRepFill::Shell(TopoDS::Wire(S1), TopoDS::Wire(S2));
  }
  else
  {
    Result = BRepFill::Face(TopoDS::Edge(S1), TopoDS::Edge(S2));
  }

  DBRep::Set(a[1], Result);
  return 0;
}

int gener(Draw_Interpretor&, int n, const char** a)
{
  if (n < 4)
    return 1;

  TopoDS_Shape Shape;

  BRepFill_Generator aGenerator;

  for (int i = 2; i <= n - 1; i++)
  {
    Shape = DBRep::Get(a[i], TopAbs_WIRE);
    if (Shape.IsNull())
      return 1;

    aGenerator.AddWire(TopoDS::Wire(Shape));
  }

  aGenerator.Perform();

  TopoDS_Shell Shell = aGenerator.Shell();

  DBRep::Set(a[1], Shell);

  return 0;
}

int thrusections(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 6)
    return 1;

  bool check      = true;
  bool samenumber = true;
  int  index      = 2;

  if (!strcmp(a[1], "-N"))
  {
    if (n < 7)
      return 1;
    check = false;
    index++;
  }

  TopoDS_Shape Shape;

  bool issolid = (Draw::Atoi(a[index]) == 1);
  bool isruled = (Draw::Atoi(a[index + 1]) == 1);

  if (Generator != nullptr)
  {
    delete Generator;
    Generator = nullptr;
  }
  Generator           = new BRepOffsetAPI_ThruSections(issolid, isruled);
  bool IsMutableInput = true;
  int  NbEdges        = 0;
  bool IsFirstWire    = false;
  for (int i = index + 2; i <= n - 1; i++)
  {
    if (!strcmp(a[i], "-safe"))
    {
      IsMutableInput = false;
      continue;
    }
    bool IsWire = true;
    Shape       = DBRep::Get(a[i], TopAbs_WIRE);
    if (!Shape.IsNull())
    {
      Generator->AddWire(TopoDS::Wire(Shape));
      IsFirstWire = !IsFirstWire;
    }
    else
    {
      Shape  = DBRep::Get(a[i], TopAbs_VERTEX);
      IsWire = false;
      if (!Shape.IsNull())
        Generator->AddVertex(TopoDS::Vertex(Shape));
      else
        return 1;
    }

    int             cpt = 0;
    TopExp_Explorer PE;
    for (PE.Init(Shape, TopAbs_EDGE); PE.More(); PE.Next())
    {
      cpt++;
    }
    if (IsFirstWire)
      NbEdges = cpt;
    else if (IsWire && cpt != NbEdges)
      samenumber = false;
  }

  Generator->SetMutableInput(IsMutableInput);

  check = (check || !samenumber);
  Generator->CheckCompatibility(check);

  Generator->Build();

  if (Generator->IsDone())
  {
    TopoDS_Shape Shell = Generator->Shape();
    DBRep::Set(a[index - 1], Shell);

    if (BRepTest_Objects::IsHistoryNeeded())
      BRepTest_Objects::SetHistory(Generator->Wires(), *Generator);
  }
  else
  {
    BRepFill_ThruSectionErrorStatus aStatus = Generator->GetStatus();
    switch (aStatus)
    {
      case BRepFill_ThruSectionErrorStatus_NotDone:
        di << "Algorithm is not done\n";
        break;
      case BRepFill_ThruSectionErrorStatus_NotSameTopology:
        di << "The input profiles should be all closed or all opened\n";
        break;
      case BRepFill_ThruSectionErrorStatus_ProfilesInconsistent:
        di << "Profiles inconsistent\n";
        break;
      case BRepFill_ThruSectionErrorStatus_WrongUsage:
        di << "Wrong usage of punctual sections\n";
        break;
      case BRepFill_ThruSectionErrorStatus_Null3DCurve:
        di << "Some edges have null 3d curve";
        break;
      case BRepFill_ThruSectionErrorStatus_Failed:
        di << "Algorithm has failed\n";
        break;
      default:
        break;
    }
  }

  return 0;
}

static int mksweep(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 2 && n != 5)
    return 1;
  TopoDS_Shape Spine = DBRep::Get(a[1], TopAbs_WIRE);
  if (Spine.IsNull())
    return 1;
  if (Sweep != nullptr)
  {
    delete Sweep;
    Sweep = nullptr;
  }

  if (n > 2 && n <= 5)
  {
    if (!strcmp(a[2], "-C"))
    {
      ShapeUpgrade_UnifySameDomain aUnif(Spine, true, false, true);

      double anAngTol = 5.;
      double aLinTol  = 0.1;

      if (n == 5)
      {
        anAngTol = Draw::Atof(a[3]);
        aLinTol  = Draw::Atof(a[4]);
      }

      aUnif.SetAngularTolerance(anAngTol * M_PI / 180.);
      aUnif.SetLinearTolerance(aLinTol);
      aUnif.Build();
      Spine = aUnif.Shape();
      if (BRepTest_Objects::IsHistoryNeeded())
      {
        BRepTest_Objects::SetHistory(aUnif.History());
      }
    }
    else
    {
      di << "To correct input spine use 'mksweep wire -C [AngTol LinTol]'\n";
      di << "By default, AngTol = 5, LinTol = 0.1";
      return 1;
    }
  }

  Sweep = new BRepOffsetAPI_MakePipeShell(TopoDS::Wire(Spine));
  return 0;
}

static int setsweep(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 1)
  {
    di << "setsweep options [arg1 [arg2 [...]]] : options are :\n";
    di << "   -FR : Tangent and Normal are given by Frenet trihedron\n";
    di << "   -CF : Tangente is given by Frenet,\n";
    di << "         the Normal is computed to minimize the torsion \n";
    di << "   -DT : discrete trihedron\n";
    di << "   -DX Surf : Tangent and Normal are given by Darboux trihedron,\n";
    di << "       Surf have to be a shell or a face\n";
    di << "   -CN dx dy dz : BiNormal is given by dx dy dz\n";
    di << "   -FX Tx Ty TZ [Nx Ny Nz] : Tangent and Normal are fixed\n";
    di << "   -G guide  0|1(Plan|ACR)  0|1|2(no contact|contact|contact on border) : with guide\n";
    di << "   -SM : Set the maximum degree of approximation\n";
    di << "         paramvalue more then 0 (100 by default)\n";
    di << "   -DM : Set the maximum number of span of approximation\n";
    di << "         paramvalue [1; 14] (11 by default)\n";
    return 0;
  }

  if (Sweep == nullptr)
  {
    di << "You have forgotten the <<mksweep>> command  !\n";
    return 1;
  }
  if (!strcmp(a[1], "-FR"))
  {
    Sweep->SetMode(true);
  }
  else if (!strcmp(a[1], "-CF"))
  {
    Sweep->SetMode(false);
  }
  else if (!strcmp(a[1], "-DT"))
  {
    Sweep->SetDiscreteMode();
  }
  else if (!strcmp(a[1], "-DX"))
  {
    if (n != 3)
    {
      di << "bad arguments !\n";
      return 1;
    }
    TopoDS_Shape Surf;
    Surf = DBRep::Get(a[2], TopAbs_SHAPE);
    if (Surf.IsNull())
    {
      di << a[2] << "is not a shape !\n";
      return 1;
    }
    Sweep->SetMode(Surf);
  }
  else if (!strcmp(a[1], "-CN"))
  {
    if (n != 5)
    {
      di << "bad arguments !\n";
      return 1;
    }
    gp_Dir D(Draw::Atof(a[2]), Draw::Atof(a[3]), Draw::Atof(a[4]));
    Sweep->SetMode(D);
  }
  else if (!strcmp(a[1], "-FX"))
  {
    if ((n != 5) && (n != 8))
    {
      di << "bad arguments !\n";
      return 1;
    }
    gp_Dir D(Draw::Atof(a[2]), Draw::Atof(a[3]), Draw::Atof(a[4]));
    if (n == 8)
    {
      gp_Dir DN(Draw::Atof(a[5]), Draw::Atof(a[6]), Draw::Atof(a[7]));
      gp_Ax2 Axe(gp_Pnt(0., 0., 0.), D, DN);
      Sweep->SetMode(Axe);
    }
    else
    {
      gp_Ax2 Axe(gp_Pnt(0., 0., 0.), D);
      Sweep->SetMode(Axe);
    }
  }
  else if (!strcmp(a[1], "-G"))
  {
    if (n != 5)
    {
      di << "bad arguments !\n";
      return 1;
    }
    else
    {
      TopoDS_Shape Guide                  = DBRep::Get(a[2], TopAbs_WIRE);
      bool         CurvilinearEquivalence = Draw::Atoi(a[3]) != 0;
      int          KeepContact            = Draw::Atoi(a[4]);
      Sweep->SetMode(TopoDS::Wire(Guide),
                     CurvilinearEquivalence,
                     (BRepFill_TypeOfContact)KeepContact);
    }
  }
  else if (!strcmp(a[1], "-DM"))
  {
    if (n != 3)
    {
      di << "bad arguments !\n";
      return 1;
    }

    if (Draw::Atoi(a[2]) > 0 && Draw::Atoi(a[2]) < 15)
    {
      Sweep->SetMaxDegree(Draw::Atoi(a[2]));
    }
    else
    {
      di << " -DM paramvalue must be [1; 14]\n";
      return 1;
    }
  }
  else if (!strcmp(a[1], "-SM"))
  {
    if (n != 3)
    {
      di << "bad arguments !\n";
      return 1;
    }

    if (Draw::Atoi(a[2]) > 0)
    {
      Sweep->SetMaxSegments(Draw::Atoi(a[2]));
    }
    else
    {
      di << " -SM paramvalue must be more then 0\n";
      return 1;
    }
  }

  else
  {
    di << "The option " << a[1] << " is unknown !\n";
    return 1;
  }
  return 0;
}

static int addsweep(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 1)
  {
    di << "addsweep wire/vertex [Vertex] [-T] [-R] [u0 v0 u1 v1 [...[uN vN]]] : options are :\n";
    di << "   -T : the wire/vertex have to be translated to assume contact\n";
    di << "        with the spine\n";
    di << "   -R : the wire have to be rotated to assume orthogonality\n";
    di << "        with the spine's tangent\n";
    return 0;
  }

  if (Sweep == nullptr)
  {
    di << "You have forgotten the <<mksweep>> command  !\n";
    return 1;
  }

  TopoDS_Shape              Section;
  TopoDS_Vertex             Vertex;
  occ::handle<Law_Interpol> thelaw;

  Section = DBRep::Get(a[1], TopAbs_SHAPE);
  if (Section.IsNull()
      || (Section.ShapeType() != TopAbs_WIRE && Section.ShapeType() != TopAbs_VERTEX))
  {
    di << a[1] << " is not a wire and is not a vertex!\n";
    return 1;
  }

  bool HasVertex = false, isT = false, isR = false;

  if (n > 2)
  {
    int cur = 2;

    TopoDS_Shape InputVertex(DBRep::Get(a[cur], TopAbs_VERTEX));
    Vertex = TopoDS::Vertex(InputVertex);
    if (!Vertex.IsNull())
    {
      cur++;
      HasVertex = true;
    }

    if ((n > cur) && !strcmp(a[cur], "-T"))
    {
      cur++;
      isT = true;
    }

    if ((n > cur) && !strcmp(a[cur], "-R"))
    {
      cur++;
      isR = true;
    }

    if (n > cur)
    {
      int nbreal = n - cur;
      if ((nbreal < 4) || (nbreal % 2 != 0))
      {

        di << "bad arguments ! :" << a[cur] << "\n";
      }
      else
      {
        int                          ii, L = nbreal / 2;
        NCollection_Array1<gp_Pnt2d> ParAndRad(1, L);
        for (ii = 1; ii <= L; ii++, cur += 2)
        {
          ParAndRad(ii).SetX(Draw::Atof(a[cur]));
          ParAndRad(ii).SetY(Draw::Atof(a[cur + 1]));
        }
        thelaw = new (Law_Interpol)();
        thelaw->Set(ParAndRad,
                    std::abs(ParAndRad(1).Y() - ParAndRad(L).Y()) < Precision::Confusion());
      }
    }
  }

  if (thelaw.IsNull())
  {
    if (HasVertex)
      Sweep->Add(Section, Vertex, isT, isR);
    else
      Sweep->Add(Section, isT, isR);
  }
  else
  {
    if (HasVertex)
      Sweep->SetLaw(Section, thelaw, Vertex, isT, isR);
    else
      Sweep->SetLaw(Section, thelaw, isT, isR);
  }

  return 0;
}

static int deletesweep(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 2)
  {
    return 1;
  }
  TopoDS_Wire  Section;
  TopoDS_Shape InputShape(DBRep::Get(a[1], TopAbs_SHAPE));
  Section = TopoDS::Wire(InputShape);
  if (Section.IsNull())
  {
    di << a[1] << "is not a wire !\n";
    return 1;
  }

  Sweep->Delete(Section);
  return 0;
}

static int buildsweep(Draw_Interpretor& di, int n, const char** a)
{
  if (n == 1)
  {
    di << "build sweep result [-M/-C/-R] [-S] [tol] : options are\n";
    di << "   -M : Discontinuities are treated by Modification of\n";
    di << "        the sweeping mode : it is the default\n";
    di << "   -C : Discontinuities are treated like Right Corner\n";
    di << "        Treatment is Extent && Intersect\n";
    di << "   -R : Discontinuities are treated like Round Corner\n";
    di << "        Treatment is Intersect and Fill\n";
    di << "   -S : To build a Solid\n";
    return 0;
  }

  bool mksolid = false;
  if (Sweep == nullptr)
  {
    di << "You have forgotten the <<mksweep>> command  !\n";
    return 1;
  }

  if (!Sweep->IsReady())
  {
    di << "You have forgotten the <<addsweep>> command  !\n";
    return 1;
  }

  TopoDS_Shape result;
  int          cur = 2;
  if (n > cur)
  {
    BRepBuilderAPI_TransitionMode Transition = BRepBuilderAPI_Transformed;

    if (!strcmp(a[cur], "-C"))
    {
      Transition = BRepBuilderAPI_RightCorner;
      cur++;
    }
    else if (!strcmp(a[cur], "-R"))
    {
      Transition = BRepBuilderAPI_RoundCorner;
      cur++;
    }
    Sweep->SetTransitionMode(Transition);
  }

  if ((n > cur) && (!strcmp(a[cur], "-S")))
    mksolid = true;

  Sweep->Build();
  if (!Sweep->IsDone())
  {
    di << "Buildsweep : Not Done\n";
    BRepBuilderAPI_PipeError Stat = Sweep->GetStatus();
    if (Stat == BRepBuilderAPI_PlaneNotIntersectGuide)
    {
      di << "Buildsweep : One Plane not intersect the guide\n";
    }
    if (Stat == BRepBuilderAPI_ImpossibleContact)
    {
      di << "BuildSweep : One section can not be in contact with the guide\n";
    }
  }
  else
  {
    if (mksolid)
    {
      bool B;
      B = Sweep->MakeSolid();
      if (!B)
        di << " BuildSweep : It is impossible to make a solid !\n";
    }
    result = Sweep->Shape();
    DBRep::Set(a[1], result);

    if (BRepTest_Objects::IsHistoryNeeded())
    {
      NCollection_List<TopoDS_Shape> aList;
      Sweep->Profiles(aList);
      TopoDS_Shape aSpine = Sweep->Spine();
      aList.Append(aSpine);
      BRepTest_Objects::SetHistory(aList, *Sweep);
    }
  }

  return 0;
}

static int errorsweep(Draw_Interpretor& di, int, const char**)
{
  if (!Sweep->IsDone())
  {
    di << "Sweep is not done\n";
    return 1;
  }
  double ErrorOnSurfaces = Sweep->ErrorOnSurface();
  di << "Tolerance on surfaces = " << ErrorOnSurfaces << "\n";
  return 0;
}

static int simulsweep(Draw_Interpretor& di, int n, const char** a)
{
  if ((n != 3) && (n != 4))
    return 1;

  if (Sweep == nullptr)
  {
    di << "You have forgotten the <<mksweep>> command  !\n";
    return 1;
  }

  if (!Sweep->IsReady())
  {
    di << "You have forgotten the <<addsweep>> command  !\n";
    return 1;
  }

  char                                     name[100];
  NCollection_List<TopoDS_Shape>           List;
  NCollection_List<TopoDS_Shape>::Iterator it;
  int                                      N, ii;
  N = Draw::Atoi(a[2]);

  if (n > 3)
  {
    BRepBuilderAPI_TransitionMode Transition = BRepBuilderAPI_Transformed;

    if (!strcmp(a[3], "-C"))
    {
      Transition = BRepBuilderAPI_RightCorner;
    }
    else if (!strcmp(a[3], "-R"))
    {
      Transition = BRepBuilderAPI_RoundCorner;
    }
    Sweep->SetTransitionMode(Transition);
  }

  Sweep->Simulate(N, List);
  for (ii = 1, it.Initialize(List); it.More(); it.Next(), ii++)
  {
    Sprintf(name, "%s_%d", a[1], ii);
    DBRep::Set(name, it.Value());
  }

  return 0;
}

static int middlepath(Draw_Interpretor&, int n, const char** a)
{
  if (n < 5)
    return 1;

  TopoDS_Shape aShape = DBRep::Get(a[2]);
  if (aShape.IsNull())
    return 1;

  TopoDS_Shape StartShape = DBRep::Get(a[3]);
  if (StartShape.IsNull())
    return 1;

  TopoDS_Shape EndShape = DBRep::Get(a[4]);
  if (EndShape.IsNull())
    return 1;

  BRepOffsetAPI_MiddlePath Builder(aShape, StartShape, EndShape);
  Builder.Build();

  TopoDS_Shape Result = Builder.Shape();
  DBRep::Set(a[1], Result);

  return 0;
}

void BRepTest::SweepCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  DBRep::BasicCommands(theCommands);

  const char* g = "Sweep commands";

  theCommands.Add("prism", "prism result base dx dy dz [Copy | Inf | Seminf]", __FILE__, prism, g);

  theCommands.Add("revol", "revol result base px py pz dx dy dz angle [Copy]", __FILE__, revol, g);

  theCommands.Add("pipe",
                  "pipe result Wire_spine Profile [Mode [Approx]], no args to get help",
                  __FILE__,
                  pipe,
                  g);

  theCommands.Add("evolved", "evolved , no args to get help", __FILE__, evolved, g);

  theCommands.Add("pruled", "pruled result Edge1/Wire1 Edge2/Wire2", __FILE__, pruled, g);

  theCommands.Add("gener", "gener result wire1 wire2 [..wire..]", __FILE__, gener, g);

  theCommands.Add("thrusections",
                  "thrusections [-N] result issolid isruled shape1 shape2 [..shape..] [-safe],\n"
                  "\t\tthe option -N means no check on wires, shapes must be wires or vertices "
                  "(only first or last),\n"
                  "\t\t-safe option allows to prevent the modifying of input shapes",
                  __FILE__,
                  thrusections,
                  g);

  theCommands.Add(
    "mksweep",
    "mksweep wire [-C [AngTol LinTol]]\n"
    "\t\tthe option -C correct input spine by merging smooth connected neighboring edges\n"
    "\t\tthe AngTol is in degrees",
    __FILE__,
    mksweep,
    g);

  theCommands.Add("setsweep", "setsweep  no args to get help", __FILE__, setsweep, g);

  theCommands.Add("addsweep",
                  "addsweep wire [vertex] [-M ] [-C] [auxiilaryshape]:no args to get help",
                  __FILE__,
                  addsweep,
                  g);

  theCommands.Add("deletesweep", "deletesweep wire, To delete a section", __FILE__, deletesweep, g);

  theCommands.Add("buildsweep",
                  "builsweep [r] [option] [Tol] , no args to get help",
                  __FILE__,
                  buildsweep,
                  g);

  theCommands.Add("errorsweep",
                  "errorsweep: returns the summary error on resulting surfaces reached by Sweep",
                  __FILE__,
                  errorsweep,
                  g);

  theCommands.Add("simulsweep", "simulsweep r [n] [option]", __FILE__, simulsweep, g);
  theCommands.Add("geompipe",
                  "geompipe r spineedge profileedge radius [byACR [byrotate]]",
                  __FILE__,
                  geompipe,
                  g);

  theCommands.Add("middlepath",
                  "middlepath res shape startshape endshape",
                  __FILE__,
                  middlepath,
                  g);
}
