#include <iostream> //TODO: remove after testing
#include <string> //TODO: remove after testing
#include <stdlib.h> //TODO: remove after testing
#include <stdio.h> //TODO: remove after testing
#include <libxml++/libxml++.h>

#include "spreadsheets_service.h"

using xmlpp::NodeSet;
using gdata::client::PostData;
using std::cout; //TODO: remove after testing
using std::endl;  //TODO: remove after testing

namespace sp14 {
namespace adbms {
namespace gstorage {

	const string SpreadsheetsService::spreadsheetsServiceURL = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";

	SpreadsheetsService::SpreadsheetsService() : Service(SPREADSHEET_SERVICE_NAME, APPLICATION_NAME, "3.0") {
		ClientLogin(LOGIN_EMAIL, LOGIN_PASSWORD);
	}

	//Retrieves and returns the cells feed URI for worksheet "Sheet 1" in the spreadsheet with title "documentTitle"
	string SpreadsheetsService::getWorksheetCellsFeedURL(string worksheetsFeedURL) throw() {
		//string worksheetsFeedURL = getPrimaryWorksheetFeedURL(documentTitle); //TODO: handle if exception is thrown
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, worksheetsFeedURL));
		NodeSet entries = atom_helper_.getEntries();
		//Do we need to do this? Or can we directly refer to entries[0]? What if it is not available?
		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.getSingleElementData(entries[i], "./atom:title").compare("Sheet 1")==0) {
				return atom_helper_.getAttribute(atom_helper_.getLinkByRel(entries[i], "http://schemas.google.com/spreadsheets/2006#cellsfeed"), "href");
			} else {
				//Do we need to handle this? we will anyways have only one sheet
			}
		}

		//TODO: Throw exception or handle appropriately. Case: No "Sheet 1" found in the given worksheet
		return "";
	}

	//Retrieves and returns the list feed URI for worksheet "Sheet 1" in the spreadsheet with title "documentTitle"
	string SpreadsheetsService::getWorksheetListFeedURL(string worksheetsFeedURL) throw() {
		//string worksheetsFeedURL = getPrimaryWorksheetFeedURL(documentTitle); //TODO: handle if exception is thrown
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, worksheetsFeedURL));
		NodeSet entries = atom_helper_.getEntries();
		//Do we need to do this? Or can we directly refer to entries[0]? What if it is not available?
		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.getSingleElementData(entries[i], "./atom:title").compare("Sheet 1")==0) {
				NodeSet contents = atom_helper_.Find(entries[i], "./atom:content");
				if(contents.size()) return atom_helper_.getAttribute(dynamic_cast<const xmlpp::Element*>(contents[0]), "src");
				else {
					//Do we need to handle this condition?
				}
			} else {
				//Do we need to handle this? we will anyways have only one sheet
			}
		}

		//TODO: Throw exception or handle appropriately. Case: No "Sheet 1" found in the given worksheet
		return "";
	}

	//Retrieves and returns the URI of the worksheets feed for the spreadsheet with title "documentTitle"
	string SpreadsheetsService::getPrimaryWorksheetFeedURL(string documentTitle) throw() {
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, spreadsheetsServiceURL));
		NodeSet entries = atom_helper_.getEntries();

		for (unsigned int i = 0; i < entries.size(); ++i) {
			if(atom_helper_.getSingleElementData(entries[i], "./atom:title").compare(documentTitle)==0) {
				NodeSet contents = atom_helper_.Find(entries[i], "./atom:content");
				if(contents.size()) return atom_helper_.getAttribute(dynamic_cast<const xmlpp::Element*>(contents[0]), "src");
				else {
					//Do we need to handle this condition?
				}
			}
		}
		
		//TODO: Throw exception or handle appropriately. Case: No matching document found for the given documen title
		return NULL;
	}

	//Inserts headers for a given worksheet
	void SpreadsheetsService::insertTableHeaders(string worksheetsFeedURL, const std::vector<string>& fieldNames) throw() {
		string cellBaseUrl = getWorksheetCellsFeedURL(worksheetsFeedURL);
		string postUrl = cellBaseUrl + "/batch";
		xmlpp::Document document;
		xmlpp::Element* nodeRoot = document.create_root_node("feed", "http://www.w3.org/2005/Atom", "");
		nodeRoot->set_namespace_declaration("http://schemas.google.com/gdata/batch", "batch");
		nodeRoot->set_namespace_declaration("http://schemas.google.com/spreadsheets/2006", "gs");
		xmlpp::Element* id = nodeRoot->add_child("id");
		id -> set_child_text(cellBaseUrl);
		for (unsigned int i = 0; i < fieldNames.size(); ++i) {
			std::stringstream ss;
			ss << i+1;
			std::string temp = ss.str();
			xmlpp::Element* entry1 = nodeRoot->add_child("entry");
			xmlpp::Element* batchId1 = entry1->add_child("batch:id");
			batchId1 -> set_child_text("A"+ temp);
			xmlpp::Element* batchOperation1 = entry1->add_child("batch:operation");
			batchOperation1 ->set_attribute("type", "update");
			xmlpp::Element* id1 = entry1->add_child("id");
			id1 -> set_child_text(cellBaseUrl+"/R1C"+temp);
			xmlpp::Element* link1 = entry1->add_child("link");
			link1 ->set_attribute("rel", "edit");
			link1 ->set_attribute("type", "application/atom+xml");
			link1 ->set_attribute("href", cellBaseUrl+"/R1C" + temp + "/version");
			xmlpp::Element* cell1 = entry1->add_child("gs:cell");
			cell1 ->set_attribute("row", "1");
			cell1 ->set_attribute("col", temp);
			cell1 ->set_attribute("inputValue", fieldNames[i]);
		}
		string requestDataString = document.write_to_string();
		PostData post_data;
		post_data.data = const_cast<char*>(requestDataString.c_str());
		std::vector<string> custom_headers;
		custom_headers.clear();
		custom_headers.push_back("Content-Type: application/atom+xml");
		custom_headers.push_back("X-Upload-Content-Length: 0");
		custom_headers.push_back("If-Match: *");		
		cout << "-------------Built request----------";
		cout << post_data.data;
		HttpRequest("POST", postUrl, custom_headers, post_data);
	}

	/*Retrieves all rows from the given spreadsheet list feed URL and adds it to the passed tableData object*/
	//TODO: Handle exceptions(like trying reading an unavailable field, etc., etc.)
	void SpreadsheetsService::getWorksheetListFeed(string listFeedURL, TableData *tableData, bool isRowMetadataRequested) throw() {
		atom_helper_.parse(HttpRequest(HTTP_REQUEST_TYPE_GET, listFeedURL));

		NodeSet entries = atom_helper_.getEntries();
		for (unsigned int i = 0; i < entries.size(); ++i) {
			std::vector<std::string> currentRow;
			if(isRowMetadataRequested) {
				tableData->rowIDs.push_back(atom_helper_.getSingleElementData(entries[i], "./atom:id"));
				tableData->rowEditURLs.push_back(atom_helper_.getAttribute(atom_helper_.getLinkByRel(entries[i], "edit"), "href"));
			}
			for (std::vector<std::string>::iterator fieldName = tableData->fieldNames.begin(); fieldName != tableData->fieldNames.end(); ++fieldName) {
				currentRow.push_back(atom_helper_.getSingleElementData(entries[i], "./gsx:" + *fieldName));
			}
			tableData->rows.push_back(currentRow);
		}
	}

	//Inserts a row at the end of a given worksheet
	string SpreadsheetsService::insertRow(string listFeedUrl, TableData *tableData) throw() {
		cout << listFeedUrl;
		xmlpp::Document document;
		xmlpp::Element* nodeRoot = document.create_root_node("entry", "http://www.w3.org/2005/Atom", "");
		nodeRoot->set_namespace_declaration("http://schemas.google.com/spreadsheets/2006/extended", "gsx");
		std::vector<std::string> row = tableData-> rows.at(0);
		int i = 0;
		for (std::vector<std::string>::iterator colName = tableData->fieldNames.begin(); colName != tableData->fieldNames.end(); ++colName) {
			xmlpp::Element* id = nodeRoot->add_child("gsx:" + *colName);
			id -> set_child_text(row[i]);
			i++;
		}
		string requestDataString = document.write_to_string();
		PostData post_data;
		post_data.data = const_cast<char*>(requestDataString.c_str());
		std::vector<string> custom_headers;
		custom_headers.clear();
		custom_headers.push_back("Content-Type: application/atom+xml");
		custom_headers.push_back("X-Upload-Content-Length: 0");	
		cout << "-------------Built request----------";
		cout << post_data.data;
		return HttpRequest("POST", listFeedUrl, custom_headers, post_data);
	}

	/*Retrieves rows with the data matching the provided tableData construct*/
	void SpreadsheetsService::fetchFilteredSingleRow(string listFeedUrl, TableData *tableData) throw() {
		if(tableData->rows.size()<=0) {
			tableData->rows.clear();
		}
		StringUtils stringUtils;

		std::vector<std::string> row = tableData-> rows.at(0);
		listFeedUrl += "?sq=";
		int i = 0;
		bool isFirst = true;
		for (std::vector<std::string>::iterator colName = tableData->fieldNames.begin(); colName != tableData->fieldNames.end(); ++colName) {
			if(strlen(row[i].c_str())>0) {
				if(!isFirst) listFeedUrl+="%20and%20";
				else isFirst = false;
				listFeedUrl+=*colName;
				listFeedUrl+="=\"";
				listFeedUrl+=stringUtils.find_and_replace(row[i], " ", "%20");
				listFeedUrl+="\"";
			}
			i++;
		}
		tableData->rows.clear();
		getWorksheetListFeed(listFeedUrl, tableData, true);
	}

	bool SpreadsheetsService::deleteRow(string rowURL) throw() {
		cout << rowURL;
		std::vector<string> custom_headers;
		custom_headers.clear();
		custom_headers.push_back("If-Match: *");
		HttpRequest("DELETE", rowURL, custom_headers);//TODO handle failure response from API
		return true;
	}

	bool SpreadsheetsService::updateRow(TableData *tableData) throw() {
		cout << "Inside updateRow" <<endl;
		if(tableData->rows.size()>0 && tableData->rowIDs.size()>0 && tableData->rowEditURLs.size()>0) {
			cout << "Inside updateRow if" <<endl;
			xmlpp::Document document;
			xmlpp::Element* nodeRoot = document.create_root_node("entry", "http://www.w3.org/2005/Atom", "");
			nodeRoot->set_namespace_declaration("http://schemas.google.com/spreadsheets/2006/extended", "gsx");
			xmlpp::Element* id = nodeRoot->add_child("id");
			id -> set_child_text(tableData->rowIDs.at(0));
			std::vector<std::string> row = tableData-> rows.at(0);
			int i = 0;
			for (std::vector<std::string>::iterator colName = tableData->fieldNames.begin(); colName != tableData->fieldNames.end(); ++colName) {
				xmlpp::Element* id = nodeRoot->add_child("gsx:" + *colName);
				id -> set_child_text(row[i]);
				i++;
			}
			cout << "Inside updateRow: after document preparation" <<endl;
			string requestDataString = document.write_to_string();
			PostData post_data;
			post_data.data = const_cast<char*>(requestDataString.c_str());
			cout << "Inside updateRow:after post data preparation" <<endl;
			std::vector<string> custom_headers;
			custom_headers.clear();
			custom_headers.push_back("Content-Type: application/atom+xml");
			custom_headers.push_back("X-Upload-Content-Length: 0");
			custom_headers.push_back("If-Match: *");
			cout << "Inside updateRow:after headers" <<endl;
			cout << "Post Data: " << post_data.data;
			cout << "Inside updateRow: before calling" <<endl;
			HttpRequest("PUT", tableData->rowEditURLs.at(0), custom_headers, post_data); //TODO handle faiure response from API
			cout << "Inside updateRow: after calling" << endl;
			return true;
		} else {
			return true; //Do we need to handle this?
		}
	}

}}}

