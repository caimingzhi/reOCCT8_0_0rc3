#include <Aspect_SkydomeBackground.hpp>

#include <Standard_RangeError.hpp>

//=================================================================================================

Aspect_SkydomeBackground::Aspect_SkydomeBackground()
    : mySunDirection(0.0f, 1.0f, 0.0f),
      myCloudiness(0.2f),
      myTime(0.0f),
      myFogginess(0.0f),
      mySize(512)
{
}

//=================================================================================================

Aspect_SkydomeBackground::Aspect_SkydomeBackground(const gp_Dir& theSunDirection,
                                                   float         theCloudiness,
                                                   float         theTime,
                                                   float         theFogginess,
                                                   int           theSize)
    : mySunDirection(theSunDirection),
      myCloudiness(theCloudiness),
      myTime(theTime),
      myFogginess(theFogginess),
      mySize(theSize)
{
  Standard_RangeError_Raise_if(
    theFogginess < 0,
    "Aspect_SkydomeBackground::Aspect_SkydomeBackground() theFoggines must be >= 0");
  Standard_RangeError_Raise_if(
    theCloudiness < 0,
    "Aspect_SkydomeBackground::Aspect_SkydomeBackground() theCloudiness must be >= 0");
  Standard_RangeError_Raise_if(
    theSize <= 0,
    "Aspect_SkydomeBackground::Aspect_SkydomeBackground() theSize must be > 0");
}

//=================================================================================================

Aspect_SkydomeBackground::~Aspect_SkydomeBackground() = default;

//=================================================================================================

void Aspect_SkydomeBackground::SetCloudiness(float theCloudiness)
{
  Standard_RangeError_Raise_if(
    theCloudiness < 0,
    "Aspect_SkydomeBackground::SetCloudiness() theCloudiness must be >= 0");
  myCloudiness = theCloudiness;
}

//=================================================================================================

void Aspect_SkydomeBackground::SetFogginess(float theFogginess)
{
  Standard_RangeError_Raise_if(theFogginess < 0,
                               "Aspect_SkydomeBackground::SetFogginess() theFoggines must be >= 0");
  myFogginess = theFogginess;
}

//=================================================================================================

void Aspect_SkydomeBackground::SetSize(int theSize)
{
  Standard_RangeError_Raise_if(theSize <= 0,
                               "Aspect_SkydomeBackground::SetSize() theSize must be > 0");
  mySize = theSize;
}

//=================================================================================================

void Aspect_SkydomeBackground::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, Aspect_GradientBackground)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &mySunDirection)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myTime)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFogginess)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myCloudiness)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySize)
}
