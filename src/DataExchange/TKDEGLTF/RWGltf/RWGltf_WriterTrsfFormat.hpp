#pragma once


//! Transformation format.
enum RWGltf_WriterTrsfFormat
{
  RWGltf_WriterTrsfFormat_Compact =
    0, //!< automatically choose most compact representation between Mat4 and TRS
  RWGltf_WriterTrsfFormat_Mat4 = 1, //!< 4x4 transformation Matrix
  RWGltf_WriterTrsfFormat_TRS  = 2, //!< transformation decomposed into Translation vector, Rotation
                                    //!< quaternion and Scale factor (T * R * S)
};

// clang-format off
enum { RWGltf_WriterTrsfFormat_LOWER = 0, RWGltf_WriterTrsfFormat_UPPER = RWGltf_WriterTrsfFormat_TRS }; // aliases

// clang-format on

