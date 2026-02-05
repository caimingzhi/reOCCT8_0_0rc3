#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopOpeBRepDS_Transition.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! An interference is the description of the
//! attachment of a new geometry on a geometry. For
//! example an intersection point on an Edge or on a
//! Curve.
//!
//! The Interference contains the following data:
//!
//! - Transition: How the interference separates the
//! existing geometry in INSIDE and OUTSIDE.
//!
//! - SupportType: Type of the object supporting the
//! interference. (FACE, EDGE, VERTEX, SURFACE, CURVE).
//!
//! - Support: Index in the data structure of the
//! object supporting the interference.
//!
//! - GeometryType: Type ofthe geometry of the
//! interference (SURFACE, CURVE, POINT).
//!
//! - Geometry: Index in the data structure of the
//! geometry.
class TopOpeBRepDS_Interference : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepDS_Interference();

  Standard_EXPORT TopOpeBRepDS_Interference(const TopOpeBRepDS_Transition& Transition,
                                            const TopOpeBRepDS_Kind        SupportType,
                                            const int                      Support,
                                            const TopOpeBRepDS_Kind        GeometryType,
                                            const int                      Geometry);

  Standard_EXPORT TopOpeBRepDS_Interference(const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT const TopOpeBRepDS_Transition& Transition() const;

  Standard_EXPORT TopOpeBRepDS_Transition& ChangeTransition();

  Standard_EXPORT void Transition(const TopOpeBRepDS_Transition& T);

  //! return GeometryType + Geometry + SupportType + Support
  Standard_EXPORT void GKGSKS(TopOpeBRepDS_Kind& GK, int& G, TopOpeBRepDS_Kind& SK, int& S) const;

  Standard_EXPORT TopOpeBRepDS_Kind SupportType() const;

  Standard_EXPORT int Support() const;

  Standard_EXPORT TopOpeBRepDS_Kind GeometryType() const;

  Standard_EXPORT int Geometry() const;

  Standard_EXPORT void SetGeometry(const int GI);

  Standard_EXPORT void SupportType(const TopOpeBRepDS_Kind ST);

  Standard_EXPORT void Support(const int S);

  Standard_EXPORT void GeometryType(const TopOpeBRepDS_Kind GT);

  Standard_EXPORT void Geometry(const int G);

  Standard_EXPORT bool HasSameSupport(const occ::handle<TopOpeBRepDS_Interference>& Other) const;

  Standard_EXPORT bool HasSameGeometry(const occ::handle<TopOpeBRepDS_Interference>& Other) const;

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_Interference, Standard_Transient)

private:
  TopOpeBRepDS_Transition myTransition;
  int                     mySupport;
  int                     myGeometry;
  TopOpeBRepDS_Kind       mySupportType;
  TopOpeBRepDS_Kind       myGeometryType;
};
