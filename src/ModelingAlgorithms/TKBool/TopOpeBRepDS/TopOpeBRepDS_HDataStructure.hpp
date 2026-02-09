#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopOpeBRepDS_DataStructure.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Config.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class TopOpeBRepDS_Surface;
class TopOpeBRepDS_CurveIterator;
class TopOpeBRepDS_Curve;
class TopOpeBRepDS_PointIterator;
class TopOpeBRepDS_Point;
class TopOpeBRepDS_SurfaceIterator;
class TopOpeBRepDS_Interference;

class TopOpeBRepDS_HDataStructure : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepDS_HDataStructure();

  Standard_EXPORT void AddAncestors(const TopoDS_Shape& S);

  Standard_EXPORT void AddAncestors(const TopoDS_Shape&    S,
                                    const TopAbs_ShapeEnum T1,
                                    const TopAbs_ShapeEnum T2);

  Standard_EXPORT void ChkIntg();

  Standard_EXPORT const TopOpeBRepDS_DataStructure& DS() const;

  Standard_EXPORT TopOpeBRepDS_DataStructure& ChangeDS();

  Standard_EXPORT int NbSurfaces() const;

  Standard_EXPORT int NbCurves() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT const TopOpeBRepDS_Surface& Surface(const int I) const;

  Standard_EXPORT TopOpeBRepDS_CurveIterator SurfaceCurves(const int I) const;

  Standard_EXPORT const TopOpeBRepDS_Curve& Curve(const int I) const;

  Standard_EXPORT TopOpeBRepDS_Curve& ChangeCurve(const int I);

  Standard_EXPORT TopOpeBRepDS_PointIterator CurvePoints(const int I) const;

  Standard_EXPORT const TopOpeBRepDS_Point& Point(const int I) const;

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT const TopoDS_Shape& Shape(const int I, const bool FindKeep = true) const;

  Standard_EXPORT int Shape(const TopoDS_Shape& S, const bool FindKeep = true) const;

  Standard_EXPORT bool HasGeometry(const TopoDS_Shape& S) const;

  Standard_EXPORT bool HasShape(const TopoDS_Shape& S, const bool FindKeep = true) const;

  Standard_EXPORT bool HasSameDomain(const TopoDS_Shape& S, const bool FindKeep = true) const;

  Standard_EXPORT NCollection_List<TopoDS_Shape>::Iterator SameDomain(const TopoDS_Shape& S) const;

  Standard_EXPORT TopOpeBRepDS_Config SameDomainOrientation(const TopoDS_Shape& S) const;

  Standard_EXPORT int SameDomainReference(const TopoDS_Shape& S) const;

  Standard_EXPORT TopOpeBRepDS_SurfaceIterator SolidSurfaces(const TopoDS_Shape& S) const;

  Standard_EXPORT TopOpeBRepDS_SurfaceIterator SolidSurfaces(const int I) const;

  Standard_EXPORT TopOpeBRepDS_CurveIterator FaceCurves(const TopoDS_Shape& F) const;

  Standard_EXPORT TopOpeBRepDS_CurveIterator FaceCurves(const int I) const;

  Standard_EXPORT TopOpeBRepDS_PointIterator EdgePoints(const TopoDS_Shape& E) const;

  Standard_EXPORT int MakeCurve(const TopOpeBRepDS_Curve& C1, TopOpeBRepDS_Curve& C2);

  Standard_EXPORT void RemoveCurve(const int iC);

  Standard_EXPORT int NbGeometry(const TopOpeBRepDS_Kind K) const;

  Standard_EXPORT int NbTopology(const TopOpeBRepDS_Kind K) const;

  Standard_EXPORT int NbTopology() const;

  Standard_EXPORT bool EdgesSameParameter() const;

  Standard_EXPORT void SortOnParameter(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&       L2) const;

  Standard_EXPORT void SortOnParameter(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L) const;

  Standard_EXPORT void MinMaxOnParameter(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L,
    double&                                                         Min,
    double&                                                         Max) const;

  Standard_EXPORT bool ScanInterfList(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
    const TopOpeBRepDS_Point&                                           PDS) const;

  Standard_EXPORT bool GetGeometry(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
    const TopOpeBRepDS_Point&                                           PDS,
    int&                                                                G,
    TopOpeBRepDS_Kind&                                                  K) const;

  Standard_EXPORT void StoreInterference(
    const occ::handle<TopOpeBRepDS_Interference>&             I,
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
    const TCollection_AsciiString&                            str = "");

  Standard_EXPORT void StoreInterference(const occ::handle<TopOpeBRepDS_Interference>& I,
                                         const TopoDS_Shape&                           S,
                                         const TCollection_AsciiString&                str = "");

  Standard_EXPORT void StoreInterference(const occ::handle<TopOpeBRepDS_Interference>& I,
                                         const int                                     IS,
                                         const TCollection_AsciiString&                str = "");

  Standard_EXPORT void StoreInterferences(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
    const TopoDS_Shape&                                             S,
    const TCollection_AsciiString&                                  str = "");

  Standard_EXPORT void StoreInterferences(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
    const int                                                       IS,
    const TCollection_AsciiString&                                  str = "");

  Standard_EXPORT void ClearStoreInterferences(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
    const TopoDS_Shape&                                             S,
    const TCollection_AsciiString&                                  str = "");

  Standard_EXPORT void ClearStoreInterferences(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
    const int                                                       IS,
    const TCollection_AsciiString&                                  str = "");

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_HDataStructure, Standard_Transient)

private:
  TopOpeBRepDS_DataStructure myDS;
};
