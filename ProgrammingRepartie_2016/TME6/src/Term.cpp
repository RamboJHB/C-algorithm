#include "Term.h"
#include "Node.h"
#include "Point.h"
#include "Cell.h"
#include "Instance.h"

namespace Netlist{
	using namespace std;

	Term::Term ( Cell* owner, const std :: string & name , Direction dir)
	:	owner_ 		(owner),
		name_ 		(name),
		direction_ 	(dir),
		type_ 		(),
		net_ 		(NULL),
		node_ 		(Node::Node(this))
	{}


	Term::Term ( Instance * owner, const Term* modelTerm)
	:	owner_ 		(owner),
		name_ 		(modelTerm->getName()),
		direction_ 	(modelTerm->getDirection()),
		type_ 		(Internal),
		net_ 		(),
		node_ 		(this)
	{owner->add(this);}


	Term::~ Term (){}
	bool Term::isInternal () const { return type_==1?true:false; }
	bool Term::isExternal () const { return type_==2?true:false; }
	Cell * Term::getOwnerCell () const {
		return isInternal()?owner_->getCell():owner_;
	}
	Cell * Term::getCell () const {	
		return isExternal()?owner_:NULL;
	}
	Instance * Term::getInstance () const{
		return isInternal()?owner_:NULL;
	}
	Point Term::getPosition () const { return node_.getPosition(); }
	void Term::setNet ( Net * inet) {
		 
		node_.setId(inet->getId()); 
	}
	void Term::setNet ( const std :: string & name) {
		vector<Net*>::iterator inet = getOwnerCell()->getNets().begin();
		for(;inet < getOwnerCell()->getNets().end(); inet ++){
			if((*inet)->getName() == name){
				node_.setId((*inet)->getId());
				break;
			}
		}
	}
	void Term::setPosition ( const Point & point){
		node_.setPosition(point);
	}
	void Term::setPosition ( int x , int y ){
		node_.setPosition(x,y);
	}
	void Term::setDirection ( Direction d ){
		direction_ = d;
	}
}



