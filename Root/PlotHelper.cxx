#include "MyAnalysis/PlotHelper.h"
 
#include "TColor.h"
#include "TObject.h"


PlotHelper::PlotHelper()
{
  this->set_plot_style();
  this->set_doSumW2(true);
}


void PlotHelper::set_plot_style()
{
    const Int_t NRGBs = 5;
    const Int_t NCont = 20;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);

    // more legible title
    gStyle->SetTitleH(0.09);        // title height
    gStyle->SetTitleW(0.80);         // title width
    gStyle->SetTitleX(0.1);         // title start

    // set up default color scheme here
    myColors.clear();
    myColors.push_back((int)kBlack);
    myColors.push_back((int)kAzure-2);
    myColors.push_back((int)kRed);
    myColors.push_back((int)kGreen+2);
    myColors.push_back((int)kMagenta+1);
    myColors.push_back((int)kCyan+1);
    myColors.push_back((int)kViolet+1);
    myColors.push_back((int)kSpring-1);
    myColors.push_back((int)kAzure+1);
    myColors.push_back((int)kTeal+1);
    myColors.push_back((int)kOrange+4);
    myColors.push_back((int)kPink-8);
    myColors.push_back((int)kBlue-7);
    myColors.push_back((int)kTeal+9);

    return;

   
    
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot1D(std::string Title, double XVal, double weight, std::map<std::string, TH1D*> &theHistos, 
			     int NumBinsX, double XMin, double XMax){

 
  std::map<std::string, TH1D*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH1D* currentHisto= new TH1D(Title.c_str(), Title.c_str(), NumBinsX, XMin, XMax);
      if(doSumW2) currentHisto->Sumw2();
      currentHisto->Fill(XVal, weight);
      theHistos.insert(std::pair<std::string, TH1D*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, weight);
    }

  
  return;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot1D(std::string Title, float XVal, double weight, std::map<std::string, TH1F*> &theHistos, 
			     int NumBinsX, float XMin, float XMax){

 
  std::map<std::string, TH1F*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH1F* currentHisto= new TH1F(Title.c_str(), Title.c_str(), NumBinsX, XMin, XMax);
      if(doSumW2) currentHisto->Sumw2();
      currentHisto->Fill(XVal, weight);
      theHistos.insert(std::pair<std::string, TH1F*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, weight);
    }

  
  return;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot1D(std::string Title, double XVal, double weight, std::map<std::string, TH1D*> &theHistos, 
			     int NumBinsX, const float* Xbins){

 
  std::map<std::string, TH1D*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH1D* currentHisto= new TH1D(Title.c_str(), Title.c_str(), NumBinsX, Xbins);
      if(doSumW2) currentHisto->Sumw2();
      currentHisto->Fill(XVal, weight);
      theHistos.insert(std::pair<std::string, TH1D*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, weight);
    }

  
  return;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot1D(std::string Title, float XVal, double weight, std::map<std::string, TH1F*> &theHistos, 
			     int NumBinsX, const float* Xbins){

 
  std::map<std::string, TH1F*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH1F* currentHisto= new TH1F(Title.c_str(), Title.c_str(), NumBinsX, Xbins);
      if(doSumW2) currentHisto->Sumw2();
      currentHisto->Fill(XVal, weight);
      theHistos.insert(std::pair<std::string, TH1F*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, weight);
    }

  
  return;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2D*> &theHistos, 
	    int NumBinsX, double XMin, double XMax, int NumBinsY, double YMin, double YMax){

 
  std::map<std::string, TH2D*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH2D* currentHisto= new TH2D(Title.c_str(), Title.c_str(), NumBinsX, XMin, XMax, NumBinsY, YMin, YMax);
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TH2D*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }

  return;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot2D(std::string Title, float XVal, float YVal, double weight, std::map<std::string, TH2F*> &theHistos, 
			int NumBinsX, float XMin, float XMax, int NumBinsY, float YMin, float YMax){

 
  std::map<std::string, TH2F*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH2F* currentHisto= new TH2F(Title.c_str(), Title.c_str(), NumBinsX, XMin, XMax, NumBinsY, YMin, YMax);
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TH2F*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }

  return;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2D*> &theHistos, 
	    int NumBinsX, const double* Xbins, int NumBinsY, double YMin, double YMax){

  std::map<std::string, TH2D*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH2D* currentHisto= new TH2D(Title.c_str(), Title.c_str(), NumBinsX, Xbins, NumBinsY, YMin, YMax);
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TH2D*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }

  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2F*> &theHistos, 
	      int NumBinsX, const double* Xbins, int NumBinsY, double YMin, double YMax){

  std::map<std::string, TH2F*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH2F* currentHisto= new TH2F(Title.c_str(), Title.c_str(), NumBinsX, Xbins, NumBinsY, YMin, YMax);
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TH2F*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }
  
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2D*> &theHistos, 
			int NumBinsX, const float* Xbins, int NumBinsY, const float* Ybins){

 
  std::map<std::string, TH2D*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH2D* currentHisto= new TH2D(Title.c_str(), Title.c_str(), NumBinsX, Xbins, NumBinsY, Ybins);
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TH2D*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }
  
  return;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::Plot2D(std::string Title, float XVal, float YVal, double weight, std::map<std::string, TH2F*> &theHistos, 
			int NumBinsX, const float* Xbins, int NumBinsY, const float* Ybins){

 
  std::map<std::string, TH2F*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one
    {
      TH2F* currentHisto= new TH2F(Title.c_str(), Title.c_str(), NumBinsX, Xbins, NumBinsY, Ybins);
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TH2F*> (Title,currentHisto) );
    }
  else // exists already, so just fill it
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }

  return;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PlotHelper::PlotTProfile(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TProfile*> &theHistos,
			      int NumBinsX, double XMin, double XMax, double YMin, double YMax){


  std::map<std::string, TProfile*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one                                                                                                        
    {
      TProfile* currentHisto= new TProfile(Title.c_str(), Title.c_str(), NumBinsX, XMin, XMax, YMin, YMax,"");
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TProfile*> (Title,currentHisto) );
    }
  else // exists already, so just fill it                                                                                                                                       
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }
  return;


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void PlotTProfile(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TProfile*> &theHistos,
		  int NumBinsX, const float* Xbins){

  std::map<std::string, TProfile*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one                                                                                                           
    {
      TProfile* currentHisto= new TProfile(Title.c_str(), Title.c_str(), NumBinsX, Xbins,"");
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TProfile*> (Title,currentHisto) );
    }
  else // exists already, so just fill it                                                                                                                                          
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }
  
  return;
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotTProfile(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TProfile*> &theHistos,
		  int NumBinsX, const double* Xbins){

  std::map<std::string, TProfile*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one                                                                                                           
    {
      TProfile* currentHisto= new TProfile(Title.c_str(), Title.c_str(), NumBinsX, Xbins, "");
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TProfile*> (Title,currentHisto) );
    }
  else // exists already, so just fill it                                                                                                                                          
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }
  
  return;
  
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

