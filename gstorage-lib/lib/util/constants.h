#ifndef GSTORAGE_CONSTANTS_H_
#define GSTORAGE_CONSTANTS_H_

#include <iostream>

using std::string;

namespace sp14 {
namespace adbms {
namespace gstorage {

//Application Credentials - used in passing to Google
const string APPLICATION_NAME = "MySQL-GStorage";
const string LOGIN_EMAIL = "sp14.adbms.storage@gmail.com";
const string LOGIN_PASSWORD = "PassworD";

//Google constants
const string SPREADSHEET_SERVICE_NAME = "wise";
const string DOCLIST_SERVICE_NAME = "writely";

//HTTP Request Types
const string HTTP_REQUEST_TYPE_GET = "GET";

}}} //namespace sp14::adbms::gstorage

#endif  // GSTORAGE_CONSTANTS_H_