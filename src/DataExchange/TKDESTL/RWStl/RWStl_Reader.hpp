#pragma once

#include <gp_XYZ.hpp>
#include <Standard_Type.hpp>
#include <Standard_ReadLineBuffer.hpp>
#include <Standard_IStream.hpp>

namespace System { namespace log {
class Message_ProgressRange;
}} // namespace System::log


class RWStl_Reader : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWStl_Reader, Standard_Transient)
public:
  Standard_EXPORT RWStl_Reader();

  Standard_EXPORT bool Read(const char* theFile, const System::log::Message_ProgressRange& theProgress);

  Standard_EXPORT bool IsAscii(Standard_IStream& theStream, const bool isSeekgAvailable);

  Standard_EXPORT bool ReadBinary(Standard_IStream&            theStream,
                                  const System::log::Message_ProgressRange& theProgress);

  Standard_EXPORT bool ReadAscii(Standard_IStream&            theStream,
                                 Standard_ReadLineBuffer&     theBuffer,
                                 const std::streampos         theUntilPos,
                                 const System::log::Message_ProgressRange& theProgress);

public:
  virtual int AddNode(const gp_XYZ& thePnt) = 0;

  virtual void AddTriangle(int theN1, int theN2, int theN3) = 0;

  virtual void AddSolid() {}

public:
  double MergeAngle() const { return myMergeAngle; }

  void SetMergeAngle(double theAngleRad) { myMergeAngle = theAngleRad; }

  double MergeTolerance() const { return myMergeTolearance; }

  void SetMergeTolerance(double theTolerance) { myMergeTolearance = theTolerance; }

protected:
  double myMergeAngle;
  double myMergeTolearance;
};
