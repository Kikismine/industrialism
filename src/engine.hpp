#pragma once

#include "kvc/kvc_window.hpp"
#include "kvc/kvc_pipeline.hpp"

namespace kvc {

class Engine {
    public:
        static constexpr std::uint16_t width = 800;
        static constexpr std::uint16_t height = 600;

        void run();
    private:
        KvcWindow kvcWindow{width, height, "window"};
        KvcPipeline kvcPipeline{"res/shaders/vertex.vert.spv", "res/shaders/fragment.frag.spv"};
};

}
