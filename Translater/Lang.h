#ifndef LANG_H
#define LANG_H

#include <cstring>

enum Lang
{
  RUSSIAN = 1, ENGLISH = 2
};

Lang strToLang(const char* lang);

const char* langToStr(Lang lang);

#endif // LANG_H
