#include "test.h"
#include "RadioActiveSource.h"
#include "MultiTAORunData.h"
#include "TAORunData.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "globals.h"
#include <iostream>
#include <vector>
#include <string>
#include "TF1.h"
#include "TLegend.h"

void TestRadioActiveSource()
{
    using namespace std;
    RadioActiveSource* testSource=new RadioActiveSource("Ge68",10,0);
    RadioActiveSource* testSource1=new RadioActiveSource("Cs137",2,0);
    RadioActiveSource* testSource2=new RadioActiveSource("Co60",3,0);
    cout<<(*testSource)<<(*testSource1)<<(*testSource2)<<endl;
    //delete testSource;
    vector<string> fileNames=testSource->GetFileNames();
    for(int i=0;i<fileNames.size();i++){
        cout<<fileNames[i]<<endl;
    } 
}

void TestMultiTAORunData()
{
    using namespace std;
    SetGlobalDrawOption();
    TCanvas* c1=new TCanvas("Test","Test");
    c1->Print((ANATOP+"/result/test.pdf]").c_str());
    TLegend* leg=new TLegend();
    const int NS=5;
    std::string sources[NS]={"Cs137","Mn54","Ge68","K40","Co60"};
    MultiTAORunData* testSource=new MultiTAORunData(sources,NS,25);
    testSource->GetTAORunData("K40")->SetGammaNumber(10000);
    testSource->FillTotalPESpectrum();
    testSource->ASBkg(20000);
    testSource->FitTotalPESprectrum();
    TH1F* histbkg=(TH1F*)(testSource->GetTotalPESpectrum())->Clone();
    TH1F* hist=(TH1F*)(testSource->GetTotalPESpectrum())->Clone();
    leg->AddEntry(hist,"Total Signal","L");
    hist->Draw("e");
    leg->AddEntry(histbkg,"Background Signal","L");
    histbkg->SetLineColor(kRed);
    //histbkg->Draw("same");
    //leg->Draw();
    c1->Print((ANATOP+"/result/test.pdf").c_str());
    c1->Print((ANATOP+"/result/test.pdf]").c_str());
    
}

void TestTAORunData()
{
    using namespace std;
    //Set Draw Option
    SetGlobalDrawOption();
    TAORunData* testTAORun=new TAORunData("Co60",30,0);
    cout<<testTAORun<<endl;
    testTAORun->FillHistOfTotalPE_FullEnergy();
    testTAORun->FitHistOfTotalPE("Gaus");
    TH1F* hist=testTAORun->GetHistOfTotalPE();
    TCanvas* c1=new TCanvas("Test","Test");
    c1->Print((ANATOP+"/result/test.pdf]").c_str());
    hist->Draw("E");
    c1->Print((ANATOP+"/result/test.pdf").c_str());
    c1->Print((ANATOP+"/result/test.pdf]").c_str());

}
