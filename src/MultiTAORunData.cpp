
#include "MultiTAORunData.h"
#include "RadioActiveSource.h"
#include <vector>
#include <string>
#include "TF1.h"
#include "globals.h"

MultiTAORunData::MultiTAORunData(std::vector<std::string> inSources,int NFile)
{  
    NPars=0;
    for(int i=0;i<inSources.size();i++){
        sources.push_back(inSources[i]);
        TAORunData* tmp_taorun = new TAORunData(inSources[i],NFile);
        taoRunDatas.push_back(tmp_taorun);
        NPars+=tmp_taorun->GetRadioActiveSource()->GetNPars();

        //get min and max energy
        if(i==0){
            minGammaEnergy = tmp_taorun->GetRadioActiveSource()->GetGammaEnergy();
            maxGammaEnergy = tmp_taorun->GetRadioActiveSource()->GetGammaEnergy();
        }else
        {
            float tmp_energy=tmp_taorun->GetRadioActiveSource()->GetGammaEnergy();
            if(tmp_energy<minGammaEnergy) minGammaEnergy=tmp_energy;
            if(tmp_energy>maxGammaEnergy) maxGammaEnergy=tmp_energy;
        }

        
    }

    for(int i=0;i<sources.size();i++){
        taoRunDatas[i]->GetRadioActiveSource()->SetXMin(minGammaEnergy*0.36*GAMMALY);
        taoRunDatas[i]->GetRadioActiveSource()->SetXMax(maxGammaEnergy*1.2*GAMMALY);
        taoRunDatas[i]->GetRadioActiveSource()->SetNBins(sources.size()*150);
        taoRunDatas[i]->UpdateHist();
    }

    totalPESpectrum = new TH1F("TotalPE_Spectrum","TotalPE_Spectrum",sources.size()*150,minGammaEnergy*0.36*GAMMALY,maxGammaEnergy*1.2*GAMMALY);
    totalPESpectrum->GetXaxis()->SetTitle("Total PE");
    totalPESpectrum->GetYaxis()->SetTitle("Count");

    //Initia        tfTotalMCShape
    tfTotalMCShape=new TF1("MCShape",this,&MultiTAORunData::TotalMCShape,minGammaEnergy*0.36*GAMMALY,maxGammaEnergy*1.2*GAMMALY,NPars,"MultiTAORunData","TotalMCShape");
    tfTotalMCShape->SetNpx(1000);
    //Set Initial Parameters
    int currentPar=0;
    for(int i=0;i<sources.size();i++){
        currentPar=i*4;
        tfTotalMCShape->SetParameter(currentPar,taoRunDatas[i]->GetRadioActiveSource()->GetInitialAmp());
        tfTotalMCShape->SetParName(currentPar,(sources[i]+"_Amplitude").c_str());
        tfTotalMCShape->SetParameter(currentPar+1,taoRunDatas[i]->GetRadioActiveSource()->GetInitialMean());
        tfTotalMCShape->SetParName(currentPar+1,(sources[i]+"_Gaus_Mean").c_str());
        tfTotalMCShape->SetParameter(currentPar+2,taoRunDatas[i]->GetRadioActiveSource()->GetInitialSigma());
        tfTotalMCShape->SetParName(currentPar+2,(sources[i]+"_Gaus_Sigma").c_str());
        tfTotalMCShape->SetParameter(currentPar+3,taoRunDatas[i]->GetRadioActiveSource()->GetInitialELeapFrac());
        tfTotalMCShape->SetParName(currentPar+3,(sources[i]+"_ELeapFrac.").c_str());
    }    
}

MultiTAORunData::MultiTAORunData(std::string inSources[], int N,int NFile)
{
    NPars=0;
    for(int i=0;i<N;i++){
        sources.push_back(inSources[i]);
        TAORunData* tmp_taorun = new TAORunData(inSources[i],NFile);
        taoRunDatas.push_back(tmp_taorun);
        NPars+=tmp_taorun->GetRadioActiveSource()->GetNPars();

        //get min and max energy
        if(i==0){
            minGammaEnergy = tmp_taorun->GetRadioActiveSource()->GetGammaEnergy();
            maxGammaEnergy = tmp_taorun->GetRadioActiveSource()->GetGammaEnergy();
        }else
        {
            float tmp_energy=tmp_taorun->GetRadioActiveSource()->GetGammaEnergy();
            if(tmp_energy<minGammaEnergy) minGammaEnergy=tmp_energy;
            if(tmp_energy>maxGammaEnergy) maxGammaEnergy=tmp_energy;
        }

        
    }

    float sameXmin=minGammaEnergy*0.36*GAMMALY;
    float sameXmax=maxGammaEnergy*1.2*GAMMALY;

    for(int i=0;i<sources.size();i++){
        taoRunDatas[i]->GetRadioActiveSource()->SetXMin(sameXmin);
        taoRunDatas[i]->GetRadioActiveSource()->SetXMax(sameXmax);
        taoRunDatas[i]->GetRadioActiveSource()->SetNBins(sources.size()*150);
        taoRunDatas[i]->UpdateHist();
    }

    totalPESpectrum = new TH1F("TotalPE_Spectrum","TotalPE_Spectrum",sources.size()*150,sameXmin,sameXmax);
    totalPESpectrum->GetXaxis()->SetTitle("Total PE");
    totalPESpectrum->GetYaxis()->SetTitle("Count");

    //Initia        tfTotalMCShape
    tfTotalMCShape=new TF1("MCShape",this,&MultiTAORunData::TotalMCShape,minGammaEnergy*0.36*GAMMALY,maxGammaEnergy*1.2*GAMMALY,NPars,"MultiTAORunData","TotalMCShape");
    tfTotalMCShape->SetNpx(1000);
    //Set Initial Parameters
    int currentPar=0;
    for(int i=0;i<sources.size();i++){
        currentPar=i*4;
        tfTotalMCShape->SetParameter(currentPar,taoRunDatas[i]->GetRadioActiveSource()->GetInitialAmp());
        tfTotalMCShape->SetParName(currentPar,(sources[i]+"_Amplitude").c_str());
        tfTotalMCShape->SetParameter(currentPar+1,taoRunDatas[i]->GetRadioActiveSource()->GetInitialMean());
        tfTotalMCShape->SetParName(currentPar+1,(sources[i]+"_Gaus_Mean").c_str());
        tfTotalMCShape->SetParameter(currentPar+2,taoRunDatas[i]->GetRadioActiveSource()->GetInitialSigma());
        tfTotalMCShape->SetParName(currentPar+2,(sources[i]+"_Gaus_Sigma").c_str());
        tfTotalMCShape->SetParameter(currentPar+3,taoRunDatas[i]->GetRadioActiveSource()->GetInitialELeapFrac());
        tfTotalMCShape->SetParName(currentPar+3,(sources[i]+"_ELeapFrac.").c_str());
    }    
}

