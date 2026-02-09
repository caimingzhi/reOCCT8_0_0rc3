#pragma once

#include <Font_Hinting.hpp>
#include <Font_NameOfFont.hpp>
#include <Graphic3d_AspectText3d.hpp>
#include <Graphic3d_TransformPers.hpp>
#include <Graphic3d_RenderTransparentMethod.hpp>

enum Graphic3d_RenderingMode
{
  Graphic3d_RM_RASTERIZATION,
  Graphic3d_RM_RAYTRACING
};

#include <Graphic3d_StereoMode.hpp>

enum Graphic3d_ToneMappingMethod
{
  Graphic3d_ToneMappingMethod_Disabled,
  Graphic3d_ToneMappingMethod_Filmic
};

#include <Graphic3d_TypeOfShadingModel.hpp>
#include <NCollection_Vec4.hpp>
#include <Standard_TypeDef.hpp>

class Graphic3d_RenderingParams
{
public:
  static const unsigned int THE_DEFAULT_RESOLUTION = 72u;

  static const int THE_DEFAULT_DEPTH = 3;

  enum Anaglyph
  {
    Anaglyph_RedCyan_Simple,
    Anaglyph_RedCyan_Optimized,
    Anaglyph_YellowBlue_Simple,
    Anaglyph_YellowBlue_Optimized,
    Anaglyph_GreenMagenta_Simple,
    Anaglyph_UserDefined
  };

  enum PerfCounters
  {
    PerfCounters_NONE      = 0x000,
    PerfCounters_FrameRate = 0x001,
    PerfCounters_CPU       = 0x002,

    PerfCounters_Layers     = 0x004,
    PerfCounters_Structures = 0x008,

    PerfCounters_Groups      = 0x010,
    PerfCounters_GroupArrays = 0x020,

    PerfCounters_Triangles = 0x040,
    PerfCounters_Points    = 0x080,
    PerfCounters_Lines     = 0x100,

    PerfCounters_EstimMem = 0x200,

    PerfCounters_FrameTime    = 0x400,
    PerfCounters_FrameTimeMax = 0x800,

    PerfCounters_SkipImmediate = 0x1000,

    PerfCounters_Basic =
      PerfCounters_FrameRate | PerfCounters_CPU | PerfCounters_Layers | PerfCounters_Structures,

    PerfCounters_Extended = PerfCounters_Basic | PerfCounters_Groups | PerfCounters_GroupArrays
                            | PerfCounters_Triangles | PerfCounters_Points | PerfCounters_Lines
                            | PerfCounters_EstimMem,

    PerfCounters_All = PerfCounters_Extended | PerfCounters_FrameTime | PerfCounters_FrameTimeMax,
  };

  enum FrustumCulling
  {
    FrustumCulling_Off,
    FrustumCulling_On,

    FrustumCulling_NoUpdate
  };

public:
  Graphic3d_RenderingParams()
      : Method(Graphic3d_RM_RASTERIZATION),
        ShadingModel(Graphic3d_TypeOfShadingModel_Phong),
        TransparencyMethod(Graphic3d_RTM_BLEND_UNORDERED),
        Resolution(THE_DEFAULT_RESOLUTION),
        FontHinting(Font_Hinting_Off),
        LineFeather(1.0f),

        PbrEnvPow2Size(9),
        PbrEnvSpecMapNbLevels(6),
        PbrEnvBakingDiffNbSamples(1024),
        PbrEnvBakingSpecNbSamples(256),
        PbrEnvBakingProbability(0.99f),

        OitDepthFactor(0.0f),
        NbOitDepthPeelingLayers(4),
        NbMsaaSamples(0),
        RenderResolutionScale(1.0f),
        ShadowMapResolution(1024),
        ShadowMapBias(0.005f),
        ToEnableDepthPrepass(false),
        ToEnableAlphaToCoverage(true),

        IsGlobalIlluminationEnabled(false),
        SamplesPerPixel(0),
        RaytracingDepth(THE_DEFAULT_DEPTH),
        IsShadowEnabled(true),
        IsReflectionEnabled(false),
        IsAntialiasingEnabled(false),
        IsTransparentShadowEnabled(false),
        UseEnvironmentMapBackground(false),
        ToIgnoreNormalMapInRayTracing(false),
        CoherentPathTracingMode(false),
        AdaptiveScreenSampling(false),
        AdaptiveScreenSamplingAtomic(false),
        ShowSamplingTiles(false),
        TwoSidedBsdfModels(false),
        RadianceClampingValue(30.0),
        RebuildRayTracingShaders(false),
        RayTracingTileSize(32),
        NbRayTracingTiles(16 * 16),
        CameraApertureRadius(0.0f),
        CameraFocalPlaneDist(1.0f),
        FrustumCullingState(FrustumCulling_On),
        ToneMappingMethod(Graphic3d_ToneMappingMethod_Disabled),
        Exposure(0.f),
        WhitePoint(1.f),