void PlotTProfile(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TProfile*> &theHistos,
		  int NumBinsX, double XMin, double XMax){

  std::map<std::string, TProfile*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one                                                                                                           
    {
      TProfile* currentHisto= new TProfile(Title.c_str(), Title.c_str(), NumBinsX, XMin, XMax, "");
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TProfile*> (Title,currentHisto) );
    }
  else // exists already, so just fill it                                                                                                                                          
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }
  
  return;


}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

void PlotTProfile(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TProfile*> &theHistos,
		  Int_t NumBinsX, const double* Xbins, double YMin, double YMax){
  std::map<std::string, TProfile*>::iterator iter= theHistos.find(Title);
  if(iter == theHistos.end()) //no histo for this yet, so maye a new one                                                                                                           
    {
      TProfile* currentHisto= new TProfile(Title.c_str(), Title.c_str(), NumBinsX, Xbins, YMin, YMax,"");
      currentHisto->Fill(XVal, YVal, weight);
      theHistos.insert(std::pair<std::string, TProfile*> (Title,currentHisto) );
    }
  else // exists already, so just fill it                                                                                                                                          
    {
      (*iter).second->Fill(XVal, YVal, weight);
    }

  return;

}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotHelper::DrawHistos(TCanvas* &theCanvas, TH1F* &Signal, TH1F* &Bkg1, TH1F* &Bkg2, TH1F* &BkgTot, 
				 double y_Maximum, bool use_logYaxis, bool plot_errorBars, std::string theTitle, 
				 std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend){
  
  if(use_logYaxis) gPad->SetLogy();

  Signal->SetTitle(theTitle.c_str());
  Signal->SetName(theTitle.c_str());
  Signal->SetFillColor(0);
  Signal->SetLineColor(3);
  Signal->SetLineWidth(2);
  Signal->SetMaximum(y_Maximum);
    
  
  TAxis* xax=Signal->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax=Signal->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);
  if(plot_errorBars) Signal->Draw("E");
  else Signal->Draw();

  theCanvas->Update();
   
  
  Bkg1->SetFillColor(0);
  Bkg1->SetLineColor(4);
  Bkg1->SetLineWidth(2);
  if(plot_errorBars) Bkg1->Draw("Esame");
  else  Bkg1->Draw("same");
  
  Bkg2->SetFillColor(0);
  Bkg2->SetLineColor(2);
  Bkg2->SetLineWidth(2);
  if(plot_errorBars) Bkg2->Draw("Esame");
  else Bkg2->Draw("same");

  BkgTot->SetFillColor(0);
  BkgTot->SetLineColor(kBlack);
  BkgTot->SetLineWidth(2);
  if(plot_errorBars) BkgTot->Draw("Esame");
  else BkgTot->Draw("same");

  theCanvas->Update();

  theLegend->Draw();
  
  return;
}



