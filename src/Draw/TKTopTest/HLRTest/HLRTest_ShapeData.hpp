#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Draw_Color.hpp>
#include <Standard_Transient.hpp>

class HLRTest_ShapeData : public Standard_Transient
{

public:
  Standard_EXPORT HLRTest_ShapeData(const Draw_Color& CVis,
                                    const Draw_Color& COVis,
                                    const Draw_Color& CIVis,
                                    const Draw_Color& CHid,
                                    const Draw_Color& COHid,
                                    const Draw_Color& CIHid);

  void VisibleColor(const Draw_Color& CVis);

  void VisibleOutLineColor(const Draw_Color& COVis);

  void VisibleIsoColor(const Draw_Color& CIVis);

  void HiddenColor(const Draw_Color& CHid);

  void HiddenOutLineColor(const Draw_Color& COHid);

  void HiddenIsoColor(const Draw_Color& CIHid);

  Draw_Color VisibleColor() const;

  Draw_Color VisibleOutLineColor() const;

  Draw_Color VisibleIsoColor() const;

  Draw_Color HiddenColor() const;

  Draw_Color HiddenOutLineColor() const;

  Draw_Color HiddenIsoColor() const;

  DEFINE_STANDARD_RTTIEXT(HLRTest_ShapeData, Standard_Transient)

private:
  Draw_Color myVColor;
  Draw_Color myVOColor;
  Draw_Color myVIColor;
  Draw_Color myHColor;
  Draw_Color myHOColor;
  Draw_Color myHIColor;
};

inline void HLRTest_ShapeData::VisibleColor(const Draw_Color& CVis)
{
  myVColor = CVis;
}

inline void HLRTest_ShapeData::VisibleOutLineColor(const Draw_Color& COVis)
{
  myVOColor = COVis;
}

inline void HLRTest_ShapeData::VisibleIsoColor(const Draw_Color& CIVis)
{
  myVIColor = CIVis;
}

inline void HLRTest_ShapeData::HiddenColor(const Draw_Color& CHid)
{
  myHColor = CHid;
}

inline void HLRTest_ShapeData::HiddenOutLineColor(const Draw_Color& COHid)
{
  myHOColor = COHid;
}

inline void HLRTest_ShapeData::HiddenIsoColor(const Draw_Color& CIHid)
{
  myHIColor = CIHid;
}

inline Draw_Color HLRTest_ShapeData::VisibleColor() const
{
  return myVColor;
}

inline Draw_Color HLRTest_ShapeData::VisibleOutLineColor() const
{
  return myVOColor;
}

inline Draw_Color HLRTest_ShapeData::VisibleIsoColor() const
{
  return myVIColor;
}

inline Draw_Color HLRTest_ShapeData::HiddenColor() const
{
  return myHColor;
}

inline Draw_Color HLRTest_ShapeData::HiddenOutLineColor() const
{
  return myHOColor;
}

inline Draw_Color HLRTest_ShapeData::HiddenIsoColor() const
{
  return myHIColor;
}