MultiTAORunData::~MultiTAORunData()
{
    for(int i=0;i<taoRunDatas.size();i++){
        delete taoRunDatas[i];
    }
}

double MultiTAORunData::TotalMCShape(double* x,double* pars)
{
    double value=0;
    double *ptr_par=pars;
    for(int i=0;i<taoRunDatas.size();i++)
    {
        ptr_par=&(pars[i*4]);
        value+=taoRunDatas[i]->GetRadioActiveSource()->MCShape(x,ptr_par);        
    }
    return value;
}

TF1* MultiTAORunData::GetTFTotalMCShape()
{
    return tfTotalMCShape;
}

TH1F* MultiTAORunData::GetTotalPESpectrum()
{
    return totalPESpectrum;
}

TAORunData* MultiTAORunData::GetTAORunData(std::string name)
{
    int count=-1;
    for(int i=0;i<sources.size();i++){
        if(strcmp(name.c_str(),sources[i].c_str())==0){
            count=i;
            break;
        }
    }
    if(count==-1){
        return 0;
    }else{
        return taoRunDatas[count];
    }
}


TAORunData* MultiTAORunData::GetTAORunData(int index)
{
    
    if(index>=sources.size() || index<0){
        return 0;
    }else{
        return taoRunDatas[index];
    }
}
void MultiTAORunData::FillTotalPESpectrum()
{
    totalPESpectrum->Sumw2();
    for(int i=0;i<sources.size();i++){
       taoRunDatas[i]->FillHistOfTotalPE();
       totalPESpectrum->Add(taoRunDatas[i]->GetHistOfTotalPE(),1);
    }
    totalPESpectrum->Sumw2(false);
}

void MultiTAORunData::FitTotalPESprectrum()
{
    totalPESpectrum->Fit(tfTotalMCShape,"");

    //set parameters to every source.
    for(int i=0;i<sources.size();i++){
        for(int j=0;j<taoRunDatas[i]->GetRadioActiveSource()->GetNPars();j++){
            taoRunDatas[i]->GetTFMCShape()->SetParameter(j,tfTotalMCShape->GetParameter(i*4+j));
        }
    }
}



void MultiTAORunData::AddBkg(float time)
{
    TH1F* signal=totalPESpectrum;

    //Read the file
    TFile* bkgFile=TFile::Open((ANATOP+"/input/Bkg/AssumedBkg.root").c_str());
    TH1F* bkgHist=(TH1F*)bkgFile->Get("Bkg_601.4s");

    //create bkg hist
    TH1F* sampleBkg=new TH1F("SampleBkg","SampleBkg",signal->GetNbinsX(),signal->GetXaxis()->GetXmin(),signal->GetXaxis()->GetXmax());
    float NBkg=bkgHist->GetEntries()*time/601.4;
    for(int i=0;i<NBkg;i++){
        sampleBkg->Fill(bkgHist->GetRandom());
    }
    signal->Sumw2(true);
    signal->Add(sampleBkg,1);
    signal->Sumw2(false);
    bkgFile->Close();
}

void MultiTAORunData::SubBkg(float time)
{
    TH1F* signal=totalPESpectrum;

    //Read the file
    TFile* bkgFile=TFile::Open((ANATOP+"/input/Bkg/AssumedBkg.root").c_str());
    TH1F* bkgHist=(TH1F*)bkgFile->Get("Bkg_601.4s");

    //create bkg hist
    TH1F* sampleBkg=new TH1F("SampleBkg","SampleBkg",signal->GetNbinsX(),signal->GetXaxis()->GetXmin(),signal->GetXaxis()->GetXmax());
    float NBkg=bkgHist->GetEntries()*time/601.4;
    for(int i=0;i<NBkg;i++){
        sampleBkg->Fill(bkgHist->GetRandom());
    }
    signal->Sumw2(true);
    signal->Add(sampleBkg,-1);
    signal->Sumw2(false);
    bkgFile->Close();
}

void MultiTAORunData::ASBkg(float time)
{
    AddBkg(time);
    SubBkg(time);
}

