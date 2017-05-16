#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MyAnalysis/MyxAODAnalysis.h>
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/Message.h"

// EDM include(s);
#include "xAODEventInfo/EventInfo.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthVertex.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODJet/Jet.h"
#include "xAODJet/JetContainer.h"

/// Helper macro for checking xAOD::TReturnCode return values
#define EL_RETURN_CHECK( CONTEXT, EXP )                     \
  do {                                                     \
  if( ! EXP.isSuccess() ) {                             \
  Error( CONTEXT,                                    \
    XAOD_MESSAGE( "Failed to execute: %s" ),    \
	 #EXP );                                     \
  return EL::StatusCode::FAILURE;                    \
  }                                                     \
  } while( false )

// this is needed to distribute the algorithm to the workers
ClassImp(MyxAODAnalysis)



MyxAODAnalysis :: MyxAODAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode MyxAODAnalysis :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  // let's initialize the algorithm to use the xAODRootAccess package
  job.useXAOD ();
  EL_RETURN_CHECK( "setupJob()", xAOD::Init() ); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  m_plotter = new PlotHelper();
  std::map<std::string, TH1F*> h_1d;
  std::map<std::string, TH2F*> h_2d;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.
  xAOD::TEvent* event = wk()->xaodEvent();

  // count number of events
  m_eventCounter = 0;

  // as a check, let's see the number of events in our xAOD
  Info("initialize()", "Number of events = %lli", event->getEntries() ); // print long long int
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  xAOD::TEvent* event = wk()->xaodEvent();

  // print every 100 events, so we know where we are:
  if( (m_eventCounter % 100) ==0 ) Info("execute()", "Event number = %i", m_eventCounter );
  m_eventCounter++;

  m_plotter->Plot1D("counter", 1, 1, h_1d, 10500, 0, 10500); 

  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo* eventInfo = 0;
  EL_RETURN_CHECK("execute",event->retrieve( eventInfo, "EventInfo"));  
  
  // check if the event is data or MC
  // (many tools are applied either to data or MC)
  bool isMC = false;
  // check if the event is MC
  if(eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) ){
    isMC = true; // can do something with this later
  }   

  //----------------------
  // TRUTH PARTICLES
  //----------------------
  const xAOD::TruthParticleContainer* truthParticles = 0;
  EL_RETURN_CHECK("execute()",event->retrieve( truthParticles, "TruthParticles"));

  // Loop over truth particles to find Higgses
  const xAOD::TruthParticle *h1 = nullptr, *h2 = nullptr; // hh 

  //  const xAOD::TruthParticle* p1 = NULL;
  //const xAOD::TruthParticle* p2 = NULL;

  //  float weight = eventInfo->mcEventWeight();

  float weight = 1.;
  bool bChild;
  bool yChild;
  int higgsCount = 0.;
  
    for(const auto& truthPar : *truthParticles) {
      bChild=false;
      yChild=false;
      if( truthPar->absPdgId() == 25) {
	if( truthPar->nChildren()!=2 ) continue;
	//if( truthPar->child(0)->absPdgId()==5 && truthPar->child(1)->absPdgId()==5 && truthPar->child(0)->status()==23 && truthPar->child(1)->status()==23) bChild = true; //UNCOMMENT FOR POWHEG SAMPLES 
	if( truthPar->child(0)->absPdgId()==5 && truthPar->child(1)->absPdgId()==5) bChild = true; 
	if( truthPar->child(0)->absPdgId()==22 && truthPar->child(1)->absPdgId()==22) yChild = true;

	if(bChild || yChild) higgsCount++;
    	else continue;
	if(higgsCount==1 && bChild) h1 = truthPar;
	else if(higgsCount==1 && yChild) h2 = truthPar;
	else if(higgsCount==2 && bChild) h1 = truthPar;
	else if(higgsCount==2 && yChild) h2 = truthPar;
      }
    } // end of loop over truth particles

    m_plotter->Plot1D("afterParSel", 1, 1, h_1d, 10500, 0, 10500);     
    
    if (h1==nullptr || h2==nullptr) return EL::StatusCode::SUCCESS;

    m_plotter->Plot1D("afterNULL", 1, 1, h_1d, 10500, 0, 10500);     

    const xAOD::TruthVertex *prodVtx1 = h1->prodVtx();
    const xAOD::TruthVertex *prodVtx2 = h2->prodVtx();
    
    //    if(prodVtx1==nullptr || prodVtx2==nullptr) return EL::StatusCode::SUCCESS; 
    //    if(prodVtx1->x()==prodVtx2->x() && prodVtx1->y()==prodVtx2->y() && prodVtx1->z()==prodVtx2->z()){
      
    //mass distributions
    m_plotter->Plot1D("m_h1", h1->m()/1000, 1, h_1d, 1000, 0, 1000);
    m_plotter->Plot1D("m_h2", h2->m()/1000, 1, h_1d, 1000, 0, 1000);
    
    //pt distributions    
    m_plotter->Plot1D("h1_pt", h1->pt()/1000, 1, h_1d, 100, 0, 1000);
    m_plotter->Plot1D("h2_pt", h2->pt()/1000, 1, h_1d, 100, 0, 1000);
    m_plotter->Plot2D("h1Vsh2Pt", h2->pt()/1000, h1->pt()/1000, 1, h_2d, 100, 0., 1000., 100, 0., 1000.);
    
    //eta distributions
    m_plotter->Plot1D("h1_eta", h1->eta(), 1, h_1d, 100, -4, 4);
    m_plotter->Plot1D("h2_eta", h2->eta(), 1, h_1d, 100, -4, 4);
    m_plotter->Plot1D("delta_eta", TMath::Abs(h1->eta() - h2->eta()), 1, h_1d, 100, 0, 10);
    m_plotter->Plot2D("h1Vsh2Eta", h2->eta(), h1->eta(), 1, h_2d, 100, -4., 4., 100, -4., 4.);
    
    //phi distributions
    m_plotter->Plot1D("h1_phi", h1->phi(), 1, h_1d, 100, -TMath::Pi(), TMath::Pi());
    m_plotter->Plot1D("h2_phi", h2->phi(), 1, h_1d, 100, -TMath::Pi(), TMath::Pi());
    m_plotter->Plot1D("delta_phi", h1->phi() - h2->phi(), 1, h_1d, 100, -TMath::Pi(), TMath::Pi());
    m_plotter->Plot2D("h1Vsh2Phi", h2->phi(), h1->phi(), 1, h_2d, 100, -TMath::Pi(), TMath::Pi(), 100, -TMath::Pi(), TMath::Pi());
    
    //theta distributions
    m_plotter->Plot1D("cosTheta", cos((h1->p4()).Theta() - (h2->p4()).Theta()), 1, h_1d, 100, -1, 1);
    
    //deltaR distribution
    m_plotter->Plot1D("deltaR_hh", (h1->p4()).DeltaR(h2->p4()), 1, h_1d, 100, 0, 10);
    
    const xAOD::TruthParticle* b1 = h1->child(0);
    const xAOD::TruthParticle* b2 = h1->child(1);
    const xAOD::TruthParticle* g1 = h2->child(0);
    const xAOD::TruthParticle* g2 = h2->child(1);
    
    TLorentzVector bq1=b1->p4(), bq2=b2->p4();
    TLorentzVector bb = bq1+bq2;
    TLorentzVector hh = h1->p4()+h2->p4();

    //Validation Plots                                                                                                                                
    m_plotter->Plot1D("deltaR_b", (bq1).DeltaR(bq2), weight, h_1d, 10, -0.5, 9.5);
    if(bq1.Pt()>bq2.Pt()) m_plotter->Plot1D("b_lead_pt", bq1.Pt()/1000, weight, h_1d, 160, 0, 800);
    if(bq2.Pt()>bq1.Pt()) m_plotter->Plot1D("b_lead_pt", bq2.Pt()/1000, weight, h_1d, 160, 0, 800);
    
    m_plotter->Plot1D("b_pt", bq1.Pt()/1000, weight, h_1d, 160, 0, 800);
    m_plotter->Plot1D("b_pt", bq2.Pt()/1000, weight, h_1d, 160, 0, 800);
    
    m_plotter->Plot1D("m_bb", bb.M()/1000, weight, h_1d, 1000, 0, 1000);
    m_plotter->Plot1D("bb_pt", bb.Pt()/1000, weight, h_1d, 160, 0, 800);
    m_plotter->Plot1D("bb_eta", bb.Eta(), 1, h_1d, 100, -4, 4);
    m_plotter->Plot1D("bb_phi", bb.Phi(), 1, h_1d, 100, -TMath::Pi(), TMath::Pi());
    
    m_plotter->Plot1D("m_hh", hh.M()/1000, weight, h_1d, 1000, 0, 1000);
    m_plotter->Plot1D("hh_pt", hh.Pt()/1000, weight, h_1d, 160, 0, 800);
    m_plotter->Plot1D("hh_eta", hh.Eta(), 1, h_1d, 100, -4, 4);
    m_plotter->Plot1D("hh_phi", hh.Phi(), 1, h_1d, 100, -TMath::Pi(), TMath::Pi());

    //      TLorentzVector y1=h2->child(0)->p4(), y2=h2->child(1)->p4();
    TLorentzVector y1=g1->p4(), y2=g2->p4();
    TLorentzVector yy = y1+y2;
    m_plotter->Plot1D("m_yy", yy.M()/1000, weight, h_1d, 1000, 0, 1000);
    m_plotter->Plot1D("yy_pt", yy.Pt()/1000, weight, h_1d, 160, 0, 800);
    m_plotter->Plot1D("yy_eta", yy.Eta(), 1, h_1d, 100, -4, 4);
    m_plotter->Plot1D("yy_phi", yy.Phi(), 1, h_1d, 100, -TMath::Pi(), TMath::Pi());      
    
    m_plotter->Plot1D("m_yybb", (bb+yy).M()/1000, weight, h_1d, 1000, 0, 1000);
    m_plotter->Plot1D("yybb_pt", (bb+yy).Pt()/1000, weight, h_1d, 160, 0, 800);
    m_plotter->Plot1D("yybb_eta", (bb+yy).Eta(), 1, h_1d, 100, -4, 4);
    m_plotter->Plot1D("yybb_phi", (bb+yy).Phi(), 1, h_1d, 100, -TMath::Pi(), TMath::Pi());
    m_plotter->Plot1D("deltaR_bb_yy", (bb).DeltaR(yy), 1, h_1d, 100, 0, 10);

    //  }
    //    else return EL::StatusCode::SUCCESS;
   
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.

  std::map<std::string, TH1F*>::iterator it1 = h_1d.begin();                                                                            
  for(; it1!=h_1d.end(); it1++)                                                                                                                              
    {                                                                                                                                                             
      wk()->addOutput(it1->second);                                                                                                                                
    }


  std::map<std::string, TH2F*>::iterator it2 = h_2d.begin();
  for(; it2!=h_2d.end(); it2++)
    {                                                                                                                                                         
      wk()->addOutput(it2->second);                                                                                                                           
    }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  xAOD::TEvent* event = wk()->xaodEvent();
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}
