#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm>
#include <string>

std::string toLower(const std::string &str) {
  std::string strInLowerCase = str;
  std::transform(strInLowerCase.begin(), strInLowerCase.end(),
                 strInLowerCase.begin(), ::tolower);
  return strInLowerCase;
}

#endif