//////////////////////////////////////////////////////////////////////////////

 void PlotHelper::Draw2DHistoNice(TCanvas* &theCanvas, TH2F* &histo, bool use_logXaxis, bool use_logYaxis, std::string theTitle, 
		      std::string xaxis_label, std::string yaxis_label, std::string DrawOption){
   
   std::string myDrawOption= (DrawOption!="" ? DrawOption : "COL CONTZ") ;

   if(use_logXaxis) gPad->SetLogx();
   if(use_logYaxis) gPad->SetLogy();

  histo->SetTitle(theTitle.c_str());
  histo->SetName(theTitle.c_str());
  
  TAxis* xax= histo->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histo->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);

  histo->Draw(myDrawOption.c_str());

  theCanvas->Update();

  return;
 }
//////////////////////////////////////////////////////////////////////////////

 void PlotHelper::Draw2DHistoNice(TCanvas* &theCanvas, TH2D* &histo, bool use_logXaxis, bool use_logYaxis, std::string theTitle, 
		      std::string xaxis_label, std::string yaxis_label, std::string DrawOption){

   std::string myDrawOption= (DrawOption!="" ? DrawOption : "COL CONTZ") ;

   if(use_logXaxis) gPad->SetLogx();
   if(use_logYaxis) gPad->SetLogy();

  histo->SetTitle(theTitle.c_str());
  histo->SetName(theTitle.c_str());
  
  TAxis* xax= histo->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histo->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);

  histo->Draw(myDrawOption.c_str());

  theCanvas->Update();

  return;
 }

//////////////////////////////////////////////////////////////////////

void PlotHelper::Draw1DHistoNice(TCanvas* &theCanvas, TH1F* &histo, bool use_logXaxis, bool use_logYaxis, std::string theTitle, 
		       std::string xaxis_label, std::string yaxis_label, std::string DrawOption)
{
  std::string myDrawOption= (DrawOption!="" ? DrawOption : "") ;

   if(use_logXaxis) gPad->SetLogx();
   if(use_logYaxis) gPad->SetLogy();

  histo->SetTitle(theTitle.c_str());
  histo->SetName(theTitle.c_str());
  
  TAxis* xax= histo->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histo->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);

  histo->Draw(myDrawOption.c_str());

  theCanvas->Update();

  return;
}

//////////////////////////////////////////////////////////////////////

void PlotHelper::DrawNormalizedHistos(TCanvas* &theCanvas, std::vector <TH1F*> &histos, 
					   double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
					   std::string xaxis_label,  std::string yaxis_label, TLegend* &theLegend){

  if(histos.size()==0){
    std::cout<<"No histograms to plot for: "<<theTitle<<std::endl;
    return;
  }
  
  // store the weights to make error calculate correct
  if(plot_errorBars) {
      for(unsigned int i = 0; i < histos.size(); i++)
          histos.at(i)->Sumw2();
  }

  if(use_logYaxis) gPad->SetLogy();

  histos.at(0)->SetTitle(theTitle.c_str());
  histos.at(0)->SetName(theTitle.c_str());
  histos.at(0)->SetFillColor(0);
  histos.at(0)->SetLineColor(myColors[0]);
  histos.at(0)->SetLineWidth(2);
  if(histos.at(0)->Integral() > 0)
      histos.at(0)->Scale(1.0/histos.at(0)->Integral());
  histos.at(0)->SetMaximum(y_Maximum);
    
  TAxis* xax= histos.at(0)->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histos.at(0)->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);
  if(plot_errorBars) histos.at(0)->Draw("E");
  else  histos.at(0)->Draw();

  theCanvas->Update();

  for(unsigned int i=1; i<histos.size(); i++){
    int color = kBlack;
    if (i > myColors.size()) {
      std::cout << "Not enough colors for " << histos.size() << " histos yet" << std::endl;
    } else {
      color = myColors[i];
    }
    histos.at(i)->SetFillColor(0);
    histos.at(i)->SetLineColor(color);
    histos.at(i)->SetLineWidth(2);
    if(histos.at(i)->Integral() > 0.)
        histos.at(i)->Scale(1.0/histos.at(i)->Integral());
    if(plot_errorBars && draw_statboxes) histos.at(i)->Draw("Esames");
    else if(plot_errorBars && !draw_statboxes) histos.at(i)->Draw("Esame");
    else if(!plot_errorBars && draw_statboxes) histos.at(i)->Draw("sames");
    else  histos.at(i)->Draw("same");
  }

  theCanvas->Update();
  
  theLegend->Draw();

  return;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

