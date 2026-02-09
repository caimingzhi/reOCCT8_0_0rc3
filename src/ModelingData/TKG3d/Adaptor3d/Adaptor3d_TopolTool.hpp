#pragma once

#include <Adaptor2d_Line2d.hpp>
#include <Adaptor3d_HVertex.hpp>
#include <Adaptor3d_Surface.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopAbs_State.hpp>
#include <TopAbs_Orientation.hpp>

class Adaptor3d_HVertex;

class Adaptor3d_TopolTool : public Standard_Transient
{

public:
  Standard_EXPORT Adaptor3d_TopolTool();

  Standard_EXPORT Adaptor3d_TopolTool(const occ::handle<Adaptor3d_Surface>& Surface);

  Standard_EXPORT virtual void Initialize();

  Standard_EXPORT virtual void Initialize(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT virtual void Initialize(const occ::handle<Adaptor2d_Curve2d>& Curve);

  Standard_EXPORT virtual void Init();

  Standard_EXPORT virtual bool More();

  Standard_EXPORT virtual occ::handle<Adaptor2d_Curve2d> Value();

  Standard_EXPORT virtual void Next();

  Standard_EXPORT virtual void InitVertexIterator();

  Standard_EXPORT virtual bool MoreVertex();

  Standard_EXPORT virtual occ::handle<Adaptor3d_HVertex> Vertex();

  Standard_EXPORT virtual void NextVertex();

  Standard_EXPORT virtual TopAbs_State Classify(const gp_Pnt2d& P,
                                                const double    Tol,
                                                const bool      ReacdreOnPeriodic = true);

  Standard_EXPORT virtual bool IsThePointOn(const gp_Pnt2d& P,
                                            const double    Tol,
                                            const bool      ReacdreOnPeriodic = true);

  Standard_EXPORT virtual TopAbs_Orientation Orientation(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT virtual TopAbs_Orientation Orientation(const occ::handle<Adaptor3d_HVertex>& V);

  Standard_EXPORT virtual bool Identical(const occ::handle<Adaptor3d_HVertex>& V1,
                                         const occ::handle<Adaptor3d_HVertex>& V2);

  Standard_EXPORT virtual bool Has3d() const;

  Standard_EXPORT virtual double Tol3d(const occ::handle<Adaptor2d_Curve2d>& C) const;

  Standard_EXPORT virtual double Tol3d(const occ::handle<Adaptor3d_HVertex>& V) const;

  Standard_EXPORT virtual gp_Pnt Pnt(const occ::handle<Adaptor3d_HVertex>& V) const;

  Standard_EXPORT virtual void ComputeSamplePoints();

  Standard_EXPORT virtual int NbSamplesU();

  Standard_EXPORT virtual int NbSamplesV();

  Standard_EXPORT virtual int NbSamples();

  Standard_EXPORT void UParameters(NCollection_Array1<double>& theArray) const;

  Standard_EXPORT void VParameters(NCollection_Array1<double>& theArray) const;

  Standard_EXPORT virtual void SamplePoint(const int Index, gp_Pnt2d& P2d, gp_Pnt& P3d);

  Standard_EXPORT virtual bool DomainIsInfinite();

  Standard_EXPORT virtual void* Edge() const;

  Standard_EXPORT virtual void SamplePnts(const double theDefl,
                                          const int    theNUmin,
                                          const int    theNVmin);

  Standard_EXPORT virtual void BSplSamplePnts(const double theDefl,
                                              const int    theNUmin,
                                              const int    theNVmin);

  Standard_EXPORT virtual bool IsUniformSampling() const;

  Standard_EXPORT static void GetConeApexParam(const gp_Cone& theC, double& theU, double& theV);

  DEFINE_STANDARD_RTTIEXT(Adaptor3d_TopolTool, Standard_Transient)

protected:
  occ::handle<Adaptor3d_Surface>           myS;
  int                                      myNbSamplesU;
  int                                      myNbSamplesV;
  occ::handle<NCollection_HArray1<double>> myUPars;
  occ::handle<NCollection_HArray1<double>> myVPars;

private:
  int                            nbRestr;
  int                            idRestr;
  double                         Uinf;
  double                         Usup;
  double                         Vinf;
  double                         Vsup;
  occ::handle<Adaptor2d_Line2d>  myRestr[4];
  int                            nbVtx;
  int                            idVtx;
  occ::handle<Adaptor3d_HVertex> myVtx[2];
};
