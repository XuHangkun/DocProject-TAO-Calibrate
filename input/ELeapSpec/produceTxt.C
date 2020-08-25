void produceTxt()
{
    string name="Gamma_2.506MeVELeapSpec";
    string filename=name+".root";
    string histname=name;
    string outName=name+".txt";
    TFile* file=new TFile(filename.c_str());
    TH1F* hist=(TH1F*)file->Get(histname.c_str());
    float interg=hist->GetBinWidth(1)*hist->Integral();
    hist->Smooth(500);
    hist->Scale(1/interg);
    hist->Draw();
    ofstream outdat(outName.c_str());
    int N=hist->GetNbinsX();
    for(int i=0;i<N;i++){
        if(i==0) { 
            outdat<<(hist->GetXaxis()->GetXmin())<<"\t"<<hist->GetBinContent(1)<<endl; 
        }else{
            outdat<<(hist->GetBinCenter(i))<<"\t"<<hist->GetBinContent(i)<<endl; 
        }
    }
    outdat.close();
    file->Close();
    TGraph* gr=new TGraph(outName.c_str());
    gr->Draw("AL");


    
}
