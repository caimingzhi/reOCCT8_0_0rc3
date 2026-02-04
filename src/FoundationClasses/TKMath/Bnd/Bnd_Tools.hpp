#pragma once


#include <Bnd_Box2d.hpp>
#include <Bnd_Box.hpp>
#include <BVH_Box.hpp>

//! Defines a set of static methods operating with bounding boxes
class Bnd_Tools
{
public: //! @name Bnd_Box to BVH_Box conversion
  //! Converts the given Bnd_Box2d to BVH_Box
  static BVH_Box<double, 2> Bnd2BVH(const Bnd_Box2d& theBox)
  {
    double aXMin, aYMin, aXMax, aYMax;
    theBox.Get(aXMin, aYMin, aXMax, aYMax);
    return BVH_Box<double, 2>(BVH_Vec2d(aXMin, aYMin), BVH_Vec2d(aXMax, aYMax));
  }

  //! Converts the given Bnd_Box to BVH_Box
  static BVH_Box<double, 3> Bnd2BVH(const Bnd_Box& theBox)
  {
    double aXMin, aYMin, aZMin, aXMax, aYMax, aZMax;
    theBox.Get(aXMin, aYMin, aZMin, aXMax, aYMax, aZMax);
    return BVH_Box<double, 3>(BVH_Vec3d(aXMin, aYMin, aZMin), BVH_Vec3d(aXMax, aYMax, aZMax));
  }
};