void PlotHelper::altDrawNormalizedHistos(std::vector <TH1F*> &histos, std::vector<std::string> names, bool draw_legend,
      			     std::string theTitle, std::string xaxis_label, std::string yaxis_label, 
			     bool renormalize, double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes) {


  if(histos.size()==0){
    std::cout<<"No histograms to plot for: "<<theTitle<<std::endl;
    return;
  }
  
  if(use_logYaxis) gPad->SetLogy();

  histos.at(0)->SetTitle(theTitle.c_str());

  histos.at(0)->SetFillColor(0);
  histos.at(0)->SetLineColor(myColors[0+m_colorStartIndex]);
  histos.at(0)->SetLineWidth(4);
  histos.at(0)->SetStats(0);

  float max = -999999.;
  int max_bin = -1;
  for(unsigned int i=0; i<histos.size(); i++){
    if (renormalize) {
      histos.at(i)->Scale(1.0/histos.at(i)->Integral());
    }
    if (histos.at(i)->GetMaximum() > max) {
      max = histos.at(i)->GetMaximum();
      max_bin = histos.at(i)->GetMaximumBin();
    }
  }
  if (y_Maximum <= 0) {	// not set by user
    y_Maximum = max * 1.2;
  }
  histos.at(0)->SetMaximum(y_Maximum);
    
  TAxis* xax= histos.at(0)->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histos.at(0)->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);
  if(plot_errorBars) histos.at(0)->Draw("E");
  else  histos.at(0)->Draw("HIST");

  for(unsigned int i=1; i<histos.size(); i++){
    int color = kBlack;
    if (i > myColors.size()-1) {
      std::cout << "Not enough colors for " << histos.size() << " histos yet" << std::endl;
    } else {
      color = myColors[i + m_colorStartIndex];
    }
    histos.at(i)->SetFillColor(0);
    histos.at(i)->SetLineColor(color);
    histos.at(i)->SetLineWidth(4);
    histos.at(i)->SetStats(0);
    if(plot_errorBars && draw_statboxes) histos.at(i)->Draw("Esames");
    else if(plot_errorBars && !draw_statboxes) histos.at(i)->Draw("Esame");
    else if(!plot_errorBars && draw_statboxes) histos.at(i)->Draw("HIST sames");
    else  histos.at(i)->Draw("HIST same");
  }

  if (draw_legend) {
    TLegend* lgnd;
    if (max_bin < histos.at(0)->GetNbinsX()/2) lgnd = new TLegend (0.55,0.89 - (histos.size() * .06),0.89,0.89);
    else lgnd = new TLegend (0.12,0.89 - (histos.size() * .06),0.37,0.89);
    lgnd->SetFillColor(0);
    lgnd->SetBorderSize(1);
    for (unsigned int i = 0; i < histos.size(); i++) {
      std::string name = i < names.size() ? names[i] : "???";
      lgnd->AddEntry(histos.at(i), name.c_str());
    }
    lgnd->DrawClone();
  }

  return;
}

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

void PlotHelper::DrawNormalizedHistos(TCanvas* &theCanvas, std::vector <TH1D*> &histos, 
					   double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
					   std::string xaxis_label,  std::string yaxis_label, TLegend* &theLegend){

  if(histos.size()==0){
    std::cout<<"No histograms to plot for: "<<theTitle<<std::endl;
    return;
  }

  // store the weights to make error calculate correct
  if(plot_errorBars) {
      for(unsigned int i = 0; i < histos.size(); i++)
          histos.at(i)->Sumw2();
  }
  
  if(use_logYaxis) gPad->SetLogy();

  histos.at(0)->SetTitle(theTitle.c_str());
  histos.at(0)->SetName(theTitle.c_str());
  histos.at(0)->SetFillColor(0);
  histos.at(0)->SetLineColor(kBlack);
  histos.at(0)->SetLineWidth(2);
  if(histos.at(0)->Integral() > 0)
      histos.at(0)->Scale(1.0/histos.at(0)->Integral());
  histos.at(0)->SetMaximum(y_Maximum);
    
  TAxis* xax= histos.at(0)->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histos.at(0)->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);
  if(plot_errorBars) histos.at(0)->Draw("E");
  else  histos.at(0)->Draw();

  theCanvas->Update();

  for(unsigned int i=1; i<histos.size(); i++){
    histos.at(i)->SetFillColor(0);
    histos.at(i)->SetLineColor(1+i);
    histos.at(i)->SetLineWidth(2);
    if(histos.at(0)->Integral() > 0.)
        histos.at(i)->Scale(1.0/histos.at(i)->Integral());
    if(plot_errorBars && draw_statboxes) histos.at(i)->Draw("Esames");
    else if(plot_errorBars && !draw_statboxes) histos.at(i)->Draw("Esame");
    else if(!plot_errorBars && draw_statboxes) histos.at(i)->Draw("sames");
    else  histos.at(i)->Draw("same");
  }

  theCanvas->Update();
  
  theLegend->Draw();

  return;
}

