#pragma once

#include <gp_Dir.hpp>
#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Aspect_SkydomeBackground
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Aspect_SkydomeBackground();

  Standard_EXPORT Aspect_SkydomeBackground(const gp_Dir& theSunDirection,
                                           float         theCloudiness,
                                           float         theTime,
                                           float         theFogginess,
                                           int           theSize);

  Standard_EXPORT ~Aspect_SkydomeBackground();

  const gp_Dir& SunDirection() const { return mySunDirection; }

  float Cloudiness() const { return myCloudiness; }

  float TimeParameter() const { return myTime; }

  float Fogginess() const { return myFogginess; }

  int Size() const { return mySize; }

  void SetSunDirection(const gp_Dir& theSunDirection) { mySunDirection = theSunDirection; }

  Standard_EXPORT void SetCloudiness(float theCloudiness);

  void SetTimeParameter(float theTime) { myTime = theTime; }

  Standard_EXPORT void SetFogginess(float theFogginess);

  Standard_EXPORT void SetSize(int theSize);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_Dir mySunDirection;
  float  myCloudiness;
  float  myTime;
  float  myFogginess;
  int    mySize;
};
