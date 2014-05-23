/*
 * GatePrio.h
 * 
 * Part of dft2lnt library - a library containing read/write operations for DFT
 * files in Galileo format and translating DFT specifications into Lotos NT.
 * 
 * @author Freark van der Berg
 */

class GatePrio;

#ifndef GatePrio_H
#define GatePrio_H

#include "Gate.h"

namespace DFT {
namespace Nodes {

class GatePrio: public Gate {
private:
	
public:
	GatePrio(Location loc, std::string name):
		Gate(loc,name,GatePrioType) {
	}
	virtual ~GatePrio() {
	}
};

} // Namespace: Nodes
} // Namespace: DFT

#endif // GatePrio_H
