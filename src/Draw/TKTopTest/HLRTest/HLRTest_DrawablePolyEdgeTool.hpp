#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <HLRBRep_BiPoint.hpp>
#include <NCollection_List.hpp>
#include <Draw_Drawable3D.hpp>
class HLRBRep_PolyAlgo;
class Draw_Display;

//! Used to display the results.
class HLRTest_DrawablePolyEdgeTool : public Draw_Drawable3D
{

public:
  Standard_EXPORT HLRTest_DrawablePolyEdgeTool(const occ::handle<HLRBRep_PolyAlgo>& Alg,
                                               const int                            ViewId,
                                               const bool                           Debug = false);

  void Show();

  void Hide();

  void DisplayRg1Line(const bool B);

  bool DisplayRg1Line() const;

  void DisplayRgNLine(const bool B);

  bool DisplayRgNLine() const;

  void DisplayHidden(const bool B);

  bool DisplayHidden() const;

  Standard_EXPORT void DrawOn(Draw_Display& D) const override;

  bool Debug() const;

  void Debug(const bool B);

  DEFINE_STANDARD_RTTIEXT(HLRTest_DrawablePolyEdgeTool, Draw_Drawable3D)

private:
  occ::handle<HLRBRep_PolyAlgo>     myAlgo;
  bool                              myDispRg1;
  bool                              myDispRgN;
  bool                              myDispHid;
  int                               myViewId;
  NCollection_List<HLRBRep_BiPoint> myBiPntVis;
  NCollection_List<HLRBRep_BiPoint> myBiPntHid;
  bool                              myDebug;
  bool                              myHideMode;
};

inline void HLRTest_DrawablePolyEdgeTool::Show()
{
  myHideMode = false;
}

//=================================================================================================

inline void HLRTest_DrawablePolyEdgeTool::Hide()
{
  myHideMode = true;
}

//=================================================================================================

inline void HLRTest_DrawablePolyEdgeTool::DisplayRg1Line(const bool B)
{
  myDispRg1 = B;
}

//=================================================================================================

inline bool HLRTest_DrawablePolyEdgeTool::DisplayRg1Line() const
{
  return myDispRg1;
}

//=================================================================================================

inline void HLRTest_DrawablePolyEdgeTool::DisplayRgNLine(const bool B)
{
  myDispRgN = B;
}

//=================================================================================================

inline bool HLRTest_DrawablePolyEdgeTool::DisplayRgNLine() const
{
  return myDispRgN;
}

//=================================================================================================

inline void HLRTest_DrawablePolyEdgeTool::DisplayHidden(const bool B)
{
  myDispHid = B;
}

//=================================================================================================

inline bool HLRTest_DrawablePolyEdgeTool::DisplayHidden() const
{
  return myDispHid;
}

//=================================================================================================

inline void HLRTest_DrawablePolyEdgeTool::Debug(const bool B)
{
  myDebug = B;
}

//=================================================================================================

inline bool HLRTest_DrawablePolyEdgeTool::Debug() const
{
  return myDebug;
}
