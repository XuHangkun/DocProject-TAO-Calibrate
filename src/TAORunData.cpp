#include "TAORunData.h"
#include "RadioActiveSource.h"
#include "TChain.h"
#include <string>
#include <vector>
#include "TH1F.h"
#include "TF1.h"
#include <iostream>

TAORunData::TAORunData(std::string inSource,int inNFile,int inCalibHeight)
{
    source=inSource;
    calibHeight=inCalibHeight;
    radioActiveSource=new RadioActiveSource(source,inNFile,calibHeight);
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
    mainTree->GetEntry(n);
    currentEntry=n;
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
    std::string histName="Hist_"+radioActiveSource->GetSourceLabel();
    TH1F* hist=new TH1F(histName.c_str(),histName.c_str(),NBins,x_min,x_max);
    hist->GetXaxis()->SetTitle("Total PE");
    hist->GetYaxis()->SetTitle("Count");
    for(int i=0;i<NEtries;i++){
        GetEntry(i);
        hist->Fill(totalPE);
    }
    if(ifFit){
        TF1 * f = new TF1("MCShape",radioActiveSource,&RadioActiveSource::MCShape,x_min,x_max,radioActiveSource->GetNPars(),"RadioActiveSource","MCShape");   // create TF1 class.
        f->SetParameter(0,radioActiveSource->GetInitialAmp());
        f->SetParameter(1,radioActiveSource->GetInitialMean());
        f->SetParameter(2,radioActiveSource->GetInitialSigma());
        f->SetParameter(3,radioActiveSource->GetInitialELeapFrac());
        hist->Fit(f,"");
    }
    return hist;
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
