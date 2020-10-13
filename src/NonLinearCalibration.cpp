#include "NonLinearCalibration.h"
#include "TAORunData.h"
#include "globals.h"
#include "TAORunData.h"
#include <string>
#include <iostream>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "MultiTAORunData.h"
#include "TGraph2D.h"
#include "TStyle.h"
#include "TVector3.h"
#include "TVirtualFitter.h"

//Photon Absorption in Source Enclosure
void PhotonAbsInEnclosure()
{
    using namespace std;

    //Define sources
    const int NSource=5;
    string Sources[NSource]={"Cs137","Mn54","K40","Ge68","Co60"};

    //Get normal data: Ref=0.95
    float normalPeak[NSource]={0};
    float normalPeakError[NSource]={0};
    for(int i=0;i<NSource;i++){
        string tmp_path=DATATOP+"/nonlinearity/Normal"+"/"+Sources[i]+"_0mm_vProcId.root";
        TAORunData* tmpTao=new TAORunData(Sources[i],tmp_path,50,TVector3(0,0,0));
        tmpTao->Initialize();
        tmpTao->FillHistOfTotalPE_FullEnergy();
        tmpTao->FitHistOfTotalPE("Gaus");
        normalPeak[i]=tmpTao->GetHistOfTotalPE()->GetFunction("gaus")->GetParameter(1);
        normalPeakError[i]=tmpTao->GetHistOfTotalPE()->GetFunction("gaus")->GetParError(1);
        delete tmpTao;
    }

    //Get Ref=1.0 Data
    float tunedPeak[NSource]={0};
    float tunedPeakError[NSource]={0};
    for(int i=0;i<NSource;i++){
        string tmp_path=DATATOP+"/nonlinearity/EnclosureRef1.0"+"/"+Sources[i]+"_0mm_vProcId.root";
        TAORunData* tmpTao=new TAORunData(Sources[i],tmp_path,50,TVector3(0,0,0));
        tmpTao->Initialize();
        tmpTao->FillHistOfTotalPE_FullEnergy();
        tmpTao->FitHistOfTotalPE("Gaus");
        tunedPeak[i]=tmpTao->GetHistOfTotalPE()->GetFunction("gaus")->GetParameter(1);
        tunedPeakError[i]=tmpTao->GetHistOfTotalPE()->GetFunction("gaus")->GetParError(1);
        delete tmpTao;
    }

    //Draw the picture here
    SetGlobalDrawOption();
    TCanvas* c1=new TCanvas("Test","Test");
    c1->Print((ANATOP+"/result/SourceEnclosureAbs.pdf[").c_str());
    c1->SetGrid();
    float bias[NSource]={0};
    float biasError[NSource]={0};
    for(int i=0;i<NSource;i++){
        bias[i]=100*(tunedPeak[i]-normalPeak[i])/normalPeak[i];
        cout<<bias[i]<<endl; 
        biasError[i]=100*sqrt(tunedPeakError[i]*tunedPeakError[i]+normalPeakError[i]*normalPeakError[i])/normalPeak[i];
    }
    float xaxis[NSource]={0};
    for(int i=0;i<NSource;i++){
        xaxis[i]=i+1;
    }
    float xaxisE[NSource]={0};
    TGraphErrors* gr=new TGraphErrors(NSource,xaxis,bias,xaxisE,biasError);
    gr->SetMarkerStyle(33);
    gr->SetMarkerSize(2);
    gr->SetLineWidth(2);
    gr->GetYaxis()->SetTitle("Relative bias[%]");
    gr->GetYaxis()->SetRangeUser(0,0.12);
    gr->GetXaxis()->SetTitle("Radioactive Source");
    for(int i=0;i<NSource;i++){
        gr->GetXaxis()->ChangeLabel(2*i+1,-1,-1,-1,-1,-1,Sources[i]);
        gr->GetXaxis()->ChangeLabel(2*i+2,-1,0.);
    }
    gr->Draw("AP");
    c1->Print((ANATOP+"/result/SourceEnclosureAbs.pdf").c_str());
    c1->Print((ANATOP+"/result/SourceEnclosureAbs.pdf]").c_str());
    
}


