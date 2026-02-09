#pragma once

#ifdef OCCT_DEBUG

  #include <Standard_Type.hpp>
  #include <TopAbs_State.hpp>

class TopOpeBRepTool_STATE
{

public:
  TopOpeBRepTool_STATE(const char* name, const bool b = false);
  void Set(const bool b);
  void Set(const TopAbs_State S, const bool b);
  void Set(const bool b, int n, char** a);
  bool Get(const TopAbs_State S);

  bool Get() { return myonetrue; }

  void Print();

private:
  bool myin, myout, myon, myunknown;
  bool myonetrue;
  char myname[100];
};

#endif
