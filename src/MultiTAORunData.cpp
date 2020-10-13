#include "MultiTAORunData.h"
#include "RadioActiveSource.h"
#include <vector>
#include <string>
#include "TF1.h"
#include "globals.h"
#include "TGraphErrors.h"
#include "math.h"
#include "TVector3.h"

MultiTAORunData::MultiTAORunData(std::vector<std::string> inSources, std::vector<std::string> dataFiles,int NFile)
{  
    Initialize(inSources,NFile,dataFiles); 
}

MultiTAORunData::MultiTAORunData(std::string inSources[], int N,std::string dataFiles[],int NFile)
{

    std::vector<std::string> tmp_source;
    std::vector<std::string> tmp_file;
    for(int i=0;i<N;i++){
        tmp_source.push_back(inSources[i]);
        tmp_file.push_back(dataFiles[i]);
        std::cout<<inSources[i]<<std::endl;
        std::cout<<dataFiles[i]<<std::endl;
    }   
    Initialize(tmp_source,NFile,tmp_file);

}

MultiTAORunData::~MultiTAORunData()
{
    delete totalPESpectrum;
    delete tfTotalMCShape;
    for(int i=0;i<taoRunDatas.size();i++)
    {
        taoRunDatas[i]->Finalize();
    }
}

void MultiTAORunData::Initialize(std::vector<std::string> inSources,int NFile,std::vector<std::string> dataFiles)
{
    //initialize source taoRunDatas
    NPars=0;
    for(int i=0;i<inSources.size();i++){
        sources.push_back(inSources[i]);
        TAORunData* tmp_taorun = new TAORunData(sources[i],dataFiles[i],NFile,TVector3(0,0,0));
        tmp_taorun->Initialize();
        taoRunDatas.push_back(tmp_taorun);
        NPars+=tmp_taorun->GetRadioActiveSource()->GetNPars();

        //get min and max energy
        if(i==0){
            minGammaEnergy = tmp_taorun->GetRadioActiveSource()->GetKinetic();
            maxGammaEnergy = tmp_taorun->GetRadioActiveSource()->GetKinetic();
        }else
        {
            float tmp_energy=tmp_taorun->GetRadioActiveSource()->GetKinetic();
            if(tmp_energy<minGammaEnergy) minGammaEnergy=tmp_energy;
            if(tmp_energy>maxGammaEnergy) maxGammaEnergy=tmp_energy;
        }

        
    }
    
    //Create total PE histogram
    float xmin=minGammaEnergy*0.36*GAMMALY;
    float xmax=maxGammaEnergy*1.2*GAMMALY;
    totalPESpectrum = new TH1F("TotalPE_Spectrum","TotalPE_Spectrum",sources.size()*150,xmin,xmax);
    totalPESpectrum->GetXaxis()->SetTitle("Total PE");
    totalPESpectrum->GetYaxis()->SetTitle("Count");
    totalPESpectrum->Sumw2();
    for(int i=0;i<sources.size();i++)
    {
        taoRunDatas[i]->UpdateTotalPEHist(xmin,xmax,150*sources.size());
    }


    //Initia        tfTotalMCShape
    tfTotalMCShape=new TF1("MCShape",this,&MultiTAORunData::TotalMCShape,xmin,xmax,NPars,"MultiTAORunData","TotalMCShape");
    tfTotalMCShape->SetNpx(3000);
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

void MultiTAORunData::UpdateTotalPEHist(bool syn)
{
    delete totalPESpectrum;

    float xmin=minGammaEnergy*0.36*GAMMALY;
    float xmax=maxGammaEnergy*1.2*GAMMALY;

    //create total pe histogram
    totalPESpectrum = new TH1F("TotalPE_Spectrum","TotalPE_Spectrum",sources.size()*150,xmin,xmax);
    totalPESpectrum->GetXaxis()->SetTitle("Total PE");
    totalPESpectrum->GetYaxis()->SetTitle("Count");
    totalPESpectrum->Sumw2();

    if(syn)
    {
        for(int i=0;i<sources.size();i++)
        {
            taoRunDatas[i]->UpdateTotalPEHist(xmin,xmax,150*sources.size());
        }
    }
}

void MultiTAORunData::UpdateTotalPEHist(float inxmin,float inxmax,int inNbins,bool syn)
{
    delete totalPESpectrum;

    float xmin=inxmin;
    float xmax=inxmax;

    //create total pe histogram
    totalPESpectrum = new TH1F("TotalPE_Spectrum","TotalPE_Spectrum",inNbins,xmin,xmax);
    totalPESpectrum->GetXaxis()->SetTitle("Total PE");
    totalPESpectrum->GetYaxis()->SetTitle("Count");
    totalPESpectrum->Sumw2();

    if(syn)
    {
        for(int i=0;i<sources.size();i++)
        {
            taoRunDatas[i]->UpdateTotalPEHist(xmin,xmax,inNbins);
        }
    }
}

void MultiTAORunData::UpdateTotalPEHist(int inNbins,float* bins,bool syn)
{
    delete totalPESpectrum;

    //create total pe histogram
    totalPESpectrum = new TH1F("TotalPE_Spectrum","TotalPE_Spectrum",inNbins,bins);
    totalPESpectrum->GetXaxis()->SetTitle("Total PE");
    totalPESpectrum->GetYaxis()->SetTitle("Count");
    totalPESpectrum->Sumw2();

    if(syn)
    {
        for(int i=0;i<sources.size();i++)
        {
            taoRunDatas[i]->UpdateTotalPEHist(inNbins,bins);
        }
    }
}

double MultiTAORunData::TotalMCShape(double* x,double* pars)
{
    double value=0;
    double *ptr_par=pars;
    for(int i=0;i<sources.size();i++)
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
    for(int i=0;i<sources.size();i++){
       taoRunDatas[i]->FillHistOfTotalPE();
       totalPESpectrum->Add(taoRunDatas[i]->GetHistOfTotalPE(),1);
       std::cout<<totalPESpectrum->GetBinError(150)<<std::endl;
    }
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
    TH1F* sampleBkg=(TH1F*)signal->Clone();
    sampleBkg->Reset();
    float NBkg=bkgHist->GetEntries()*time/601.4;
    for(int i=0;i<NBkg;i++){
        sampleBkg->Fill(bkgHist->GetRandom());
    }
    signal->Add(sampleBkg,1);
    std::cout<<totalPESpectrum->GetBinError(150)<<std::endl;
    bkgFile->Close();
}

void MultiTAORunData::SubBkg(float time)
{
    TH1F* signal=totalPESpectrum;

    //Read the file
    TFile* bkgFile=TFile::Open((ANATOP+"/input/Bkg/AssumedBkg.root").c_str());
    TH1F* bkgHist=(TH1F*)bkgFile->Get("Bkg_601.4s");

    //create bkg hist
    TH1F* sampleBkg=(TH1F*)signal->Clone();
    sampleBkg->Reset();
    float NBkg=bkgHist->GetEntries()*time/601.4;
    for(int i=0;i<NBkg;i++){
        sampleBkg->Fill(bkgHist->GetRandom());
    }
    signal->Add(sampleBkg,-1);
    std::cout<<totalPESpectrum->GetBinError(150)<<std::endl;
    bkgFile->Close();
}

void MultiTAORunData::ASBkg(float time)
{
    AddBkg(time);
    SubBkg(time);
}

void MultiTAORunData::AddK40Co60Bkg(float time)
{
    TH1F* signal=totalPESpectrum;

    //Read the file
    TFile* bkgFile=TFile::Open((ANATOP+"/input/Bkg/K40Co60Spectrum.root").c_str());
    TH1F* bkgHist=(TH1F*)bkgFile->Get("K40Co60Spectrum");

    //create bkg hist
    TH1F* sampleBkg=new TH1F("SampleBkg","SampleBkg",signal->GetNbinsX(),signal->GetXaxis()->GetXmin(),signal->GetXaxis()->GetXmax());
    float NBkg=bkgHist->GetEntries()*time/5000;
    for(int i=0;i<NBkg;i++){
        sampleBkg->Fill(bkgHist->GetRandom());
    }
    signal->Add(sampleBkg,1);
    bkgFile->Close();
}

TGraphErrors* MultiTAORunData::GetFittingBias()
{
    const int NSource=sources.size();
    //Get the true value and the fitted value
    float truePeak[NSource]={0.};
    float truePeakError[NSource]={0.};
    float peak[NSource]={0.};
    float peakError[NSource]={0.};
    for(int i=0;i<NSource;i++){
        taoRunDatas[i]->FillHistOfTotalPE_FullEnergy();
        taoRunDatas[i]->FitHistOfTotalPE("Gaus");
        TH1F* tmp=taoRunDatas[i]->GetHistOfTotalPE();
        truePeak[i]=tmp->GetFunction("gaus")->GetParameter(1);
        truePeakError[i]=tmp->GetFunction("gaus")->GetParError(1);

        peak[i]=totalPESpectrum->GetFunction("MCShape")->GetParameter(4*i+1);
        peakError[i]=totalPESpectrum->GetFunction("MCShape")->GetParError(4*i+1);
    }

    float bias[NSource]={0};
    float biasError[NSource]={0};
    for(int i=0;i<NSource;i++){
        bias[i]=fabs(100*(truePeak[i]-peak[i])/truePeak[i]);
        biasError[i]=fabs(100*sqrt(truePeakError[i]*truePeakError[i]+peakError[i]*truePeakError[i])/truePeak[i]);
    }
    
    //Create graph 
    float xaxis[NSource]={0};
    for(int i=0;i<NSource;i++){
        xaxis[i]=i+1;
    }
    float xaxisE[NSource]={0};
    TGraphErrors* gr=new TGraphErrors(NSource,xaxis,bias,xaxisE,biasError);
    gr->SetMarkerStyle(33);
    gr->SetMarkerSize(1);
    gr->SetLineWidth(2);
    gr->GetYaxis()->SetTitle("Relative bias[%]");
    //gr->GetYaxis()->SetRangeUser(0,0.12);
    gr->GetXaxis()->SetTitle("Radioactive Source");
    for(int i=0;i<NSource;i++){
        int delta=2;
        gr->GetXaxis()->ChangeLabel(delta*i+1,-1,-1,-1,-1,-1,sources[i]);
        for(int j=2;j<=delta;j++){
            gr->GetXaxis()->ChangeLabel(delta*i+j,-1,0.);
        }
    }

    return gr;
}
