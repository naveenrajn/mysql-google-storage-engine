#include <iostream> //TODO: remove after testing
#include <libxml++/libxml++.h>

#include "spreadsheets_service.h"

using xmlpp::NodeSet;
using std::cout; //TODO: remove after testing
using std::endl; //TODO: remove after testing

namespace sp14 {
namespace adbms {
namespace gstorage {

	const string SpreadsheetsService::spreadsheetListServiceURL = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";

	SpreadsheetsService::SpreadsheetsService() : Service(SPREADSHEET_SERVICE_NAME, APPLICATION_NAME, "3.0") {
		ClientLogin(LOGIN_EMAIL, LOGIN_PASSWORD);
	}

	//Retrieves and returns the cells feed URI for worksheet "Sheet 1" in the spreadsheet with title "documentTitle"
	string SpreadsheetsService::getWorksheetCellsFeedURL(string worksheetsFeedURL) {
		//string worksheetsFeedURL = getPrimaryWorksheetFeedURL(documentTitle); //TODO: handle if exception is thrown
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, worksheetsFeedURL));
		NodeSet entries = atom_helper_.getEntries();
		//Do we need to do this? Or can we directly refer to entries[0]? What if it is not available?
		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.getSingleElementData(entries[i], "./atom:title").compare("Sheet 1")==0) {
				return atom_helper_.getAttribute(atom_helper_.getLinkByRel(entries[i], "http://schemas.google.com/spreadsheets/2006#cellsfeed"), "href");
			} else {
				//Do we need to handle this? we will anyways have only one sheet
			}
		}

		//TODO: Throw exception or handle appropriately. Case: No "Sheet 1" found in the given worksheet
		return "";
	}

	//Retrieves and returns the list feed URI for worksheet "Sheet 1" in the spreadsheet with title "documentTitle"
	string SpreadsheetsService::getWorksheetListFeedURL(string worksheetsFeedURL) {
		//string worksheetsFeedURL = getPrimaryWorksheetFeedURL(documentTitle); //TODO: handle if exception is thrown
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, worksheetsFeedURL));
		NodeSet entries = atom_helper_.getEntries();
		//Do we need to do this? Or can we directly refer to entries[0]? What if it is not available?
		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.getSingleElementData(entries[i], "./atom:title").compare("Sheet 1")==0) {
				NodeSet contents = atom_helper_.Find(entries[i], "./atom:content");
				if(contents.size()) return atom_helper_.getAttribute(dynamic_cast<const xmlpp::Element*>(contents[0]), "src");
				else {
					//Do we need to handle this condition?
				}
			} else {
				//Do we need to handle this? we will anyways have only one sheet
			}
		}

		//TODO: Throw exception or handle appropriately. Case: No "Sheet 1" found in the given worksheet
		return "";
	}

	//Retrieves and returns the URI of the worksheets feed for the spreadsheet with title "documentTitle"
	/*string SpreadsheetsService::getPrimaryWorksheetFeedURL(string documentTitle) {
		atom_helper_.Parse(HttpRequest(HTTP_REQUEST_TYPE_GET, spreadsheetListServiceURL));
		NodeSet entries = atom_helper_.Entries();

		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.Title(entries[i]) == documentTitle) {
				return atom_helper_.ContentSrc(entries[i]);
			}
		}
		
		//TODO: Throw exception or handle appropriately. Case: No matching document found for the given documen title
		return NULL;
	}*/

}}}