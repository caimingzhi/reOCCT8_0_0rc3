#pragma once


//! Type of output selection image.
enum StdSelect_TypeOfSelectionImage
{
  StdSelect_TypeOfSelectionImage_NormalizedDepth = 0,     //!< normalized   depth (grayscale)
  StdSelect_TypeOfSelectionImage_NormalizedDepthInverted, //!< normalized   depth, inverted
  StdSelect_TypeOfSelectionImage_UnnormalizedDepth,       //!< unnormalized depth (grayscale)
  StdSelect_TypeOfSelectionImage_ColoredDetectedObject,   //!< color of detected object
  StdSelect_TypeOfSelectionImage_ColoredEntity,           //!< random color for each entity
  StdSelect_TypeOfSelectionImage_ColoredEntityType,       //!< random color for each entity type
  StdSelect_TypeOfSelectionImage_ColoredOwner,            //!< random color for each owner
  StdSelect_TypeOfSelectionImage_ColoredSelectionMode,    //!< color of selection mode
  StdSelect_TypeOfSelectionImage_SurfaceNormal            //!< normal direction values
};

