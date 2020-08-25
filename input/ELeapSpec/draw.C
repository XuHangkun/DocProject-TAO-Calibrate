void draw()
{
    TCanvas* c1=new TCanvas("c1","c1");
    c1->SetLeftMargin(0.15);
    c1->SetBottomMargin(0.15);
    TGraph* gr=new TGraph("Gamma613ELeapSpec.txt");
    //gr->SetTitle("Mn54ELeapSpec");
    gr->SetTitle("");
    gr->GetXaxis()->SetTitle("total PE");
    gr->GetXaxis()->SetLabelFont(132);
    gr->GetXaxis()->SetLabelSize(0.06);
    gr->GetXaxis()->SetTitleFont(132);
    gr->GetXaxis()->SetTitleSize(0.06);
    gr->GetYaxis()->SetTitle("a.u.");
    gr->GetYaxis()->SetLabelFont(132);
    gr->GetYaxis()->SetLabelSize(0.06);
    gr->GetYaxis()->SetTitleFont(132);
    gr->GetYaxis()->SetTitleSize(0.06);
    gr->Draw("AL");

}
