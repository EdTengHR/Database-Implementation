#include <iostream>
#include "table.h"

using namespace std;

string **
_alloc_entries(int numAttrs, int numEntries)
{
	string **entries = new string*[numEntries];
	for (int i = 0; i < numEntries; ++i)
		entries[i] = new string[numAttrs];

	return entries;
}

void
_dealloc_entries(string **entries, int numEntries)
{
	for (int i = 0; i < numEntries; ++i)
		delete [] entries[i];
	delete [] entries;
}

void
_copy_entry(string *dst, const string *src, int numAttrs)
{
	for (int i = 0; i < numAttrs; ++i)
		dst[i] = src[i];
}

Table::Table():
attrs(nullptr), entries(nullptr), numAttrs(0), numEntries(0)
{

}

Table::Table(const Table &another):
attrs(nullptr), entries(nullptr), numAttrs(another.numAttrs), numEntries(another.numEntries)
{
	if (numAttrs > 0)
	{
		attrs = new string[numAttrs];
		for (int i = 0; i < numAttrs; ++i)
			attrs[i] = another.attrs[i];

		if (numEntries > 0) {
			entries = _alloc_entries(numAttrs, numEntries);
			for (int i = 0; i < numEntries; ++i)
				_copy_entry(entries[i], another.entries[i], numAttrs);
		}
	}
}

Table::~Table()
{
	delete [] attrs;
	_dealloc_entries(entries, numEntries);
}

bool
Table::addAttribute(const string &attr, int index, const string &default_value)
{
	if (index < -1 || index > numAttrs)
		return false;

	if (index == -1)
		index = numAttrs;

	if (numAttrs == 0) {
		attrs = new string[1];
		attrs[0] = attr;
		numAttrs = 1;
	}
	else {
		string *old = attrs;

		attrs = new string[numAttrs + 1];

		for (int i = 0; i < numAttrs; ++i) {
			if (i < index)
				attrs[i] = old[i];
			else
				attrs[i+1] = old[i];
		}
		attrs[index] = attr;

		delete [] old;

		if (numEntries > 0) {
			string **old = entries;

			entries = _alloc_entries(numAttrs + 1, numEntries);

			for (int i = 0; i < numEntries; ++i) {
				for (int j = 0; j < numAttrs; ++j) {
					if (j < index)
						entries[i][j] = old[i][j];
					else
						entries[i][j+1] = old[i][j];
				}
				entries[i][index] = default_value;
			}

			_dealloc_entries(old, numEntries);
		}

		++numAttrs;
	}

	return true;
}

bool
Table::addEntry(const string *entry, int index)
{
	if (index < -1 || index > numEntries)
		return false;

	if (index == -1)
		index = numEntries;

	if (numEntries == 0) {
		numEntries = 1;
		entries = _alloc_entries(numAttrs, numEntries);

		_copy_entry(entries[0], entry, numAttrs);
	}
	else {
		string **old = entries;

		entries = _alloc_entries(numAttrs, numEntries + 1);
		for (int i = 0; i < numEntries; ++i) {
			if (i < index)
				_copy_entry(entries[i], old[i], numAttrs);
			else
				_copy_entry(entries[i+1], old[i], numAttrs);
		}
		_copy_entry(entries[index], entry, numAttrs);

		_dealloc_entries(old, numEntries);
		++numEntries;
	}

	return true;
}

bool
Table::deleteAttribute(int index)
{
	if (index < 0 || index >= numAttrs)
		return false;

	if (numAttrs == 1) {
		// Remove all attributes and all entries
		delete [] attrs;
		_dealloc_entries(entries, numEntries);

		attrs = nullptr;
		entries = nullptr;

		numEntries = 0;
	}
	else {
		string *old = attrs;

		attrs = new string[numAttrs - 1];

		for (int i = 0; i < numAttrs - 1; ++i) {
			if (i < index)
				attrs[i] = old[i];
			else
				attrs[i] = old[i+1];
		}

		delete [] old;

		if (numEntries > 0) {
			string **old = entries;

			entries = _alloc_entries(numAttrs - 1, numEntries);

			for (int i = 0; i < numEntries; ++i) {
				for (int j = 0; j < numAttrs - 1; ++j) {
					if (j < index)
						entries[i][j] = old[i][j];
					else
						entries[i][j] = old[i][j+1];
				}
			}

			_dealloc_entries(old, numEntries);
		}
	}

	--numAttrs;

	return true;
}

bool 
Table::deleteEntry(int index)
{
	if (index < 0 || index >= numEntries)
		return false;

	if (numEntries == 1) {
		_dealloc_entries(entries, numEntries);

		entries = nullptr;
	}
	else {
		string ** old = entries;

		entries = _alloc_entries(numAttrs, numEntries - 1);

		for (int i = 0; i < numEntries - 1; ++i) {
			if (i < index)
				_copy_entry(entries[i], old[i], numAttrs);
			else
				_copy_entry(entries[i], old[i+1], numAttrs);
		}

		_dealloc_entries(old, numEntries);
	}

	--numEntries;

	return true;
}

bool
Table::append(const Table &another)
{
	if (numAttrs != another.numAttrs)
		return false;

	for (int i = 0; i < numAttrs; ++i)
		if (attrs[i] != another.attrs[i])
			return false;

	for (int i = 0; i < another.numEntries; ++i)
		addEntry(another.entries[i]);

	return true;
}
