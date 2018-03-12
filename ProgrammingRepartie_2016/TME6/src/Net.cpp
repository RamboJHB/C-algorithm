#include "Net.h"

namespace Netlist{
	using namespace std;

	Net::Net ( Cell * owner, const std :: string & name,Term::Type type)
		:	owner_ 		(owner),
			name_ 		(name),
			type_ 		(type),
			id_		(owner->newnetId()),
			nodes_		()
	{	owner_->add(this);}
			Net::~ Net 	(){}
	Cell *		Net::getCell () const {
		return owner_;
	}
	const std::string& 
			Net::getName () const {
		return name_;
	}
	unsigned int 	Net::getId () const {
		return id_;
	}
	Term::Type 	Net::getType () const {
		return type_;
	}
	const std::vector<Node*>&	
			Net::getNodes () const {
		if(id < nodes_.size()) return nodes_[id];
		return NULL;
	}
	size_t 		Net::getFreeNodeId () const {
		for(size_t i = 0;i < nodes_.size(); ++i){
			if(nodes_[i] == NULL)
				return i;
		}
		return nodes_.size();
	}
	void 		Net::add ( Node * node){
		if(not node) return;
		size_t id = node->getId();
		if(id == Node::noid){
			id = getFreeNodeId();
			node->setId(id);
		}
		if(id < nodes_.size()){
			if(nodes_[id] != NULL){
				cerr<<"ERROR"<<endl;
				node->setId(Node::noid);
				return;
			}
			nodes_[id] = node;
		}else{
			for(size_t i=node_.size();i<id;++i)
				nodes_.push_back(NULL);
			nodes_.push_back(node);
		}
	}
	bool 		Net::remove ( Node * node){
		if (node){
			size_t id = node->getId();
			if ((id <nodes_.size()) and (nodes_[id] == node) {
				nodes_[id] = NULL;
				return true;
				}
			}
			return false;
		}

	void Net::toXml( ostream& stream )const 
{
	stream  << indent++
		<< "<net name=\"" << name_ << "\""
		<< "type=\"" << Term::toString(type_) << "\"/>\n";

	for (size_t i=0 ; i<nodes_.size() ; ++i){
		if (nodes_.[i]) nodes_[i]->toXml (stream);
		}
	stream << --indent <<"</net>\n";
	}
		
}
