//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file SensitiveDetector.cc
/// \brief Implementation of the SensitiveDetectorHit class
//

#include "SensitiveDetectorHit.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// -- one more nasty trick for new and delete operator overloading:
G4Allocator<SensitiveDetectorHit> SDHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
SensitiveDetectorHit::SensitiveDetectorHit(const G4Step* step) // no need for strip, write parentID instead
// const means that the compiler won't let you modify the step, which is what we want
  
// <<-- note BTW this is the only way to initialize a "const" member
{
   
   // step info for particle tree
   const G4VProcess* currentProcess = step -> GetPreStepPoint() ->GetProcessDefinedStep();  
   
   if (currentProcess != 0){ // save the step process if it exists
	processPre_ = step -> GetPreStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
   }
   else processPre_ = "NaN"; // otherwise print a NaN as a place holder

   processPost_ = step -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
   particleType_ = step -> GetTrack() -> GetParticleDefinition() -> GetParticleName();
   volumePre_ = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName();
 
   if (step -> GetPostStepPoint() -> GetPhysicalVolume() != 0){ // save the post volume name if it exists
	volumePost_ = step -> GetPostStepPoint() -> GetPhysicalVolume() -> GetName();
   }
   else volumePost_ = "NaN"; // otherwise print a NaN as a place holder

   // step info for energy tree
   //eDep_ = step -> GetTotalEnergyDeposit(); // get energy deposition from the step, extract the parent ID
   //nonIeDep_ = step -> GetNonIonizingEnergyDeposit();
   kineticEnergyPre_ = step -> GetPreStepPoint() -> GetKineticEnergy();
   kineticEnergyPost_ = step -> GetPostStepPoint() -> GetKineticEnergy();
   parentID_ = step -> GetTrack() -> GetParentID();
   //chargePre_ = step -> GetPreStepPoint() -> GetCharge();
   //chargePost_ = step -> GetPostStepPoint() -> GetCharge();

   // step info for particle pre position
   postPreX_ = step -> GetPreStepPoint() -> GetPosition().x();
   postPreY_ = step -> GetPreStepPoint() -> GetPosition().y();
   postPreZ_ = step -> GetPreStepPoint() -> GetPosition().z(); 
   
   // step info for particle post position
   postPostX_ = step -> GetPostStepPoint() -> GetPosition().x();
   postPostY_ = step -> GetPostStepPoint() -> GetPosition().y();
   postPostZ_ = step -> GetPostStepPoint() -> GetPosition().z(); 
   // verified that GetTrack() gives the same position as the PostStep Position
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SensitiveDetectorHit::~SensitiveDetectorHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


