CC = g++
CFLAGS = -c -Wall -O3
INCLUDES = `pkg-config libxml++-2.6 --cflags` `curl-config --cflags`
LDFLAGS = `curl-config --libs` `pkg-config libxml++-2.6 --cflags --libs`
REMOVECMD = rm -rf *.o
EXE = spreadsheet_test

all: $(EXE)

clean:
	$(REMOVECMD) $(EXE)

$(EXE): string_utils.o atom_helper.o service.o spreadsheet_metadata_service.o spreadsheet_test.o
	$(CC) -Wall -O3 *.o $(LDFLAGS) -o $(EXE)

spreadsheet_test.o: spreadsheet_test.cc gstorage/spreadsheet_metadata_service.h
	$(CC) $(CFLAGS) spreadsheet_test.cc $(INCLUDES)

spreadsheet_metadata_service.o: gstorage/spreadsheet_metadata_service.cc gstorage/spreadsheet_metadata_service.h
	$(CC) $(CFLAGS) gstorage/spreadsheet_metadata_service.cc $(INCLUDES)

service.o: gstorage/gdata/client/service.cc gstorage/gdata/client/service.h
	$(CC) $(CFLAGS) gstorage/gdata/client/service.cc $(INCLUDES)

atom_helper.o: gstorage/gdata/atom_helper.cc gstorage/gdata/atom_helper.h
	$(CC) $(CFLAGS) gstorage/gdata/atom_helper.cc $(INCLUDES)

string_utils.o: gstorage/gdata/util/string_utils.cc gstorage/gdata/util/string_utils.h
	$(CC) $(CFLAGS) gstorage/gdata/util/string_utils.cc
