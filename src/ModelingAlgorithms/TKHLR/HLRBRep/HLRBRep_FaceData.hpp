#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_Surface.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_Integer.hpp>
class HLRAlgo_WiresBlock;
class TopoDS_Face;

class HLRBRep_FaceData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_FaceData();

  //! <Or> is the orientation of the face. <Cl> is true
  //! if the face belongs to a closed volume. <NW> is
  //! the number of wires (or block of edges) of the
  //! face.
  Standard_EXPORT void Set(const TopoDS_Face&       FG,
                           const TopAbs_Orientation Or,
                           const bool               Cl,
                           const int                NW);

  //! Set <NE> the number of edges of the wire number
  //! <WI>.
  Standard_EXPORT void SetWire(const int WI, const int NE);

  //! Set the edge number <EWI> of the wire <WI>.
  Standard_EXPORT void SetWEdge(const int                WI,
                                const int                EWI,
                                const int                EI,
                                const TopAbs_Orientation Or,
                                const bool               OutL,
                                const bool               Inte,
                                const bool               Dble,
                                const bool               IsoL);

  bool Selected() const;

  void Selected(const bool B);

  bool Back() const;

  void Back(const bool B);

  bool Side() const;

  void Side(const bool B);

  bool Closed() const;

  void Closed(const bool B);

  bool Hiding() const;

  void Hiding(const bool B);

  bool Simple() const;

  void Simple(const bool B);

  bool Cut() const;

  void Cut(const bool B);

  bool WithOutL() const;

  void WithOutL(const bool B);

  bool Plane() const;

  void Plane(const bool B);

  bool Cylinder() const;

  void Cylinder(const bool B);

  bool Cone() const;

  void Cone(const bool B);

  bool Sphere() const;

  void Sphere(const bool B);

  bool Torus() const;

  void Torus(const bool B);

  double Size() const;

  void Size(const double S);

  TopAbs_Orientation Orientation() const;

  void Orientation(const TopAbs_Orientation O);

  occ::handle<HLRAlgo_WiresBlock>& Wires();

  HLRBRep_Surface& Geometry();

  float Tolerance() const;

protected:
  enum EMaskFlags
  {
    EMaskOrient   = 15,
    FMaskSelected = 16,
    FMaskBack     = 32,
    FMaskSide     = 64,
    FMaskClosed   = 128,
    FMaskHiding   = 256,
    FMaskSimple   = 512,
    FMaskCut      = 1024,
    FMaskWithOutL = 2048,
    FMaskPlane    = 4096,
    FMaskCylinder = 8192,
    FMaskCone     = 16384,
    FMaskSphere   = 32768,
    FMaskTorus    = 65536
  };

private:
  int                             myFlags;
  occ::handle<HLRAlgo_WiresBlock> myWires;
  HLRBRep_Surface                 myGeometry;
  double                          mySize;
  float                           myTolerance;
};

inline bool HLRBRep_FaceData::Selected() const
{
  return (myFlags & (int)FMaskSelected) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Selected(const bool B)
{
  if (B)
    myFlags |= (int)FMaskSelected;
  else
    myFlags &= ~((int)FMaskSelected);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Back() const
{
  return (myFlags & (int)FMaskBack) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Back(const bool B)
{
  if (B)
    myFlags |= (int)FMaskBack;
  else
    myFlags &= ~((int)FMaskBack);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Side() const
{
  return (myFlags & (int)FMaskSide) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Side(const bool B)
{
  if (B)
    myFlags |= (int)FMaskSide;
  else
    myFlags &= ~((int)FMaskSide);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Closed() const
{
  return (myFlags & (int)FMaskClosed) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Closed(const bool B)
{
  if (B)
    myFlags |= (int)FMaskClosed;
  else
    myFlags &= ~((int)FMaskClosed);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Hiding() const
{
  return (myFlags & (int)FMaskHiding) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Hiding(const bool B)
{
  if (B)
    myFlags |= (int)FMaskHiding;
  else
    myFlags &= ~((int)FMaskHiding);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Simple() const
{
  return (myFlags & (int)FMaskSimple) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Simple(const bool B)
{
  if (B)
    myFlags |= (int)FMaskSimple;
  else
    myFlags &= ~((int)FMaskSimple);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Cut() const
{
  return (myFlags & (int)FMaskCut) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Cut(const bool B)
{
  if (B)
    myFlags |= (int)FMaskCut;
  else
    myFlags &= ~((int)FMaskCut);
}

//=================================================================================================

inline bool HLRBRep_FaceData::WithOutL() const
{
  return (myFlags & (int)FMaskWithOutL) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::WithOutL(const bool B)
{
  if (B)
    myFlags |= (int)FMaskWithOutL;
  else
    myFlags &= ~((int)FMaskWithOutL);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Plane() const
{
  return (myFlags & (int)FMaskPlane) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Plane(const bool B)
{
  if (B)
    myFlags |= (int)FMaskPlane;
  else
    myFlags &= ~((int)FMaskPlane);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Cylinder() const
{
  return (myFlags & (int)FMaskCylinder) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Cylinder(const bool B)
{
  if (B)
    myFlags |= (int)FMaskCylinder;
  else
    myFlags &= ~((int)FMaskCylinder);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Cone() const
{
  return (myFlags & (int)FMaskCone) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Cone(const bool B)
{
  if (B)
    myFlags |= (int)FMaskCone;
  else
    myFlags &= ~((int)FMaskCone);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Sphere() const
{
  return (myFlags & (int)FMaskSphere) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Sphere(const bool B)
{
  if (B)
    myFlags |= (int)FMaskSphere;
  else
    myFlags &= ~((int)FMaskSphere);
}

//=================================================================================================

inline bool HLRBRep_FaceData::Torus() const
{
  return (myFlags & (int)FMaskTorus) != 0;
}

//=================================================================================================

inline void HLRBRep_FaceData::Torus(const bool B)
{
  if (B)
    myFlags |= (int)FMaskTorus;
  else
    myFlags &= ~((int)FMaskTorus);
}

//=================================================================================================

inline double HLRBRep_FaceData::Size() const
{
  return mySize;
}

//=================================================================================================

inline void HLRBRep_FaceData::Size(const double S)
{
  mySize = S;
}

//=================================================================================================

inline TopAbs_Orientation HLRBRep_FaceData::Orientation() const
{
  return ((TopAbs_Orientation)(myFlags & (int)EMaskOrient));
}

//=================================================================================================

inline void HLRBRep_FaceData::Orientation(const TopAbs_Orientation O)
{
  myFlags &= ~(int)EMaskOrient;
  myFlags |= ((int)O & (int)EMaskOrient);
}

//=================================================================================================

inline occ::handle<HLRAlgo_WiresBlock>& HLRBRep_FaceData::Wires()
{
  return myWires;
}

//=================================================================================================

inline HLRBRep_Surface& HLRBRep_FaceData::Geometry()
{
  return myGeometry;
}

//=================================================================================================

inline float HLRBRep_FaceData::Tolerance() const
{
  return myTolerance;
}
