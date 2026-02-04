#pragma once


//! Options to be used with image dumping.
//! Notice that the value will have no effect with disabled stereo output.
enum V3d_StereoDumpOptions
{
  V3d_SDO_MONO,      //!< ignore stereo mode and dump monographic projection for stereo camera
  V3d_SDO_LEFT_EYE,  //!< dump only left  eye projection for stereo camera
  V3d_SDO_RIGHT_EYE, //!< dump only right eye projection for stereo camera
  V3d_SDO_BLENDED //!< dump blended pair specific to the active device output Graphic3d_StereoMode
                  //!< (result will be undefined for modes like Graphic3d_StereoMode_QuadBuffer)
};

