#pragma once

#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Image_PixMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

struct AVFrame;

//! AVFrame wrapper - the frame (decoded image/audio sample data) holder.
class Media_Frame : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Frame, Standard_Transient)
public:
  //! Convert pixel format from FFmpeg (AVPixelFormat) to OCCT.
  Standard_EXPORT static Image_Format FormatFFmpeg2Occt(int theFormat);

  //! Convert pixel format from OCCT to FFmpeg (AVPixelFormat).
  //! Returns -1 (AV_PIX_FMT_NONE) if undefined.
  Standard_EXPORT static int FormatOcct2FFmpeg(Image_Format theFormat);

  //! Swap AVFrame* within two frames.
  Standard_EXPORT static void Swap(const occ::handle<Media_Frame>& theFrame1,
                                   const occ::handle<Media_Frame>& theFrame2);

public:
  //! Empty constructor
  Standard_EXPORT Media_Frame();

  //! Destructor
  Standard_EXPORT ~Media_Frame() override;

  //! Return true if frame does not contain any data.
  Standard_EXPORT bool IsEmpty() const;

  //! av_frame_unref() wrapper.
  Standard_EXPORT void Unref();

  //! Return image dimensions.
  NCollection_Vec2<int> Size() const { return NCollection_Vec2<int>(SizeX(), SizeY()); }

  //! Return image width.
  Standard_EXPORT int SizeX() const;

  //! Return image height.
  Standard_EXPORT int SizeY() const;

  //! Return pixel format (AVPixelFormat).
  Standard_EXPORT int Format() const;

  //! Return TRUE if YUV range is full.
  Standard_EXPORT bool IsFullRangeYUV() const;

  //! Access data plane for specified Id.
  Standard_EXPORT uint8_t* Plane(int thePlaneId) const;

  //! @return linesize in bytes for specified data plane
  Standard_EXPORT int LineSize(int thePlaneId) const;

  //! @return frame timestamp estimated using various heuristics, in stream time base
  Standard_EXPORT int64_t BestEffortTimestamp() const;

  //! Return frame.
  const AVFrame* Frame() const { return myFrame; }

  //! Return frame.
  AVFrame* ChangeFrame() { return myFrame; }

  //! Return presentation timestamp (PTS).
  double Pts() const { return myFramePts; }

  //! Set presentation timestamp (PTS).
  void SetPts(double thePts) { myFramePts = thePts; }

  //! Return PAR.
  float PixelAspectRatio() const { return myPixelRatio; }

  //! Set PAR.
  void SetPixelAspectRatio(float theRatio) { myPixelRatio = theRatio; }

  //! Return locked state.
  bool IsLocked() const { return myIsLocked; }

  //! Lock/free frame for edition.
  void SetLocked(bool theToLock) { myIsLocked = theToLock; }

public:
  //! Wrap allocated image pixmap.
  Standard_EXPORT bool InitWrapper(const occ::handle<Image_PixMap>& thePixMap);

protected:
  AVFrame* myFrame;      //!< frame
  double   myFramePts;   //!< presentation timestamp
  float    myPixelRatio; //!< pixel aspect ratio
  bool     myIsLocked;   //!< locked state
};
