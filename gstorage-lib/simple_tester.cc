#include <iostream>
#include <map>
#include <string>
#include <libxml++/libxml++.h>
#include <curl/curl.h>

#include "lib/doclist_service.h"
#include "lib/spreadsheets_service.h"

using sp14::adbms::gstorage::DocListService;
using sp14::adbms::gstorage::SpreadsheetsService;
using std::string;
using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {

	//DocListService driveService;
	//driveService.createSpreadsheet("simple_tester_upload_4");
	//cout << endl << driveService.searchSpreadsheetByTitle("simple_tester_upload_4") << endl;

	//SpreadsheetsService sheetsService;
	//cout <<endl<< sheetsService.getWorksheetListFeedURL("https://spreadsheets.google.com/feeds/worksheets/0Ao_7Rhfs8LHbdGdsVFhFLWxlTVY1Q21Od25CeTdYVnc/private/full");

	SpreadsheetsService sheetsService;
	string worksheetsFeedURL = sheetsService.getPrimaryWorksheetFeedURL("./test/test_table_3");
	cout << endl << worksheetsFeedURL;
//	cout << endl << sheetsService.getWorksheetCellsFeedURL(worksheetsFeedURL);
	std::vector<string> values;
	values.push_back("A1");
	values.push_back("A2");
	std::cout << endl << "-------------Calling insert header---------------" << endl;
	std::cout << sheetsService.insertTableHeaders(worksheetsFeedURL, values);
	return 0;
}
