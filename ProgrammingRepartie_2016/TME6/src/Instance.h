#ifndef NETLIST_INSTANCE_H
#define NETLIST_INSTANCE_H

#include <string>
#include <vector>
#include "Term.h"
#include "Node.h"
#include "Point.h"
#include "Cell.h"

namespace Netlist {

  class Net;
  class Term;
  class Symbol;


  class Instance {
    public:
      static       std::vector<Cell*>&     getAllCells       ();
      static       Cell*                   find              ( const std::string& );
    public:                                                  
                                        Instance 	( Cell* owner, Cell* model, const std::string& );
					~Instance 	();
      		const std::string& 	getName 	() const;
		Cell* 			getMasterCell 	() const;
		Cell* 			getCell 	() const;
		const std::vector<Term*>& 
					getTerms 	() const;
		Term* 			getTerm 	( const std::string& ) const;
		Point 			getPosition 	() const;
		bool 			connect 	( const std::string& name, Net* );
		void 			add 		( Term* );
		void 			remove 		( Term* );
		void 			setPosition 	( const Point& );
		void 			setPosition 	( int x, int y );
    private:
      static  	Cell* 			owner_;
		Cell*			masterCell_;
		std::string 		name_;
		std::vector<Term*> 	terms_;
		Point 			position_;
  };

	


}  // Netlist namespace.

#endif
