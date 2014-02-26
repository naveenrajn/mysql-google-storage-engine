#include "doclist_service.h"

using xmlpp::NodeSet;
using gdata::client::PostData;
using std::cout; //TODO: remove after testing
using std::endl; //TODO: remove after testing

namespace sp14 {
namespace adbms {
namespace gstorage {

	const string DocListService::docListServiceURL = "https://docs.google.com/feeds/documents/private/full";

	DocListService::DocListService() : Service(DOCLIST_SERVICE_NAME, APPLICATION_NAME, "2.0") {
		ClientLogin(LOGIN_EMAIL, LOGIN_PASSWORD);
	}

	/*Creates a new spreadsheet with the name sheetTitle, if not already available
	  Returns the worksheets feed URL*/
	void DocListService::createSpreadsheet(string sheetTitle) {
		if(!isSpreadsheetAlreadyAvailable(sheetTitle)) {
			xmlpp::Document document;
			xmlpp::Element* nodeRoot = document.create_root_node("entry", "http://www.w3.org/2005/Atom", "");
			nodeRoot->set_namespace_declaration("http://schemas.google.com/docs/2007", "docs");

			xmlpp::Element* category = nodeRoot->add_child("category");
			category->set_attribute("scheme", "http://schemas.google.com/g/2005#kind");
			category->set_attribute("term", "http://schemas.google.com/docs/2007#spreadsheet");

			xmlpp::Element* title = nodeRoot->add_child("title");
			title->set_child_text(sheetTitle);
			
			string requestDataString = document.write_to_string();

			PostData post_data;
			post_data.data = const_cast<char*>(requestDataString.c_str());
			std::vector<string> custom_headers;
			custom_headers.push_back("Content-Length: " + strlen(post_data.data));
			custom_headers.push_back("Content-Type: application/atom+xml");
			custom_headers.push_back("X-Upload-Content-Length: 0");

			atom_helper_.parse(HttpRequest("POST", "https://docs.google.com/feeds/documents/private/full", custom_headers, post_data));
			const xmlpp::Element *element = atom_helper_.getLinkByRel(atom_helper_.getRootNode(), worksheetsFeedLinkRel);
			cout << atom_helper_.getAttribute(element, "href");
		} else {
			cout << "Spreadsheet already available"; //TODO: handle this
		}
	}

	bool DocListService::isSpreadsheetAlreadyAvailable(string sheetTitle) {
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, docListServiceURL + "?title=" + sheetTitle + "&title-exact=true"));
		int resultsCount = atoi((atom_helper_.getSingleElementData(atom_helper_.getRootNode(), searchResultCount_xpath)).c_str());
		if(resultsCount>0) return true;
		return false;
	}

	string DocListService::searchSpreadsheetByTitle(string sheetTitle) {
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, docListServiceURL + "?title=" + sheetTitle + "&title-exact=true"));
		int resultsCount = atoi((atom_helper_.getSingleElementData(atom_helper_.getRootNode(), searchResultCount_xpath)).c_str());
		if(resultsCount>0) {
			NodeSet entries = atom_helper_.getEntries();
			if(entries.size()) {
				return atom_helper_.getAttribute(atom_helper_.getLinkByRel(entries[0], worksheetsFeedLinkRel), "href");
			} else {
				//This scenario should not happen as per Google Api documentation. Do we need to handle this?
				return NULL;
			}
		} else {
			cout<< "Document not found"; //TODO: remove this
			return NULL; //TODO: handle this
		}
	}

}}}