//Fitting Bias Study
std::vector<float> MultiSourceFitBias(int NK40Gamma, int NCo60Gamma)
{
    using namespace std;
    //Situation
    const int NSituation=4;
    string situations[NSituation]={DATATOP+"/nonlinearity/Normal",DATATOP+"/nonlinearity/EnclosureRef1.0",DATATOP+"/nonlinearity/TunePPOBisAbsFrac",DATATOP+"/nonlinearity/TuneOpModel"};
    string legName[NSituation]={"Normal","Tune Enclosure Ref.","Tune Abs Frac","Tune Op. Model"};
    int Color[NSituation]={1,2,4,7};
    int MarkerStyle[NSituation]={20,21,22,23};
    TGraphErrors* gr_Bias[NSituation];

    const int NSource=4;
    string Sources[NSource]={"Cs137","Mn54","Ge68","K40"};
    //int    SourceColor[NSource]={1,2,3,4,5};
    //string Sources[NSource]={"Cs137","Mn54","Ge68"};
    //string Sources[NSource]={"K40","Co60"};

    SetGlobalDrawOption();
    TCanvas* c1=new TCanvas("Test","Test");
    TString canvasName=ANATOP+Form("/result/MultiSourceFitBias_K40_%d_Co60_%d.pdf",NK40Gamma,NCo60Gamma);
    c1->Print(canvasName+"[");
    c1->SetGrid();
    //TLegend* leg=new TLegend(0.55,0.65,0.9,0.9); //right top
    TLegend* leg=new TLegend(0.15,0.65,0.5,0.9); //left top

    float xaxis[601]={0};
    xaxis[0]=4300*0.36*0.662;
    float delta1=(4800-4300*0.36*0.662)/300;
    float delta2=(12000-4800)/300;
    for(int i=1;i<601;i++){
        if(i<=300){
            xaxis[i]=delta1+xaxis[i-1];
        }else{
            xaxis[i]=delta2+xaxis[i-1];
        }
    }

    for(int i=0;i<NSituation;i++){
       //Create the data path
        string tmp_paths[NSource];
       for(int j=0;j<NSource;j++){
           tmp_paths[j]=situations[i]+"/"+Sources[j]+"_0mm_vProcId.root";
       }
       //Create data
       MultiTAORunData* tmp=new MultiTAORunData(Sources , NSource , tmp_paths , 30);
       //Set the total PE hist
       //tmp->UpdateTotalPEHist(4300*0.662*0.36,4800,300);
       //tmp->UpdateTotalPEHist(4800,12000,300);
       tmp->UpdateTotalPEHist(600,xaxis);
       
       //Fill Data
       tmp->GetTAORunData("K40")->SetGammaNumber(5000);
       //tmp->GetTAORunData("Co60")->SetGammaNumber(NCo60Gamma);
       tmp->FillTotalPESpectrum();
       //tmp->AddK40Co60Bkg();
       tmp->ASBkg(10000);
       tmp->FitTotalPESprectrum();
       //output corr matrix
       /*
       TVirtualFitter* fitter=TVirtualFitter::GetFitter();
       for(int m=0;m<4*NSource;m++){
           for(int n=0;n<4*NSource;n++){
               cout<<fitter->GetCovarianceMatrixElement(m,n)<<"\t";
           }
           cout<<endl;
       }*/
       tmp->GetTAORunData("K40")->SetGammaNumber(50000);
       //tmp->GetTAORunData("Co60")->SetGammaNumber(50000);
       gr_Bias[i]=tmp->GetFittingBias();

       tmp->GetTotalPESpectrum()->Draw("e");
       
       /*
       for(int j=0;j<NSource;j++){
           RadioActiveSource* tmp_radio=new RadioActiveSource(Sources[j],0);
           for(int k=0;k<4;k++) tmp_radio->GetTFMCShape()->SetParameter(k,tmp->GetTFTotalMCShape()->GetParameter(4*j+k));
           tmp_radio->GetTFMCShape()->SetLineColor(SourceColor[j]);
           tmp_radio->GetTFMCShape()->SetLineStyle(7);
           tmp_radio->GetTFMCShape()->Draw("L same");
       }*/
       c1->Print(canvasName);
       delete tmp;
    }
    std::vector<float> destination;
    for(int i=0;i<NSituation;i++){
        //we can cout the lose here
        gr_Bias[i]->SetLineColor(Color[i]);
        gr_Bias[i]->SetMarkerColor(Color[i]);
        gr_Bias[i]->SetMarkerStyle(MarkerStyle[i]);
        leg->AddEntry(gr_Bias[i],legName[i].c_str(),"PL");
        if(i==0){
            gr_Bias[i]->GetYaxis()->SetRangeUser(0,0.4);
            gr_Bias[i]->Draw("AP");
            for(int j=0;j<NSource;j++){
                float bias=gr_Bias[i]->GetPointY(j);
                float biase=gr_Bias[i]->GetErrorY(j);
                if(true){
                    destination.push_back(sqrt(bias*bias+biase+biase));
                }else{
                    destination.push_back(0);
                }
            }
        }else{
            gr_Bias[i]->Draw("same P");
            for(int j=0;j<NSource;j++){
                float bias=gr_Bias[i]->GetPointY(j);
                if(bias>1.2) { continue; }
                float biase=gr_Bias[i]->GetErrorY(j);
                if(destination[j]<sqrt(bias*bias+biase+biase)){
                    destination[j]=(sqrt(bias*bias+biase+biase));
                }
            }
        }
    }
    leg->Draw();
    c1->Print(canvasName);
    c1->Print(canvasName+"]");
    //for(int i=0;i<NSituation;i++) delete gr_Bias[i];
    return destination;    
}

