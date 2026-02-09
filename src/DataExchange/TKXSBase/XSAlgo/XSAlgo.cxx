#include <XSAlgo.hpp>

#include <Interface_Static.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeProcess_OperLibrary.hpp>
#include <XSAlgo_AlgoContainer.hpp>

static occ::handle<XSAlgo_AlgoContainer> theContainer;

void XSAlgo::Init()
{
  static bool init = false;
  if (init)
    return;
  init = true;
  ShapeAlgo::Init();
  theContainer = new XSAlgo_AlgoContainer;

  Interface_Static::Standards();

  Interface_Static::Init("XSTEP", "read.stdsameparameter.mode", 'e', "");
  Interface_Static::Init("XSTEP", "read.stdsameparameter.mode", '&', "ematch 0");
  Interface_Static::Init("XSTEP", "read.stdsameparameter.mode", '&', "eval Off");
  Interface_Static::Init("XSTEP", "read.stdsameparameter.mode", '&', "eval On");
  Interface_Static::SetIVal("read.stdsameparameter.mode", 0);

  Interface_Static::Init("XSTEP", "xstep.cascade.unit", 'e', "");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "enum 1");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval INCH");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval MM");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval ??");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval FT");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval MI");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval M");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval KM");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval MIL");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval UM");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval CM");
  Interface_Static::Init("XSTEP", "xstep.cascade.unit", '&', "eval UIN");
  Interface_Static::SetCVal("xstep.cascade.unit", "MM");

  ShapeProcess_OperLibrary::Init();
}

void XSAlgo::SetAlgoContainer(const occ::handle<XSAlgo_AlgoContainer>& aContainer)
{
  theContainer = aContainer;
}

occ::handle<XSAlgo_AlgoContainer> XSAlgo::AlgoContainer()
{
  return theContainer;
}
