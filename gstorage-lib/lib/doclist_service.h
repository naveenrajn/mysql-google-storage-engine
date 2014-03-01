#ifndef GSTORAGE_GOOGLE_DRIVE_SERVICE_H_
#define GSTORAGE_GOOGLE_DRIVE_SERVICE_H_

#include <iostream>

#include "util/constants.h"
#include "util/service.h"
#include "spreadsheets_service.h"

namespace sp14 {
namespace adbms {
namespace gstorage {

using std::string;
using gdata::client::Service;
using sp14::adbms::gstorage::SpreadsheetsService;

class DocListService : public Service {
public:
	DocListService();
	DocListService(SpreadsheetsService* spreadsheetsService);
	~DocListService() {};

	void createSpreadsheet(string sheetTitle, const std::vector<string>& fieldNames);
	string searchSpreadsheetByTitle(string sheetTitle);

	//see if static can be removed and made private
	static const string docListServiceURL; // = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";
	static const string searchResultCount_xpath;
	static const string worksheetsFeedLinkRel;

private:
	SpreadsheetsService *spreadsheetsService = NULL;
	bool isSpreadsheetAlreadyAvailable(string sheetName);
};

}}} //namespace sp14::adbms::gstorage

#endif  // GSTORAGE_GOOGLE_DRIVE_SERVICE_H_