void OptimizeEventNumbers()
{
    const int K40Choice=6;
    const int Co60Choice=5;
    int NK40[K40Choice]={5000,6000,7000,8000,9000,10000};
    int NCo60[Co60Choice]={30000,35000,40000,45000,50000};
    float K40Bias[K40Choice][Co60Choice]={0};
    float Co60Bias[K40Choice][Co60Choice]={0};
    
    TGraph2D* gr_K40=new TGraph2D();
    TGraph2D* gr_Co60=new TGraph2D();
    for(int i=0 ; i<K40Choice ; i++){
        for(int j=0;j<Co60Choice ;j++){
            std::vector<float> tmp=MultiSourceFitBias(NK40[i],NCo60[j]);
            K40Bias[i][j]=tmp[3];
            Co60Bias[i][j]=tmp[4];
            std::cout<<"Error: "<<tmp[3]<<"\t"<<tmp[4]<<std::endl;
            gr_K40->SetPoint(Co60Choice*i+j,float(NK40[i])/1000,float(NCo60[j])/1000,tmp[0]);
            gr_Co60->SetPoint(Co60Choice*i+j,float(NK40[i])/1000,float(NCo60[j])/1000,tmp[1]);
        }
    }

    SetGlobalDrawOption();
    TCanvas* c1=new TCanvas("Test","Test");
    c1->Print((ANATOP+"/result/EventNumberOptimization.pdf[").c_str());
    gPad->SetRightMargin(0.15);
    gPad->SetTopMargin(0.15);
    gPad->SetLeftMargin(0.2);
    gPad->SetBottomMargin(0.2);
    c1->SetGrid();
    
    gr_K40->SetName("K40 Error");
    gr_K40->SetTitle("K40 Error");
    gr_K40->GetXaxis()->SetRangeUser(5000,10000);
    gr_K40->GetYaxis()->SetRangeUser(35000,50000);
    gr_K40->GetXaxis()->SetTitle("K40 Gamma Number[k]");
    gr_K40->GetXaxis()->SetName("K40 Gamma Number[k]");
    gr_K40->GetYaxis()->SetTitle("Co60 Gamma Number[k]");
    gr_K40->GetYaxis()->SetName("Co60 Gamma Number[k]");
    gr_K40->Draw("colz");
    c1->Print((ANATOP+"/result/EventNumberOptimization.pdf").c_str());

    gr_Co60->SetName("Co60 Error");
    gr_Co60->SetTitle("Co60 Error");
    gr_Co60->GetXaxis()->SetRangeUser(5000,10000);
    gr_Co60->GetYaxis()->SetRangeUser(35000,50000);
    gr_Co60->GetXaxis()->SetTitle("K40 Gamma Number");
    gr_Co60->GetYaxis()->SetTitle("Co60 Gamma Number");
    gr_Co60->Draw("colz");
    c1->Print((ANATOP+"/result/EventNumberOptimization.pdf").c_str());
    c1->Print((ANATOP+"/result/EventNumberOptimization.pdf]").c_str());

}
