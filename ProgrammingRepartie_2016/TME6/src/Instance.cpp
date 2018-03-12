#include "Instance.h"
#include "Term.h"
#include "Cell.h"


namespace Netlist{
	using namespace std;
	Instance::Instance ( Cell* owner, Cell* model, const std::string& name)
	:	owner_			(owner),
		masterCell_		(model),
		name_			(name),
		terms_			(),
		position_		()
	{
		const vector<Term*>& terms = mastercell_->getTerm();
		for(vectro<Term*>::const_iterator iterm=terms_.begin();iterm != terms_.end();++iterm)
			new Term(this,*iterm);
		owner_->add(this);
	}

	Instance::~Instance 	()
        {
		for ( vector<Term*>::const_iterator iterm=terms_.begin(); iterm != terms_.end(); ++iterm){
			delete *iterm;
	}
			owner_->remove(this);
	}

      	const std::string& 	Instance::getName 	() const{
		return name_;
	}

	Cell* 			Instance::getMasterCell 	() const{
		return masterCell_;
	}
	Cell* 			Instance::getCell 	() const{
		return owner_;
	}
	const std::vector<Term*>& 
				Instance::getTerms 	(const string& name ) const {
		for ( vector<Term*>::const_iterator iterm=terms_.begin(); iterm != terms_.end(); ++iterm){		if ((*iterm)->getName() == name) return *iterm; }
			return NULL;
	}

	Term* 			Instance::getTerm 	( const std::string& name) const{
		for ( vector<Term*>::const_iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
      			if ((*iterm)->getName() == name)  return *iterm;
    		}
    		return NULL;
	}
	Point 			Instance::getPosition 	() const{
		return position_;
	}
	bool 			Instance::connect 	( const std::string& name, Net* net){
		Term* term = getTerm(name);
		if(term == NULL)
			return false;
		term->setNet(net);
		return true;
	}
	void 			Instance::add 		( Term* term)
	{
			terms_.push_back(term);
	}

	void 			Instance::remove 		( Term* term){
		for ( vector<Term*>::iterator iterm=terms_.begin() ; iterm != terms_.end() ; ++iterm ) {
			if((*iterms== term){
				terms_.erase(iterm);
				break;
			}
		}
	}

	void 			Instance::setPosition 	( const Point& pos){
		position_ = pos;	
		for (size_t i=0; i<term_.size(); ++i) {
	#ifdef DISABLED
		TermShape* shape = terms_[i]->getTermShape();
		if (shape)
		   terms_[i]->setPosition(shape->getPosition().translate(position))
		else
	#endif
		   terms_[i]->setPosition(position_);  
		}
        }
	void 			Instance::setPosition 	( int x, int y ){
		position_ = Point(x,y);
	}

	void	Instance::toXml ( ostream& stream)
	{
		stream << indent 
		       << "<instance name=\"" << name_
		       << "\"mastercell=\"" << nasterCell_->getName()
		       << "<\"x=\"" << position_.getX();
		       << "<\"y=\"" << position_.getY();
		       <<"/>\n";
}


