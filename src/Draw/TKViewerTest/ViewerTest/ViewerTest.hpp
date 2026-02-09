#pragma once

#include <Aspect_TypeOfLine.hpp>
#include <Aspect_TypeOfMarker.hpp>
#include <Aspect_TypeOfTriedronPosition.hpp>
#include <Draw_Interpretor.hpp>
#include <Graphic3d_TypeOfShadingModel.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <Quantity_ColorRGBA.hpp>

class AIS_InteractiveContext;
class AIS_InteractiveObject;
class Image_PixMap;
class V3d_View;
class V3d_Viewer;
class ViewerTest_EventManager;
class TopoDS_Shape;
class WNT_WClass;

struct ViewerTest_VinitParams
{
  TCollection_AsciiString       ViewName;
  TCollection_AsciiString       DisplayName;
  occ::handle<V3d_View>         ViewToClone;
  occ::handle<V3d_View>         ParentView;
  NCollection_Vec2<double>      Offset;
  NCollection_Vec2<double>      Size;
  Aspect_TypeOfTriedronPosition Corner;
  NCollection_Vec2<int>         SubviewMargins;
  bool                          IsVirtual;
  bool                          IsComposer;

  ViewerTest_VinitParams()
      : Corner(Aspect_TOTP_LEFT_UPPER),
        IsVirtual(false),
        IsComposer(false)
  {
  }
};

class ViewerTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);

  Standard_EXPORT static TCollection_AsciiString ViewerInit(
    const ViewerTest_VinitParams& theParams);

  static TCollection_AsciiString ViewerInit(const TCollection_AsciiString& theViewName = "")
  {
    ViewerTest_VinitParams aParams;
    aParams.ViewName = theViewName;
    return ViewerInit(aParams);
  }

  static TCollection_AsciiString ViewerInit(
    const int                      thePxLeft,
    const int                      thePxTop,
    const int                      thePxWidth,
    const int                      thePxHeight,
    const TCollection_AsciiString& theViewName,
    const TCollection_AsciiString& theDisplayName = "",
    const occ::handle<V3d_View>&   theViewToClone = occ::handle<V3d_View>(),
    const bool                     theIsVirtual   = false)
  {
    ViewerTest_VinitParams aParams;
    aParams.Offset.SetValues((float)thePxLeft, (float)thePxTop);
    aParams.Size.SetValues((float)thePxWidth, (float)thePxHeight);
    aParams.ViewName    = theViewName;
    aParams.DisplayName = theDisplayName;
    aParams.ViewToClone = theViewToClone;
    aParams.IsVirtual   = theIsVirtual;
    return ViewerInit(aParams);
  }

  Standard_EXPORT static void RemoveViewName(const TCollection_AsciiString& theName);

  Standard_EXPORT static void InitViewName(const TCollection_AsciiString& theName,
                                           const occ::handle<V3d_View>&   theView);

  Standard_EXPORT static TCollection_AsciiString GetCurrentViewName();

  Standard_EXPORT static void ActivateView(const occ::handle<V3d_View>& theView, bool theToUpdate);

  Standard_EXPORT static void RemoveView(const TCollection_AsciiString& theViewName,
                                         const bool                     theToRemoveContext = true);

  Standard_EXPORT static void RemoveView(const occ::handle<V3d_View>& theView,
                                         const bool                   theToRemoveContext = true);

  Standard_EXPORT static bool Display(const TCollection_AsciiString&            theName,
                                      const occ::handle<AIS_InteractiveObject>& theObject,
                                      const bool                                theToUpdate = true,
                                      const bool theReplaceIfExists                         = true);

  Standard_EXPORT static TopoDS_Shape PickShape(const TopAbs_ShapeEnum aType,
                                                const int              MaxPick = 5);

  Standard_EXPORT static bool PickShapes(const TopAbs_ShapeEnum                          aType,
                                         occ::handle<NCollection_HArray1<TopoDS_Shape>>& thepicked,
                                         const int MaxPick = 5);

  Standard_EXPORT static void Commands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void ViewerCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void RelationCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void ObjectCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void FilletCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void OpenGlCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void GetMousePosition(int& xpix, int& ypix);

  Standard_EXPORT static occ::handle<V3d_Viewer> GetViewerFromContext();

  Standard_EXPORT static occ::handle<V3d_Viewer> GetCollectorFromContext();

  Standard_EXPORT static const occ::handle<AIS_InteractiveContext>& GetAISContext();

  Standard_EXPORT static void SetAISContext(const occ::handle<AIS_InteractiveContext>& aContext);

  Standard_EXPORT static const occ::handle<V3d_View>& CurrentView();

  Standard_EXPORT static void CurrentView(const occ::handle<V3d_View>& aViou);

  Standard_EXPORT static void Clear();

  Standard_EXPORT static void SetEventManager(const occ::handle<ViewerTest_EventManager>& theMgr);

  Standard_EXPORT static void UnsetEventManager();

  Standard_EXPORT static void ResetEventManager();

  Standard_EXPORT static occ::handle<ViewerTest_EventManager> CurrentEventManager();

  Standard_EXPORT static void RemoveSelected();

  Standard_EXPORT static void RedrawAllViews();

  Standard_EXPORT static bool SplitParameter(const TCollection_AsciiString& theString,
                                             TCollection_AsciiString&       theName,
                                             TCollection_AsciiString&       theValue);

  Standard_EXPORT static void GetSelectedShapes(NCollection_List<TopoDS_Shape>& theShapes);

  Standard_EXPORT static bool ParseLineType(const char*        theArg,
                                            Aspect_TypeOfLine& theType,
                                            uint16_t&          thePattern);

  static bool ParseLineType(const char* theArg, Aspect_TypeOfLine& theType)
  {
    uint16_t aPattern = 0xFFFF;
    return ParseLineType(theArg, theType, aPattern);
  }

  Standard_EXPORT static bool ParseMarkerType(const char*                theArg,
                                              Aspect_TypeOfMarker&       theType,
                                              occ::handle<Image_PixMap>& theImage);

  Standard_EXPORT static bool ParseShadingModel(const char*                   theArg,
                                                Graphic3d_TypeOfShadingModel& theModel);

  static bool ParseZLayerName(const char* theArg, Graphic3d_ZLayerId& theLayer)
  {
    return parseZLayer(theArg, false, theLayer);
  }

  static bool ParseZLayer(const char* theArg, Graphic3d_ZLayerId& theLayer)
  {
    return parseZLayer(theArg, true, theLayer);
  }

  Standard_EXPORT static bool ParseCorner(const char*                    theArg,
                                          Aspect_TypeOfTriedronPosition& theCorner);

public:
  Standard_DEPRECATED("Method has been moved to Draw::ParseColor()")
  Standard_EXPORT static int ParseColor(const int                theArgNb,
                                        const char* const* const theArgVec,
                                        Quantity_ColorRGBA&      theColor);

  Standard_DEPRECATED("Method has been moved to Draw::ParseColor()")
  Standard_EXPORT static int ParseColor(const int                theArgNb,
                                        const char* const* const theArgVec,
                                        Quantity_Color&          theColor);

  Standard_DEPRECATED("Method has been moved to Draw::ParseOnOff()")
  Standard_EXPORT static bool ParseOnOff(const char* theArg, bool& theIsOn);

  Standard_DEPRECATED("Method has been moved to Quantity_Color::ColorFromName()")
  Standard_EXPORT static Quantity_NameOfColor GetColorFromName(const char* name);

private:
  Standard_EXPORT static bool parseZLayer(const char*         theArg,
                                          bool                theToAllowInteger,
                                          Graphic3d_ZLayerId& theLayer);

  static const occ::handle<WNT_WClass>& WClass();
};
