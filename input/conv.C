TGraph gr0("AmBeN1PromptPE.txt");
TGraph gr1("Gamma_4.43MeVPromptPE.txt");
double NRecoil(double* x,double *par)
{
    return gr0.Eval(x[0]);
}
double ELeap(double* x,double *par)
{
    double p[4]={12677,18827,1.0,200};
    double a=p[0]*p[3]*gr1.Eval(x[0])+p[0]*exp(-0.5*pow((x[0]-p[1])/(p[2]* p[1]*0.01),2));
    return a;
}
double AmBeShape(double* x,double* par)
{
    TF1* func1=new TF1("func1",NRecoil,0,15000,0);
    TF1* func2=new TF1("func2",ELeap,0,40000,3);
    TF1Convolution* f_conv=new TF1Convolution(func1,func2,0,40000,true); 
    f_conv->SetNofPointsFFT(10000);
    TF1* func=new TF1("func",f_conv,0.,40000,f_conv->GetNpar());
    return func->Eval(x[0]);

}
void conv()
{
   
    
    //TF1* func1=new TF1("func1",NRecoil,0,15000,0);
    //cout<<func1->Eval(-100)<<endl;
    //TF1* func2=new TF1("func2",ELeap,0,40000,0);
    //TF1Convolution* f_conv=new TF1Convolution(func1,func2,0,40000,true); 
    //f_conv->SetNofPointsFFT(10000);
    TF1* func=new TF1("func",AmBeShape,0.,40000,0);
    func->Draw();
    /*
    ofstream outdat;
    outdat.open("ELeapConvNRecoil.txt");
    for(int i=0;i<=10000;i++){
        outdat<<(3.0*i)<<"\t"<<(func->Eval(3.0*i))<<endl;
    }
    outdat.close();*/
}
