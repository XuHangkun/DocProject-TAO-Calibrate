#include "AcrylicBarStrategy.h"
#include "TAORunData.h"
#include "globals.h"
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TString.h"
#include "SiPM.h"

void CompareChargePattern()
{
    using namespace std;

    SiPM* sipms=new SiPM();

    const int NCalibPoint=4;
    float calibZ[NCalibPoint]={0,400,700,850};

    //read data without acrylic bar
    TH2F* normalPattern_Up[NCalibPoint];
    TH2F* normalPattern_Down[NCalibPoint];
    double normalHitCharge[SiPM::NSIPM]={0};
    for(int i=0;i<NCalibPoint;i++){
        string histName = Form("Normal_0MeV_Z%0.f_Upball",calibZ[i]);
        normalPattern_Up[i] = new TH2F(histName.c_str(),histName.c_str(),450,-900,900,450,-900,900);
        normalPattern_Up[i]->GetXaxis()->SetTitle("X[mm]");
        normalPattern_Up[i]->GetYaxis()->SetTitle("Y[mm]");
        histName = Form("Normal_0MeV_Z%0.f_Downball",calibZ[i]);
        normalPattern_Down[i] = new TH2F(histName.c_str(),histName.c_str(),450,-900,900,450,-900,900);
        normalPattern_Down[i]->GetXaxis()->SetTitle("X[mm]");
        normalPattern_Down[i]->GetYaxis()->SetTitle("Y[mm]");
        string normal_filepath = TAOTOP+Form("/Data/newCalibStrategy/Positron_acbar/Positron_0MeV_X0_Y0_Z%.0f_VProcId.root",calibZ[i]);
        TAORunData* normalData = new TAORunData("Positron",1.022,normal_filepath,2);
        normalData->Initialize(); 
        cout<<"Total Entries: "<<normalData->GetEntries()<<endl;
        for(int j=0;j<normalData->GetEntries();j++){
            normalData->GetEntry(j);
            //cout<<normalData->GetEdep()<<endl;
            if(j%10000==0) cout<<Form("%dth Events!",j)<<endl;
            //if( !normalData->GetIsFullDepositGamma() ) { continue; }
            //judge r index and theta index
            for(int k=0;k<SiPM::NSIPM;k++){ 
                normalHitCharge[k]+=normalData->GetHitCharge(k);
            }
        }
        //Fill to histogram
        for(int j=0;j<SiPM::NSIPM;j++){
            double xx=sipms->GetSiPMPositionX(j);
            int xbin=normalPattern_Up[i]->GetXaxis()->FindBin(xx);
            double yy=sipms->GetSiPMPositionY(j);
            int ybin=normalPattern_Up[i]->GetYaxis()->FindBin(yy);
            double zz=sipms->GetSiPMPositionZ(j);
            if ( zz>=0 ){
               normalPattern_Up[i]->SetBinContent(xbin,ybin,normalHitCharge[j]); 
            }else{
               normalPattern_Down[i]->SetBinContent(xbin,ybin,normalHitCharge[j]) ;
            }
        } 
        //delete normalData;
    }

    //read data with acrylic bar
    TH2F* newPattern_Up[NCalibPoint];
    TH2F* newPattern_Down[NCalibPoint];
    double newHitCharge[SiPM::NSIPM]={0};
    for(int i=0;i<NCalibPoint;i++){
        string histName = Form("new_0MeV_Z%0.f_Upball",calibZ[i]);
        newPattern_Up[i] = new TH2F(histName.c_str(),histName.c_str(),450,-900,900,450,-900,900);
        newPattern_Up[i]->GetXaxis()->SetTitle("X[mm]");
        newPattern_Up[i]->GetYaxis()->SetTitle("Y[mm]");
        histName = Form("new_0MeV_Z%0.f_Downball",calibZ[i]);
        newPattern_Down[i] = new TH2F(histName.c_str(),histName.c_str(),450,-900,900,450,-900,900);
        newPattern_Down[i]->GetXaxis()->SetTitle("X[mm]");
        newPattern_Down[i]->GetYaxis()->SetTitle("Y[mm]");
        string new_filepath = TAOTOP+Form("/Data/newCalibStrategy/Positron_acbar/Positron_0MeV_X0_Y0_Z%.0f_VProcId.root",calibZ[i]);
        TAORunData* newData = new TAORunData("Positron",1.022,new_filepath,2);
        newData->Initialize(); 
        cout<<"Total Entries: "<<newData->GetEntries()<<endl;
        for(int j=0;j<newData->GetEntries();j++){
            newData->GetEntry(j);
            //cout<<newData->GetEdep()<<endl;
            if(j%10000==0) cout<<Form("%dth Events!",j)<<endl;
            //if( !newData->GetIsFullDepositGamma() ) { continue; }
            //judge r index and theta index
            for(int k=0;k<SiPM::NSIPM;k++){ 
                newHitCharge[k]+=newData->GetHitCharge(k);
            }
        }
        //Fill to histogram
        for(int j=0;j<SiPM::NSIPM;j++){
            double xx=sipms->GetSiPMPositionX(j);
            int xbin=newPattern_Up[i]->GetXaxis()->FindBin(xx);
            double yy=sipms->GetSiPMPositionY(j);
            int ybin=newPattern_Up[i]->GetYaxis()->FindBin(yy);
            double zz=sipms->GetSiPMPositionZ(j);
            if ( zz>=0 ){
               newPattern_Up[i]->SetBinContent(xbin,ybin,newHitCharge[j]); 
            }else{
               newPattern_Down[i]->SetBinContent(xbin,ybin,newHitCharge[j]) ;
            }
        } 
        //delete newData;
    }
    
    //draw picture here
    SetGlobalDrawOption(); 
    TCanvas* c1=new TCanvas("Test","Test");
    TString canvasName=ANATOP+Form("/result/NewStrategy_ComparePattern.pdf");
    c1->Print(canvasName+"[");
    c1->SetRightMargin(0.15);
    c1->Divide(2,2);
    for(int i=0;i<SiPM::NSIPM;i++){
        c1->cd(1);
        normalPattern_Up[i]->Draw();
        c1->cd(2);
        normalPattern_Down[i]->Draw();
        c1->cd(3);
        newPattern_Up[i]->Draw();
        c1->cd(4);
        newPattern_Down[i]->Draw();
        c1->Print(canvasName);
    }
    c1->Print(canvasName+"]");
    

}

