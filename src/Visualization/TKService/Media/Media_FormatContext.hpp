#pragma once

#include <Media_Packet.hpp>

#include <TCollection_AsciiString.hpp>

struct AVCodecContext;
struct AVFormatContext;
struct AVStream;
struct AVRational;

//! AVFormatContext wrapper - the media input/output stream holder.
class Media_FormatContext : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_FormatContext, Standard_Transient)
public:
  //! Returns string description for AVError code.
  Standard_EXPORT static TCollection_AsciiString FormatAVErrorDescription(int theErrCodeAV);

  //! Convert time units into seconds for context.
  //! @param theTimeUnits value to convert
  //! @return converted time units in seconds
  Standard_EXPORT static double FormatUnitsToSeconds(int64_t theTimeUnits);

  //! Convert time units into seconds. Returns zero for invalid value.
  //! @param theTimeBase  the timebase
  //! @param theTimeUnits value to convert
  //! @return converted time units in seconds
  Standard_EXPORT static double UnitsToSeconds(const AVRational& theTimeBase, int64_t theTimeUnits);

  //! Convert time units into seconds using stream base.
  //! @param theStream    the stream;
  //! @param theTimeUnits value to convert;
  //! @return converted time units in seconds.
  Standard_EXPORT static double StreamUnitsToSeconds(const AVStream& theStream,
                                                     int64_t         theTimeUnits);

  //! Convert seconds into time units for context.
  //! @param theTimeSeconds value to convert
  //! @return time units
  Standard_EXPORT static int64_t SecondsToUnits(double theTimeSeconds);

  //! Convert seconds into time units.
  //! @param theTimeBase    the timebase
  //! @param theTimeSeconds value to convert
  //! @return time units
  Standard_EXPORT static int64_t SecondsToUnits(const AVRational& theTimeBase,
                                                double            theTimeSeconds);

  //! Convert seconds into time units for stream.
  //! @param theStream      the stream
  //! @param theTimeSeconds value to convert
  //! @return time units
  Standard_EXPORT static int64_t StreamSecondsToUnits(const AVStream& theStream,
                                                      double          theTimeSeconds);

  //! Time formatter.
  Standard_EXPORT static TCollection_AsciiString FormatTime(double theSeconds);

  //! Time progress / duration formatter.
  Standard_EXPORT static TCollection_AsciiString FormatTimeProgress(double theProgress,
                                                                    double theDuration);

public:
  //! Constructor.
  Standard_EXPORT Media_FormatContext();

  //! Destructor.
  Standard_EXPORT ~Media_FormatContext() override;

  //! Return context.
  AVFormatContext* Context() const { return myFormatCtx; }

  //! Open input.
  Standard_EXPORT bool OpenInput(const TCollection_AsciiString& theInput);

  //! Close input.
  Standard_EXPORT void Close();

  //! Return amount of streams.
  Standard_EXPORT unsigned int NbSteams() const;

  //! Return stream.
  Standard_EXPORT const AVStream& Stream(unsigned int theIndex) const;

  //! Format stream info.
  Standard_EXPORT TCollection_AsciiString StreamInfo(unsigned int    theIndex,
                                                     AVCodecContext* theCodecCtx = nullptr) const;

  //! Return PTS start base in seconds.
  double PtsStartBase() const { return myPtsStartBase; }

  //! Return duration in seconds.
  double Duration() const { return myDuration; }

  //! av_read_frame() wrapper.
  Standard_EXPORT bool ReadPacket(const occ::handle<Media_Packet>& thePacket);

  //! Seek stream to specified position.
  Standard_EXPORT bool SeekStream(unsigned int theStreamId, double theSeekPts, bool toSeekBack);

  //! Seek context to specified position.
  Standard_EXPORT bool Seek(double theSeekPts, bool toSeekBack);

protected:
  AVFormatContext* myFormatCtx;    //!< format context
  double           myPtsStartBase; //!< start time
  double           myDuration;     //!< duration
};
