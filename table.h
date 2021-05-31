#ifndef TABLE_H
#define TABLE_H

#include <string>

#include "intermediate.h"

using namespace std;


class Table {
public:
	// TODO
	Table();

	// TODO
	Table(const Table &another);

	// TODO
	~Table();

	// TODO
	bool addAttribute(const string &attr, int index = -1, const string &default_value = "");

	// TODO
	bool addEntry(const string *entry, int index = -1);

	// TODO
	bool deleteAttribute(int index);

	// TODO
	bool deleteEntry(int index);

	// TODO
	bool append(const Table &another);

	// Given
	// Begin a query by making an "Intermediate" object from the table
	Intermediate query() const { return Intermediate {*this}; }

	// Not required, will not be graded
	// For the purpose of debugging, you can implement this function to print out the table
	void print() const;

	// Conversion from Table to Intermediate needs to access private members of Table objects
	// By declaring Intermediate as a friend class of Table, Intermediate can access the private members of Table
	friend class Intermediate;

	int getNumAttrs() const { return numAttrs; }

	int getNumEntries() const { return numEntries; }

	const string& getAttribute(int index) const { return attrs[index]; }

	const string& getEntry(int entryIndex, int attrIndex) const { return entries[entryIndex][attrIndex]; }

private:
	// 1D array of attributes
	// When there are no attributes, this must be set to nullptr
	string *attrs;

	// 2D array of entries
	// When there are no entries, this must be set to nullptr
	string **entries;

	// This must be set to number of attributes
	int numAttrs;

	// This must be set to number of entries
	int numEntries;
};

#endif
