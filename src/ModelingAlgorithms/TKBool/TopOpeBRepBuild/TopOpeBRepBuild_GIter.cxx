#include <TopOpeBRepBuild_GIter.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>

#define MYGTOPO (*((TopOpeBRepBuild_GTopo*)mypG))

TopOpeBRepBuild_GIter::TopOpeBRepBuild_GIter()
    : myII(0),
      mypG(nullptr)
{
}

TopOpeBRepBuild_GIter::TopOpeBRepBuild_GIter(const TopOpeBRepBuild_GTopo& G)
    : myII(0),
      mypG(nullptr)
{
  Init(G);
}

void TopOpeBRepBuild_GIter::Find()
{
  while (myII <= 8)
  {
    bool b = MYGTOPO.Value(myII);
    if (b)
      break;
    myII++;
  }
}

void TopOpeBRepBuild_GIter::Init()
{
  myII = 0;
  Find();
}

void TopOpeBRepBuild_GIter::Init(const TopOpeBRepBuild_GTopo& G)
{
  mypG = (void*)&G;
  Init();
}

bool TopOpeBRepBuild_GIter::More() const
{
  if (myII <= 8)
  {
    bool b = MYGTOPO.Value(myII);
    return b;
  }
  else
    return false;
}

void TopOpeBRepBuild_GIter::Next()
{
  myII++;
  Find();
}

void TopOpeBRepBuild_GIter::Current(TopAbs_State& s1, TopAbs_State& s2) const
{
  if (!More())
  {
    s1 = s2 = TopAbs_UNKNOWN;
    return;
  }
  int i1, i2;
  MYGTOPO.Index(myII, i1, i2);
  s1 = MYGTOPO.GState(i1);
  s2 = MYGTOPO.GState(i2);
}

void TopOpeBRepBuild_GIter::Dump(Standard_OStream& OS) const
{
  if (!More())
    return;
  TopAbs_State s1, s2;
  Current(s1, s2);
  bool b = MYGTOPO.Value(s1, s2);
  TopOpeBRepBuild_GTopo::DumpSSB(OS, s1, s2, b);
  OS << std::endl;
}
