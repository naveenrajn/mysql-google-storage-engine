#ifndef GSTORAGE_ROW_DATA_STRUCTURE_H_
#define GSTORAGE_ROW_DATA_STRUCTURE_H_

#include <string>
#include <vector>

namespace sp14 {
namespace adbms {
namespace gstorage {
namespace model {

typedef struct TableData {
	std::string worksheetListFeedURL;

	std::vector<std::string> fieldNames;
	std::vector<std::string> rowIDs;
	std::vector<std::string> rowEditURLs;
	std::vector<std::vector<std::string> > rows;

	TableData() {};
	~TableData() {};
} TableData;

}}}} //namespace sp14::adbms::gstorage::model

#endif  // GSTORAGE_ROW_DATA_STRUCTURE_H_