#ifndef _WIN32
  #include <strings.h>
#endif

#ifdef OCCT_DEBUG

  #include <Standard_Type.hpp>

class TopOpeBRep_ALWL
{

public:
  TopOpeBRep_ALWL(const char* name, const bool b = false);

  void Set(const bool b) { mydefdef = mypasdef = mynbpdef = myonetrue = b; }

  void SetDef(const double p)
  {
    mydeflectionmax = p;
    mydefdef        = true;
  }

  void SetPas(const double p)
  {
    mypasUVmax = p;
    mypasdef   = true;
  }

  void SetNbp(const int p)
  {
    mynbpointsmax = p;
    mynbpdef      = true;
  }

  bool GetDef(double& p)
  {
    p = mydeflectionmax;
    return mydefdef;
  }

  bool GetPas(double& p)
  {
    p = mypasUVmax;
    return mypasdef;
  }

  bool GetNbp(int& p)
  {
    p = mynbpointsmax;
    return mynbpdef;
  }

  bool Get() { return myonetrue; }

  void Set(const bool b, int n, char** a);
  void Print();

private:
  double mydeflectionmax;
  bool   mydefdef;

  double mypasUVmax;
  bool   mypasdef;

  int  mynbpointsmax;
  bool mynbpdef;

  bool myonetrue;
  char myname[100];
};

TopOpeBRep_ALWL::TopOpeBRep_ALWL(const char* name, const bool b)
    : mydeflectionmax(0.01),
      mydefdef(false),
      mypasUVmax(0.05),
      mypasdef(false),
      mynbpointsmax(200),
      mynbpdef(false)
{
  strcpy(myname, name);
  Set(b);
}

void TopOpeBRep_ALWL::Set(const bool b, int n, char** a)
{
  if (!n)
    Set(b);
  else
  {
    Set(false);
    for (int i = 0; i < n; i++)
    {
      const char* p = a[i];
      if (!strcasecmp(p, "def"))
      {
        if (++i < n)
          SetDef(Atof(a[i]));
      }
      else if (!strcasecmp(p, "pas"))
      {
        if (++i < n)
          SetPas(Atof(a[i]));
      }
      else if (!strcasecmp(p, "nbp"))
      {
        if (++i < n)
          SetNbp(atoi(a[i]));
      }
    }
  }
  myonetrue = mydefdef || mypasdef || mynbpdef;
  Print();
}

void TopOpeBRep_ALWL::Print()
{
  std::cout << myname << " defined :";
  int n = 0;
  if (mydefdef)
  {
    std::cout << " Def = " << mydeflectionmax;
    n++;
  }
  if (mypasdef)
  {
    std::cout << " Pas = " << mypasUVmax;
    n++;
  }
  if (mynbpdef)
  {
    std::cout << " Nbp = " << mynbpointsmax;
    n++;
  }
  if (!n)
    std::cout << " none";
  std::cout << std::endl;
}

static TopOpeBRep_ALWL TopOpeBRep_contextALWL("LineGeomTool ALWL parameters");

void TopOpeBRep_SetcontextALWL(const bool b, int narg, char** a)
{
  TopOpeBRep_contextALWL.Set(b, narg, a);
}

bool TopOpeBRep_GetcontextALWLNBP(int& n)
{
  bool b = TopOpeBRep_contextALWL.GetNbp(n);
  return b;
}

// #ifdef OCCT_DEBUG
#endif
