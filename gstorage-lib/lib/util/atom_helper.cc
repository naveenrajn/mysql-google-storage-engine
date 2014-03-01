#include "atom_helper.h"

namespace gdata {

using xmlpp::TextNode;
using xmlpp::Attribute;
using std::cout; //TODO: remove this

AtomHelper::AtomHelper() {
  map<string, string> namespaces;
  namespaces_["atom"] = "http://www.w3.org/2005/Atom";
  namespaces_["openSearch"] = "http://a9.com/-/spec/opensearch/1.1/";
  namespaces_["gsx"] = "http://schemas.google.com/spreadsheets/2006/extended";
  registerNamespaces(namespaces);
}

void AtomHelper::registerNamespaces(const map<string, string>& namespaces) {
  map<string, string>::const_iterator iter;
  for (iter = namespaces.begin(); iter != namespaces.end(); ++iter) {
    namespaces_[iter->first] = iter->second;
  }
}

///////////////////////////[START] Generic access methods//////////////////////////////////

/*Returns the root node of the last parsed document*/
const Node* AtomHelper::getRootNode() const {
  const Node *node = NULL;

  if (parser_) {
    node = parser_.get_document()->get_root_node();
  }
  return node; //TODO: handle this
}

/*Returns content of the first element with xpath found under the specified parent*/
string AtomHelper::getSingleElementData(const Node *parent, string xpath) const {
  if (!parser_) return ""; //TODO: handle this
  NodeSet children = Find(parent, xpath);
  if (children.size()) {
    const TextNode *child = dynamic_cast<const TextNode*>(*children[0]->get_children().begin());
    return child->get_content();
  } else {
    return ""; //TODO: handle this
  }
}

/*Returns the value of attribute with name attr_name in the element from_element*/
string AtomHelper::getAttribute(const Element *from_element, string attr_name) const {
  if (!parser_) return ""; //TODO: handle this

  const Element::AttributeList& attributes = from_element->get_attributes();

  Element::AttributeList::const_iterator iter;
  for (iter = attributes.begin(); iter != attributes.end(); ++iter) {
    const xmlpp::Attribute *attribute = *iter;
    if (attribute->get_name() == attr_name) {
      return attribute->get_value();
    }
  }
  return ""; //TODO: handle this
}
///////////////////////////[END] Generic access methods//////////////////////////////////


///////////////////////////[START] Specific access methods//////////////////////////////////

/*Returns the list of nodes with xpath ./atom:entry under the document root*/
NodeSet AtomHelper::getEntries() const {
  NodeSet entries;
  if (parser_) {
    entries = Find(parser_.get_document()->get_root_node(), "./atom:entry");
  }
  return entries; //TODO: handle this
}

const Element* AtomHelper::getLinkByRel(const Node *entry, string rel) const {
  if (!parser_) return NULL;

  NodeSet links = Find(entry, "./atom:link");
  for (unsigned int i = 0; i < links.size(); ++i) {
    const Element *nodeElement = dynamic_cast<const Element*>(links[i]);
    const Element::AttributeList& attributes =
        nodeElement->get_attributes();

    Element::AttributeList::const_iterator iter;
    for (iter = attributes.begin(); iter != attributes.end(); ++iter) {
      const xmlpp::Attribute *attribute = *iter;
      if (attribute->get_name() == "rel" && attribute->get_value() == rel) {
        return nodeElement;
      }
    }
  }
  return NULL;
}

} // namespace gdata
