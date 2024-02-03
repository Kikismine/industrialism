#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../util/util.hpp"

enum camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 2.5f;
const GLfloat SENS = 0.1f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
    // camera attribs
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    // eluer
    GLfloat yaw;
    GLfloat pitch;

    // camera settings
    GLfloat movement_speed;
    GLfloat mouse_sens;
    GLfloat zoom;

    // constructor
    Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _world_up = glm::vec3(0.0f, 1.0f, 0.0), float _yaw = YAW, float _pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sens(SENS), zoom(ZOOM) {
        position = _position;
        world_up = _world_up;
        yaw = _yaw;
        pitch = _pitch;
        update_camera_vectors();
    }

    // constructor scalar
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float _yaw, float _pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sens(SENS), zoom(ZOOM) {
        position = glm::vec3(pos_x, pos_y, pos_z);
        world_up = glm::vec3(up_x, up_y, up_z);
        yaw = _yaw;
        pitch = _pitch;
        update_camera_vectors();
    }

    glm::mat4 get_view_matrix() {
        return glm::lookAt(position, position + front, up);
    }

    void keyboard_process(camera_movement direction, float delta_time) {
        float velocity = movement_speed * delta_time;
        if (direction == FORWARD)
            position += front * velocity;
        if (direction == BACKWARD)
            position -= front * velocity;
        if (direction == LEFT)
            position -= right * velocity;
        if (direction == RIGHT)
            position += right * velocity;
    }

    void mouse_process(float x_offset, float y_offset, GLboolean constrain_pitch = true) {
        x_offset *= mouse_sens;
        y_offset *= mouse_sens;

        yaw += x_offset;
        pitch += y_offset;

        if (constrain_pitch) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        update_camera_vectors();
    }

    void mouse_scroll_process(float y_offset) {
        zoom -= (float) y_offset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > ZOOM)
            zoom = ZOOM;
    }

    // timing
    GLfloat get_current_frame();

private:
    void update_camera_vectors() {
        glm::vec3 _front;
        _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        _front.y = sin(glm::radians(pitch));
        _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(_front);

        // recalculating right & up
        right = glm::normalize(glm::cross(front, world_up));  // normalize the vectors for slower movement safety
        up = glm::normalize(glm::cross(right, front));
    }
};

# endif
