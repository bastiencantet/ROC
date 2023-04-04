#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>


void hideMaximizeButton(GLFWwindow* window) {
    // Get the X11 display and window ID from the GLFW window object
    Display* display = glfwGetX11Display();
    Window x11Window = glfwGetX11Window(window);

}

void hideMinimizeButton(GLFWwindow* window) {
    // Get the X11 display and window ID from the GLFW window object
    Display* display = glfwGetX11Display();
    Window x11Window = glfwGetX11Window(window);

}

void hideCloseButton(GLFWwindow* glfwWindow) {

    Display *display = glfwGetX11Display();
    Window window = glfwGetX11Window(glfwWindow);

}

void makeWindowNonResizable(GLFWwindow* glfwWindow) {

    Display *display = glfwGetX11Display();
    Window window = glfwGetX11Window(glfwWindow);

}

void makeWindowWithoutDecorations(GLFWwindow* glfwWindow) {

    Display *display = glfwGetX11Display();
    Window window = glfwGetX11Window(glfwWindow);

}

void disableMinimizeButton(GLFWwindow* glfwWindow) {

    Display *display = glfwGetX11Display();
    Window window = glfwGetX11Window(glfwWindow);

}

void disableMaximizeButton(GLFWwindow* glfwWindow) {

    Display *display = glfwGetX11Display();
    Window window = glfwGetX11Window(glfwWindow);

}

void disableCloseButton(GLFWwindow* glfwWindow) {

    Display *display = glfwGetX11Display();
    Window window = glfwGetX11Window(glfwWindow);

}