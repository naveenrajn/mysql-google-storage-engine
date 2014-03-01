CC = g++
CFLAGS = -c -Wall -O3
INCLUDES = `pkg-config libxml++-2.6 --cflags` `curl-config --cflags`
LDFLAGS = `curl-config --libs` `pkg-config libxml++-2.6 --cflags --libs`
REMOVECMD = rm -rf *.o
EXE = spreadsheet_test

all: $(EXE)

clean:
	$(REMOVECMD) $(EXE)

$(EXE): string_utils.o atom_helper.o service.o doclist_service.o spreadsheets_service.o simple_tester.o
	$(CC) -Wall -O3 *.o $(LDFLAGS) -o $(EXE)

spreadsheet_test.o: spreadsheet_test.cc lib/spreadsheets_service.h
	$(CC) $(CFLAGS) spreadsheet_test.cc $(INCLUDES)

spreadsheets_service.o: lib/spreadsheets_service.cc lib/spreadsheets_service.h lib/model/table_data.h
	$(CC) $(CFLAGS) lib/spreadsheets_service.cc $(INCLUDES)

doclist_service.o: lib/doclist_service.cc lib/doclist_service.h
	$(CC) $(CFLAGS) lib/doclist_service.cc $(INCLUDES)

service.o: lib/util/service.cc lib/util/service.h
	$(CC) $(CFLAGS) lib/util/service.cc $(INCLUDES)

atom_helper.o: lib/util/atom_helper.cc lib/util/atom_helper.h
	$(CC) $(CFLAGS) lib/util/atom_helper.cc $(INCLUDES)

string_utils.o: lib/util/string_utils.cc lib/util/string_utils.h
	$(CC) $(CFLAGS) lib/util/string_utils.cc

xmlpp_document_trials.o: xmlpp_document_trials.cc
	$(CC) $(CFLAGS) xmlpp_document_trials.cc $(INCLUDES)

simple_tester.o: simple_tester.cc
	$(CC) $(CFLAGS) simple_tester.cc $(INCLUDES)
