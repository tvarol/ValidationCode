#ifndef PLOT_HELPER_H
#define PLOT_HELPER_H
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TH1.h>
#include <TProfile.h>
#include <TLorentzVector.h>
#include "TLorentzRotation.h"
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TPaveStats.h>
#include <TMath.h>
#include "TRandom.h"
#include <vector>


class PlotHelper{
public :
    
  PlotHelper();

  void set_plot_style();
  void set_doSumW2( bool s) { doSumW2=s; };

  void Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2D*> &theHistos, 
	      int NumBinsX, double XMin, double XMax, int NumBinsY, double YMin, double YMax);
	      
  void Plot2D(std::string Title, float XVal, float YVal, double weight, std::map<std::string, TH2F*> &theHistos, 
	      int NumBinsX, float XMin, float XMax, int NumBinsY, float YMin, float YMax);

  void Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2D*> &theHistos, 
	      int NumBinsX, const double* Xbins, int NumBinsY, double YMin, double YMax);

  void Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2F*> &theHistos, 
	      int NumBinsX, const double* Xbins, int NumBinsY, double YMin, double YMax);

  void Plot2D(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TH2D*> &theHistos, 
	      int NumBinsX, const float* Xbins, int NumBinsY, const float* Ybins);
  
  void Plot2D(std::string Title, float XVal,  float YVal, double weight, std::map<std::string, TH2F*> &theHistos, 
	      int NumBinsX, const float* Xbins, int NumBinsY, const float* Ybins);
  
  void PlotTProfile(std::string Title, double XVal, double YVal, double weight, std::map<std::string, TProfile*> &theHistos,
		    int NumBinsX, double XMin, double XMax, double YMin, double YMax);
  /*
  void PlotTProfile(string Title, double XVal, double YVal, double weight, std::map<string, TProfile*> &theHistos,
		    int NumBinsX, const float* Xbins);

  void PlotTProfile(string Title, double XVal, double YVal, double weight, std::map<string, TProfile*> &theHistos, 
		    int NumBinsX, const double* Xbins);
  
  void PlotTProfile(string Title, double XVal, double YVal, double weight, std::map<string, TProfile*> &theHistos, 
		    int NumBinsX, double XMin, double XMax);

  void PlotTProfile(string Title, double XVal, double YVal, double weight, std::map<string, TProfile*> &theHistos,
		    Int_t NumBinsX, const double* Xbins, double YMin, double YMax);
  */
  void Plot1D(std::string Title, double XVal, double weight, std::map<std::string, TH1D*> &theHistos, 
	    int NumBinsX, double XMin, double XMax);
	   
  void Plot1D(std::string Title, float XVal, double weight, std::map<std::string, TH1F*> &theHistos, 
	    int NumBinsX, float XMin, float XMax);

  void Plot1D(std::string Title, double XVal, double weight, std::map<std::string, TH1D*> &theHistos, 
	    int NumBinsX, const float* Xbins);
	   
  void Plot1D(std::string Title, float XVal, double weight, std::map<std::string, TH1F*> &theHistos, 
	    int NumBinsX, const float* Xbins);

  void DrawHistos(TCanvas* &theCanvas, TH1F* &Signal, TH1F* &Bkg1, TH1F* &Bkg2, TH1F* &BkgTot, 
		  double y_Maximum, bool use_logYaxis, bool plot_errorBars, std::string theTitle, 
		   std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend);

  void Draw2DHistoNice(TCanvas* &theCanvas, TH2F* &histo, bool use_logXaxis, bool use_logYaxis, std::string theTitle, 
		       std::string xaxis_label, std::string yaxis_label, std::string DrawOption="");
  
  void Draw2DHistoNice(TCanvas* &theCanvas, TH2D* &histo, bool use_logXaxis, bool use_logYaxis, std::string theTitle, 
		       std::string xaxis_label, std::string yaxis_label, std::string DrawOption="");

  void DrawProfileHistoNice(TCanvas* &theCanvas, TProfile* &histo, bool use_logXaxis, bool use_logYaxis, std::string theTitle, 
		       std::string xaxis_label, std::string yaxis_label, std::string DrawOption="");

  void Draw1DHistoNice(TCanvas* &theCanvas, TH1F* &histo, bool use_logXaxis, bool use_logYaxis, std::string theTitle, 
		       std::string xaxis_label, std::string yaxis_label, std::string DrawOption="");

  void DrawNormalizedHistos(TCanvas* &theCanvas, std::vector <TH1F*> &histos, 
			    double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
			    std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend);

  void DrawNormalizedHistos(TCanvas* &theCanvas, std::vector <TH1D*> &histos, 
			    double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
			    std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend);

  // a slightly different style, by corrinne, with lots of default values and an auto-generating TLegend
  // also, you can tell it not to rescale the plots
  void altDrawNormalizedHistos(std::vector <TH1F*> &histos, std::vector<std::string> names, bool draw_legend = false, 
      			     std::string theTitle = "", std::string xaxis_label = "", std::string yaxis_label = "", 
			     bool renormalize = true, double y_Maximum = 0, bool use_logYaxis = false, 
			     bool plot_errorBars = false, bool draw_statboxes = false);

  void altDrawStackedHistos(std::vector <TH1F*> &histos, std::vector<std::string> names, bool draw_legend = false, 
      			     std::string theTitle = "", std::string xaxis_label = "", std::string yaxis_label = "", 
			     double y_Maximum = 0, bool use_logYaxis = false, 
			     bool plot_errorBars = false, bool draw_statboxes = false);
	
	// small modifications: mostly draw the data last, so it can be seen. always put error bars on data. 
	// might change this more in the future, so wanted to have something to play with. gio.
  void altDrawStackedHistos2(std::vector <TH1F*> &histos, std::vector<std::string> names, bool draw_legend = false, 
						  std::string theTitle = "", std::string xaxis_label = "", std::string yaxis_label = "", 
						  double y_Maximum = 0, bool use_logYaxis = false, 
						  bool plot_errorBars = false, bool draw_statboxes = false);

  void DrawStackedHistos(TCanvas* &theCanvas, std::vector <TH1F*> &histos, 
			 double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
			 std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend);

  void DrawStackedHistos(TCanvas* &theCanvas, std::vector <TH1D*> &histos, 
			 double y_Maximum, bool use_logYaxis, bool plot_errorBars, bool draw_statboxes, std::string theTitle, 
			 std::string xaxis_label, std::string yaxis_label, TLegend* &theLegend);

  void DrawAllOnCanvas(TCanvas* &theCanvas, std::map<std::string, TH1F*> histos, std::string saveAs="NO_SAVE");
  void DrawAllOnCanvas(TCanvas* &theCanvas, std::map<std::string, TH2F*> histos, std::string saveAs="NO_SAVE");

  std::map<std::string, TH1F*> MapWithStr(std::map<std::string, TH1F*> &histos, std::string search); 
  std::map<std::string, TH2F*> MapWithStr(std::map<std::string, TH2F*> &histos, std::string search);

  int FindBinContaining(TObject* h, double val, int axis=1);

 std::vector<int> myColors;
 
 bool doSumW2;

 int m_colorStartIndex;
};





#endif
