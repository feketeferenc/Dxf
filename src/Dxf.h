#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

enum Dxf_section{HEADER, CLASSES, TABLES, BLOCKS, ENTITIES, OBJECTS, THUMBNAILIMAGE};

struct Gv_pair
{
    int gc;         // group code
    std::string av; // associated value
    Gv_pair(int i=int(0), std::string s=std::string(""));
    Gv_pair(int i, double d);
};
std::ostream& operator<<(std::ostream& os, const Gv_pair& pair);
std::istream& operator>>(std::istream& is, Gv_pair& pair);

struct Section
{
    Gv_pair s;  // 0 SECTION
    Gv_pair sn; // 2 ENTITIES
    std::vector <Gv_pair> data;
    Gv_pair en; // 0 ENDSEC
    Section(Dxf_section ds=HEADER);
    void operator()(Gv_pair p);
};
std::ostream& operator<<(std::ostream& os, const Section& ps);

struct Dxf
{
    std::map< Dxf_section, Section > sec;
    
    Dxf();
    void read(std::string fname);
    void write(std::string fname);
    void add_line(double x0, double y0, double z0, double x1, double y1, double z1, std::string layer="0");
};


/*
void Szerkezet::add_rope(string dxf_file)
{
    ifstream f(dxf_file);
    int c; //group code
    string v; // group code value
    // f >> c >> v;cout << c << '\t' << v << '\n';
    // while(!f.eof())
    for(int i=0; i<1000;i++)
    {
        f >> c >> v;cout << c << '\t' << v << '\n';//; f >> v; 
        if(c!=0 && v!="SECTION") continue;
        else
        {
            f >> c; f >> v;
            if(f!="ENTITIES") continue;
            else
            {
                while(c!=0 && v!="ENDSEC")
                {
                    f >> c; f >> v;
                    if(c!=0 && f!="LINE") continue;
                    else
                    {
                        f >> c;
                        while(c!=10) {f >> v; f >> c;}
                        double x0, y0, z0, x, y, z;
                        f >> x0 >> c >> y0 >> c >> z0;
                        f >> x  >> c >> y  >> c >> z ;
                        this->add_rope(x0,y0,z0,x,y,z);
                    }
                }
            }
        }
    }
}

class Dxf
{

};*/