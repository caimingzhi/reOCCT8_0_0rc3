#include <Draw_Color.hpp>
#include <HLRTest_ShapeData.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRTest_ShapeData, Standard_Transient)

//=================================================================================================

HLRTest_ShapeData::HLRTest_ShapeData(const Draw_Color& CVis,
                                     const Draw_Color& COVis,
                                     const Draw_Color& CIVis,
                                     const Draw_Color& CHid,
                                     const Draw_Color& COHid,
                                     const Draw_Color& CIHid)
    : myVColor(CVis),
      myVOColor(COVis),
      myVIColor(CIVis),
      myHColor(CHid),
      myHOColor(COHid),
      myHIColor(CIHid)
{
}
