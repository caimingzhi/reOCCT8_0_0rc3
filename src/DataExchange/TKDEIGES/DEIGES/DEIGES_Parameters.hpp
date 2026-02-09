#pragma once

#include <DE_ShapeFixParameters.hpp>
#include <Resource_FormatType.hpp>
#include <STEPControl_StepModelType.hpp>
#include <TCollection_AsciiString.hpp>
#include <UnitsMethods_LengthUnit.hpp>

class DEIGES_Parameters
{
public:
  enum ReadMode_BSplineContinuity
  {
    ReadMode_BSplineContinuity_C0 = 0,
    ReadMode_BSplineContinuity_C1,
    ReadMode_BSplineContinuity_C2
  };

  enum ReadMode_Precision
  {
    ReadMode_Precision_File = 0,
    ReadMode_Precision_User
  };

  enum ReadMode_MaxPrecision
  {
    ReadMode_MaxPrecision_Preferred = 0,
    ReadMode_MaxPrecision_Forced
  };

  enum ReadMode_SurfaceCurve
  {
    ReadMode_SurfaceCurve_Default         = 0,
    ReadMode_SurfaceCurve_2DUse_Preferred = 2,
    ReadMode_SurfaceCurve_2DUse_Forced    = -2,
    ReadMode_SurfaceCurve_3DUse_Preferred = 3,
    ReadMode_SurfaceCurve_3DUse_Forced    = -3
  };

  enum WriteMode_BRep
  {
    WriteMode_BRep_Faces = 0,
    WriteMode_BRep_BRep
  };

  enum WriteMode_ConvertSurface
  {
    WriteMode_ConvertSurface_Off = 0,
    WriteMode_ConvertSurface_On
  };

  enum WriteMode_PrecisionMode
  {
    WriteMode_PrecisionMode_Least    = -1,
    WriteMode_PrecisionMode_Average  = 0,
    WriteMode_PrecisionMode_Greatest = 1,
    WriteMode_PrecisionMode_Session  = 2
  };

  enum WriteMode_PlaneMode
  {
    WriteMode_PlaneMode_Plane = 0,
    WriteMode_PlaneMode_BSpline
  };

public:
  DEIGES_Parameters() = default;

  Standard_EXPORT void InitFromStatic();

  Standard_EXPORT void Reset();

  Standard_EXPORT static DE_ShapeFixParameters GetDefaultShapeFixParameters();

public:
  ReadMode_BSplineContinuity ReadBSplineContinuity = ReadMode_BSplineContinuity_C1;
  ReadMode_Precision         ReadPrecisionMode     = ReadMode_Precision_File;
  double                     ReadPrecisionVal      = 0.0001;
  ReadMode_MaxPrecision      ReadMaxPrecisionMode  = ReadMode_MaxPrecision_Preferred;
  double                     ReadMaxPrecisionVal   = 1;
  bool                       ReadSameParamMode     = false;
  ReadMode_SurfaceCurve      ReadSurfaceCurveMode  = ReadMode_SurfaceCurve_Default;
  double                     EncodeRegAngle        = 0.57295779513;

  bool ReadApproxd1       = false;
  bool ReadFaultyEntities = false;
  bool ReadOnlyVisible    = false;
  bool ReadColor          = true;
  bool ReadName           = true;
  bool ReadLayer          = true;

  WriteMode_BRep           WriteBRepMode           = WriteMode_BRep_Faces;
  WriteMode_ConvertSurface WriteConvertSurfaceMode = WriteMode_ConvertSurface_Off;
  TCollection_AsciiString  WriteHeaderAuthor;
  TCollection_AsciiString  WriteHeaderCompany;
  TCollection_AsciiString  WriteHeaderProduct;
  TCollection_AsciiString  WriteHeaderReciever;
  WriteMode_PrecisionMode  WritePrecisionMode = WriteMode_PrecisionMode_Average;
  double                   WritePrecisionVal  = 0.0001;
  WriteMode_PlaneMode      WritePlaneMode     = WriteMode_PlaneMode_Plane;
  bool                     WriteOffsetMode    = false;
  bool                     WriteColor         = true;
  bool                     WriteName          = true;
  bool                     WriteLayer         = true;
};
