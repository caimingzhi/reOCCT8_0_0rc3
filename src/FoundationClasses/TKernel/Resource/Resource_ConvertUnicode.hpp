#pragma once

extern "C"
{

  void Resource_sjis_to_unicode(unsigned int* ph, unsigned int* pl);
  void Resource_unicode_to_sjis(unsigned int* ph, unsigned int* pl);
  void Resource_unicode_to_euc(unsigned int* ph, unsigned int* pl);
  void Resource_euc_to_unicode(unsigned int* ph, unsigned int* pl);
  void Resource_gb_to_unicode(unsigned int* ph, unsigned int* pl);
  void Resource_unicode_to_gb(unsigned int* ph, unsigned int* pl);
}
