#include <iostream>
#include <map>
#include <string>
#include <libxml++/libxml++.h>
#include <curl/curl.h>

#include "gstorage/gdata/client/service.h"
#include "gstorage/gdata/util/string_utils.h"

using gdata::client::Service;
using gdata::client::PostData;
using gdata::util::StringUtils;
using std::string;

int main(int argc, char const *argv[]) {

	xmlpp::Document document;
	xmlpp::Element* nodeRoot = document.create_root_node("entry", "http://www.w3.org/2005/Atom", "");
	nodeRoot->set_namespace_declaration("http://schemas.google.com/docs/2007", "docs");

	xmlpp::Element* category = nodeRoot->add_child("category");
	category->set_attribute("scheme", "http://schemas.google.com/g/2005#kind");
	category->set_attribute("term", "http://schemas.google.com/docs/2007#spreadsheet");

	xmlpp::Element* title = nodeRoot->add_child("title");
	title->set_child_text("test_sheet_code1");

	//std::cout << document.write_to_string();
	string requestDataString = document.write_to_string();
	//requestDataString = StringUtils::find_and_replace(requestDataString, "\"", "%22");

	Service service ("writely", "test_app");
	service.ClientLogin("sp14.adbms.storage@gmail.com", "PassworD");

	PostData post_data;
	post_data.data = const_cast<char*>(requestDataString.c_str());
	//post_data.data = const_cast<char*>(document.write_to_string().c_str());
	//post_data.filename = NULL;
	std::cout<<post_data.data;
	std::cout<<strlen(post_data.data);
	std::vector<string> custom_headers;
	custom_headers.push_back("Content-Length: 283");
	custom_headers.push_back("Content-Type: application/atom+xml");
	custom_headers.push_back("X-Upload-Content-Length: 0");

	//string response = service.HttpRequest("POST", "https://docs.google.com/feeds/upload/create-session/default/private/full", custom_headers, post_data);
	string response = service.HttpRequest("POST", "https://docs.google.com/feeds/documents/private/full", custom_headers, post_data);
	//string response = service.HttpRequest("GET", "https://docs.google.com/feeds/default/private/full");
	/*https://www.googleapis.com/upload/drive/v2/files */
	std::cout << response;

	return 0;
}