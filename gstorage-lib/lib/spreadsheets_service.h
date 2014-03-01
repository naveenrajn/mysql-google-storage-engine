#ifndef GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_
#define GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_

#include <iostream>

#include "util/constants.h"
#include "util/service.h"
#include "model/row_data.h"

namespace sp14 {
namespace adbms {
namespace gstorage {

using std::string;
using xmlpp::NodeSet;
using gdata::client::Service;
using sp14::adbms::gstorage::model::RowData;

class SpreadsheetsService : public Service {
public:
	SpreadsheetsService();
	~SpreadsheetsService() {};

	string getWorksheetCellsFeedURL(string worksheetsFeedURL);
	string getWorksheetListFeedURL(string worksheetsFeedURL);
	string getPrimaryWorksheetFeedURL(string documentTitle);
	string insertTableHeaders(string worksheetsFeedURL, const std::vector<string>& values);
	string insertRow(string worksheetsFeedURL, RowData *rowData);
	//string getWorksheetCellFeedURL(string documentTitle);
	void getWorksheetListFeed(string listFeedURL, RowData *rowData);

	//see if static can be removed and made private
	static const string spreadsheetsServiceURL; // = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";
	
private:
	//string getPrimaryWorksheetFeedURL(string documentTitle);
};

}}} //namespace sp14::adbms::gstorage

#endif  // GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_
