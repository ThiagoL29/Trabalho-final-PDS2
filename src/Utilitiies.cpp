#include "../include/Utilitiies.h"

std::string toLower(const std::string &str) {
  std::string strInLowerCase = str;
  std::transform(strInLowerCase.begin(), strInLowerCase.end(),
                 strInLowerCase.begin(), ::tolower);
  return strInLowerCase;
}