#ifndef GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_
#define GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_

#include <iostream>

#include "constants.h"
#include "gdata/client/service.h"

namespace sp14 {
namespace adbms {
namespace gstorage {

using std::string;
using gdata::client::Service;

class SpreadsheetMetadataService : public Service {
public:
	SpreadsheetMetadataService();
	~SpreadsheetMetadataService() {};

	string getWorksheetListFeedURL(string documentTitle);
	string getWorksheetCellFeedURL(string documentTitle);

	//see if static can be removed and made private
	static const string spreadsheetListServiceURL; // = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";
	
private:
	string getPrimaryWorksheetFeedURL(string documentTitle);
};

}}} //namespace sp14::adbms::gstorage

#endif  // GSTORAGE_SPREADSHEET_METADATA_SERVICE_H_