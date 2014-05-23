/*
 * GateSEQAnd.h
 * 
 * Part of dft2lnt library - a library containing read/write operations for DFT
 * files in Galileo format and translating DFT specifications into Lotos NT.
 * 
 * @author Freark van der Berg
 */

class GateSEQAnd;

#ifndef GATESEQAND_H
#define GATESEQAND_H

#include "Gate.h"

namespace DFT {
namespace Nodes {

class GateSEQAnd: public Gate {
private:
	
public:
	GateSEQAnd(Location loc, std::string name):
		Gate(loc,name,GateSEQAndType) {
	}
	virtual ~GateSEQAnd() {
	}
};

} // Namespace: Nodes
} // Namespace: DFT

#endif // GateSEQAnd_H
