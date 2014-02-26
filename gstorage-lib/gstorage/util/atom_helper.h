/**
 * Copyright 2008 Google Inc. All Rights Reserved.
 * Author: e.bidelman@google.com (Eric Bidelman)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 *
 * Dependencies:
 * libxml++: C++ wrapper for libxml2 (http://libxmlplusplus.sourceforge.net/)
 */

#ifndef GDATA_ATOM_HELPER_H_
#define GDATA_ATOM_HELPER_H_

#include <iostream>
#include <map>
#include <string>
#include <libxml++/libxml++.h>

namespace gdata {

using std::string;
using std::map;
using xmlpp::Node;
using xmlpp::NodeSet;
using xmlpp::Element;

class AtomHelper {
 public:
  AtomHelper();
  ~AtomHelper() {}

  void parse(const string& xml_str) { parser_.parse_memory(xml_str); }

  NodeSet Find(const Node *node, string xpath) const {
    return node->find(xpath, namespaces_);
  }

  const Node* getRootNode() const;
  NodeSet getEntries() const;

  string getSingleElementData(const Node *parent, string xpath) const;
  string getAttribute(const Element *from_element, string attr_name) const;
  const Element* getLinkByRel(const Node *entry, string rel) const;

 private:
  xmlpp::DomParser parser_;
  Node::PrefixNsMap namespaces_;
  void registerNamespaces(const map<string, string>& namespaces);
};

}  // namespace gdata

#endif  // GDATA_ATOM_HELPER_H_
