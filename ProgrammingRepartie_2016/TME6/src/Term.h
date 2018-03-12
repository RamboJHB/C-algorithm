# ifndef SCHEMATIC_TERM_H
# define SCHEMATIC_TERM_H

#include <string>
#include <vector>
#include "Indentation.h"
#include "Node.h"
#include "Point.h"
#include "Cell.h"
#include "Instance.h"

namespace Netlist {
// Les *forward declarations* des autres objets de la
// structure de données sont mis *à l’intérieur* du namespace.
//class Net;
//class Node;

class Term{
public :
	enum Type { Internal =1 , External =2 };
	enum Direction { In =1 , Out =2 , Inout =3 , Tristate =4 , Transcv =5, Unknown =6 };
private :
	void * owner_ ;
	std :: string name_ ;
	Direction direction_ ;
	Type type_ ;
	Net * net_ ;
	Node node_ ;
public :
	Term ( Cell * , const std :: string &  , Direction );
	Term ( Instance * , const std :: string & , Direction );
	~ Term ();
	bool isInternal () const ;
	bool isExternal () const ;
	inline std :: string & getName () const ;
	inline Net * getNet () const ;
	Cell * getCell () const ;
	Cell * getOwnerCell () const ;
	Instance * getInstance () const ;
	inline Direction getDirection () const ;
	Point getPosition () const ;
	inline Type getType () const ;
	void setNet ( Net * );
	void setNet ( const std :: string & );
	void setPosition ( const Point & );
	void setPosition ( int x , int y );
	void setDirection ( Direction );
};
	
	inline std :: string & Term::getName () const {return name_;}
	inline Net * Term::getNet () const {return net_;}
	inline Direction Term::getDirection () const {return direction_;}
	inline Type Term::getType () const {return type_;}
}
#endif
