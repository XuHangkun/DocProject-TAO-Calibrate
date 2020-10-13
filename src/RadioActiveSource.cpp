#include "RadioActiveSource.h"
#include <string>
#include "globals.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "TF1.h"

RadioActiveSource::RadioActiveSource(std::string inSource,float calibHeight)
{

    source=inSource;
    calibPosition.SetX(0.);
    calibPosition.SetY(0.);
    calibPosition.SetZ(calibHeight);
    QuerySourceKinetic();
    
    //initial fit parameters
    NPars=4;
    initialAmp=0;
    initialMean=0;
    initialSigma=0;
    initialELeapFrac=0;
    matchMean=0;

    //create tfMCShape and initialize the parameters
    tfMCShape = new TF1("MCShape",this,&RadioActiveSource::MCShape,0.36*kinetic*GAMMALY,1.2*kinetic*1.2,NPars,"RadioActiveSource","MCShape");   // create TF1 class.
    tfMCShape->SetParameter(0,initialAmp);
    tfMCShape->SetParName(0,"Amplitude");
    tfMCShape->SetParameter(1,initialMean);
    tfMCShape->SetParName(1,"Gaus_Mean");
    tfMCShape->SetParameter(2,initialSigma);
    tfMCShape->SetParName(2,"Gaus_Sigma");
    tfMCShape->SetParameter(3,initialELeapFrac);
    tfMCShape->SetParName(3,"ELeapFrac.");

}

RadioActiveSource::RadioActiveSource(std::string inSource,float inKinetic,float calibHeight)
{

    source=inSource;
    calibPosition.SetX(0.);
    calibPosition.SetY(0.);
    calibPosition.SetZ(calibHeight);
    kinetic=inKinetic;
    
    //initial fit parameters
    NPars=4;
    initialAmp=0;
    initialMean=0;
    initialSigma=0;
    initialELeapFrac=0;
    matchMean=0;

    //create tfMCShape and initialize the parameters
    tfMCShape = new TF1("MCShape",this,&RadioActiveSource::MCShape,0.36*kinetic*GAMMALY,1.2*kinetic*1.2,NPars,"RadioActiveSource","MCShape");   // create TF1 class.
    tfMCShape->SetParameter(0,initialAmp);
    tfMCShape->SetParName(0,"Amplitude");
    tfMCShape->SetParameter(1,initialMean);
    tfMCShape->SetParName(1,"Gaus_Mean");
    tfMCShape->SetParameter(2,initialSigma);
    tfMCShape->SetParName(2,"Gaus_Sigma");
    tfMCShape->SetParameter(3,initialELeapFrac);
    tfMCShape->SetParName(3,"ELeapFrac.");

}

RadioActiveSource::RadioActiveSource(std::string inSource,TVector3 inCalibPos)
{

    source=inSource;
    calibPosition.SetX(inCalibPos.X());
    calibPosition.SetY(inCalibPos.Y());
    calibPosition.SetZ(inCalibPos.Z());
    QuerySourceKinetic();
    

    //initial fit parameters
    NPars=4;
    initialAmp=0;
    initialMean=0;
    initialSigma=0;
    initialELeapFrac=0;
    matchMean=0;

    //create tfMCShape and initialize the parameters
    tfMCShape = new TF1("MCShape",this,&RadioActiveSource::MCShape,0.36*kinetic*GAMMALY,1.2*kinetic*1.2,NPars,"RadioActiveSource","MCShape");   // create TF1 class.
    tfMCShape->SetParameter(0,initialAmp);
    tfMCShape->SetParName(0,"Amplitude");
    tfMCShape->SetParameter(1,initialMean);
    tfMCShape->SetParName(1,"Gaus_Mean");
    tfMCShape->SetParameter(2,initialSigma);
    tfMCShape->SetParName(2,"Gaus_Sigma");
    tfMCShape->SetParameter(3,initialELeapFrac);
    tfMCShape->SetParName(3,"ELeapFrac.");

}

RadioActiveSource::RadioActiveSource(std::string inSource,float inKinetic,TVector3 inCalibPos)
{

    source=inSource;
    calibPosition.SetX(inCalibPos.X());
    calibPosition.SetY(inCalibPos.Y());
    calibPosition.SetZ(inCalibPos.Z());
    kinetic=inKinetic;
    

    //initial fit parameters
    NPars=4;
    initialAmp=0;
    initialMean=0;
    initialSigma=0;
    initialELeapFrac=0;
    matchMean=0;

    //create tfMCShape and initialize the parameters
    tfMCShape = new TF1("MCShape",this,&RadioActiveSource::MCShape,0.36*kinetic*GAMMALY,1.2*kinetic*1.2,NPars,"RadioActiveSource","MCShape");   // create TF1 class.
    tfMCShape->SetParameter(0,initialAmp);
    tfMCShape->SetParName(0,"Amplitude");
    tfMCShape->SetParameter(1,initialMean);
    tfMCShape->SetParName(1,"Gaus_Mean");
    tfMCShape->SetParameter(2,initialSigma);
    tfMCShape->SetParName(2,"Gaus_Sigma");
    tfMCShape->SetParameter(3,initialELeapFrac);
    tfMCShape->SetParName(3,"ELeapFrac.");

}

RadioActiveSource::~RadioActiveSource()
{
    delete gr_ELeap;
    delete tfMCShape;
}

