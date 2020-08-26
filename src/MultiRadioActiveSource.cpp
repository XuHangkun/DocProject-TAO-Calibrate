
#include "MultiRadioActiveSource.h"
#include "RadioActiveSource.h"
#include <vector>
#include <string>
#include "TF1.h"
#include "globals.h"

MultiRadioActiveSource::MultiRadioActiveSource(std::vector<std::string> inSources,int NFile)
{  
    NPars=0;
    for(int i=0;i<inSources.size();i++){
        sources.push_back(inSources[i]);
        RadioActiveSource* tmp_source=new RadioActiveSource(inSources[i],NFile);
        radioActiveSources.push_back(tmp_source);
        NPars+=tmp_source->GetNPars();

        //get min and max energy
        if(i==0){
            minGammaEnergy = tmp_source->GetGammaEnergy();
            maxGammaEnergy = tmp_source->GetGammaEnergy();
        }else
        {
            float tmp_energy=tmp_source->GetGammaEnergy();
            if(tmp_energy<minGammaEnergy) minGammaEnergy=tmp_energy;
            if(tmp_energy>maxGammaEnergy) maxGammaEnergy=tmp_energy;
        }
        
    }
    
}

MultiRadioActiveSource::MultiRadioActiveSource(std::string inSources[], int N,int NFile)
{
    NPars=0;
    for(int i=0;i<N;i++){
        sources.push_back(inSources[i]);
        RadioActiveSource* tmp_source=new RadioActiveSource(inSources[i],NFile);
        radioActiveSources.push_back(tmp_source);
        NPars+=tmp_source->GetNPars();

        //get min and max energy
        if(i==0){
            minGammaEnergy = tmp_source->GetGammaEnergy();
            maxGammaEnergy = tmp_source->GetGammaEnergy();
        }else
        {
            float tmp_energy=tmp_source->GetGammaEnergy();
            if(tmp_energy<minGammaEnergy) minGammaEnergy=tmp_energy;
            if(tmp_energy>maxGammaEnergy) maxGammaEnergy=tmp_energy;
        }
        
    }   
}

MultiRadioActiveSource::~MultiRadioActiveSource()
{
    for(int i=0;i<radioActiveSources.size();i++){
        delete radioActiveSources[i];
    }
}

double MultiRadioActiveSource::TotalMCShape(double* x,double* pars)
{
    double value=0;
    double *ptr_par=pars;
    for(int i=0;i<radioActiveSources.size();i++)
    {
        ptr_par=&(pars[i*4]);
        value+=radioActiveSources[i]->MCShape(x,ptr_par);        
    }
    return value;
}

TF1* MultiRadioActiveSource::TFTotalMCShape()
{

    TF1* function=new TF1("MCShape",this,&MultiRadioActiveSource::TotalMCShape,minGammaEnergy*0.36*GAMMALY,maxGammaEnergy*1.2*GAMMALY,NPars,"MultiRadioActiveSource","TotalMCShape");
    //Set Initial Parameters
    int currentPar=0;
    for(int i=0;i<sources.size();i++){
        currentPar=i*4;
        function->SetParameter(currentPar,radioActiveSources[i]->GetInitialAmp());
        function->SetParameter(currentPar+1,radioActiveSources[i]->GetInitialMean());
        function->SetParameter(currentPar+2,radioActiveSources[i]->GetInitialSigma());
        function->SetParameter(currentPar+3,radioActiveSources[i]->GetInitialELeapFrac());
    }
    return function;
}