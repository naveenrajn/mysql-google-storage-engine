#ifndef GSTORAGE_ROW_DATA_STRUCTURE_H_
#define GSTORAGE_ROW_DATA_STRUCTURE_H_

#include <string>
#include <vector>

namespace sp14 {
namespace adbms {
namespace gstorage {
namespace model {

typedef struct RowData {
	int numberOfRows; //Do we need this? can we use rows.size() to get the number of rows?
	std::vector<std::string> fieldNames;
	std::vector<std::vector<std::string> > rows;

	RowData() {};
	~RowData() {};
} RowData;

}}}} //namespace sp14::adbms::gstorage::model

#endif  // GSTORAGE_ROW_DATA_STRUCTURE_H_