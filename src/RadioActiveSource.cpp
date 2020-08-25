#include "RadioActiveSource.h"
#include <string>
#include "globals.h"
#include <vector>
#include <sstream>
#include <iostream>

RadioActiveSource::RadioActiveSource(std::string inSource,int inNFile,int inCalibHeight)
{

    source=inSource;
    calibHeight=inCalibHeight;
    NFile=inNFile;
    if(source.find("Ge68")!=std::string::npos || source.find("ge68")!=std::string::npos)
    {
        gammaEnergy=0.511*2;   //MeV
    }else if (source.find("Cs137")!=std::string::npos || source.find("cs137")!=std::string::npos)
    {
        gammaEnergy=0.662;   //MeV   
    }else if (source.find("Mn54")!=std::string::npos || source.find("mn54")!=std::string::npos)
    {
        gammaEnergy=0.835;   //MeV   
    }else if (source.find("K40")!=std::string::npos || source.find("k40")!=std::string::npos)
    {
        gammaEnergy=1.461;   //MeV   
    }else if (source.find("Co60")!=std::string::npos || source.find("co60")!=std::string::npos)
    {
        gammaEnergy=2.506;   //MeV   
    }else
    {
        gammaEnergy=0;
    }
    
    //initial fit parameters
    NPars=4;
    initialAmp=0;
    initialMean=0;
    initialSigma=0;
    initialELeapFrac=0;
    matchMean=0;
    ReadInitialFitPars();   //read from xml file
    std::stringstream fmt;
    fmt<<ANATOP<<"/input/ELeapSpec/"<<source<<"_"<<calibHeight<<"mm_EleapSpec.txt";
    gr_ELeap=new TGraph(fmt.str().c_str());
}

RadioActiveSource::~RadioActiveSource()
{
    delete gr_ELeap;
}

#include "TXMLEngine.h"
void RadioActiveSource::ReadInitialFitPars()
{
    using namespace std;
    
    std::string lowSource=source;
    for(int i=0;i<lowSource.size();i++) lowSource[i]=tolower(lowSource[i]);
    std::string xmlFile=ANATOP+Form("/input/xml/%sfitpars.xml",lowSource.c_str());
    TXMLEngine xml;
    XMLDocPointer_t xmldoc=xml.ParseFile(xmlFile.c_str());
    XMLNodePointer_t node=xml.DocGetRootElement(xmldoc);     //root Node
 
    //Find Source Node
    
    while(strcmp(xml.GetNodeName(node),"Source") != 0 ){
        node = xml.GetChild(node);
        if( node == 0 ){
            break;
        }
    }

    
    //FitPars Node
    node=xml.GetChild(node); 

    //find right calibhight node
    while(node != 0){
        XMLAttrPointer_t attr=xml.GetFirstAttr(node);

        //Find CalibHeight Attribute
        while(attr != 0){
            if(strcmp(xml.GetAttrName(attr),"CalibHeight") == 0){
                break;
            }else{
                attr = xml.GetNextAttr(attr);
            }
        }

        if(atoi(xml.GetAttrValue(attr)) == calibHeight){
            break;
        }else
        {
            node = xml.GetNext(node);
        }
    
    }

    //now we get the right node
    node = xml.GetChild(node);
    while (node != 0 )
    {
        XMLAttrPointer_t attr=xml.GetFirstAttr(node);
        if(strcmp(xml.GetNodeName(node),"Amp") == 0) {
            initialAmp=atof(xml.GetAttrValue(attr));
        }else if(strcmp(xml.GetNodeName(node),"Mean") == 0){
            initialMean=atof(xml.GetAttrValue(attr));
        }else if(strcmp(xml.GetNodeName(node),"Sigma") == 0){
            initialSigma=atof(xml.GetAttrValue(attr));
        }else if(strcmp(xml.GetNodeName(node),"ELeapFrac") == 0){
            initialELeapFrac=atof(xml.GetAttrValue(attr));
        }else if(strcmp(xml.GetNodeName(node),"MatchMean") == 0){
            matchMean=atof(xml.GetAttrValue(attr));
        }
        node=xml.GetNext(node);
    }
    
    xml.FreeDoc(xmldoc);   
}

double RadioActiveSource::Gaus(double* x,double* par)
{
    double energy=x[0];
    double amp=par[0]/(sqrt(2*3.1415926)*par[2]);
    return amp*exp(-0.5*pow((energy-par[1])/par[2],2));
}

double RadioActiveSource::ELeapSpec(double* x,double* par)
{
    double energy=x[0];
    double eScale=par[1]/matchMean;
    return par[0]*gr_ELeap->Eval(energy/eScale);
}

double RadioActiveSource::MCShape(double* x,double* par)
{
    double gausPars[3]={par[0]*(1-par[3]),par[1],par[2]};
    double gaus=Gaus(x,gausPars);

    double eleapPars[2]={par[0]*par[3],par[1]};
    double eleap=ELeapSpec(x,eleapPars);

    return gaus+eleap;
}


std::vector<std::string> RadioActiveSource::GetFileNames()
{
    using std::stringstream;
    std::vector<std::string> tmp_fileNames(0);
    for(int i=0;i<NFile;i++){
        stringstream fmt;
        fmt<<DATATOP<<"/"<<source<<"/data/"<<source<<"_"<<calibHeight<<"mm_v"<<i<<".root";
        tmp_fileNames.push_back(fmt.str());
    }
    return tmp_fileNames;
}

float RadioActiveSource::GetTotalPEHistXMin()
{
    return 0.36*gammaEnergy*4300;
}

float RadioActiveSource::GetTotalPEHistXMax()
{
    return 1.2*gammaEnergy*4300;
}

int RadioActiveSource::GetTotalPEHistNBins()
{
    return 200;
}


std::string RadioActiveSource::GetSourceLabel()
{
    using std::stringstream;
    stringstream fmt;
    fmt<<source<<"_CalibHeight-"<<calibHeight;
    return fmt.str();
}

std::ostream & operator<<(std::ostream & os, const RadioActiveSource radioAS)
{
    using namespace std;
    
    os<<"------------------------------------------------------"<<endl;
    os<<"Source Name : "<<radioAS.source<<endl;
    os<<"Calibration Height : "<<radioAS.calibHeight<<endl;
    os<<"Gamma Energy : "<<radioAS.gammaEnergy<<"[MeV]"<<endl;
    os<<"Number of root file : "<<radioAS.NFile<<endl;
    os<<"Initial fitting parameters : "<<endl;
    os<<"                           Amp: "<<radioAS.initialAmp<<endl;
    os<<"                           Mean: "<<radioAS.initialMean<<endl;
    os<<"                           Sigma: "<<radioAS.initialSigma<<endl;
    os<<"                           Energy Leap Fraction: "<<radioAS.initialELeapFrac<<endl;
    os<<"                           Match Mean: "<<radioAS.matchMean<<endl; 
    os<<"------------------------------------------------------"<<endl;
    return os;
}
