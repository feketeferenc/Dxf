#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "d:/Lib/Dxf/src/dxf.h"
using namespace std;

int main()
{

Dxf d;
d.read("proba.dxf");
// d.add_line(0,0,0,10,10,10,"0");
// d.add_line(0,10,0,10,0,10,"0");
// cout << d.data[HEADER][0];
d.write("kimenet.dxf");

return 0;
}