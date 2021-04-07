#pragma once
#include <string>
class StringBuilder
{
protected:
	char* m_memory;
	int m_capacity;
	int m_stringSize;

public:
	StringBuilder();
	StringBuilder(int reserved_size);
	~StringBuilder();
	void Append(std::string str);
	std::string GetString();
	int GetLength();
	int GetCapacity();
	void SetCapacity(int new_capacity);

};

