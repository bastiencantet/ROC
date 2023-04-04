#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

void setAppIcon(GLFWwindow* window, const char* iconFilePath) {
    // Get the X11 display and window ID from the GLFW window object
    Display* display = glfwGetX11Display();
    Window x11Window = glfwGetX11Window(window);

    // Load icon image from file
    Pixmap iconPixmap = XCreateBitmapFromData(display, x11Window, iconFilePath, 32, 32);

    // Set the icon image
    XWMHints* wmHints = XAllocWMHints();
    wmHints->flags = IconPixmapHint;
    wmHints->icon_pixmap = iconPixmap;
    XSetWMHints(display, x11Window, wmHints);
    XFree(wmHints);
}