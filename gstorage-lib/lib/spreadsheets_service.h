#ifndef GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_
#define GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_

#include <iostream>

#include "util/constants.h"
#include "util/service.h"
#include "model/table_data.h"
#include "util/string_utils.h"

namespace sp14 {
namespace adbms {
namespace gstorage {

using std::string;
using xmlpp::NodeSet;
using gdata::client::Service;
using sp14::adbms::gstorage::model::TableData;
using gdata::util::StringUtils;

class SpreadsheetsService : public Service {
public:
	SpreadsheetsService();
	~SpreadsheetsService() {};

	string getWorksheetCellsFeedURL(string worksheetsFeedURL) throw();
	string getWorksheetListFeedURL(string worksheetsFeedURL) throw();
	string getPrimaryWorksheetFeedURL(string documentTitle) throw();
	void insertTableHeaders(string worksheetsFeedURL, const std::vector<string>& values) throw();
	string insertRow(string listFeedUrl, TableData *tableData) throw();
	void getWorksheetListFeed(string listFeedURL, TableData *tableData, bool isRowMetadataRequested) throw();
	void fetchFilteredSingleRow(string listFeedUrl, TableData *tableData) throw();
	bool deleteRow(string rowURL) throw();
	bool updateRow(TableData *tableData) throw();

	//see if static can be removed and made private
	static const string spreadsheetsServiceURL; // = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";
	
private:
	//string getPrimaryWorksheetFeedURL(string documentTitle);
};

}}} //namespace sp14::adbms::gstorage

#endif  // GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_
