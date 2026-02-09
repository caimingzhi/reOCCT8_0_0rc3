

#include <IFSelect.hpp>
#include <IFSelect_SessionFile.hpp>
#include <IFSelect_WorkSession.hpp>

bool IFSelect::SaveSession(const occ::handle<IFSelect_WorkSession>& WS, const char* file)
{
  IFSelect_SessionFile sesfile(WS, file);
  return sesfile.IsDone();
}

bool IFSelect::RestoreSession(const occ::handle<IFSelect_WorkSession>& WS, const char* file)
{
  IFSelect_SessionFile sesfile(WS);
  return (sesfile.Read(file) == 0);
}
