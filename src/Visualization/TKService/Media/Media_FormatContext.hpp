#pragma once

#include <Media_Packet.hpp>

#include <TCollection_AsciiString.hpp>

struct AVCodecContext;
struct AVFormatContext;
struct AVStream;
struct AVRational;

class Media_FormatContext : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_FormatContext, Standard_Transient)
public:
  Standard_EXPORT static TCollection_AsciiString FormatAVErrorDescription(int theErrCodeAV);

  Standard_EXPORT static double FormatUnitsToSeconds(int64_t theTimeUnits);

  Standard_EXPORT static double UnitsToSeconds(const AVRational& theTimeBase, int64_t theTimeUnits);

  Standard_EXPORT static double StreamUnitsToSeconds(const AVStream& theStream,
                                                     int64_t         theTimeUnits);

  Standard_EXPORT static int64_t SecondsToUnits(double theTimeSeconds);

  Standard_EXPORT static int64_t SecondsToUnits(const AVRational& theTimeBase,
                                                double            theTimeSeconds);

  Standard_EXPORT static int64_t StreamSecondsToUnits(const AVStream& theStream,
                                                      double          theTimeSeconds);

  Standard_EXPORT static TCollection_AsciiString FormatTime(double theSeconds);

  Standard_EXPORT static TCollection_AsciiString FormatTimeProgress(double theProgress,
                                                                    double theDuration);

public:
  Standard_EXPORT Media_FormatContext();

  Standard_EXPORT ~Media_FormatContext() override;

  AVFormatContext* Context() const { return myFormatCtx; }

  Standard_EXPORT bool OpenInput(const TCollection_AsciiString& theInput);

  Standard_EXPORT void Close();

  Standard_EXPORT unsigned int NbSteams() const;

  Standard_EXPORT const AVStream& Stream(unsigned int theIndex) const;

  Standard_EXPORT TCollection_AsciiString StreamInfo(unsigned int    theIndex,
                                                     AVCodecContext* theCodecCtx = nullptr) const;

  double PtsStartBase() const { return myPtsStartBase; }

  double Duration() const { return myDuration; }

  Standard_EXPORT bool ReadPacket(const occ::handle<Media_Packet>& thePacket);

  Standard_EXPORT bool SeekStream(unsigned int theStreamId, double theSeekPts, bool toSeekBack);

  Standard_EXPORT bool Seek(double theSeekPts, bool toSeekBack);

protected:
  AVFormatContext* myFormatCtx;
  double           myPtsStartBase;
  double           myDuration;
};
