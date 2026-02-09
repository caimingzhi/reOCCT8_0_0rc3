#include <TopOpeBRepDS_DataStructure.hpp>
#include <TopOpeBRepDS_Surface.hpp>
#include <TopOpeBRepDS_SurfaceExplorer.hpp>

#define MYDS (*((TopOpeBRepDS_DataStructure*)myDS))

TopOpeBRepDS_SurfaceExplorer::TopOpeBRepDS_SurfaceExplorer()
    : myIndex(1),
      myMax(0),
      myDS(nullptr),
      myFound(false)
{
}

TopOpeBRepDS_SurfaceExplorer::TopOpeBRepDS_SurfaceExplorer(const TopOpeBRepDS_DataStructure& DS,
                                                           const bool FindKeep)
{
  Init(DS, FindKeep);
}

void TopOpeBRepDS_SurfaceExplorer::Init(const TopOpeBRepDS_DataStructure& DS, const bool FindKeep)
{
  myIndex    = 1;
  myMax      = DS.NbSurfaces();
  myDS       = (TopOpeBRepDS_DataStructure*)&DS;
  myFindKeep = FindKeep;
  Find();
}

void TopOpeBRepDS_SurfaceExplorer::Find()
{
  myFound = false;
  while (myIndex <= myMax)
  {
    if (myFindKeep)
    {
      myFound = IsSurfaceKeep(myIndex);
    }
    else
    {
      myFound = IsSurface(myIndex);
    }
    if (myFound)
      break;
    else
      myIndex++;
  }
}

bool TopOpeBRepDS_SurfaceExplorer::More() const
{
  return myFound;
}

void TopOpeBRepDS_SurfaceExplorer::Next()
{
  myIndex++;
  Find();
}

const TopOpeBRepDS_Surface& TopOpeBRepDS_SurfaceExplorer::Surface() const
{
  if (myFound)
  {
    return MYDS.Surface(myIndex);
  }
  else
  {
    return myEmpty;
  }
}

bool TopOpeBRepDS_SurfaceExplorer::IsSurface(const int I) const
{
  bool b = MYDS.mySurfaces.IsBound(I);
  return b;
}

bool TopOpeBRepDS_SurfaceExplorer::IsSurfaceKeep(const int I) const
{
  bool b = MYDS.mySurfaces.IsBound(I);
  if (b)
    b = MYDS.Surface(I).Keep();
  return b;
}

const TopOpeBRepDS_Surface& TopOpeBRepDS_SurfaceExplorer::Surface(const int I) const
{
  if (IsSurface(I))
  {
    return MYDS.Surface(I);
  }
  else
  {
    return myEmpty;
  }
}

int TopOpeBRepDS_SurfaceExplorer::NbSurface()
{
  myIndex = 1;
  myMax   = MYDS.NbSurfaces();
  Find();
  int n = 0;
  for (; More(); Next())
    n++;
  return n;
}

int TopOpeBRepDS_SurfaceExplorer::Index() const
{
  return myIndex;
}
