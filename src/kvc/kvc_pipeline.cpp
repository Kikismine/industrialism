#include "kvc_pipeline.hpp"

#include "kvc_util.hpp"

namespace kvc {

KvcPipeline::KvcPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
    createGraphicsPipeline(vertFilepath, fragFilepath);
}

// reads file (based on filepath) and returns the buffer of the file
std::vector<char> KvcPipeline::readFile(const std::string& filepath) {
    // read file (ifstream) and then return it's contents
    std::ifstream file{filepath, std::ios::ate | std::ios::binary};

    if (!file.is_open())
        throw std::runtime_error("failed to open file: " + filepath);

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

// reads vertex and fragment compiled shader files (based on the filepaths) and cout the size of them
void KvcPipeline::createGraphicsPipeline(const std::string &vertFilepath, const std::string &fragFilepath) {
    // read the shader files and cout it's code size
    auto vertCode = readFile(vertFilepath);
    auto fragCode = readFile(fragFilepath);

    std::cout << "\nVertex Shader code size: " << vertCode.size() << "\n";
    std::cout << "Fragment Shader code size: " << fragCode.size() << "\n";
}

}