//////////////////////////////////////////////////////////////////////////////


void PlotHelper::DrawStackedHistos(TCanvas* &theCanvas, std::vector <TH1F*> &histos, double y_Maximum, 
					bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
					std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend){


   if(histos.size()==0){
    std::cout<<"No histograms to plot for: "<<theTitle<<std::endl;
    return;
  }
  
  if(use_logYaxis) gPad->SetLogy();

  unsigned int N_hists=histos.size();
  std::vector<TH1F*> histos_stack;
  std::vector<TH1F*>::iterator it;
  
  for(unsigned int i=0; i< N_hists; i++){
    histos_stack.push_back( (TH1F*) histos.at(i)->Clone() );
    histos.at(i)->SetFillColor(myColors.at(i+1)); histos_stack.at(i)->SetLineColor(i+2);
    for(unsigned int j=i+1; j<N_hists; j++){
      histos_stack.at(i)->Add( (TH1F*) histos.at(j)->Clone() );
    }
  }
  // for errors, assume histos[0] is signal, and all others are background.
  // errors will be only on total bkg, as sqrt(N_bkg), for histos[1]
  // and for signal, as sqrt(N_signal)
  
  for(int i=1; i <= histos_stack.at(0)->GetNbinsX(); i++)
    histos_stack.at(0)->SetBinError(i, histos.at(0)->GetBinError(i));

  histos_stack.at(0)->SetTitle(theTitle.c_str());
  histos_stack.at(0)->SetName(theTitle.c_str());
  histos_stack.at(0)->SetFillColor(myColors.at(1));
  //histos_stack.at(0)->SetFillStyle(0);
  histos_stack.at(0)->SetLineColor(kBlue); 
  histos_stack.at(0)->SetLineWidth(myColors.at(1));
  histos_stack.at(0)->SetMaximum(y_Maximum);
    
  TAxis* xax= histos_stack.at(0)->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histos_stack.at(0)->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);
  if(plot_errorBars) {histos_stack.at(0)->Draw("E");}
  else  histos_stack.at(0)->Draw();

  theCanvas->Update();

  for(unsigned int i=1; i<histos_stack.size(); i++){
    histos_stack.at(i)->SetFillColor(myColors.at(i+1));
    //histos_stack.at(i)->SetFillStyle(0);
    histos_stack.at(i)->SetLineColor(myColors.at(i+1));
    histos_stack.at(i)->SetLineWidth(2);
    if( (i==1 && plot_errorBars) && draw_statboxes) histos_stack.at(i)->Draw("Esames");
    else if( (i==1 && plot_errorBars) && !draw_statboxes) histos_stack.at(i)->Draw("Esame");
    else if(!plot_errorBars && draw_statboxes) histos_stack.at(i)->Draw("sames");
    else  histos_stack.at(i)->Draw("same");
  }

  theCanvas->Update();
  
  theLegend->Draw();

  return;
}

//////////////////////////////////////////////////////////////////////////////

