#pragma once

#include "kvc/kvc_window.hpp"
#include "kvc/kvc_pipeline.hpp"
#include "kvc/kvc_instance.hpp"
#include "kvc/kvc_device.hpp"

namespace kvc {

class Engine {
    public:
        static constexpr std::uint16_t width = 800;
        static constexpr std::uint16_t height = 600;

        void run();
    private:
        KvcWindow kvcWindow{width, height, "window"};
        KvcInstance kvcInstance{"KVC", {1, 0, 0}, "KVC Engine", {1, 0, 0}};
        KvcDevice kvcDevice{kvcInstance.instance};
        KvcPipeline kvcPipeline{"res/shaders/vertex.vert.spv", "res/shaders/fragment.frag.spv"};
};

}
