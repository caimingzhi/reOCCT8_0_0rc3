#pragma once

#include <DE_ShapeFixParameters.hpp>
#include <Resource_FormatType.hpp>
#include <STEPControl_StepModelType.hpp>
#include <TCollection_AsciiString.hpp>
#include <UnitsMethods_LengthUnit.hpp>

class DESTEP_Parameters
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

  enum AngleUnitMode
  {
    AngleUnitMode_File = 0,
    AngleUnitMode_Rad,
    AngleUnitMode_Deg
  };

  enum ReadMode_ProductContext
  {
    ReadMode_ProductContext_All = 1,
    ReadMode_ProductContext_Design,
    ReadMode_ProductContext_Analysis
  };

  enum ReadMode_ShapeRepr
  {
    ReadMode_ShapeRepr_All = 1,
    ReadMode_ShapeRepr_ABSR,
    ReadMode_ShapeRepr_MSSR,
    ReadMode_ShapeRepr_GBSSR,
    ReadMode_ShapeRepr_FBSR,
    ReadMode_ShapeRepr_EBWSR,
    ReadMode_ShapeRepr_GBWSR
  };

  enum ReadMode_AssemblyLevel
  {
    ReadMode_AssemblyLevel_All = 1,
    ReadMode_AssemblyLevel_Assembly,
    ReadMode_AssemblyLevel_Structure,
    ReadMode_AssemblyLevel_Shape
  };

  enum RWMode_Tessellated
  {
    RWMode_Tessellated_Off = 0,
    RWMode_Tessellated_On,
    RWMode_Tessellated_OnNoBRep
  };

  enum WriteMode_PrecisionMode
  {
    WriteMode_PrecisionMode_Least    = -1,
    WriteMode_PrecisionMode_Average  = 0,
    WriteMode_PrecisionMode_Greatest = 1,
    WriteMode_PrecisionMode_Session  = 2
  };

  enum WriteMode_Assembly
  {
    WriteMode_Assembly_Off = 0,
    WriteMode_Assembly_On,
    WriteMode_Assembly_Auto
  };

  enum WriteMode_StepSchema
  {
    WriteMode_StepSchema_AP214CD = 1,
    WriteMode_StepSchema_AP214DIS,
    WriteMode_StepSchema_AP203,
    WriteMode_StepSchema_AP214IS,
    WriteMode_StepSchema_AP242DIS
  };

  enum WriteMode_VertexMode
  {
    WriteMode_VertexMode_OneCompound = 0,
    WriteMode_VertexMode_SingleVertex
  };

public:
  Standard_EXPORT DESTEP_Parameters();

  Standard_EXPORT void InitFromStatic();

  Standard_EXPORT void Reset();

  Standard_EXPORT TCollection_AsciiString GetString(const ReadMode_ProductContext theMode)
  {
    switch (theMode)
    {
      case ReadMode_ProductContext_All:
        return "all";
      case ReadMode_ProductContext_Design:
        return "design";
      case ReadMode_ProductContext_Analysis:
        return "analysis";
      default:
        return "";
    }
  }

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
  AngleUnitMode              AngleUnit             = AngleUnitMode_File;

  bool                    ReadProductMode        = true;
  ReadMode_ProductContext ReadProductContext     = ReadMode_ProductContext_All;
  ReadMode_ShapeRepr      ReadShapeRepr          = ReadMode_ShapeRepr_All;
  RWMode_Tessellated      ReadTessellated        = RWMode_Tessellated_On;
  ReadMode_AssemblyLevel  ReadAssemblyLevel      = ReadMode_AssemblyLevel_All;
  bool                    ReadRelationship       = true;
  bool                    ReadShapeAspect        = true;
  bool                    ReadConstrRelation     = false;
  bool                    ReadSubshapeNames      = false;
  Resource_FormatType     ReadCodePage           = Resource_FormatType_UTF8;
  bool                    ReadNonmanifold        = false;
  bool                    ReadIdeas              = false;
  bool                    ReadAllShapes          = false;
  bool                    ReadRootTransformation = true;
  bool                    ReadColor              = true;
  bool                    ReadName               = true;
  bool                    ReadLayer              = true;
  bool                    ReadProps              = true;
  bool                    ReadMetadata           = true;
  bool                    ReadProductMetadata    = false;

  WriteMode_PrecisionMode   WritePrecisionMode = WriteMode_PrecisionMode_Average;
  double                    WritePrecisionVal  = 0.0001;
  WriteMode_Assembly        WriteAssembly      = WriteMode_Assembly_Auto;
  WriteMode_StepSchema      WriteSchema        = WriteMode_StepSchema_AP214IS;
  RWMode_Tessellated        WriteTessellated   = RWMode_Tessellated_OnNoBRep;
  TCollection_AsciiString   WriteProductName;
  bool                      WriteSurfaceCurMode = true;
  UnitsMethods_LengthUnit   WriteUnit           = UnitsMethods_LengthUnit_Millimeter;
  WriteMode_VertexMode      WriteVertexMode     = WriteMode_VertexMode_OneCompound;
  bool                      WriteSubshapeNames  = false;
  bool                      WriteColor          = true;
  bool                      WriteNonmanifold    = false;
  bool                      WriteName           = true;
  bool                      WriteLayer          = true;
  bool                      WriteProps          = true;
  bool                      WriteMetadata       = true;
  bool                      WriteMaterial       = true;
  bool                      WriteVisMaterial    = false;
  STEPControl_StepModelType WriteModelType      = STEPControl_AsIs;
  bool                      CleanDuplicates     = false;
  bool                      WriteScalingTrsf    = true;
};