void PlotHelper::DrawStackedHistos(TCanvas* &theCanvas, std::vector <TH1D*> &histos, double y_Maximum, 
					bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
					std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend){



   if(histos.size()==0){
    std::cout<<"No histograms to plot for: "<<theTitle<<std::endl;
    return;
  }
  
  if(use_logYaxis) gPad->SetLogy();

  unsigned int N_hists=histos.size();
  std::vector<TH1D*> histos_stack;
  std::vector<TH1D*>::iterator it;
  
  for(unsigned int i=0; i< N_hists; i++){
    histos_stack.push_back( (TH1D*) histos.at(i)->Clone() );
    histos.at(i)->SetFillColor(myColors.at(i+1)); histos_stack.at(i)->SetLineColor(i+2);
    for(unsigned int j=i+1; j<N_hists; j++){
      histos_stack.at(i)->Add( (TH1D*) histos.at(j)->Clone() );
    }
  }
  // for errors, assume histos[0] is signal, and all others are background.
  // errors will be only on total bkg, as sqrt(N_bkg), for histos[1]
  // and for signal, as sqrt(N_signal)
  
  for(int i=1; i <= histos_stack.at(0)->GetNbinsX(); i++)
    histos_stack.at(0)->SetBinError(i, histos.at(0)->GetBinError(i));

  histos_stack.at(0)->SetTitle(theTitle.c_str());
  histos_stack.at(0)->SetName(theTitle.c_str());
  histos_stack.at(0)->SetFillColor(myColors.at(1));
  histos_stack.at(0)->SetFillStyle(3001);
  histos_stack.at(0)->SetLineColor(myColors.at(1)); 
  histos_stack.at(0)->SetLineWidth(2);
  histos_stack.at(0)->SetMaximum(y_Maximum);
    
  TAxis* xax= histos_stack.at(0)->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histos_stack.at(0)->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);
  if(plot_errorBars) {histos_stack.at(0)->Draw("E");}
  else  histos_stack.at(0)->Draw("B");
  histos_stack.at(0)->SetFillStyle(3001);
  theCanvas->Update();

  for(unsigned int i=1; i<histos_stack.size(); i++){
    histos_stack.at(i)->SetFillColor(myColors.at(i+1));
    histos_stack.at(i)->SetFillStyle(3001);
    histos_stack.at(i)->SetLineColor(myColors.at(i+1));
    histos_stack.at(i)->SetLineWidth(2);
    if( (i==1 && plot_errorBars) && draw_statboxes) histos_stack.at(i)->Draw("Esames");
    else if( (i==1 && plot_errorBars) && !draw_statboxes) histos_stack.at(i)->Draw("Esame");
    else if(!plot_errorBars && draw_statboxes) histos_stack.at(i)->Draw("sames");
    else  histos_stack.at(i)->Draw("Bsame");
    histos_stack.at(i)->SetFillStyle(3001);
  }

  theCanvas->Update();
  
  theLegend->Draw();

  return;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

