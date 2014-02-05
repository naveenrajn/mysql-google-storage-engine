#include <iostream> //TODO: remove after testing
#include <libxml++/libxml++.h>

#include "spreadsheet_metadata_service.h"

using xmlpp::NodeSet;
using std::cout; //TODO: remove after testing
using std::endl; //TODO: remove after testing

namespace sp14 {
namespace adbms {
namespace gstorage {

	const string SpreadsheetMetadataService::spreadsheetListServiceURL = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";

	SpreadsheetMetadataService::SpreadsheetMetadataService() : Service(SPREADSHEET_SERVICE_NAME, APPLICATION_NAME) {
		ClientLogin(LOGIN_EMAIL, LOGIN_PASSWORD);
	}

	//Retrieves and returns the feeds list URI for worksheet "Sheet1" in the spreadsheet with title "documentTitle"
	string SpreadsheetMetadataService::getWorksheetListFeedURL(string documentTitle) {
		string worksheetsFeedURL = getPrimaryWorksheetFeedURL(documentTitle); //TODO: handle if exception is thrown
		atom_helper_.Parse(HttpRequest(HTTP_REQUEST_TYPE_GET, worksheetsFeedURL));
		NodeSet entries = atom_helper_.Entries();
		
		//Do we need to do this? Or can we directly refer to entries[0]? What if it is not available?
		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.Title(entries[i]) == "Sheet1") {
				return atom_helper_.ContentSrc(entries[i]);
			}
		}

		//TODO: Throw exception or handle appropriately. Case: No "Sheet1" found in the given worksheet
		return NULL;
	}

	//Retrieves and returns the URI of the worksheets feed for the spreadsheet with title "documentTitle"
	string SpreadsheetMetadataService::getPrimaryWorksheetFeedURL(string documentTitle) {
		atom_helper_.Parse(HttpRequest(HTTP_REQUEST_TYPE_GET, spreadsheetListServiceURL));
		NodeSet entries = atom_helper_.Entries();

		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.Title(entries[i]) == documentTitle) {
				return atom_helper_.ContentSrc(entries[i]);
			}
		}
		
		//TODO: Throw exception or handle appropriately. Case: No matching document found for the given documen title
		return NULL;
	}

}}}