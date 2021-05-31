#include <iostream>

#include "intermediate.h"
#include "table.h"

using namespace std;

const string sep = " | ";

Intermediate::Intermediate(const Table &table):
attrs(table.attrs), numAttrs(table.numAttrs), head(nullptr), tail(nullptr)
{
	for (int i = 0; i < table.numEntries; ++i) {
		string *entry = table.entries[i];
		EntryNode *node = new EntryNode {entry, tail, nullptr};

		if (node->prev != nullptr)
			node->prev->next = node;

		if (head == nullptr)
			head = node;
		tail = node;
	}
}

Intermediate::~Intermediate()
{
	for (EntryNode *curr = head; curr != nullptr; ) {
		EntryNode *del = curr;
		curr = curr->next;
		delete del;
	}
}

Intermediate&
Intermediate::where(const string &attr, enum compare mode, const string &value)
{
	int index;
	for (index = 0; index < numAttrs; ++index) {
		if (attr == attrs[index])
			break;
	}

	if (index < numAttrs) {
		for (EntryNode *curr = head; curr != nullptr;) {
			EntryNode *node = curr;
			curr = curr->next;

			string *entry = node->entry;
			string v = entry[index];

			if ((mode == EQ       && v             != value)         ||
			    (mode == CONTAINS && v.find(value) == string::npos))
			{
				// Remove node
				if (node->prev != nullptr)
					node->prev->next = node->next;

				if (node->next != nullptr)
					node->next->prev = node->prev;

				if (head == node)
					head = node->next;

				if (tail == node)
					tail = node->prev;

				delete node;
			}
		}
	}		

	return *this;
}

Intermediate&
Intermediate::orderBy(const string &attr, enum order order)
{
	int index;
	for (index = 0; index < numAttrs; ++index) {
		if (attr == attrs[index])
			break;
	}

	if (index < numAttrs) {
		// Bubble Sort
		for (EntryNode *end = tail; end != head; end = end->prev) {
			for (EntryNode *curr = head; curr != end; curr = curr->next) {
				string l = curr->entry[index];
				string r = curr->next->entry[index];

				if ((order == ASCENDING  && l.compare(r) > 0) ||
				    (order == DESCENDING && l.compare(r) < 0))
				{
					// swap(curr->entry, curr->next->entry);
					string *tmp = curr->entry;
					curr->entry = curr->next->entry;
					curr->next->entry = tmp;
				}
			}
		}
	}

	return *this;
}

Intermediate&
Intermediate::limit(unsigned int limit)
{
	EntryNode *curr = head;
	for (unsigned int i = 0; i < limit && curr != nullptr; ++i, curr = curr->next)
		;

	if (curr != nullptr)
		tail = curr->prev;

	if (tail != nullptr)
		tail->next = nullptr;

	if (curr == head)
		head = nullptr;

	while (curr != nullptr) {
		EntryNode *del = curr;
		curr = curr->next;
		delete del;
	}

	return *this;
}

void
Intermediate::update(const string &attr, const string &new_value) const
{
	int index;
	for (index = 0; index < numAttrs; ++index) {
		if (attr == attrs[index])
			break;
	}

	if (index < numAttrs) {
		for (EntryNode *curr = head; curr != nullptr; curr = curr->next) {
			string *entry = curr->entry;
			entry[index] = new_value;
		}
	}
}

void
Intermediate::select(const string *attrs, int numAttrs) const
{
	if (this->numAttrs == 0)
		return;

	if (attrs == nullptr)
		numAttrs = this->numAttrs;

	// Find the mapping from attrs to this->attrs
	int *mapping = new int[numAttrs];
	if (attrs != nullptr) {
		for (int i = 0; i < numAttrs; ++i) {
			for (int j = 0; j < this->numAttrs; ++j) {
				if (attrs[i] == this->attrs[j])
					mapping[i] = j;
			}
		}
	}
	else {
		attrs = this->attrs;
		for (int i = 0; i < numAttrs; ++i) {
			mapping[i] = i;
		}
	}

	// Calculate max length of each column
	int *lengths = new int[numAttrs];

	for (int i = 0; i < numAttrs; ++i) {
		lengths[i] = attrs[i].length();

		for (EntryNode *curr = head; curr != nullptr; curr = curr->next) {
			int length = (curr->entry)[mapping[i]].length();
			if (length > lengths[i])
				lengths[i] = length;
		}
	}

	// Print attributes
	if (numAttrs > 0) {
		cout << _left_pad_until(attrs[0], lengths[0]);
	
		for (int i = 1; i < numAttrs; ++i)
			cout << sep << _left_pad_until(attrs[i], lengths[i]);
	
		cout << endl;
	}

	for (EntryNode *curr = head; curr != nullptr; curr = curr->next) {
		string *entry = curr->entry;

		cout << _left_pad_until(entry[mapping[0]], lengths[0]);
		for (int i = 1; i < numAttrs; ++i)
			cout << sep << _left_pad_until(entry[mapping[i]], lengths[i]);
		cout << endl;
	}

	delete [] mapping;
	delete [] lengths;
}
