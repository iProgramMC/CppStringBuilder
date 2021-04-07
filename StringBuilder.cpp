#include "StringBuilder.hpp"

StringBuilder::StringBuilder() {
	// initialize the stringbuilder to a default of 1024 bytes in size
	m_capacity = 1024;
	m_memory = new char[m_capacity + 1];
	// ensure a size of zero
	m_stringSize = 0;
	m_memory[0] = '\0';
}
StringBuilder::StringBuilder(int reserved_size) {
	// initialize the stringbuilder to what ever we specified
	m_capacity = reserved_size;
	m_memory = new char[m_capacity + 1];//reserve space for the nullterminator
	// ensure a size of zero
	m_stringSize = 0;
	m_memory[0] = '\0';
}

void StringBuilder::Append(std::string str) {
	// Appends a string to the stringbuilder
	int newSize = m_stringSize + str.size();
	if (newSize >= m_capacity - 1) {
		//! Uh oh, we can't fit this string yet, we gotta expand
		int new_capacity = m_capacity + str.size() * 2; // just for good measure?
		SetCapacity(new_capacity);
	}
	// We're good to go
	int position = m_stringSize;
	m_stringSize = newSize;
	// copy from the string to our buffer
	memcpy(&m_memory[position], str.c_str(), str.size());
	// additionally, add a null terminator
	m_memory[m_stringSize] = '\0';
}

int StringBuilder::GetLength() {
	// get the length of this
	return m_stringSize;
}
int StringBuilder::GetCapacity() {
	return m_capacity;
}
void StringBuilder::SetCapacity(int new_capacity) {
	// Does the string we've got even fit?!
	if (m_stringSize + 1 > new_capacity) {
		//! No no no.
		return;
	}
	char* new_memory = new char[new_capacity];
	memcpy(new_memory, m_memory, m_capacity);
	delete[] m_memory;
	m_memory = new_memory;
	m_capacity = new_capacity;
}

std::string StringBuilder::GetString() {
	return std::string(m_memory, m_stringSize);
}

StringBuilder::~StringBuilder() {
	if (m_memory != nullptr)
		delete[] m_memory;
}