        StereoMode(Graphic3d_StereoMode_QuadBuffer),
        HmdFov2d(30.0f),
        AnaglyphFilter(Anaglyph_RedCyan_Optimized),
        ToReverseStereo(false),
        ToSmoothInterlacing(true),
        ToMirrorComposer(true),

        StatsPosition(new Graphic3d_TransformPers(Graphic3d_TMF_2d,
                                                  Aspect_TOTP_LEFT_UPPER,
                                                  NCollection_Vec2<int>(20, 20))),
        ChartPosition(new Graphic3d_TransformPers(Graphic3d_TMF_2d,
                                                  Aspect_TOTP_RIGHT_UPPER,
                                                  NCollection_Vec2<int>(20, 20))),
        ChartSize(-1, -1),
        StatsTextAspect(new Graphic3d_AspectText3d()),
        StatsUpdateInterval(1.0),
        StatsTextHeight(16),
        StatsNbFrames(1),
        StatsMaxChartTime(0.1f),
        CollectedStats(PerfCounters_Basic),
        ToShowStats(false)
  {
    const NCollection_Vec4<float> aZero(0.0f, 0.0f, 0.0f, 0.0f);
    AnaglyphLeft.SetRow(0, NCollection_Vec4<float>(1.0f, 0.0f, 0.0f, 0.0f));
    AnaglyphLeft.SetRow(1, aZero);
    AnaglyphLeft.SetRow(2, aZero);
    AnaglyphLeft.SetRow(3, aZero);
    AnaglyphRight.SetRow(0, aZero);
    AnaglyphRight.SetRow(1, NCollection_Vec4<float>(0.0f, 1.0f, 0.0f, 0.0f));
    AnaglyphRight.SetRow(2, NCollection_Vec4<float>(0.0f, 0.0f, 1.0f, 0.0f));
    AnaglyphRight.SetRow(3, aZero);

    StatsTextAspect->SetColor(Quantity_NOC_WHITE);
    StatsTextAspect->SetColorSubTitle(Quantity_NOC_BLACK);
    StatsTextAspect->SetFont(Font_NOF_ASCII_MONO);
    StatsTextAspect->SetDisplayType(Aspect_TODT_SHADOW);
    StatsTextAspect->SetTextZoomable(false);
    StatsTextAspect->SetTextFontAspect(Font_FA_Regular);
  }

  float ResolutionRatio() const { return Resolution / static_cast<float>(THE_DEFAULT_RESOLUTION); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  Graphic3d_RenderingMode           Method;
  Graphic3d_TypeOfShadingModel      ShadingModel;
  Graphic3d_RenderTransparentMethod TransparencyMethod;
  unsigned int                      Resolution;

  Font_Hinting FontHinting;

  float LineFeather;

public:
  int PbrEnvPow2Size;
  int PbrEnvSpecMapNbLevels;
  int PbrEnvBakingDiffNbSamples;

  int   PbrEnvBakingSpecNbSamples;
  float PbrEnvBakingProbability;

  float OitDepthFactor;
  int   NbOitDepthPeelingLayers;
  int   NbMsaaSamples;
  float RenderResolutionScale;

  int   ShadowMapResolution;
  float ShadowMapBias;
  bool  ToEnableDepthPrepass;
  bool  ToEnableAlphaToCoverage;

public:
  bool  IsGlobalIlluminationEnabled;
  int   SamplesPerPixel;
  int   RaytracingDepth;
  bool  IsShadowEnabled;
  bool  IsReflectionEnabled;
  bool  IsAntialiasingEnabled;
  bool  IsTransparentShadowEnabled;
  bool  UseEnvironmentMapBackground;
  bool  ToIgnoreNormalMapInRayTracing;
  bool  CoherentPathTracingMode;
  bool  AdaptiveScreenSampling;
  bool  AdaptiveScreenSamplingAtomic;
  bool  ShowSamplingTiles;
  bool  TwoSidedBsdfModels;
  float RadianceClampingValue;
  bool  RebuildRayTracingShaders;
  int   RayTracingTileSize;
  int   NbRayTracingTiles;

  float          CameraApertureRadius;
  float          CameraFocalPlaneDist;
  FrustumCulling FrustumCullingState;

  Graphic3d_ToneMappingMethod ToneMappingMethod;
  float                       Exposure;
  float                       WhitePoint;

public:
  Graphic3d_StereoMode    StereoMode;
  float                   HmdFov2d;
  Anaglyph                AnaglyphFilter;
  NCollection_Mat4<float> AnaglyphLeft;
  NCollection_Mat4<float> AnaglyphRight;
  bool                    ToReverseStereo;
  bool                    ToSmoothInterlacing;
  bool                    ToMirrorComposer;

public:
  occ::handle<Graphic3d_TransformPers> StatsPosition;
  occ::handle<Graphic3d_TransformPers> ChartPosition;
  NCollection_Vec2<int>                ChartSize;
  occ::handle<Graphic3d_AspectText3d>  StatsTextAspect;
  float                                StatsUpdateInterval;

  int          StatsTextHeight;
  int          StatsNbFrames;
  float        StatsMaxChartTime;
  PerfCounters CollectedStats;

  bool ToShowStats;
};
