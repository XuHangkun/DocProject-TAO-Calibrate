#include "globals.h"
#include "TAORunData.h"
#include "RadioActiveSource.h"
#include "Nonuniformity.h"
#include "TH1F.h"
#include "TVector3.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <string>
#include <iostream>
#include "TStyle.h"
#include "TAxis.h"

void DrawMulEnergySpec(bool full)
{
    using namespace std;

    SetGlobalDrawOption();
    TCanvas* c1=new TCanvas("Test","Test");
    TString canvasName=ANATOP+Form("/result/MultiEnergySpec.pdf");
    c1->Print(canvasName+"[");
    c1->SetGrid();
    //TLegend* leg=new TLegend(0.55,0.65,0.9,0.9); //right top
    TLegend* leg=new TLegend(0.15,0.65,0.55,0.9); //left top

    const int NHeight=2;
    float height[NHeight]={800,850};
    int color[NHeight]={1,4};
    string SourceName="Co60";
    string legName[NHeight]={"H_{Calib}=800mm","H_{Calib}=850mm"};
    TAORunData* data[NHeight];
    TH1F* hist[NHeight];
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(1);
    for(int i=0;i<NHeight;i++){
        string histName=Form("%s_%.0fmm",SourceName.c_str(),height[i]);
        //hist=new TH1F(histName.c_str(),histName.c_str(),100,1000,5000);
        string fileName=DATATOP+Form("/nonuniformity/%s/data-nonuniformity/%s_%.0fmm_vProcId.root",SourceName.c_str(),SourceName.c_str(),height[i]);
        cout<<fileName<<endl;
        data[i]=new TAORunData(SourceName,fileName,30,TVector3(0,0,height[i]));
        data[i]->Initialize();
        /*
        int countGamma=0;
        for(int j=0;j<data->GetEntries();j++){
            data->GetEntry(j);
            if (data->GetIsGamma()){
                countGamma++;
                if(data->GetIsFullDepositGamma()){
                    hists[i]->Fill(data->GetTotalPE())
                }
                if(countGamma>=50000) { break; }
            }
        }*/
        if(full){
            data[i]->FillHistOfTotalPE_FullEnergy();    
        }else{
            data[i]->FillHistOfTotalPE();
            if(height[i]<800) data[i]->FitHistOfTotalPE();
        }
        hist[i]=data[i]->GetHistOfTotalPE();
        if(full){
            hist[i]->Fit("gaus");    
        }
        hist[i]->SetLineColor(color[i]);
        hist[i]->SetLineWidth(2);
        hist[i]->SetTitle(SourceName.c_str());
        hist[i]->GetXaxis()->SetRangeUser(5000,11000);
        hist[i]->GetXaxis()->SetTitle("Total PE");
        hist[i]->GetYaxis()->SetTitle("Count");
        leg->AddEntry(hist[i],legName[i].c_str(),"L");
        if(i==0) {
            hist[i]->Draw();
        }else{
            hist[i]->Draw("same");
        }
        c1->Print(canvasName);
    }
    c1->Print(canvasName);
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    hist[0]->Draw();
    for(int i=1;i<NHeight;i++) hist[i]->Draw("same");
    leg->Draw();
    c1->Print(canvasName);
    c1->Print(canvasName+"]");
}
