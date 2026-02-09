#pragma once

#include <HLRAlgo_Projector.hpp>
#include <Draw_Drawable3D.hpp>
#include <Draw_Interpretor.hpp>

class HLRTest_Projector : public Draw_Drawable3D
{
  DEFINE_STANDARD_RTTIEXT(HLRTest_Projector, Draw_Drawable3D)
  Draw_Drawable3D_FACTORY
public:
  Standard_EXPORT HLRTest_Projector(const HLRAlgo_Projector& P);

  const HLRAlgo_Projector& Projector() const { return myProjector; }

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  Standard_EXPORT void Save(Standard_OStream& theStream) const override;

  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

private:
  HLRAlgo_Projector myProjector;
};
