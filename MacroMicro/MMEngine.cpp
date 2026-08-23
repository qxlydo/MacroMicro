#include "MMEngine.h"


std::vector<MetaData> MMEngine::addToList(std::vector<MetaData>& Md, const std::string& newNameFile, const std::int64_t& newSizeFile) {
    Md.emplace_back(newNameFile, newSizeFile);
    return Md;
}

void MMEngine::getData()
{
    std::sort(MD.begin(), MD.end(), [](const MetaData& a, const MetaData& b) {
        return a.sizeFile > b.sizeFile;
        });

    std::cout << "Сортировка по размеру:\n";
    for (const auto& file : MD) {
        std::cout << file.nameFile << " — " << file.sizeFile << " Mb\n";
    }
}


void MMEngine::YesOrNot(path dirPath){
    if (exists(dirPath)) {
        std::cout << "Файл - " << dirPath << " Существует" << std::endl;
    }
    else {
        std::cout << "Файл - " << dirPath << " Не существует" << std::endl;
    }
}


void MMEngine::IterForDir(const path& dirPath) {
    std::error_code ec;
    auto it = std::filesystem::recursive_directory_iterator(dirPath,std::filesystem::directory_options::skip_permission_denied, ec);

    if (ec) {
        return;
    }

    while (it != std::filesystem::end(it)) {
        const auto& entry = *it;
        if (std::filesystem::is_regular_file(entry.status(ec)) && !ec) {
            auto size = std::filesystem::file_size(entry.path(), ec);
            if (!ec) {
                double megabytes = static_cast<double>(size) / (1024 * 1024);
                if (megabytes >= 100.0) {
                    addToList(MD, entry.path().filename().string(), megabytes);
                }
            }
        }
        ec.clear();
        it.increment(ec);

        if (ec) {
            ec.clear(); 
        }
    }
}

