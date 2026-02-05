#include <Draw_Display.hpp>
#include <Draw_Drawable3D.hpp>
#include <HLRTest_OutLiner.hpp>
#include <HLRTopoBRep_OutLiner.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRTest_OutLiner, Draw_Drawable3D)

//=================================================================================================

HLRTest_OutLiner::HLRTest_OutLiner(const TopoDS_Shape& S)
{
  myOutLiner = new HLRTopoBRep_OutLiner(S);
}

//=================================================================================================

void HLRTest_OutLiner::DrawOn(Draw_Display& /*dis*/) const {}

//=================================================================================================

occ::handle<Draw_Drawable3D> HLRTest_OutLiner::Copy() const
{
  occ::handle<HLRTest_OutLiner> O = new HLRTest_OutLiner(myOutLiner->OriginalShape());
  return O;
}

//=================================================================================================

void HLRTest_OutLiner::Dump(Standard_OStream& S) const
{
  S << "This is an outliner" << std::endl;
}

//=================================================================================================

void HLRTest_OutLiner::Whatis(Draw_Interpretor& I) const
{
  I << "outliner";
}
