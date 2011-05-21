/*
Simple Xlib application drawing a box in a window.
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	Display *display;
	int screen;
	Window window;
	XEvent event;

	/* open connection with the server */
	display = XOpenDisplay(NULL);
	if (!display)
	{
		printf("Cannot open display\n");
		exit(EXIT_FAILURE);
	}
	screen = DefaultScreen(display);

	/* create window */
	window = XCreateSimpleWindow(display, RootWindow(display, screen),
		10, 10, 100, 100, 1, BlackPixel(display, screen),
		WhitePixel(display, screen));

	/* select kind of events we are interested in */
	XSelectInput(display, window, ExposureMask | KeyPressMask);

	/* map (show) the window */
	XMapWindow(display, window);

	int i = 0;
	char buffer[127];
	
	XWindowAttributes winInfos;
	
	/* event loop */
	while (1)
	{
		XNextEvent(display, &event);
		
		/* draw or redraw the window */
		//if (event.type == Expose)
		{
			
			XGetWindowAttributes(display, window, &winInfos);
        
			XFillRectangle(
				display, window, DefaultGC(display, screen), 20, 20, 10, 10);
			sprintf(buffer, "width=%d",	 winInfos.width);
			XDrawString(
				display, window, DefaultGC(display, screen),
				winInfos.width / 2, 10,
				buffer, strlen(buffer));
			sprintf(buffer, "height=%d", winInfos.height);
			XDrawString(
				display, window, DefaultGC(display, screen),
				0, winInfos.height / 2,
				buffer, strlen(buffer));
		}

		/* exit on key press */
		if (event.type == KeyPress)
			break;
	}

	/* close connection to server */
	XCloseDisplay(display);

	return EXIT_SUCCESS;
}
