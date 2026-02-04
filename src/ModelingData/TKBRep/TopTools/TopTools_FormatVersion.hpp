#pragma once


//! Defined TopTools format version
enum TopTools_FormatVersion
{
  TopTools_FormatVersion_VERSION_1 = 1, //!< Does not write CurveOnSurface UV Points into the file.
                                        //!  On reading calls Check() method.
                                        //!  This is default version.
  TopTools_FormatVersion_VERSION_2 = 2, //!< Stores CurveOnSurface UV Points.
                                        //!  On reading format is recognized from Version string.
  TopTools_FormatVersion_VERSION_3 =
    3, //!< Stores per-vertex normal information in case of triangulation-only Faces,
       //!  because no analytical geometry to restore normals
  TopTools_FormatVersion_CURRENT = TopTools_FormatVersion_VERSION_3 //!< Current version
};

enum
{
  TopTools_FormatVersion_LOWER = TopTools_FormatVersion_VERSION_1,
  TopTools_FormatVersion_UPPER = TopTools_FormatVersion_VERSION_3
};

