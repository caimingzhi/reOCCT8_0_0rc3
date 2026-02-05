#include <AdvApp2Var_SysBase.hpp>

static int init_STBAS()
{
  int ICODE = 0;
  // allocation tables are now local, so no global initialization is required
  // Init de LEC IBB IMP
  AdvApp2Var_SysBase::macinit_(&ICODE, &ICODE);
  //
  return 1;
}

//
class STBASLibInit
{
  static int var_STBASLibINIT;
};

int STBASLibInit::var_STBASLibINIT = init_STBAS();
