#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_CheckStatus.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Transient.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_OStream.hpp>
#include <Standard_CString.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopOpeBRepDS_HDataStructure;

class TopOpeBRepDS_Check : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepDS_Check();

  Standard_EXPORT TopOpeBRepDS_Check(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT bool ChkIntg();

  Standard_EXPORT bool ChkIntgInterf(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT bool CheckDS(const int i, const TopOpeBRepDS_Kind K);

  Standard_EXPORT bool ChkIntgSamDom();

  Standard_EXPORT bool CheckShapes(const NCollection_List<TopoDS_Shape>& LS) const;

  Standard_EXPORT bool OneVertexOnPnt();

  Standard_EXPORT const occ::handle<TopOpeBRepDS_HDataStructure>& HDS() const;

  Standard_EXPORT occ::handle<TopOpeBRepDS_HDataStructure>& ChangeHDS();

  Standard_EXPORT Standard_OStream& PrintIntg(Standard_OStream& S);

  Standard_EXPORT Standard_OStream& Print(const TopOpeBRepDS_CheckStatus stat, Standard_OStream& S);

  Standard_EXPORT Standard_OStream& PrintShape(const TopAbs_ShapeEnum SE, Standard_OStream& S);

  Standard_EXPORT Standard_OStream& PrintShape(const int index, Standard_OStream& S);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_Check, Standard_Transient)

private:
  Standard_EXPORT Standard_OStream& PrintMap(
    NCollection_DataMap<int, TopOpeBRepDS_CheckStatus>& MapStat,
    const char*                                         eltstr,
    Standard_OStream&                                   S);

  Standard_EXPORT Standard_OStream& PrintElts(
    NCollection_DataMap<int, TopOpeBRepDS_CheckStatus>& MapStat,
    const TopOpeBRepDS_CheckStatus                      Stat,
    bool&                                               b,
    Standard_OStream&                                   S);

  occ::handle<TopOpeBRepDS_HDataStructure>           myHDS;
  NCollection_DataMap<int, TopOpeBRepDS_CheckStatus> myMapSurfaceStatus;
  NCollection_DataMap<int, TopOpeBRepDS_CheckStatus> myMapCurveStatus;
  NCollection_DataMap<int, TopOpeBRepDS_CheckStatus> myMapPointStatus;
  NCollection_DataMap<int, TopOpeBRepDS_CheckStatus> myMapShapeStatus;
};
