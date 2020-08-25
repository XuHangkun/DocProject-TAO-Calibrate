#include "RadioActiveSource.h"
#include <string>
#include "globals.h"
#include <vector>
#include <sstream>

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
    std::stringstream fmt;
    fmt<<ANATOP<<"/input/ELeapSpec/"<<source<<"_"<<calibHeight<<"mm_EleapSpec.txt";
    gr_ELeap=new TGraph(fmt.str().c_str());
}

RadioActiveSource::~RadioActiveSource()
{
    delete gr_ELeap;
}

#include "TDOMParser.h"
#include "TXMLAttr.h"
#include "TXMLNode.h"
#include "TList.h"
void RadioActiveSource::ReadInitialFitPars()
{
    /*
    std::string lowSource=source;
    for(int i=0;i<lowSource.size();i++) lowSource[i]=tolower(lowSource[i]);
    std::string xmlFile=ANATOP+Form("/xml/%sfitpars.xml",lowSource.c_str());
    TDOMParser *domParser=new TDOMParser();
    domParser->ParseFile(xmlFile.c_str());
    TXMLNode* rootNode=domParser->GetXMLDocument()->GetRootNode();
    TXMLNode* sourceNode=rootNode->GetChildren();  //Get Source Node

    delete domParser;*/
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
