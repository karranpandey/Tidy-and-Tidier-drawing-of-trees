#include <GL/glut.h>
#include <cmath>

using namespace std;


/**
Helper function to draw circle
(sx, xy) is center of circle
(x, y) are are drawn using 8-way symmetry
*/
void symPixel(int x, int y, int xc, int yc) {

	glBegin(GL_POINTS);
	    glVertex2i(x+xc,y+yc);
	    glVertex2i(-x+xc,y+yc);
	    glVertex2i(x+xc,-y+yc);
	    glVertex2i(-x+xc,-y+yc);
	    glVertex2i(y+xc,x+yc);
	    glVertex2i(-y+xc,x+yc);
	    glVertex2i(y+xc,-x+yc);
	    glVertex2i(-y+xc,-x+yc);
	glEnd();
}

/**
Draws nodes (circles) using the mid-point algo
(xc,yc) denotes the centre of circle with 'r' as its radius.
*/
void drawNode(int xc, int yc, int r)
{
	///Scan conversion starts at top most point of the circle.
	int x = 0, y = r;                       /// coordinates assuming centre at (0,0)
	int d = 1-r;                            /// decision variable
	int deltaE = 3, deltaSE = -2 * r + 5;   /// used for updation of decision variable -'d'.


	///Plot the first point
	symPixel(x, y, xc, yc);

	while(y > x)
	{
		if(d < 0)			                /// If d < 0, East coordinate is to be selected.
			{
			d += deltaE;
			deltaE += 2;
			deltaSE += 2; 	}
		else
		{
			d += deltaSE;                   /// South-East coordinate is selected.
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;
		symPixel(x, y, xc, yc);             ///Plot the symmetrical points
	}
}


void drawLine(int x1, int y1, int x2, int y2) {
	int dy = abs(y2-y1);
	int dx = abs(x2-x1);
	int x, y;
	int d, incrE, incrNE;
	int x_dir, y_dir;

	x_dir = (x2 > x1) ? 1 : -1;
	y_dir = (y2 > y1) ? 1 : -1;

	if (dy <= dx) { 						/// |slope| <= 1, scan column-wise
	d = 2*dy - dx;
	incrE = 2 * dy;
	incrNE = 2 * (dy - dx);
	    x = x1; y = y1;
		for(int i=1;i <= dx; i++) {
			if(d <= 0) {
                d += incrE;
			}
 	        else {
				d += incrNE;
				y = y+y_dir;
	        }

			glBegin(GL_POINTS);
			glVertex2i(x, y);
	        glEnd();
	        x = x + x_dir;
		}
	}
	else { 									/// |slope| >= 1
		d = 2*dx - dy;
		incrE = 2 * dx;
		incrNE = 2 * (dx - dy);
		y = y1; x = x1;
		for (int i=0; i < dy; i++) {
			if (d < 0) {
				d += incrE;
			}
            else {
				d += incrNE;
				x = x + x_dir;
			}
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
       		 y = y + y_dir;
	     }
	}

}

void connectNodes(int x1, int y1, int x2, int y2, int r)
{
    float xl, xr, yl, yr;

    //Distance between two nodes.
    float dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

    //Locate Perimeter point of node to draw line from.
    xl = x1 + r*(x2-x1)/dist;
    yl = y1 + r*(y2-y1)/dist;

    xr = x2 + r*(x1-x2)/dist;
    yr = y2 + r*(y1-y2)/dist;

	//Draw line.
	drawLine(xl, yl, xr, yr);
}
