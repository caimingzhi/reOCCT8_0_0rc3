#pragma once


//! this enumeration defines several modes of chamfer
enum ChFiDS_ChamfMode
{
  //! chamfer with constant distance from spine to one of the two surfaces
  ChFiDS_ClassicChamfer,

  //! symmetric chamfer with constant throat
  //! that is the height of isosceles triangle in section
  ChFiDS_ConstThroatChamfer,

  //! chamfer with constant throat: the section of chamfer is right-angled triangle,
  //! the first of two surfaces (where is the top of the chamfer)
  //! is virtually moved inside the solid by offset operation,
  //! the apex of the section is on the intersection curve between moved surface and second surface,
  //! right angle is at the top of the chamfer,
  //! the length of the leg from apex to top is constant - it is throat
  ChFiDS_ConstThroatWithPenetrationChamfer
};