#include "TXMLEngine.h"
bool RadioActiveSource::ReadInitialFitPars()
{
    using namespace std;
    
    std::string lowSource=source;
    for(int i=0;i<lowSource.size();i++) lowSource[i]=tolower(lowSource[i]);
    std::string xmlFile=ANATOP+Form("/input/xml/%sfitpars.xml",lowSource.c_str());
    //cout<<xmlFile<<endl;
    if ( access(xmlFile.c_str(),F_OK)==(-1) ) return false;
    TXMLEngine xml;
    XMLDocPointer_t xmldoc=xml.ParseFile(xmlFile.c_str());
    XMLNodePointer_t node=xml.DocGetRootElement(xmldoc);     //root Node
 
    //Find Source Node
    
    while(strcmp(xml.GetNodeName(node),"Source") != 0 ){
        cout<<xml.GetNodeName(node)<<endl;
        node = xml.GetChild(node);
        cout<<xml.GetNodeName(node)<<endl;
        if( node == 0 ){
            break;
        }
    }

    
    //FitPars Node
    node=xml.GetChild(node); 

    //find right calibhight node
    while(node != 0){
        XMLAttrPointer_t attr=xml.GetFirstAttr(node);

        //Find calibPosition.Z() Attribute
        float tmp_x=1;
        float tmp_y=1;
        float tmp_z=1;
        while(attr != 0){
            //cout<<xml.GetAttrName(attr)<<"\t"<<xml.GetAttrValue(attr)<<endl;
            if(strcmp(xml.GetAttrName(attr),"CalibPosZ") == 0){
                tmp_z=atof(xml.GetAttrValue(attr));
            }else if(strcmp(xml.GetAttrName(attr),"CalibPosX") == 0){
                tmp_x=atof(xml.GetAttrValue(attr));
            }else if(strcmp(xml.GetAttrName(attr),"CalibPosY") == 0){
                tmp_y=atof(xml.GetAttrValue(attr));
            }
            attr = xml.GetNextAttr(attr);
        }
        
        if(calibPosition.X()==tmp_x && calibPosition.Y()==tmp_y && calibPosition.Z()==tmp_z){
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

    //Read Energy Leap Spectrum
    std::stringstream fmt;
    fmt<<ANATOP<<"/input/ELeapSpec/"<<source<<"_"<<calibPosition.Z()<<"mm_EleapSpec.txt";
    //std::cout<<fmt.str()<<std::endl;
    gr_ELeap=new TGraph(fmt.str().c_str());

    //Initialze the parameters of fitting function
    tfMCShape->SetParameter(0,initialAmp);
    tfMCShape->SetParName(0,"Amplitude");
    tfMCShape->SetParameter(1,initialMean);
    tfMCShape->SetParName(1,"Gaus_Mean");
    tfMCShape->SetParameter(2,initialSigma);
    tfMCShape->SetParName(2,"Gaus_Sigma");
    tfMCShape->SetParameter(3,initialELeapFrac);
    tfMCShape->SetParName(3,"ELeapFrac.");
    cout<<"Amp: "<<initialAmp<<"\tMean:"<<initialMean<<"\tSigma"<<initialSigma<<"\tELeap"<<initialELeapFrac<<"\tMatchMean:"<<matchMean<<std::endl;

    return true;
}

double RadioActiveSource::Gaus(double* x,double* par)
{
    double energy=x[0];
    return par[0]*exp(-0.5*pow((energy-par[1])/(par[1]*par[2]*0.01),2));
}

double RadioActiveSource::ELeapSpec(double* x,double* par)
{
    double energy=x[0];
    double eScale=par[1]/matchMean;
    return par[0]*gr_ELeap->Eval(energy/eScale);
}

double RadioActiveSource::MCShape(double* x,double* par)
{
    double gausPars[3]={par[0],par[1],par[2]};
    double gaus=Gaus(x,gausPars);

    double eleapPars[2]={par[0]*par[3],par[1]};
    double eleap=ELeapSpec(x,eleapPars);

    return gaus+eleap;
}



std::string RadioActiveSource::GetSourceLabel()
{
    using std::stringstream;
    stringstream fmt;
    fmt<<source<<"_Kinetic_"<<kinetic<<"_"<<"X"<<calibPosition.X()<<"_"<<"Y"<<calibPosition.Y()<<"_"<<"Z"<<calibPosition.Z();
    return fmt.str();
}

void RadioActiveSource::QuerySourceKinetic()
{
    if(source.find("Ge68")!=std::string::npos || source.find("ge68")!=std::string::npos)
    {
        kinetic=0.511*2;   //MeV
    }else if (source.find("Cs137")!=std::string::npos || source.find("cs137")!=std::string::npos)
    {
        kinetic=0.6617;   //MeV   
    }else if (source.find("Mn54")!=std::string::npos || source.find("mn54")!=std::string::npos)
    {
        kinetic=0.835;   //MeV   
    }else if (source.find("K40")!=std::string::npos || source.find("k40")!=std::string::npos)
    {
        kinetic=1.461;   //MeV   
    }else if (source.find("Co60")!=std::string::npos || source.find("co60")!=std::string::npos)
    {
        kinetic=2.50574;   //MeV   
    }else{
        kinetic=0;
    }
}

std::ostream & operator<<(std::ostream & os, const RadioActiveSource radioAS)
{
    using namespace std;
    
    os<<"------------------------------------------------------"<<endl;
    os<<"Source Name : "<<radioAS.source<<endl;
    os<<"Calibration Height : "<<radioAS.calibPosition.Z()<<endl;
    os<<"Kinetic Energy : "<<radioAS.kinetic<<"[MeV]"<<endl;
    os<<"Initial fitting parameters : "<<endl;
    os<<"                           Amp: "<<radioAS.initialAmp<<endl;
    os<<"                           Mean: "<<radioAS.initialMean<<endl;
    os<<"                           Sigma: "<<radioAS.initialSigma<<endl;
    os<<"                           Energy Leap Fraction: "<<radioAS.initialELeapFrac<<endl;
    os<<"                           Match Mean: "<<radioAS.matchMean<<endl; 
    os<<"------------------------------------------------------"<<endl;
    return os;
}
