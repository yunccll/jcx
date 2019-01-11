#ifndef  JCX_BASE_CROSSPLATFORM_H
#define  JCX_BASE_CROSSPLATFORM_H

#include <cstdint>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cassert>

#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <unordered_map>
#include <map>
#include <vector>
#include <list>


//WINDOWS IF


//DEFAULT--LINUX
#include <time.h>
#include <unistd.h>
#include <sys/param.h>
#include <fcntl.h>

#include <jcx/base/Macro.h>

#include <jcx/base/ErrorCodeRange.h>
#include <jcx/base/Error.h>

#endif   /* CROSSPLATFORM_H */
