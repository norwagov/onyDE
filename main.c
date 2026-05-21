#include <X11/X.h>
#include <X11/Xlib.h>
#include <stddef.h>

void handle_map(Display *display, XMapRequestEvent e) {
    XMapWindow(display, e.window);
}

void handle_configure(Display *display, XConfigureRequestEvent e) {
    XWindowChanges windowChanges;

    windowChanges.width = e.width;
    windowChanges.border_width = e.border_width;
    windowChanges.height = e.height;
    windowChanges.sibling = e.above;
    windowChanges.stack_mode = e.detail;
    windowChanges.x = e.x;
    windowChanges.y = e.y;

    unsigned int value_mask = e.value_mask;

    XConfigureWindow(display, e.window, value_mask, &windowChanges);
}

void handle_click(Display *display, XButtonEvent e) {
    return (void)NULL;
}

int main() {
    Display *display = XOpenDisplay(":0.0");
    Window parent = DefaultRootWindow(display);
    int screen = DefaultScreen(display);

    int width = XDisplayWidth(display, screen);
    int height = XDisplayHeight(display, screen);

    Window window = XCreateSimpleWindow(
        display,
        parent,
        0, 0,
        width, height,
        1,
        BlackPixel(display, screen),
        BlackPixel(display, screen)
    );
    XSelectInput(display, window,
        SubstructureRedirectMask |
        SubstructureNotifyMask | 
        ButtonPressMask);
    
    XMapWindow(display, window);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        switch (event.type) {
            case MapRequest:
                handle_map(display, event.xmaprequest);
                break;
            case ConfigureRequest:
                handle_configure(display, event.xconfigurerequest);
                break;
            case ButtonPress:
                XAllowEvents(
                    display,
                    ReplayPointer,
                    CurrentTime);
                break;
            
        }
    }

    XCloseDisplay(display);
    return 0;
}