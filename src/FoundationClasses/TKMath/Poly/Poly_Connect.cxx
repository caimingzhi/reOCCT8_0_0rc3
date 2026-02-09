#include <Poly_Connect.hpp>

#include <NCollection_IncAllocator.hpp>
#include <Poly_Triangulation.hpp>

struct polyedge
{
  polyedge* next;
  int       nt[2];
  int       nn[2];
  int       nd;
  DEFINE_STANDARD_ALLOC
};

Poly_Connect::Poly_Connect()
    : mytr(0),
      myfirst(0),
      mynode(0),
      myothernode(0),
      mysense(false),
      mymore(false)
{
}

Poly_Connect::Poly_Connect(const occ::handle<Poly_Triangulation>& theTriangulation)
    : myTriangulation(theTriangulation),
      myTriangles(1, theTriangulation->NbNodes()),
      myAdjacents(1, 6 * theTriangulation->NbTriangles()),
      mytr(0),
      myfirst(0),
      mynode(0),
      myothernode(0),
      mysense(false),
      mymore(false)
{
  Load(theTriangulation);
}

void Poly_Connect::Load(const occ::handle<Poly_Triangulation>& theTriangulation)
{
  myTriangulation = theTriangulation;
  mytr            = 0;
  myfirst         = 0;
  mynode          = 0;
  myothernode     = 0;
  mysense         = false;
  mymore          = false;

  const int aNbNodes = myTriangulation->NbNodes();
  const int aNbTris  = myTriangulation->NbTriangles();
  {
    const int aNbAdjs = 6 * aNbTris;
    if (myTriangles.Size() != aNbNodes)
    {
      myTriangles.Resize(1, aNbNodes, false);
    }
    if (myAdjacents.Size() != aNbAdjs)
    {
      myAdjacents.Resize(1, aNbAdjs, false);
    }
  }

  myTriangles.Init(0);
  myAdjacents.Init(0);

  NCollection_Array1<polyedge*> anEdges(1, aNbNodes);
  anEdges.Init(nullptr);

  occ::handle<NCollection_IncAllocator> anIncAlloc = new NCollection_IncAllocator();

  NCollection_Vec3<int> aTriNodes;
  NCollection_Vec2<int> anEdgeNodes;
  for (int aTriIter = 1; aTriIter <= aNbTris; ++aTriIter)
  {

    myTriangulation->Triangle(aTriIter).Get(aTriNodes[0], aTriNodes[1], aTriNodes[2]);

    myTriangles.SetValue(aTriNodes[0], aTriIter);
    myTriangles.SetValue(aTriNodes[1], aTriIter);
    myTriangles.SetValue(aTriNodes[2], aTriIter);

    for (int aNodeInTri = 0; aNodeInTri < 3; ++aNodeInTri)
    {
      const int aNodeNext = (aNodeInTri + 1) % 3;
      if (aTriNodes[aNodeInTri] < aTriNodes[aNodeNext])
      {
        anEdgeNodes[0] = aTriNodes[aNodeInTri];
        anEdgeNodes[1] = aTriNodes[aNodeNext];
      }
      else
      {
        anEdgeNodes[0] = aTriNodes[aNodeNext];
        anEdgeNodes[1] = aTriNodes[aNodeInTri];
      }

      polyedge* ced = anEdges[anEdgeNodes[0]];
      for (; ced != nullptr; ced = ced->next)
      {

        if (ced->nd == anEdgeNodes[1])
        {

          ced->nt[1] = aTriIter;
          ced->nn[1] = aTriNodes[3 - aNodeInTri - aNodeNext];
          break;
        }
      }

      if (ced == nullptr)
      {

        ced                     = (polyedge*)anIncAlloc->Allocate(sizeof(polyedge));
        ced->next               = anEdges[anEdgeNodes[0]];
        anEdges[anEdgeNodes[0]] = ced;
        ced->nd                 = anEdgeNodes[1];
        ced->nt[0]              = aTriIter;
        ced->nn[0]              = aTriNodes[3 - aNodeInTri - aNodeNext];
        ced->nt[1]              = 0;
        ced->nn[1]              = 0;
      }
    }
  }

  int anAdjIndex = 1;
  for (int aTriIter = 1; aTriIter <= aNbTris; ++aTriIter)
  {

    myTriangulation->Triangle(aTriIter).Get(aTriNodes[0], aTriNodes[1], aTriNodes[2]);

    for (int aNodeInTri = 0; aNodeInTri < 3; ++aNodeInTri)
    {
      const int aNodeNext = (aNodeInTri + 1) % 3;
      if (aTriNodes[aNodeInTri] < aTriNodes[aNodeNext])
      {
        anEdgeNodes[0] = aTriNodes[aNodeInTri];
        anEdgeNodes[1] = aTriNodes[aNodeNext];
      }
      else
      {
        anEdgeNodes[0] = aTriNodes[aNodeNext];
        anEdgeNodes[1] = aTriNodes[aNodeInTri];
      }

      const polyedge* ced = anEdges[anEdgeNodes[0]];
      while (ced->nd != anEdgeNodes[1])
      {
        ced = ced->next;
      }

      const int l = ced->nt[0] == aTriIter ? 1 : 0;

      myAdjacents.SetValue(anAdjIndex, ced->nt[l]);
      myAdjacents.SetValue(anAdjIndex + 3, ced->nn[l]);
      ++anAdjIndex;
    }
    anAdjIndex += 3;
  }
}

void Poly_Connect::Initialize(const int N)
{
  mynode  = N;
  myfirst = Triangle(N);
  mytr    = myfirst;
  mysense = true;
  mymore  = (myfirst != 0);
  myPassedTr.Clear();
  myPassedTr.Add(mytr);
  if (mymore)
  {
    int i, no[3];
    myTriangulation->Triangle(myfirst).Get(no[0], no[1], no[2]);
    for (i = 0; i < 3; i++)
      if (no[i] == mynode)
        break;
    myothernode = no[(i + 2) % 3];
  }
}

void Poly_Connect::Next()
{
  int i, j;
  int n[3];
  int t[3];
  Triangles(mytr, t[0], t[1], t[2]);
  if (mysense)
  {
    for (i = 0; i < 3; i++)
    {
      if (t[i] != 0)
      {
        myTriangulation->Triangle(t[i]).Get(n[0], n[1], n[2]);
        for (j = 0; j < 3; j++)
        {
          if ((n[j] == mynode) && (n[(j + 1) % 3] == myothernode))
          {
            mytr        = t[i];
            myothernode = n[(j + 2) % 3];
            mymore      = !myPassedTr.Contains(mytr);
            myPassedTr.Add(mytr);
            return;
          }
        }
      }
    }

    myTriangulation->Triangle(myfirst).Get(n[0], n[1], n[2]);
    for (i = 0; i < 3; i++)
      if (n[i] == mynode)
        break;
    myothernode = n[(i + 1) % 3];
    mysense     = false;
    mytr        = myfirst;
    Triangles(mytr, t[0], t[1], t[2]);
  }
  if (!mysense)
  {
    for (i = 0; i < 3; i++)
    {
      if (t[i] != 0)
      {
        myTriangulation->Triangle(t[i]).Get(n[0], n[1], n[2]);
        for (j = 0; j < 3; j++)
        {
          if ((n[j] == mynode) && (n[(j + 2) % 3] == myothernode))
          {
            mytr        = t[i];
            myothernode = n[(j + 1) % 3];
            mymore      = !myPassedTr.Contains(mytr);
            myPassedTr.Add(mytr);
            return;
          }
        }
      }
    }
  }
  mymore = false;
}