void PlotHelper::altDrawStackedHistos(std::vector <TH1F*> &histos, std::vector<std::string> names, bool draw_legend,
									  std::string theTitle, std::string xaxis_label, std::string yaxis_label, 
									  double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes) {
	
	
	if(histos.size()==0){
		std::cout<<"No histograms to plot for: "<<theTitle<<std::endl;
		return;
	}
	
	if(use_logYaxis) gPad->SetLogy();
	
	unsigned int N_hists=histos.size();
	std::vector<TH1F*> histos_stack;
	std::vector<TH1F*>::iterator it;
	
	for(unsigned int i=0; i< N_hists; i++){
		// histos_stack.push_back( (TH1F*) histos.at(i)->Clone() );
		histos_stack.push_back( histos.at(i) );
		histos_stack.at(i)->SetStats(0);
		histos_stack.at(i)->SetLineWidth(2);
		// add all later histograms -- puts first entry on top
		for(unsigned int j=i+1; j<N_hists; j++){
			histos_stack.at(i)->Add( (TH1F*) histos.at(j)->Clone() );
		}
	}
	// for errors, assume histos[0] is signal, and all others are background.
	// errors will be only on total bkg, as sqrt(N_bkg), for histos[1]
	// and for signal, as sqrt(N_signal)
	
	// for(int i=1; i <= histos_stack.at(0)->GetNbinsX(); i++)
    // histos_stack.at(0)->SetBinError(i, histos.at(0)->GetBinError(i));
	
	
	int max_bin = histos_stack.at(0)->GetMaximumBin();
	if (y_Maximum <= 0) {	// not set by user
		y_Maximum = histos_stack.at(0)->GetMaximum() * 1.2;
		// cout << "Set maximum to " << y_Maximum << endl;
	}
	histos_stack.at(0)->SetMaximum(y_Maximum);
    
	histos_stack.at(0)->SetTitle(theTitle.c_str());
	// histos_stack.at(0)->SetFillColor(myColors.at(0));
	// histos_stack.at(0)->SetFillStyle(3001);
	histos_stack.at(0)->SetLineColor(myColors.at(0)); 
	histos_stack.at(0)->SetLineWidth(3);
	histos_stack.at(0)->SetMaximum(y_Maximum);
    
	TAxis* xax= histos_stack.at(0)->GetXaxis();
	xax->SetTitle(xaxis_label.c_str());
	xax->SetTitleColor(kBlack);
	xax->SetTitleSize(0.05);
	
	TAxis* yax= histos_stack.at(0)->GetYaxis();
	yax->SetTitle(yaxis_label.c_str());
	yax->SetTitleColor(kBlack);
	yax->SetTitleSize(0.05);
	if(plot_errorBars) {histos_stack.at(0)->Draw("E");}
	else  histos_stack.at(0)->Draw("HIST");
	
	for(unsigned int i=0; i<histos_stack.size(); i++){
		
		// want consistent colors between stacked and normed histograms
		if (i != 0) histos_stack.at(i)->SetFillColor(myColors.at(i));
		histos_stack.at(i)->SetLineColor(myColors.at(i));
		// histos_stack.at(i)->SetFillStyle(3001);
		
		// no special treatment of 0th (signal) entry
		// if( (i==1 && plot_errorBars) && draw_statboxes) histos_stack.at(i)->Draw("Esames");
		// else if( (i==1 && plot_errorBars) && !draw_statboxes) histos_stack.at(i)->Draw("Esame");
		if(!plot_errorBars && draw_statboxes) histos_stack.at(i)->Draw("hist sames");
		else if (plot_errorBars) histos_stack.at(i)->Draw("e same");
		else histos_stack.at(i)->Draw("hist same");
	}
	
	if (draw_legend) {
		TLegend* lgnd;
		if (max_bin < histos.at(0)->GetNbinsX()/2) lgnd = new TLegend (0.55,0.89 - (histos.size() * .06),0.89,0.89);
		else lgnd = new TLegend (0.18,0.89 - (histos.size() * .06),0.40,0.89);
		lgnd->SetFillColor(0);
		lgnd->SetBorderSize(1);
		for (unsigned int i = 0; i < histos.size(); i++) {
			std::string name = i < names.size() ? names[i] : "???";
			lgnd->AddEntry(histos_stack.at(i), name.c_str());
		}
		lgnd->DrawClone();
	}
	
	
	return;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

void PlotHelper::altDrawStackedHistos2(std::vector <TH1F*> &histos, std::vector<std::string> names, bool draw_legend,
      			     std::string theTitle, std::string xaxis_label, std::string yaxis_label, 
			     double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes) {


   if(histos.size()==0){
    std::cout<<"No histograms to plot for: "<<theTitle<<std::endl;
    return;
  }
  
  if(use_logYaxis) gPad->SetLogy();

  unsigned int N_hists=histos.size();
  std::vector<TH1F*> histos_stack;
  std::vector<TH1F*>::iterator it;
  
  for(unsigned int i=0; i< N_hists; i++){
    // histos_stack.push_back( (TH1F*) histos.at(i)->Clone() );
    histos_stack.push_back( histos.at(i) );
    histos_stack.at(i)->SetStats(0);
    histos_stack.at(i)->SetLineWidth(2);
    // add all later histograms -- puts first entry on top
    for(unsigned int j=i+1; j<N_hists; j++){
      histos_stack.at(i)->Add( (TH1F*) histos.at(j)->Clone() );
    }
  }
  // for errors, assume histos[0] is signal, and all others are background.
  // errors will be only on total bkg, as sqrt(N_bkg), for histos[1]
  // and for signal, as sqrt(N_signal)
  
  // for(int i=1; i <= histos_stack.at(0)->GetNbinsX(); i++)
    // histos_stack.at(0)->SetBinError(i, histos.at(0)->GetBinError(i));


  int max_bin = histos_stack.at(0)->GetMaximumBin();
  if (y_Maximum <= 0) {	// not set by user
    y_Maximum = histos_stack.at(0)->GetMaximum() * 1.2;
    // cout << "Set maximum to " << y_Maximum << endl;
  }
  histos_stack.at(0)->SetMaximum(y_Maximum);
    
  histos_stack.at(0)->SetTitle(theTitle.c_str());
  // histos_stack.at(0)->SetFillColor(myColors.at(0));
  // histos_stack.at(0)->SetFillStyle(3001);
  histos_stack.at(0)->SetLineColor(myColors.at(0)); 
  histos_stack.at(0)->SetLineWidth(3);	
  histos_stack.at(0)->SetMaximum(y_Maximum);
    
  TAxis* xax= histos_stack.at(0)->GetXaxis();
  xax->SetTitle(xaxis_label.c_str());
  xax->SetTitleColor(kBlack);
  xax->SetTitleSize(0.05);

  TAxis* yax= histos_stack.at(0)->GetYaxis();
  yax->SetTitle(yaxis_label.c_str());
  yax->SetTitleColor(kBlack);
  yax->SetTitleSize(0.05);
  if(plot_errorBars) {histos_stack.at(0)->Draw("E");}
  else  histos_stack.at(0)->Draw("E");

  for(unsigned int i=1; i<histos_stack.size(); i++){

    // want consistent colors between stacked and normed histograms
    if (!plot_errorBars) histos_stack.at(i)->SetFillColor(myColors.at(i));
    histos_stack.at(i)->SetLineColor(myColors.at(i));
    // histos_stack.at(i)->SetFillStyle(3001);

    // no special treatment of 0th (signal) entry
    // if( (i==1 && plot_errorBars) && draw_statboxes) histos_stack.at(i)->Draw("Esames");
    // else if( (i==1 && plot_errorBars) && !draw_statboxes) histos_stack.at(i)->Draw("Esame");
    if(!plot_errorBars && draw_statboxes) histos_stack.at(i)->Draw("hist sames");
    else if (plot_errorBars) histos_stack.at(i)->Draw("e same");
    else histos_stack.at(i)->Draw("hist same");
  }
	// redraw to get on top
	if(plot_errorBars) {histos_stack.at(0)->Draw("e same");}
	else  histos_stack.at(0)->Draw("e same");

  if (draw_legend) {
    TLegend* lgnd;
    if (max_bin < histos.at(0)->GetNbinsX()/2) lgnd = new TLegend (0.55,0.89 - (histos.size() * .06),0.89,0.89);
    else lgnd = new TLegend (0.18,0.89 - (histos.size() * .06),0.40,0.89);
    lgnd->SetFillColor(0);
    lgnd->SetBorderSize(1);
    for (unsigned int i = 0; i < histos.size(); i++) {
      std::string name = i < names.size() ? names[i] : "???";
      lgnd->AddEntry(histos_stack.at(i), name.c_str());
    }
    lgnd->DrawClone();
  }


  return;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////


void PlotHelper::DrawAllOnCanvas(TCanvas* &theCanvas, std::map<std::string, TH1F*> histos, std::string saveAs)
{
  theCanvas->Clear();
  theCanvas->Divide(3, (int)(histos.size()/3.0) + (histos.size()%3==0 ? 0 : 1) );
  int nc=1;
  std::map<std::string, TH1F*>::iterator it=histos.begin();
  for(; it!=histos.end(); it++)
    {
      theCanvas->cd(nc);
      it->second->SetLineWidth(3);
      it->second->SetStats(111);
      it->second->Draw();
      nc++;
    }

  if(saveAs!="NO_SAVE")
    {
      theCanvas->Print( (saveAs+".C").c_str()   );
      theCanvas->Print( (saveAs+".png").c_str() );
      theCanvas->Print( (saveAs+".pdf").c_str() );   
    }
}

//////////////////////////////////////////////////////////////////////////////

std::map<std::string, TH1F*> PlotHelper::MapWithStr(std::map<std::string, TH1F*> &histos, std::string search)
{
  std::map<std::string, TH1F*> out;

  std::map<std::string, TH1F*>::iterator it=histos.begin();
  for(; it!=histos.end(); it++)
    {
      if( (*it).first.find(search)!=std::string::npos ) { out[it->first]=it->second; }
    }

  return out;
}

//////////////////////////////////////////////////////////////////////////////

void PlotHelper::DrawAllOnCanvas(TCanvas* &theCanvas, std::map<std::string, TH2F*> histos, std::string saveAs)
{
  theCanvas->Clear();
  theCanvas->Divide(3, (int)(histos.size()/3.0) + (histos.size()%3==0 ? 0 : 1) );
  int nc=1;
  std::map<std::string, TH2F*>::iterator it=histos.begin();
  for(; it!=histos.end(); it++)
    {
      theCanvas->cd(nc);
      it->second->SetLineWidth(3);
      it->second->SetStats(111);
      it->second->Draw();
      nc++;
    }

  if(saveAs!="NO_SAVE")
    {
      theCanvas->Print( (saveAs+".C").c_str()   );
      theCanvas->Print( (saveAs+".png").c_str() );
      theCanvas->Print( (saveAs+".pdf").c_str() );   
    }
}

//////////////////////////////////////////////////////////////////////////////

std::map<std::string, TH2F*> PlotHelper::MapWithStr(std::map<std::string, TH2F*> &histos, std::string search)
{
  std::map<std::string, TH2F*> out;
  
  std::map<std::string, TH2F*>::iterator it=histos.begin();
  for(; it!=histos.end(); it++)
    {
      if( (*it).first.find(search)!=std::string::npos ) { out[it->first]=it->second; }
    }

  return out;
}


//////////////////////////////////////////////////////////////////////////////
int PlotHelper::FindBinContaining(TObject* h, double val, int axis)
{
  TH1* proj;
  if(h->IsA()->InheritsFrom("TH1") && !(h->IsA()->InheritsFrom("TH2")) )
    { 
      proj = (TH1*) h->Clone("proj"); 
    }
  else if( h->IsA()->InheritsFrom("TH2") ) 
    {
      TH2* h2=(TH2*) h;
      if(axis==1)      { proj=(TH1*) h2->ProjectionX(); }
      else if(axis==2) { proj=(TH1*) h2->ProjectionY(); }
      else return -1;
    }
  else return -1;
  
  int theBin=-1;
  for(int i=1; i<=proj->GetNbinsX(); i++)
    {
      if(val >= proj->GetBinLowEdge(i) && val < (proj->GetBinLowEdge(i) + proj->GetBinWidth(i)) ){
	theBin=i;
	break;
      }
    }
  
  delete proj;
  return theBin;
  
}

