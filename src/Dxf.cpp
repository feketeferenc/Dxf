#include "Dxf.h"
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;

Gv_pair::Gv_pair(int i, string s) : gc(i), av(s) {};
Gv_pair::Gv_pair(int i, double d) : gc(i), av("") { stringstream s; s << d; av=s.str();};
std::ostream& operator<<(std::ostream& os, const Gv_pair& pair)
{return os << pair.gc << '\n' << pair.av << '\n';}

std::istream& operator>>(std::istream& is, Gv_pair& pair)
{
  string s; getline(is,s);
  pair.gc=atoi(s.c_str()); // stoi valamiért nem működik
  getline(is,pair.av);
  return is;
}

Section::Section(Dxf_section ds) : s(0,"SECTION"), sn(2,"ENTITIES"), data(), en(0,"ENDSEC")
{
    switch (ds)
    {
        case HEADER   : sn.av="HEADER"  ; break;
        case CLASSES  : sn.av="CLASSES" ; break;
        case TABLES   : sn.av="TABLES"  ; break;
        case BLOCKS   : sn.av="BLOCKS"  ; break;
        case ENTITIES : sn.av="ENTITIES"; break;
        case OBJECTS  : sn.av="OBJECTS" ; break;
        case THUMBNAILIMAGE  : sn.av="THUMBNAILIMAGE"; break;
    }
}

void Section::operator()(Gv_pair p)
{data.push_back(p);}

std::ostream& operator<<(std::ostream& os, const Section& ps)
{
    os << ps.s << ps.sn;
    for(Gv_pair p : ps.data) {os << p;}
    return os << ps.en;
}


Dxf::Dxf() : sec()
{ sec[ENTITIES]=Section(ENTITIES); };


void Dxf::read(string fname)
{
    ifstream f(fname);
    Gv_pair p;
    while(!f.eof())
    {
        Gv_pair sp;
        f >> sp;if(sp.gc==0 && sp.av=="EOF") break;
        f >> p;
        if(p.av=="HEADER")
        {
            sec[HEADER]=Section(HEADER);
            f >> p;
            while(!(p.gc==0 && p.av=="ENDSEC"))
            { sec[HEADER](p); f >> p;}
        }
        if(p.av=="CLASSES")
        {
            sec[CLASSES]=Section(CLASSES);
            f >> p;
            while(!(p.gc==0 && p.av=="ENDSEC"))
            { sec[CLASSES](p); f >> p;}
        }
        if(p.av=="TABLES")
        {
            sec[TABLES]=Section(TABLES);
            f >> p;
            while(!(p.gc==0 && p.av=="ENDSEC"))
            { sec[TABLES](p); f >> p;}
        }
        if(p.av=="BLOCKS")
        {
            sec[BLOCKS]=Section(BLOCKS);
            f >> p;
            while(!(p.gc==0 && p.av=="ENDSEC"))
            { sec[BLOCKS](p); f >> p;}
        }
        if(p.av=="ENTITIES")
        {
            f >> p;
            while(!(p.gc==0 && p.av=="ENDSEC"))
            { sec[ENTITIES](p); f >> p;}
        }
        if(p.av=="OBJECTS")
        {
            sec[OBJECTS]=Section(OBJECTS);
            f >> p;
            while(!(p.gc==0 && p.av=="ENDSEC"))
            { sec[OBJECTS](p); f >> p;}
        }
        if(p.av=="THUMBNAILIMAGE")
        {
            sec[THUMBNAILIMAGE]=Section(THUMBNAILIMAGE);
            f >> p;
            while(!(p.gc==0 && p.av=="ENDSEC"))
            { sec[THUMBNAILIMAGE](p); f >> p;}
        }
    }
    f.close();
}

void Dxf::write(string fname)
{
    ofstream f(fname);
    for( std::pair< Dxf_section, Section > s : sec)
    {
        f << s.second;
    }
    f << "  0\n" << "EOF\n";
}

void Dxf::add_line(double x0, double y0, double z0, double x1, double y1, double z1, string layer)
{
    sec[ENTITIES](Gv_pair(0,"LINE"));
    sec[ENTITIES](Gv_pair(8,layer));
    sec[ENTITIES](Gv_pair(10,x0));
    sec[ENTITIES](Gv_pair(20,y0));
    sec[ENTITIES](Gv_pair(30,z0));
    sec[ENTITIES](Gv_pair(11,x1));
    sec[ENTITIES](Gv_pair(21,y1));
    sec[ENTITIES](Gv_pair(31,z1));
}
