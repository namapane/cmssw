/** \file
 * 
 *
 * \author N. Amapane - INFN Torino
 */


#include <DataFormats/DTDigi/interface/DTDigi.h>
#include <FWCore/Utilities/interface/Exception.h>

using namespace std;


DTDigi::DTDigi (int wire, int nTDC, int number, int base) : 
  theCounts(nTDC),
  theWire(wire),
  theNumber(number),
  theTDCBase(base)
{
  if (number>255 || number <0 || !(base==30 || base==32)) {
    throw cms::Exception("InvalidDetId") << "DTDigi ctor: invalid parameters: number: " << number << " base: " << base << endl;
  }
}


DTDigi::DTDigi (int wire, double tdrift, int number, int base): 
  theCounts(static_cast<int>(tdrift/25.*base)),
  theWire(wire),
  theNumber(number),
  theTDCBase(base)
{
  if (number>255 || number <0 || !(base==30 || base==32)) {
    throw cms::Exception("InvalidDetId") << "DTDigi ctor: invalid parameters: number: " << number << " base: " << base << endl;
  }
}


DTDigi::DTDigi ():
  theCounts(0), 
  theWire(0),
  theNumber(0),
  theTDCBase(32)
{}


// Comparison
bool
DTDigi::operator == (const DTDigi& digi) const {
  if ( theWire != digi.wire() ||
       //       theNumber != digi.number() || //FIXME required ??
       theCounts != digi.countsTDC() ) return false;
  return true;
}

double DTDigi::time() const { return theCounts*25./theTDCBase; }

int32_t DTDigi::countsTDC() const { return theCounts; }

int DTDigi::wire() const { return theWire; }

int DTDigi::number() const { return theNumber; }

double DTDigi::tdcUnit() const { return 25./theTDCBase; }

int DTDigi::tdcBase() const { return theTDCBase; }


// Setters - DEPRECATED

// void DTDigi::setTime(double time){
//   theCounts = static_cast<int>(time/reso);
// }

// void DTDigi::setCountsTDC (int nTDC) {
//   if (nTDC<0) cout << "WARNING: DTDigi::setCountsTDC: negative TDC count not supported "
// 		   << nTDC << endl;
//   theCounts = nTDC;
// }


// Debug

void
DTDigi::print() const {
  cout << "Wire " << wire() 
       << " Digi # " << number()
       << " Drift time (ns) " << time() << endl;
}

