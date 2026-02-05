#pragma once

enum Approx_ParametrizationType
{
  Approx_ChordLength,  //!< parameters of points are proportionate to distances between them
  Approx_Centripetal,  //!< parameters of points are proportionate to square roots of distances
                       //!< between them
  Approx_IsoParametric //!< parameters of points are distributed uniformly
};
