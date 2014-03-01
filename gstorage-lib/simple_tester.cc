#include <iostream>
#include <map>
#include <string>
#include <libxml++/libxml++.h>
#include <curl/curl.h>

#include "lib/doclist_service.h"
#include "lib/spreadsheets_service.h"
#include "lib/model/table_data.h"

using sp14::adbms::gstorage::DocListService;
using sp14::adbms::gstorage::SpreadsheetsService;
using sp14::adbms::gstorage::model::TableData;
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
	//cout << endl << sheetsService.getWorksheetListFeedURL(worksheetsFeedURL);
	/*std::vector<string> values;
	values.push_back("A1");
	values.push_back("A2");
	std::cout << endl << "-------------Calling insert header---------------" << endl;
	std::cout << sheetsService.insertTableHeaders(worksheetsFeedURL, values);
	cout << endl << sheetsService.getWorksheetCellsFeedURL(worksheetsFeedURL);

	SpreadsheetsService sheetsService;*/
	TableData *tableData = new TableData();
	tableData->fieldNames.clear();
	tableData->rows.clear();
	std::vector<string> row;
	row.push_back("val1");
	row.push_back("val2");
	tableData->fieldNames.push_back("col1");
	tableData->fieldNames.push_back("col2");
	tableData->rows.push_back(row);
	//tableData->fieldNames.push_back("col3");
	//tableData->fieldNames.push_back("col4");

	//sheetsService.getWorksheetListFeed("https://spreadsheets.google.com/feeds/list/tCa_wbrrXoJSjpZmRnxKNng/od6/private/full",
		//tableData);
//	cout << endl << "No of rows: " << tableData->numberOfRows << endl;

	/*for (std::vector<std::vector<string> >::iterator i = tableData->rows.begin(); i != tableData->rows.end(); ++i) {
		std::vector<string> currentRow = *i;
		for (std::vector<string>::iterator j = currentRow.begin(); j != currentRow.end(); ++j) {
			cout << *j << " ";
		}
		cout << endl;
	}

	delete tableData;*/
	sheetsService.insertRow(worksheetsFeedURL, tableData);
	return 0;
}
