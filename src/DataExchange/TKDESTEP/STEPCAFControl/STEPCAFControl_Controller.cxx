#include <Interface_Static.hpp>
#include <Standard_Type.hpp>
#include <STEPCAFControl_ActorWrite.hpp>
#include <STEPCAFControl_Controller.hpp>
#include <XSAlgo.hpp>

#include <mutex>

IMPLEMENT_STANDARD_RTTIEXT(STEPCAFControl_Controller, STEPControl_Controller)

STEPCAFControl_Controller::STEPCAFControl_Controller()
{
  occ::handle<STEPCAFControl_ActorWrite> ActWrite = new STEPCAFControl_ActorWrite;
  myAdaptorWrite                                  = ActWrite;
}

bool STEPCAFControl_Controller::Init()
{
  static std::mutex           aMutex;
  std::lock_guard<std::mutex> aLock(aMutex);
  {
    static bool inic = false;
    if (inic)
      return true;
    inic = true;
  }

  occ::handle<STEPCAFControl_Controller> STEPCTL = new STEPCAFControl_Controller;

  XSAlgo::Init();

  STEPCTL->AutoRecord();

  Interface_Static::Init("stepcaf", "write.stepcaf.subshapes.name", 'e', "");
  Interface_Static::Init("stepcaf", "write.stepcaf.subshapes.name", '&', "enum 0");
  Interface_Static::Init("stepcaf", "write.stepcaf.subshapes.name", '&', "eval Off");
  Interface_Static::Init("stepcaf", "write.stepcaf.subshapes.name", '&', "eval On");
  Interface_Static::SetIVal("write.stepcaf.subshapes.name", 0);

  Interface_Static::Init("stepcaf", "read.stepcaf.subshapes.name", 'e', "");
  Interface_Static::Init("stepcaf", "read.stepcaf.subshapes.name", '&', "enum 0");
  Interface_Static::Init("stepcaf", "read.stepcaf.subshapes.name", '&', "eval Off");
  Interface_Static::Init("stepcaf", "read.stepcaf.subshapes.name", '&', "eval On");
  Interface_Static::SetIVal("read.stepcaf.subshapes.name", 0);

  return true;
}
