#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <numeric>
#include <array>

#include "boost/format.hpp"

using namespace std;
using boost::format;


#ifdef DEBUG
#define dout std::cout
#else
#define dout 0 && cout
#endif