#include "fs.h"

#include <windows.h>
#include <codecvt>
#include <locale>
#include <string>

std::string fs::getPath(const std::string &resource) {
  wchar_t buffer[MAX_PATH];
  GetModuleFileNameW(NULL, buffer, MAX_PATH);
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  std::string path = converter.to_bytes(std::wstring(buffer));
  return path.substr(0, path.find_last_of('\\') + 1) + resource;
}
