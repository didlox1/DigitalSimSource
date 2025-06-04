#include<iostream>
#include <string>
#include <fstream>
#include "Module.h"
#include <sstream>
#include "Clock.h"
class File {
private:
	std::string m_filename;
public:
	void saveModule(const std::string& filename, Module& m);
	void loadModule(const std::string& filename, Module& m);
};