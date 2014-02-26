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

spreadsheet_test.o: spreadsheet_test.cc gstorage/spreadsheets_service.h
	$(CC) $(CFLAGS) spreadsheet_test.cc $(INCLUDES)

spreadsheets_service.o: gstorage/spreadsheets_service.cc gstorage/spreadsheets_service.h
	$(CC) $(CFLAGS) gstorage/spreadsheets_service.cc $(INCLUDES)

doclist_service.o: gstorage/doclist_service.cc gstorage/doclist_service.h
	$(CC) $(CFLAGS) gstorage/doclist_service.cc $(INCLUDES)

service.o: gstorage/util/service.cc gstorage/util/service.h
	$(CC) $(CFLAGS) gstorage/util/service.cc $(INCLUDES)

atom_helper.o: gstorage/util/atom_helper.cc gstorage/util/atom_helper.h
	$(CC) $(CFLAGS) gstorage/util/atom_helper.cc $(INCLUDES)

string_utils.o: gstorage/util/string_utils.cc gstorage/util/string_utils.h
	$(CC) $(CFLAGS) gstorage/util/string_utils.cc

xmlpp_document_trials.o: xmlpp_document_trials.cc
	$(CC) $(CFLAGS) xmlpp_document_trials.cc $(INCLUDES)

simple_tester.o: simple_tester.cc
	$(CC) $(CFLAGS) simple_tester.cc $(INCLUDES)