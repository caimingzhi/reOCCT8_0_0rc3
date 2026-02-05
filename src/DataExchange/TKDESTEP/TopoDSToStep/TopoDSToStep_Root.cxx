#include <TopoDSToStep_Root.hpp>

TopoDSToStep_Root::TopoDSToStep_Root()
{
  done  = false;
  toler = 0.0001;
}

double& TopoDSToStep_Root::Tolerance()
{
  return toler;
}

bool TopoDSToStep_Root::IsDone() const
{
  return done;
}
