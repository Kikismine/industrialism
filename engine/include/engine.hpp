#pragma once

#include "kvc/kvc_window.hpp"
#include "kvc/kvc_pipeline.hpp"
#include "kvc/kvc_instance.hpp"
#include "kvc/kvc_device.hpp"
#include "kvc/kvc_surface.hpp"

namespace kvc {

class Engine {
    public:
        static constexpr std::uint16_t width = 800;
        static constexpr std::uint16_t height = 600;

        void run();
    private:
        KvcWindow kvcWindow{width, height, "window"};
        KvcInstance kvcInstance{"KVC", {1, 0, 0}, "KVC Engine", {1, 0, 0}};
        KvcSurface kvcSurface{kvcInstance.instance, kvcWindow.window};
        KvcDevice kvcDevice{kvcInstance.instance, kvcSurface.surface, kvcInstance.enableValidationLayers, kvcInstance.validationLayers};
    [[maybe_unused]] KvcPipeline kvcPipeline{"../engine/res/shaders/vertex.vert.spv", "../engine/res/shaders/fragment.frag.spv"};
};

}
