#pragma once

#include "kvc_util.hpp"

namespace kvc {

class KvcPipeline {
    public:
        KvcPipeline(const std::string& vertFilepath, const std::string& fragFilepath);

    private:
        static std::vector<char> readFile(const std::string& filepath);

        void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
};

}
