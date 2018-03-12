# ifndef SCHEMATIC_NET_H
# define SCHEMATIC_NET_H

#include <string>
#include <vector>
#include "Term.h"
#include "Node.h"
#include "Point.h"
#include "Cell.h"
#include "Instance.h"
#include "Indentation.h"
namespace Netlist {
// Les *forward declarations* des autres objets de la
// structure de données sont mis *à l’intérieur* du namespace.
class Cell;
class Node;

class Net {
private :
	Cell * owner_ ;
	std :: string name_ ;
	unsigned int id_ ;
	Term :: Type type_ ;
	std :: vector < Node * > nodes_ ;
public :
			Net 	( Cell *, const std :: string &,Term::Type );
			~ Net 	();
	Cell *		getCell () const ;
	const std::string& 
			getName () const ;
	unsigned int 	getId () const ;
	Term::Type 	getType () const ;
	const std::vector<Node*>&	
			getNodes () const ;
	size_t 		getFreeNodeId () const ;
	void 		add ( Node * );
	bool 		remove ( Node * );
};


#endif
