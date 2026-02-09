#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Bnd_Box.hpp>
#include <IntPolyh_ArrayOfPoints.hpp>
#include <IntPolyh_ArrayOfEdges.hpp>
#include <IntPolyh_ArrayOfTriangles.hpp>
#include <NCollection_List.hpp>
#include <IntPolyh_Couple.hpp>
#include <NCollection_Array1.hpp>
#include <IntPolyh_ArrayOfPointNormal.hpp>
#include <IntPolyh_ArrayOfSectionLines.hpp>
#include <IntPolyh_ArrayOfTangentZones.hpp>

class IntPolyh_StartPoint;

class IntPolyh_MaillageAffinage
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPolyh_MaillageAffinage(const occ::handle<Adaptor3d_Surface>& S1,
                                            const int                             NbSU1,
                                            const int                             NbSV1,
                                            const occ::handle<Adaptor3d_Surface>& S2,
                                            const int                             NbSU2,
                                            const int                             NbSV2,
                                            const int                             PRINT);

  Standard_EXPORT IntPolyh_MaillageAffinage(const occ::handle<Adaptor3d_Surface>& S1,
                                            const occ::handle<Adaptor3d_Surface>& S2,
                                            const int                             PRINT);

  Standard_EXPORT void MakeSampling(const int                   SurfID,
                                    NCollection_Array1<double>& theUPars,
                                    NCollection_Array1<double>& theVPars);

  Standard_EXPORT void FillArrayOfPnt(const int SurfID);

  Standard_EXPORT void FillArrayOfPnt(const int SurfID, const bool isShiftFwd);

  Standard_EXPORT void FillArrayOfPnt(const int                         SurfID,
                                      const NCollection_Array1<double>& Upars,
                                      const NCollection_Array1<double>& Vpars,
                                      const double*                     theDeflTol = nullptr);

  Standard_EXPORT void FillArrayOfPnt(const int                         SurfID,
                                      const bool                        isShiftFwd,
                                      const NCollection_Array1<double>& Upars,
                                      const NCollection_Array1<double>& Vpars,
                                      const double*                     theDeflTol = nullptr);

  Standard_EXPORT void FillArrayOfPnt(const int                          SurfID,
                                      const bool                         isShiftFwd,
                                      const IntPolyh_ArrayOfPointNormal& thePoints,
                                      const NCollection_Array1<double>&  theUPars,
                                      const NCollection_Array1<double>&  theVPars,
                                      const double                       theDeflTol);

  Standard_EXPORT void CommonBox();

  Standard_EXPORT void CommonBox(const Bnd_Box& B1,
                                 const Bnd_Box& B2,
                                 double&        xMin,
                                 double&        yMin,
                                 double&        zMin,
                                 double&        xMax,
                                 double&        yMax,
                                 double&        zMax);

  Standard_EXPORT void FillArrayOfEdges(const int SurfID);

  Standard_EXPORT void FillArrayOfTriangles(const int SurfID);

  Standard_EXPORT void CommonPartRefinement();

  Standard_EXPORT void LocalSurfaceRefinement(const int SurfId);

  Standard_EXPORT void ComputeDeflections(const int SurfID);

  Standard_EXPORT void TrianglesDeflectionsRefinementBSB();

  Standard_EXPORT int TriContact(const IntPolyh_Point& P1,
                                 const IntPolyh_Point& P2,
                                 const IntPolyh_Point& P3,
                                 const IntPolyh_Point& Q1,
                                 const IntPolyh_Point& Q2,
                                 const IntPolyh_Point& Q3,
                                 double&               Angle) const;

  Standard_EXPORT int TriangleEdgeContact(const int                TriSurfID,
                                          const int                EdgeIndice,
                                          const IntPolyh_Triangle& Tri1,
                                          const IntPolyh_Triangle& Tri2,
                                          const IntPolyh_Point&    P1,
                                          const IntPolyh_Point&    P2,
                                          const IntPolyh_Point&    P3,
                                          const IntPolyh_Point&    C1,
                                          const IntPolyh_Point&    C2,
                                          const IntPolyh_Point&    C3,
                                          const IntPolyh_Point&    Pe1,
                                          const IntPolyh_Point&    Pe2,
                                          const IntPolyh_Point&    E,
                                          const IntPolyh_Point&    N,
                                          IntPolyh_StartPoint&     SP1,
                                          IntPolyh_StartPoint&     SP2) const;

  Standard_EXPORT int StartingPointsResearch(const int            T1,
                                             const int            T2,
                                             IntPolyh_StartPoint& SP1,
                                             IntPolyh_StartPoint& SP2) const;

  Standard_EXPORT int NextStartingPointsResearch(const int                  T1,
                                                 const int                  T2,
                                                 const IntPolyh_StartPoint& SPInit,
                                                 IntPolyh_StartPoint&       SPNext) const;

  Standard_EXPORT int TriangleCompare();

  Standard_EXPORT int StartPointsChain(IntPolyh_ArrayOfSectionLines& TSectionLines,
                                       IntPolyh_ArrayOfTangentZones& TTangentZones);

  Standard_EXPORT int GetNextChainStartPoint(const IntPolyh_StartPoint&    SPInit,
                                             IntPolyh_StartPoint&          SPNext,
                                             IntPolyh_SectionLine&         MySectionLine,
                                             IntPolyh_ArrayOfTangentZones& TTangentZones,
                                             const bool                    Prepend = false);

  Standard_EXPORT const IntPolyh_ArrayOfPoints& GetArrayOfPoints(const int SurfID) const;

  Standard_EXPORT const IntPolyh_ArrayOfEdges& GetArrayOfEdges(const int SurfID) const;

  Standard_EXPORT const IntPolyh_ArrayOfTriangles& GetArrayOfTriangles(const int SurfID) const;

  Standard_EXPORT int GetFinTE(const int SurfID) const;

  Standard_EXPORT int GetFinTT(const int SurfID) const;

  Standard_EXPORT Bnd_Box GetBox(const int SurfID) const;

  Standard_EXPORT NCollection_List<IntPolyh_Couple>& GetCouples();

  Standard_EXPORT void SetEnlargeZone(const bool EnlargeZone);

  Standard_EXPORT bool GetEnlargeZone() const;

  Standard_EXPORT double GetMinDeflection(const int SurfID) const;

  Standard_EXPORT double GetMaxDeflection(const int SurfID) const;

private:
  occ::handle<Adaptor3d_Surface> MaSurface1;
  occ::handle<Adaptor3d_Surface> MaSurface2;
  Bnd_Box                        MyBox1;
  Bnd_Box                        MyBox2;
  int                            NbSamplesU1;
  int                            NbSamplesU2;
  int                            NbSamplesV1;
  int                            NbSamplesV2;
  double                         FlecheMax1;
  double                         FlecheMax2;
  double                         FlecheMin1;
  double                         FlecheMin2;

  IntPolyh_ArrayOfPoints    TPoints1;
  IntPolyh_ArrayOfPoints    TPoints2;
  IntPolyh_ArrayOfEdges     TEdges1;
  IntPolyh_ArrayOfEdges     TEdges2;
  IntPolyh_ArrayOfTriangles TTriangles1;
  IntPolyh_ArrayOfTriangles TTriangles2;

  NCollection_List<IntPolyh_Couple> TTrianglesContacts;

  bool myEnlargeZone;
};
