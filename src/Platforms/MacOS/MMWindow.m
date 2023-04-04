#include <Cocoa/Cocoa.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

void disableMinimizeButton(GLFWwindow *window) {
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    [nsWindow setStyleMask:[nsWindow styleMask] & ~NSWindowStyleMaskMiniaturizable];
}

void disableMaximizeButton(GLFWwindow *window) {
    NSWindow* nsWindow = (NSWindow*)glfwGetCocoaWindow(window);
    [nsWindow standardWindowButton:NSWindowZoomButton].enabled = NO;
}

void disableCloseButton(GLFWwindow *window) {
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    [nsWindow setStyleMask:[nsWindow styleMask] & ~NSWindowStyleMaskClosable];
}

void hideMinimizeButton(GLFWwindow *window) {
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    [[nsWindow standardWindowButton:NSWindowMiniaturizeButton]  setHidden:YES];
}

void hideMaximizeButton(GLFWwindow *window) {
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    [[nsWindow standardWindowButton:NSWindowZoomButton]  setHidden:YES];
}

void hideCloseButton(GLFWwindow *window) {
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    [[nsWindow standardWindowButton:NSWindowCloseButton]  setHidden:YES];
}

void makeWindowNonResizable(GLFWwindow *window) {
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    [nsWindow setStyleMask:[nsWindow styleMask] & ~NSWindowStyleMaskResizable];
}

void makeWindowWithoutDecorations(GLFWwindow *window) {
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    [nsWindow setStyleMask:NSWindowStyleMaskBorderless];
}