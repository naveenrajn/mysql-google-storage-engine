#ifndef GSTORAGE_GOOGLE_DRIVE_SERVICE_H_
#define GSTORAGE_GOOGLE_DRIVE_SERVICE_H_

#include <iostream>

#include "util/constants.h"
#include "util/service.h"

namespace sp14 {
namespace adbms {
namespace gstorage {

using std::string;
using gdata::client::Service;

class DocListService : public Service {
public:
	DocListService();
	~DocListService() {};

	void createSpreadsheet(string sheetTitle);
	string searchSpreadsheetByTitle(string sheetTitle);

	//see if static can be removed and made private
	static const string docListServiceURL; // = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";

	const string searchResultCount_xpath = "./openSearch:totalResults";
	const string worksheetsFeedLinkRel = "http://schemas.google.com/spreadsheets/2006#worksheetsfeed";

private:
	bool isSpreadsheetAlreadyAvailable(string sheetName);
};

}}} //namespace sp14::adbms::gstorage

#endif  // GSTORAGE_GOOGLE_DRIVE_SERVICE_H_