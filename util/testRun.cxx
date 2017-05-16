#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ScanDir.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>
#include <TTree.h>
#include <sstream>
#include "SampleHandler/ScanDir.h"
#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoop/OutputStream.h>

#include "MyAnalysis/MyxAODAnalysis.h"

int main( int argc, char* argv[] ) {

  //  Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  if( argc > 1 ) submitDir = argv[ 1 ];
  
  
  //  Construct the samples to run on:
  SH::SampleHandler sh;
  
  // MC single file:                                                                                                                                  
  //  const char* inputFilePath = gSystem->ExpandPathName ("/scratch/users/tvarol/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/eskiNR/");
  //   const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344714/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344723/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344724/");                    
  // const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344725/");                    
  //const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344726/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344727/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344728/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344729/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344730/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344731/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344732/");                    
    const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344733/");                    
  //const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/344734/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/runNomNR/");                    
  //  const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/generation2/outputs/DAOD/341004/");                    
  //const char* inputFilePath = gSystem->ExpandPathName ("/users/tvarol/bbyy/validation/Run_NLO/");                    
  SH::DiskListLocal list (inputFilePath);
  SH::scanDir (sh, list, "DAOD_TRUTH0*.root*"); // specifying one particular file for testing 
  sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );
  job.options()->setDouble (EL::Job::optMaxEvents, -1);

  // Add our analysis to the job:
  MyxAODAnalysis* alg = new MyxAODAnalysis();

  /*
  // define an output and an ntuple associated to that output                                                                                         
  EL::OutputStream output("myOutput");
  job.outputAdd (output);
  EL::NTupleSvc *ntuple = new EL::NTupleSvc ("myOutput");
  job.algsAdd (ntuple);
  */
  job.algsAdd( alg );

  //  alg->outputName = "myOutput"; // give the name of the output to our algorithm  

  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}
