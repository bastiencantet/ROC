#import <Cocoa/Cocoa.h>
#import <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#import <GLFW/glfw3native.h>

void setAppIcon(GLFWwindow* window, const char* iconFilePath) {
    // Initialize NSApplication instance
    [NSApplication sharedApplication];

    // Load icon image
    NSImage* iconImage = [[NSImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:iconFilePath]];

    // Set application icon image
    [[NSApplication sharedApplication] setApplicationIconImage:iconImage];

    // Create dock tile for the GLFW window
    NSWindow* cocoaWindow = glfwGetCocoaWindow(window);
    NSDockTile* dockTile = [cocoaWindow dockTile];

    // Set dock tile icon
    if (dockTile != nil) {
        [dockTile setContentView:[[NSImageView alloc] initWithFrame:NSMakeRect(0, 0, 0, 0)]];
        [[dockTile contentView] setImage:iconImage];
    }
}