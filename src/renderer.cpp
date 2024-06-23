#include <renderer.hpp>
#include <util.hpp>

Renderer *Renderer::renderer;

Renderer *Renderer::get_renderer() {
    if (!renderer)
        renderer = new Renderer();

    return renderer;
}

void Renderer::render() {
    glClearColor(0.48, 0.79, 1.00, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}