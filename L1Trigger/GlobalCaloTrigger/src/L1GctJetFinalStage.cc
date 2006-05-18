#include "L1Trigger/GlobalCaloTrigger/interface/L1GctJetFinalStage.h"

#include "FWCore/Utilities/interface/Exception.h"

L1GctJetFinalStage::L1GctJetFinalStage():
  m_wheelFpgas(MAX_WHEEL_FPGAS),
  m_inputCentralJets(MAX_JETS_IN),
  m_inputForwardJets(MAX_JETS_IN),
  m_inputTauJets(MAX_JETS_IN),
  m_centralJets(MAX_JETS_OUT),
  m_forwardJets(MAX_JETS_OUT),
  m_tauJets(MAX_JETS_OUT),
  m_outputJc(12)
{
}

L1GctJetFinalStage::~L1GctJetFinalStage()
{
}

void L1GctJetFinalStage::reset()
{
  //Clear all jet data
  m_inputCentralJets.clear();
  m_inputForwardJets.clear();
  m_inputTauJets.clear();
  m_centralJets.clear();
  m_forwardJets.clear();
  m_tauJets.clear();
  //Resize the vectors
  m_inputCentralJets.resize(MAX_JETS_IN);
  m_inputForwardJets.resize(MAX_JETS_IN);
  m_inputTauJets.resize(MAX_JETS_IN);
  m_centralJets.resize(MAX_JETS_OUT);
  m_forwardJets.resize(MAX_JETS_OUT);
  m_tauJets.resize(MAX_JETS_OUT);
  //
  m_outputHt.reset();
  for (int i=0; i<12; ++i) {
    m_outputJc[i].reset();
  }
}

void L1GctJetFinalStage::fetchInput()
{
  for(unsigned short iWheel=0; iWheel < MAX_WHEEL_FPGAS; ++iWheel)
  {
    storeJets(m_inputCentralJets, m_wheelFpgas[iWheel]->getCentralJets(), iWheel);
    storeJets(m_inputForwardJets, m_wheelFpgas[iWheel]->getForwardJets(), iWheel);
    storeJets(m_inputTauJets, m_wheelFpgas[iWheel]->getTauJets(), iWheel);
  }
}

void L1GctJetFinalStage::process()
{
  //Process jets
  sort(m_inputCentralJets.begin(), m_inputCentralJets.end(), L1GctJetCand::rankGreaterThan());
  sort(m_inputForwardJets.begin(), m_inputForwardJets.end(), L1GctJetCand::rankGreaterThan());
  sort(m_inputTauJets.begin(), m_inputTauJets.end(), L1GctJetCand::rankGreaterThan());

  for(unsigned short iJet = 0; iJet < MAX_JETS_OUT; ++iJet)
  {
    m_centralJets[iJet] = m_inputCentralJets[iJet];
    m_forwardJets[iJet] = m_inputForwardJets[iJet];
    m_tauJets[iJet] = m_inputTauJets[iJet];
  }  
}

void L1GctJetFinalStage::setInputWheelJetFpga(int i, L1GctWheelJetFpga* wjf)
{
  if(i >= 0 && i < MAX_WHEEL_FPGAS)
  {
    m_wheelFpgas[i] = wjf;
  }
  else
  {
    throw cms::Exception("RangeError")
    << "In L1GctJetFinalStage, Wheel Jet FPGA " << i << " is outside input range of 0 to "
    << (MAX_WHEEL_FPGAS-1) << "\n";
  }
}

void L1GctJetFinalStage::setInputCentralJet(int i, L1GctJetCand jet)
{
  if(i >= 0 && i < MAX_JETS_IN)
  {
    m_inputCentralJets[i] = jet;
  }
  else
  {
    throw cms::Exception("RangeError")
    << "In L1GctJetFinalStage, Central Jet " << i << " is outside input range of 0 to "
    << (MAX_JETS_IN-1) << "\n";
  }
}

void L1GctJetFinalStage::setInputForwardJet(int i, L1GctJetCand jet)
{
  if(i >= 0 && i < MAX_JETS_IN)
  {
    m_inputForwardJets[i] = jet;
  }
  else
  {
    throw cms::Exception("RangeError")
    << "In L1GctJetFinalStage, Forward Jet " << i << " is outside input range of 0 to "
    << (MAX_JETS_IN-1) << "\n";
  }
}

void L1GctJetFinalStage::setInputTauJet(int i, L1GctJetCand jet)
{
  if(i >= 0 && i < MAX_JETS_IN)
  {
    m_inputTauJets[i] = jet;
  }
  else
  {
    throw cms::Exception("RangeError")
    << "In L1GctJetFinalStage, Tau Jet " << i << " is outside input range of 0 to "
    << (MAX_JETS_IN-1) << "\n";
  }
}

void L1GctJetFinalStage::storeJets(JetVector& storageVector, JetVector jets, unsigned short iWheel)
{
  for(unsigned short iJet = 0; iJet < L1GctWheelJetFpga::MAX_JETS_OUT; ++iJet)
  {
    storageVector[(iWheel*L1GctWheelJetFpga::MAX_JETS_OUT) + iJet] = jets[iJet];
  }
}
