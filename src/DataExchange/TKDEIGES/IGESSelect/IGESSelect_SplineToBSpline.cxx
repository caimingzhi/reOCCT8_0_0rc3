

#include <IGESData_IGESEntity.hpp>
#include <IGESSelect_SplineToBSpline.hpp>
#include <Interface_CheckIterator.hpp>
#include <Interface_CopyControl.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SplineToBSpline, IFSelect_Transformer)

IGESSelect_SplineToBSpline::IGESSelect_SplineToBSpline(const bool tryC2)
{
  thetryc2 = tryC2;
  thefound = false;
}

bool IGESSelect_SplineToBSpline::OptionTryC2() const
{
  return thetryc2;
}

bool IGESSelect_SplineToBSpline::Perform(const Interface_Graph& G,
                                         const occ::handle<Interface_Protocol>&,
                                         Interface_CheckIterator&               checks,
                                         occ::handle<Interface_InterfaceModel>& newmod)
{
  int nbe  = G.Size();
  thefound = false;
  themap.Nullify();
  for (int i = 1; i <= nbe; i++)
  {
    DeclareAndCast(IGESData_IGESEntity, ent, G.Entity(i));
    if (ent.IsNull())
      continue;
    int it = ent->TypeNumber();
    if (it == 112 || it == 126)
    {
      thefound = true;
#ifdef OCCT_DEBUG
      std::cout << "IGESSelect_SplineToBSpline : n0." << i << (it == 112 ? ", Curve" : ", Surface")
                << " to convert" << std::endl;
#endif
    }
  }
  newmod.Nullify();
  if (!thefound)
    return true;

  checks.CCheck(0)->AddFail("IGESSelect_SplineToBSpline : not yet implemented");
  return false;
}

bool IGESSelect_SplineToBSpline::Updated(const occ::handle<Standard_Transient>& entfrom,
                                         occ::handle<Standard_Transient>&       entto) const
{
  if (!thefound)
  {
    entto = entfrom;
    return true;
  }
  if (themap.IsNull())
    return false;
  return themap->Search(entfrom, entto);
}

TCollection_AsciiString IGESSelect_SplineToBSpline::Label() const
{
  if (thetryc2)
    return TCollection_AsciiString(
      "Convert Spline Forms to BSpline, trying to recover C1-C2 continuity");
  else
    return TCollection_AsciiString("Convert Spline Forms to BSpline");
}
