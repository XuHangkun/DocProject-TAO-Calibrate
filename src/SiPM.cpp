#include "SiPM.h"
#include <string>
#include <iostream>
#include <fstream>
#include "globals.h"
#include <cmath>
#include "TMath.h"
#include "TF2.h"
#include "TVector3.h"


SiPM::SiPM()
{
    SiPMX=50.0;      //mm
    SiPMY=50.0;      //mm
    SiPMPosR=930.2;  //mm
    //SiPMSolidAngle
    tf_SiPMSolidAngle=new TF2("SiPMSolidAngle",fSiPMSolidAngle,-SiPMX/2.0,SiPMX/2.0,-SiPMY/2.0,SiPMY/2.0,3);
    //Read SiPM information here
    Initialize();
}

SiPM::~SiPM()
{

}

void SiPM::Initialize()
{
    using namespace std;
    string filename=ANATOP+"/input/SiPM/sipm_pos.csv";
    ifstream indat;
    indat.open(filename.c_str());
    int id=0;
    float theta,phi;
    int index=0;
    while(indat>>id>>theta>>phi){
        theta*=(TMath::Pi()/180.0);
        phi*=(TMath::Pi()/180.0);
        float xx=SiPMPosR*sin(theta)*cos(phi);
        float yy=SiPMPosR*sin(theta)*sin(phi);
        float zz=SiPMPosR*cos(theta);
        ID[index]=id;
        position[index]=TVector3(xx,yy,zz);
        darkNoise[index]=0.;
        index+=1;
    }
    indat.close();

    CalSiPMSolidAngle();
    CoverRatio=NSIPM*SiPMSolidAngle/(4*TMath::Pi());
    //calculate the gap correct factor
    CalGapCorrectFactor();

    
}

//According to center!
void SiPM::CalSiPMSolidAngle()
{
    //SiPMSolidAngle=SiPMX*SiPMY/(SiPMPosR*SiPMPosR);
    SiPMSolidAngle=CalSiPMSolidAngle(2000,TVector3(0,0,0));
}


double SiPM::CalSiPMSolidAngle(int sipmId,TVector3 refPoint)
{
   
    TVector3 delta=refPoint-position[sipmId];
    delta.RotateZ(-position[sipmId].Phi());
    delta.RotateY(-position[sipmId].Theta());
    tf_SiPMSolidAngle->SetParameter(0,delta.X());
    tf_SiPMSolidAngle->SetParameter(1,delta.Y());
    tf_SiPMSolidAngle->SetParameter(2,delta.Z());
    double solidAngle = tf_SiPMSolidAngle->Integral(-SiPMX/2.0,SiPMX/2.0,-SiPMY/2.0,SiPMY/2.0);
    return solidAngle;
}


void SiPM::CalGapCorrectFactor()
{
    float earlyTheta=0.-0.151495;
    float nextTheta=2*TMath::Pi()-2.9901;
    float NRow=0;
    for(int i=0;i<NSIPM;i++){
        earlyTheta=0.-0.151495;
        nextTheta=2*TMath::Pi()-2.9901;
        float thisTheta=position[i].Theta();
        NRow=1;
        //find the early theta
        for(int j=i-1;j>=0;j--){
            if(position[j].Theta()<(thisTheta-0.0001)){
                earlyTheta=position[j].Theta();
                break;
            }
            NRow+=1;
        }
        //find the next theta
        for(int j=i+1;j<NSIPM;j++){
            if(position[j].Theta()>(thisTheta+0.0001)){
                nextTheta=position[j].Theta();
                break;
            }
            NRow+=1;
        }
        earlyTheta=earlyTheta+(thisTheta-earlyTheta)/2.0;
        nextTheta=thisTheta+(nextTheta-thisTheta)/2.0;
        eTheta[i]=earlyTheta;
        nTheta[i]=nextTheta;
        ePhi[i]=position[i].Phi()-TMath::Pi()/NRow;
        nPhi[i]=position[i].Phi()+TMath::Pi()/NRow;
        float solidangle=(cos(earlyTheta)-cos(nextTheta))*2*TMath::Pi();
        gapCorrectFactor[i]=solidangle/(NRow*SiPMSolidAngle);
    }
}

std::ostream& operator<<(std::ostream& os,const SiPM sipm)
{
    using namespace std;
    os<<"--------------------------------------------------------"<<endl;
    os<<"Total SiPM : "<<sipm.NSIPM<<endl;
    os<<"SiPM Size: deltaX: "<<sipm.SiPMX<<"\tdeltaY"<<sipm.SiPMY<<"\t Solid Angle: "<<sipm.SiPMSolidAngle<<endl;
    os<<"SiPM Position Radius: "<<sipm.SiPMPosR<<endl;
    os<<setw(10)<<"ID"<<setw(10)<<"Theta"<<setw(10)<<"Phi"<<setw(10)<<"GapFac."<<endl;
    for(int i=0;i<sipm.NSIPM*0.02;i++){
        os<<setw(10)<<sipm.ID[i]<<setw(10)<<sipm.position[i].Theta()<<setw(10)<<sipm.position[i].Phi()<<setw(10)<<sipm.gapCorrectFactor[i]<<endl;
    }
    os<<"......"<<endl;
    for(int i=0.98*sipm.NSIPM;i<sipm.NSIPM;i++){
        os<<setw(10)<<sipm.ID[i]<<setw(10)<<sipm.position[i].Theta()<<setw(10)<<sipm.position[i].Phi()<<setw(10)<<sipm.gapCorrectFactor[i]<<endl;
    }
    os<<"--------------------------------------------------------"<<endl;
    return os;

}

double fSiPMSolidAngle(double *var,double* par)
{
    //SiPM surface norm 
    return fabs(par[2])/pow((var[0]-par[0])*(var[0]-par[0])+(var[1]-par[1])*(var[1]-par[1])+(par[2])*(par[2]),1.5);
}
