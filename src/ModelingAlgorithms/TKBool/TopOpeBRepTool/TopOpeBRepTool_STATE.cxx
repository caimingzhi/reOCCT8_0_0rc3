#ifdef OCCT_DEBUG

  #include <TopOpeBRepTool_STATE.hpp>

TopOpeBRepTool_STATE::TopOpeBRepTool_STATE(const char* name, const bool b)
    : myin(false),
      myout(false),
      myon(false),
      myunknown(false),
      myonetrue(false)
{
  strcpy(myname, name);
  Set(b);
}

void TopOpeBRepTool_STATE::Set(const bool b)
{
  Set(TopAbs_IN, b);
  Set(TopAbs_OUT, b);
  Set(TopAbs_ON, b);
  Set(TopAbs_UNKNOWN, b);
}

void TopOpeBRepTool_STATE::Set(const TopAbs_State S, const bool b)
{
  switch (S)
  {
    case TopAbs_IN:
      myin = b;
      break;
    case TopAbs_OUT:
      myout = b;
      break;
    case TopAbs_ON:
      myon = b;
      break;
    case TopAbs_UNKNOWN:
      myunknown = b;
      break;
  }
  myonetrue = myin || myout || myon || myunknown;
}

void TopOpeBRepTool_STATE::Set(const bool b, int n, char** a)
{
  if (!n)
    Set(b);
  else
  {
    Set(false);
    for (int i = 0; i < n; i++)
    {
      const char* p = a[i];
      if (!strcmp(p, "IN"))
        Set(TopAbs_IN, b);
      else if (!strcmp(p, "OUT"))
        Set(TopAbs_OUT, b);
      else if (!strcmp(p, "ON"))
        Set(TopAbs_ON, b);
      else if (!strcmp(p, "UNKNOWN"))
        Set(TopAbs_UNKNOWN, b);
    }
    Print();
  }
}

bool TopOpeBRepTool_STATE::Get(const TopAbs_State S)
{
  bool b = false;
  switch (S)
  {
    case TopAbs_IN:
      b = myin;
      break;
    case TopAbs_OUT:
      b = myout;
      break;
    case TopAbs_ON:
      b = myon;
      break;
    case TopAbs_UNKNOWN:
      b = myunknown;
      break;
  }
  return b;
}

void TopOpeBRepTool_STATE::Print()
{
  std::cout << myname << " : ";
  std::cout << "IN/OUT/ON/UNKNOWN = ";
  std::cout << Get(TopAbs_IN) << Get(TopAbs_OUT) << Get(TopAbs_ON) << Get(TopAbs_UNKNOWN);
  std::cout << std::endl;
}

#endif
