#include <BRepAdaptor_Surface.hpp>
#include <Precision.hpp>
#include <Standard_ProgramError.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_BlockBuilder.hpp>
#include <TopOpeBRepBuild_ShellFaceClassifier.hpp>

#ifdef OCCT_DEBUG
extern bool TopOpeBRepBuild_GettraceCHK();
#endif

TopOpeBRepBuild_ShellFaceClassifier::TopOpeBRepBuild_ShellFaceClassifier(
  const TopOpeBRepBuild_BlockBuilder& BB)
    : TopOpeBRepBuild_CompositeClassifier(BB)
{
}

void TopOpeBRepBuild_ShellFaceClassifier::Clear()
{
  mySolidClassifier.Clear();
  myFaceShellMap.Clear();
}

TopAbs_State TopOpeBRepBuild_ShellFaceClassifier::CompareShapes(const TopoDS_Shape& B1,
                                                                const TopoDS_Shape& B2)
{
#ifdef OCCT_DEBUG

#endif

  ResetShape(B1);
  myShell = TopoDS::Shell(B2);
  mySolidClassifier.LoadShell(myShell);

  TopAbs_State state = State();
  return state;
}

TopAbs_State TopOpeBRepBuild_ShellFaceClassifier::CompareElementToShape(const TopoDS_Shape& F,
                                                                        const TopoDS_Shape& SHE)
{
#ifdef OCCT_DEBUG

#endif

  ResetElement(F);
  myShell = TopoDS::Shell(SHE);
  mySolidClassifier.LoadShell(myShell);

  TopAbs_State state = State();
  return state;
}

void TopOpeBRepBuild_ShellFaceClassifier::ResetShape(const TopoDS_Shape& SHE)
{
#ifdef OCCT_DEBUG

#endif

  TopExp_Explorer    ex(SHE, TopAbs_FACE);
  const TopoDS_Face& F = TopoDS::Face(ex.Current());
  ResetElement(F);
}

void TopOpeBRepBuild_ShellFaceClassifier::ResetElement(const TopoDS_Shape& F)
{
  const TopAbs_ShapeEnum t = F.ShapeType();

  myFirstCompare = true;

  TopExp_Explorer ex(F, TopAbs_VERTEX);
  if (ex.More())
  {
    const TopoDS_Vertex& V = TopoDS::Vertex(ex.Current());
    myPoint3d              = BRep_Tool::Pnt(V);
  }
  else
  {
    if (t == TopAbs_FACE)
    {
      BRepAdaptor_Surface BAS(TopoDS::Face(F));
      myPoint3d = BAS.Value(.5 * (BAS.FirstUParameter() + BAS.LastUParameter()),
                            .5 * (BAS.FirstVParameter() + BAS.LastVParameter()));
    }
    else
    {
      myPoint3d.SetCoord(0., 0., 0.);
    }
  }
}

bool TopOpeBRepBuild_ShellFaceClassifier::CompareElement(const TopoDS_Shape& F)
{
#ifdef OCCT_DEBUG

#endif
  bool bRet = true;

  if (myFirstCompare)
  {
    bool found = myFaceShellMap.IsBound(F);
    if (!found)
    {

      myBuilder.MakeShell(myShell);
      myBuilder.Add(myShell, F);
      myFaceShellMap.Bind(F, myShell);
    }
    else
    {

      TopoDS_Shape sbid = myFaceShellMap.Find(F);
      myShell           = TopoDS::Shell(sbid);
      bRet              = !bRet;
    }
    myFirstCompare = false;
  }
  else
  {

    myBuilder.Add(myShell, F);
  }
  return bRet;
}

#ifdef OCCT_DEBUG
  #include <BRepTools.hpp>
  #include <BRep_Builder.hpp>
  #include <TCollection_AsciiString.hpp>
static int STATIC_ishell = 0;
#endif

TopAbs_State TopOpeBRepBuild_ShellFaceClassifier::State()
{
  TopAbs_State state;
  double       tol3d = Precision::Confusion();

#ifdef OCCT_DEBUG
  if (TopOpeBRepBuild_GettraceCHK())
  {
    STATIC_ishell++;
    TCollection_AsciiString home("/home/wb/mdl/gti/prod/TTOPOPE/src/test/data/");
    TCollection_AsciiString sname("shell_");
    sname = home + sname + STATIC_ishell;
    TCollection_AsciiString vname("vertex_");
    vname = home + vname + STATIC_ishell;
    BRep_Builder  B;
    TopoDS_Vertex V;
    B.MakeVertex(V, myPoint3d, tol3d);
    std::cout << "TopOpeBRepBuild_ShellFaceClassifier : write shell " << sname;
    std::cout << " vertex " << vname << std::endl;
    BRepTools::Write(myShell, sname.ToCString());
    BRepTools::Write(V, vname.ToCString());
  }
#endif
  mySolidClassifier.Classify(myShell, myPoint3d, tol3d);
  state = mySolidClassifier.State();
  return state;
}
