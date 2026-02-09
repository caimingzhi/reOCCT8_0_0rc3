#pragma once

#include <NCollection_Buffer.hpp>
#include <OpenGl_Buffer.hpp>

template <class BaseBufferT>
class OpenGl_BufferCompatT : public BaseBufferT
{

public:
  OpenGl_BufferCompatT() {}

  ~OpenGl_BufferCompatT() override { Release(nullptr); }

  bool IsVirtual() const override { return true; }

  inline bool Create(const occ::handle<OpenGl_Context>& theGlCtx) override;

  inline void Release(OpenGl_Context* theGlCtx) override;

  void Bind(const occ::handle<OpenGl_Context>&) const override {}

  void Unbind(const occ::handle<OpenGl_Context>&) const override {}

public:
  inline bool initLink(const occ::handle<NCollection_Buffer>& theData,
                       const unsigned int                     theComponentsNb,
                       const int                              theElemsNb,
                       const unsigned int                     theDataType);

  inline bool init(const occ::handle<OpenGl_Context>& theGlCtx,
                   const unsigned int                 theComponentsNb,
                   const int                          theElemsNb,
                   const void*                        theData,
                   const unsigned int                 theDataType,
                   const int                          theStride) override;

  inline bool subData(const occ::handle<OpenGl_Context>& theGlCtx,
                      const int                          theElemFrom,
                      const int                          theElemsNb,
                      const void*                        theData,
                      const unsigned int                 theDataType) override;

  inline bool getSubData(const occ::handle<OpenGl_Context>& theGlCtx,
                         const int                          theElemFrom,
                         const int                          theElemsNb,
                         void*                              theData,
                         const unsigned int                 theDataType) override;

protected:
  occ::handle<NCollection_Buffer> myData;
};

template <class BaseBufferT>
bool OpenGl_BufferCompatT<BaseBufferT>::Create(const occ::handle<OpenGl_Context>&)
{
  if (BaseBufferT::myBufferId == OpenGl_Buffer::NO_BUFFER)
  {
    BaseBufferT::myBufferId = (unsigned int)-1;
    myData                  = new NCollection_Buffer(Graphic3d_Buffer::DefaultAllocator());
  }
  return BaseBufferT::myBufferId != OpenGl_Buffer::NO_BUFFER;
}

template <class BaseBufferT>
void OpenGl_BufferCompatT<BaseBufferT>::Release(OpenGl_Context*)
{
  if (BaseBufferT::myBufferId == OpenGl_Buffer::NO_BUFFER)
  {
    return;
  }

  BaseBufferT::myOffset   = nullptr;
  BaseBufferT::myBufferId = OpenGl_Buffer::NO_BUFFER;
  myData.Nullify();
}

template <class BaseBufferT>
bool OpenGl_BufferCompatT<BaseBufferT>::initLink(const occ::handle<NCollection_Buffer>& theData,
                                                 const unsigned int theComponentsNb,
                                                 const int          theElemsNb,
                                                 const unsigned int theDataType)
{
  if (theData.IsNull())
  {
    BaseBufferT::myOffset = nullptr;
    return false;
  }

  if (BaseBufferT::myBufferId == OpenGl_Buffer::NO_BUFFER)
  {
    BaseBufferT::myBufferId = (unsigned int)-1;
  }
  myData                      = theData;
  BaseBufferT::myDataType     = theDataType;
  BaseBufferT::myComponentsNb = theComponentsNb;
  BaseBufferT::myElemsNb      = theElemsNb;
  BaseBufferT::myOffset       = myData->ChangeData();
  return true;
}

template <class BaseBufferT>
bool OpenGl_BufferCompatT<BaseBufferT>::init(const occ::handle<OpenGl_Context>& theCtx,
                                             const unsigned int                 theComponentsNb,
                                             const int                          theElemsNb,
                                             const void*                        theData,
                                             const unsigned int                 theDataType,
                                             const int                          theStride)
{
  if (!Create(theCtx))
  {
    BaseBufferT::myOffset = nullptr;
    return false;
  }

  BaseBufferT::myDataType     = theDataType;
  BaseBufferT::myComponentsNb = theComponentsNb;
  BaseBufferT::myElemsNb      = theElemsNb;

  const size_t aNbBytes = size_t(BaseBufferT::myElemsNb) * theStride;
  if (!myData->Allocate(aNbBytes))
  {
    BaseBufferT::myOffset = nullptr;
    return false;
  }

  BaseBufferT::myOffset = myData->ChangeData();
  if (theData != nullptr)
  {
    memcpy(myData->ChangeData(), theData, aNbBytes);
  }
  return true;
}

template <class BaseBufferT>
bool OpenGl_BufferCompatT<BaseBufferT>::subData(const occ::handle<OpenGl_Context>&,
                                                const int          theElemFrom,
                                                const int          theElemsNb,
                                                const void*        theData,
                                                const unsigned int theDataType)
{
  if (!BaseBufferT::IsValid() || BaseBufferT::myDataType != theDataType || theElemFrom < 0
      || ((theElemFrom + theElemsNb) > BaseBufferT::myElemsNb))
  {
    return false;
  }
  else if (theData == nullptr)
  {
    return true;
  }

  const size_t aDataSize = BaseBufferT::sizeOfGlType(theDataType);
  const size_t anOffset  = size_t(theElemFrom) * size_t(BaseBufferT::myComponentsNb) * aDataSize;
  const size_t aNbBytes  = size_t(theElemsNb) * size_t(BaseBufferT::myComponentsNb) * aDataSize;
  memcpy(myData->ChangeData() + anOffset, theData, aNbBytes);
  return true;
}

template <class BaseBufferT>
bool OpenGl_BufferCompatT<BaseBufferT>::getSubData(const occ::handle<OpenGl_Context>&,
                                                   const int          theElemFrom,
                                                   const int          theElemsNb,
                                                   void*              theData,
                                                   const unsigned int theDataType)
{
  if (!BaseBufferT::IsValid() || BaseBufferT::myDataType != theDataType || theElemFrom < 0
      || ((theElemFrom + theElemsNb) > BaseBufferT::myElemsNb) || theData == nullptr)
  {
    return false;
  }

  const size_t aDataSize = BaseBufferT::sizeOfGlType(theDataType);
  const size_t anOffset  = size_t(theElemFrom) * size_t(BaseBufferT::myComponentsNb) * aDataSize;
  const size_t aNbBytes  = size_t(theElemsNb) * size_t(BaseBufferT::myComponentsNb) * aDataSize;
  memcpy(theData, myData->Data() + anOffset, aNbBytes);
  return true;
}

#include <OpenGl_VertexBuffer.hpp>
#include <OpenGl_IndexBuffer.hpp>

typedef OpenGl_BufferCompatT<OpenGl_VertexBuffer> OpenGl_VertexBufferCompat;
typedef OpenGl_BufferCompatT<OpenGl_IndexBuffer>  OpenGl_IndexBufferCompat;
