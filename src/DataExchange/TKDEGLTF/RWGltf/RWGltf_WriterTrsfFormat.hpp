#pragma once

enum RWGltf_WriterTrsfFormat
{
  RWGltf_WriterTrsfFormat_Compact = 0,
  RWGltf_WriterTrsfFormat_Mat4    = 1,
  RWGltf_WriterTrsfFormat_TRS     = 2,
};

enum
{
  RWGltf_WriterTrsfFormat_LOWER = 0,
  RWGltf_WriterTrsfFormat_UPPER = RWGltf_WriterTrsfFormat_TRS
};
