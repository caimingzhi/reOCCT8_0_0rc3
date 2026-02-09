#pragma once

#include <Adaptor3d_TopolTool.hpp>
#include <Adaptor3d_Surface.hpp>

class gp_Pnt2d;
class gp_Pnt;

class IntTools_TopolTool : public Adaptor3d_TopolTool
{

public:
  Standard_EXPORT IntTools_TopolTool();

  Standard_EXPORT IntTools_TopolTool(const occ::handle<Adaptor3d_Surface>& theSurface);

  Standard_EXPORT void Initialize() override;

  Standard_EXPORT void Initialize(const occ::handle<Adaptor3d_Surface>& theSurface) override;

  Standard_EXPORT void ComputeSamplePoints() override;

  Standard_EXPORT int NbSamplesU() override;

  Standard_EXPORT int NbSamplesV() override;

  Standard_EXPORT int NbSamples() override;

  Standard_EXPORT void SamplePoint(const int Index, gp_Pnt2d& P2d, gp_Pnt& P3d) override;

  Standard_EXPORT void SamplePnts(const double theDefl,
                                  const int    theNUmin,
                                  const int    theNVmin) override;

  DEFINE_STANDARD_RTTIEXT(IntTools_TopolTool, Adaptor3d_TopolTool)

private:
  int    myNbSmplU;
  int    myNbSmplV;
  double myU0;
  double myV0;
  double myDU;
  double myDV;
};
