LIB=d:/Lib

a.exe : $(LIB)/Dxf/o/Dxf.o debug.o
	c++  debug.o $(LIB)/Dxf/o/Dxf.o -o a.exe -std=c++11

debug.o : $(LIB)/Dxf/src/Dxf.h debug.cpp
	c++ -c debug.cpp -o debug.o -std=c++11

$(LIB)/Dxf/o/Dxf.o :  $(LIB)/Dxf/src/Dxf.h $(LIB)/Dxf/src/Dxf.cpp
	c++ -c $(LIB)/Dxf/src/Dxf.cpp -o $(LIB)/DXF/o/Dxf.o -std=c++11
