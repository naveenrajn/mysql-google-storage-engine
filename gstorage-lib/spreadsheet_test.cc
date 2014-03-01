#include <iostream>
#include <map>
#include <string>
#include <libxml++/libxml++.h>
#include <curl/curl.h>

#include "gstorage/spreadsheet_metadata_service.h"

using sp14::adbms::gstorage::SpreadsheetMetadataService;
using std::string;
using std::map;
using xmlpp::NodeSet;
using std::cout;
using std::endl;

/*namespace abc {

	void getSpreadsheetsList(Service* serviceHelper) {
		ServiceHelper->atom_helper_.Parse(serviceHelper->HttpRequest("GET", "https://spreadsheets.google.com/feeds/spreadsheets/private/full"));
		NodeSet entries = serviceHelper->atom_helper_.Entries();

		for (unsigned int i = 0; i < entries.size(); ++i) {
			cout << "Title: " << serviceHelper->atom_helper_.Title(entries[i]);// << ". Worksheet Feed URL: " << serviceHelper->atom_helper_.FeedLinkHref(entries[i]) << endl;
		}
	}

	void readSpreadSheetContent(Service* serviceHelper) {
		serviceHelper->atom_helper_.Parse(serviceHelper->HttpRequest("GET", "https://spreadsheets.google.com/feeds/worksheets/tL0gIAg-7hRon3qcgUCWsIg/private/full"));
		NodeSet entries = serviceHelper->atom_helper_.Entries();

		for (unsigned int i = 0; i < entries.size(); ++i) {
			cout << serviceHelper->atom_helper_.Title(entries[i]) << endl;
		}
	}

	void printAllNodeEntryValues(Service* serviceHelper, string url) {
		serviceHelper->atom_helper_.Parse(serviceHelper->HttpRequest("GET", url));
		NodeSet entries = serviceHelper->atom_helper_.Entries();

		for (unsigned int i = 0; i < entries.size(); ++i) {
			//cout << "AlternateLinkHref: " << serviceHelper->atom_helper_.AlternateLinkHref(entries[i]) << endl;
			cout << "CategoryLabel: " << serviceHelper->atom_helper_.CategoryLabel(entries[i]) << endl;
			//cout << "AclRole: " << serviceHelper->atom_helper_.AclRole(entries[i]) << endl;
			//cout << "AclScope: " << serviceHelper->atom_helper_.AclScope(entries[i]) << endl;
			cout << "ContentSrc: " << serviceHelper->atom_helper_.ContentSrc(entries[i]) << endl;
			//cout << "EditLinkHref: " << serviceHelper->atom_helper_.EditLinkHref(entries[i]) << endl;
			//cout << "EditMediaLinkHref: " << serviceHelper->atom_helper_.EditMediaLinkHref(entries[i]) << endl;
			cout << "ETag: " << serviceHelper->atom_helper_.ETag(entries[i]) << endl;
			//cout << "FeedLinkHref: " << serviceHelper->atom_helper_.FeedLinkHref(entries[i]) << endl;
			cout << "Id: " << serviceHelper->atom_helper_.Id(entries[i]) << endl;
			cout << "Title: " << serviceHelper->atom_helper_.Title(entries[i]) << endl;
		}
	}

}*/

int main(int argc, char const *argv[])
{

	/*Service serviceHelper("wise", "SpreadsheetTest");

	serviceHelper.ClientLogin("sp14.adbms.storage@gmail.com", "PassworD");*/

	// register namespaces used by the DocList APIs
  	/*map<string, string> doclist_namespaces;
  	doclist_namespaces["g.Acl"] = "http://schemas.google.com/acl/2007";
	doclist_namespaces["gd"] = "http://schemas.google.com/g/2005";
	serviceHelper.atom_helper_.RegisterNamespaces(doclist_namespaces);*/
	
	//Full output of the spreadsheets list call
	//cout << serviceHelper.HttpRequest("GET", "https://spreadsheets.google.com/feeds/spreadsheets/private/full?fields=entry(title)") << endl;

	//Full output of the worksheets list call
	//cout << serviceHelper.HttpRequest("GET", "https://spreadsheets.google.com/feeds/worksheets/tL0gIAg-7hRon3qcgUCWsIg/private/full") << endl;

	//Full output of the feed list
	//cout << serviceHelper.HttpRequest("GET", "https://spreadsheets.google.com/feeds/list/tL0gIAg-7hRon3qcgUCWsIg/od6/private/full") << endl;

	//abc::getSpreadsheetsList(&serviceHelper);
	//abc::readSpreadSheetContent(&serviceHelper);

	//abc::printAllNodeEntryValues(&serviceHelper, "https://spreadsheets.google.com/feeds/spreadsheets/private/full");
	//abc::printAllNodeEntryValues(&serviceHelper, "https://spreadsheets.google.com/feeds/worksheets/tL0gIAg-7hRon3qcgUCWsIg/private/full");

	SpreadsheetMetadataService service;
	string worksheetsFeedURL = service.getWorksheetListFeedURL("spreadsheet_test");
	std::cout << "Am here------" << worksheetsFeedURL;
	std::vector<string> values;
	values.push_back("A1");
	values.push_back("A2");
	std::cout << endl; << "-------------Calling insert header---------------" << endl;
	std::cout << service.insertTableHeaders(worksheetsFeedURL, values);
//	cout << service.getWorksheetCellsFeedURL(worksheetsFeedURL);

	return 0;
}
