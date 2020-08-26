#include "TAORunData.h"
#include "RadioActiveSource.h"
#include "TChain.h"
#include <string>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include <iostream>
#include "TFile.h"
#include "globals.h"

TAORunData::TAORunData(std::string inSource,int inNFile,int inCalibHeight)
{
    source=inSource;
    calibHeight=inCalibHeight;
    radioActiveSource=new RadioActiveSource(source,inNFile,calibHeight);

    isGamma=false;
    ifASBkg=false;
    gammaNumber=50000;   //defaultly we use 50000 gammas.

    Initialize();

}

TAORunData::~TAORunData()
{
    delete radioActiveSource;


    Finalize();
}

void TAORunData::Initialize()
{
    //create the TChain
    mainTree=new TChain("fSiPMTree");
    TChain* event_tree=new TChain("event_tree");
    TChain* fmuon=new TChain("fmuon");
    std::vector<std::string> fileNames=radioActiveSource->GetFileNames();
    for(int i=0;i<fileNames.size();i++){
        std::cout<<fileNames[i]<<std::endl;
        mainTree->Add(fileNames[i].c_str());
        event_tree->Add(fileNames[i].c_str());
        fmuon->Add(fileNames[i].c_str());
    }
    mainTree->AddFriend("event_tree");
    mainTree->AddFriend("fmuon");

    NEtries=mainTree->GetEntries();
    std::cout<<NEtries<<std::endl;    
    mainTree->SetBranchStatus("*",kFALSE);

    capTime=0;
    mainTree->SetBranchStatus("capTime",kTRUE);
    mainTree->SetBranchAddress("capTime",&capTime);

    
    totalPE=0;
    mainTree->SetBranchStatus("hit_sum",kTRUE);
    mainTree->SetBranchAddress("hit_sum",&totalPE);
    

    NCompton=0;
    mainTree->SetBranchStatus("nCompton",kTRUE);
    mainTree->SetBranchAddress("nCompton",&NCompton);
    
    Edep=0;
    mainTree->SetBranchStatus("event_tree.miniJUNOGdLSEdep",kTRUE);
    mainTree->SetBranchAddress("event_tree.miniJUNOGdLSEdep",&Edep);

    NParticles=0;
    mainTree->SetBranchStatus("vertex.n_particles",kTRUE);
    mainTree->SetBranchAddress("vertex.n_particles",&NParticles);


    EDepCenterX=0;
    mainTree->SetBranchStatus("GdLS.Edep_x",kTRUE);
    mainTree->SetBranchAddress("GdLS.Edep_x",&EDepCenterX);

    EDepCenterY=0;
    mainTree->SetBranchStatus("GdLS.Edep_y",kTRUE);
    mainTree->SetBranchAddress("GdLS.Edep_y",&EDepCenterY);

    EDepCenterZ=0;
    mainTree->SetBranchStatus("GdLS.Edep_z",kTRUE);
    mainTree->SetBranchAddress("GdLS.Edep_z",&EDepCenterZ);
}

void TAORunData::GetEntry(int n)
{

    int pdgs[5]={0};
    mainTree->SetBranchStatus("vertex.pdg_code",kTRUE);
    mainTree->SetBranchAddress("vertex.pdg_code",pdgs);

    mainTree->GetEntry(n);
    currentEntry=n;

    //clean vector
    //judge if the initial contains Gamma or contains positron
    isGamma=false;
    std::vector<int> tmp;
    PDGCode.swap(tmp);
    for(int i=0;i<NParticles;i++){
        PDGCode.push_back(pdgs[i]);
        if(pdgs[i]==22 || pdgs[i]==(-11)){
            isGamma=true;
        }
    }
    mainTree->SetBranchStatus("vertex.pdg_code",kFALSE);

}

std::vector<int>& TAORunData::GetPDGCode()
{
    return PDGCode;
}

std::vector<double>& TAORunData::GetHitTime()
{
    return hitTime;
}

TH1F* TAORunData::GetHistOfTotalPE(bool ifFit)
{
    float x_min=radioActiveSource->GetTotalPEHistXMin();
    float x_max=radioActiveSource->GetTotalPEHistXMax();
    int NBins=radioActiveSource->GetTotalPEHistNBins();
    std::string histName="TotalPE_"+radioActiveSource->GetSourceLabel();
    TH1F* hist=new TH1F(histName.c_str(),histName.c_str(),NBins,x_min,x_max);
    hist->GetXaxis()->SetTitle("Total PE");
    hist->GetYaxis()->SetTitle("Count");
    int count=0;
    for(int i=0;i<NEtries;i++){
        GetEntry(i);
        if(isGamma)
        {
            count++;
            hist->Fill(totalPE);
        }
        if(count>=gammaNumber)
        {
            std::cout<<"Gamma Number : "<<count<<" Reached!"<<std::endl;
            break;
        }
    }
    if(ifASBkg){
        ASBkg(hist);
    }
    if(ifFit){

        hist->Fit(radioActiveSource->GetTFMCShape(),"");
    }
    return hist;
}


TH1F* TAORunData::GetHistOfFullEnergyPeak(bool ifFit)
{
    float x_min=radioActiveSource->GetTotalPEHistXMin();
    float x_max=radioActiveSource->GetTotalPEHistXMax();
    int NBins=radioActiveSource->GetTotalPEHistNBins();
    std::string histName="FullEnergyPeak_"+radioActiveSource->GetSourceLabel();
    TH1F* hist=new TH1F(histName.c_str(),histName.c_str(),NBins,x_min,x_max);
    hist->GetXaxis()->SetTitle("Total PE");
    hist->GetYaxis()->SetTitle("Count");
    int count=0;
    for(int i=0;i<NEtries;i++){
        GetEntry(i);
        if(isGamma)
        {
            count++;
            if(Edep>(radioActiveSource->GetGammaEnergy()*0.9999) && Edep<(radioActiveSource->GetGammaEnergy()*1.0001))
            {
                hist->Fill(totalPE);
            }
        }
        if(count>=gammaNumber)
        {
            std::cout<<"Gamma Number : "<<count<<" Reached!"<<std::endl;
            break;
        }
    }
    if(ifFit){
        hist->Fit("gaus","");
    }
    return hist;
}

void TAORunData::AddBkg(TH1F* signal, float time)
{
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

void TAORunData::SubBkg(TH1F* signal, float time)
{
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

void TAORunData::ASBkg(TH1F* signal, float time)
{
    AddBkg(signal,time);
    SubBkg(signal,time);
}



void TAORunData::Finalize()
{
    delete mainTree;
}

std::ostream & operator<<(std::ostream & os, const TAORunData TAORun)
{
    using namespace std;
    return os;
}

