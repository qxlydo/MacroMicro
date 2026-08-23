#pragma once
#include <iostream>
#include <filesystem>
#include <cstdint>
#include <string>
#include <vector>
#include <thread>

using namespace std::filesystem;

struct MetaData {
	std::string nameFile;
	double sizeFile;
};


class MMEngine {
private:
	std::vector<MetaData> MD;
public:
	void YesOrNot(path dirPath);
	void IterForDir(const path& dirPath);
	std::vector<MetaData> addToList(std::vector<MetaData>& Md, const std::string& NewNameFile, const std::int64_t& newSizeFile);
	void getData();
};