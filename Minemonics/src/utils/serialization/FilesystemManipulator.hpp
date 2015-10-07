#ifndef UTILS_SERIALIZATION_FILESYSTEMMANIPULATOR_HPP_
#define UTILS_SERIALIZATION_FILESYSTEMMANIPULATOR_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <iostream>
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iterator/iterator_facade.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The FileSystemManipulator helps with the creation and retrieval of files.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class FilesystemManipulator {
public:
	static std::vector<std::string> getFileNamesByExtension(std::string path,
		std::string extension) {
		std::vector < std::string > files;

		// iterate through the directory content
		for (boost::filesystem::directory_iterator it(path);
			it != boost::filesystem::directory_iterator(); ++it) {

			//if the file is a regular one and its extension is the right one
			if (boost::filesystem::is_regular_file(it->status())
				&& it->path().extension() == extension) {
				files.push_back(it->path().filename().c_str());
			}
		}

//		std::cout << "Number of files: " << files.size() << std::endl;
//		std::copy(files.begin(), files.end(),
//			std::ostream_iterator < std::string > (std::cout, "\n"));

		return files;
	}

	static std::string createFolder(std::string parentPath, std::string folderName){
		std::string path = parentPath + "/" + folderName;
		boost::filesystem::path bpath = boost::filesystem::path(path);
		if(!boost::filesystem::exists(bpath)){
			boost::filesystem::create_directories(bpath);
		}
		return boost::filesystem::absolute(bpath).c_str();
	}
};

#endif /* UTILS_SERIALIZATION_FILESYSTEMMANIPULATOR_HPP_ */
