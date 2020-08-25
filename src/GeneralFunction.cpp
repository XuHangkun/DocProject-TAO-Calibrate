#include <string>
#include <algorithm>
#include "GeneralFunction.h"


float EvaluateTotalPEHistMin(std::string source)
{
    using namespace std;
    transform(source.begin(), source.end(), source.begin(), ::tolower); //转换成小写

    float hist_min=0;
    float assumedLY=4300;
    if(source.find("ge68")!=string::npos)
    {
        hist_min=0.2*assumedLY*1.022;
    }else if (source.find("cs137")!=string::npos)
    {
        hist_min=0.2*assumedLY*0.662;
    }else if (source.find("mn54")!=string::npos)
    {
        hist_min=0.2*assumedLY*0.835;
    }else if (source.find("k40")!=string::npos)
    {
        hist_min=0.2*assumedLY*1.461;
    }else if (source.find("co60")!=string::npos)
    {
        hist_min=0.2*assumedLY*2.506;
    }else{
        hist_min=500;
    }
    return hist_min;

}

float EvaluateTotalPEHistMax(std::string source)
{
    using namespace std;
    transform(source.begin(), source.end(), source.begin(), ::tolower); //转换成小写

    float hist_max=0;
    float assumedLY=4300;
    if(source.find("ge68")!=string::npos)
    {
        hist_max=1.2*assumedLY*1.022;
    }else if (source.find("cs137")!=string::npos)
    {
        hist_max=1.2*assumedLY*0.662;
    }else if (source.find("mn54")!=string::npos)
    {
        hist_max=1.2*assumedLY*0.835;
    }else if (source.find("k40")!=string::npos)
    {
        hist_max=1.2*assumedLY*1.461;
    }else if (source.find("co60")!=string::npos)
    {
        hist_max=1.2*assumedLY*2.506;
    }else{
        hist_max=30000;
    }
    return hist_max;

}