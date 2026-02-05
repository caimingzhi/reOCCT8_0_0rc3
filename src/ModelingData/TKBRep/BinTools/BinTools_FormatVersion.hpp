#pragma once

//! Defined BinTools format version
enum BinTools_FormatVersion
{
  BinTools_FormatVersion_VERSION_1 = 1, //!< Does not write CurveOnSurface UV Points into the file.
                                        //!  On reading calls Check() method.
  BinTools_FormatVersion_VERSION_2 = 2, //!< Stores CurveOnSurface UV Points.
                                        //!  On reading format is recognized from Version string.
  BinTools_FormatVersion_VERSION_3 =
    3, //!< (OCCT 6.2.1) Correctly processes geometry with points on Curve,
       //!  or point on Surface, or points on curve of surface [#0009745]
  BinTools_FormatVersion_VERSION_4 = 4, //!< Stores per-vertex normal information in case
                                        //!  of triangulation-only Faces, because
                                        //!  no analytical geometry to restore normals
  BinTools_FormatVersion_CURRENT = BinTools_FormatVersion_VERSION_4 //!< Current version
};

enum
{
  BinTools_FormatVersion_LOWER = BinTools_FormatVersion_VERSION_1,
  BinTools_FormatVersion_UPPER = BinTools_FormatVersion_VERSION_4
};
