#pragma once

class Renderer {
public:
    static Renderer *renderer;

    static Renderer *get_renderer();
    void render();
private:
};
