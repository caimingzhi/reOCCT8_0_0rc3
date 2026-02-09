#include <Standard_Type.hpp>
#include <TransferBRep_TransferResultInfo.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TransferBRep_TransferResultInfo, Standard_Transient)

TransferBRep_TransferResultInfo::TransferBRep_TransferResultInfo()
{
  Clear();
}

void TransferBRep_TransferResultInfo::Clear()
{
  myNR = myNRW = myNRF = myNRWF = myR = myRW = myRF = myRWF = 0;
}
