#include "fs.h"

#include <mach-o/dyld.h>
#include <string>

std::string fs::getPath(const std::string &resource) {
  char buffer[1024];
  uint32_t size = sizeof(buffer);
  _NSGetExecutablePath(buffer, &size);
  std::string path(buffer);
  return path.substr(0, path.find_last_of('/') + 1) + resource;
}
