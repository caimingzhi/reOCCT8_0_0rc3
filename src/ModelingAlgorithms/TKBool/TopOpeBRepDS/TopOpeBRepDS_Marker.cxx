#include <Standard_Type.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepDS_Marker.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopOpeBRepDS_Marker, Standard_Transient)

// #include <TopExp.hpp>
// #include <NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>.hxx>
TopOpeBRepDS_Marker::TopOpeBRepDS_Marker()
{
  Reset();
}

void TopOpeBRepDS_Marker::Reset()
{
  myhe.Nullify();
  myne = 0;
}

void TopOpeBRepDS_Marker::Set(const int ie, const bool b)
{
  Allocate(ie);
  if (ie < 1 || ie > myne)
    return;
  myhe->SetValue(ie, b);
}

void TopOpeBRepDS_Marker::Set(const bool b, const int na, void* const aa)
{
  char** a = (char**)aa;
  //  int ia,ie;
  int ia;
  if (!na)
    myhe->Init(b);
  else
    for (ia = 0; ia < na; ia++)
      Set(atoi(a[ia]), b);
}

bool TopOpeBRepDS_Marker::GetI(const int ie) const
{
  if (myhe.IsNull())
    return false;
  if (ie < 1 || ie > myne)
    return false;
  return myhe->Value(ie);
}

void TopOpeBRepDS_Marker::Allocate(const int n)
{
  bool all  = (n > myne);
  int  nall = n;
  if (all)
  {
    if (myne == 0)
      nall = 1000;
    myhe = new NCollection_HArray1<bool>(0, nall);
    myhe->Init(false);
  }
  if (nall)
    myne = nall;
}
