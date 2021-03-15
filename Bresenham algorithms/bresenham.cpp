#include "bresenham.h"
#include "math.h"


//Detects in which octant a line is situated
int getOctant(BresenhamLine line) {

	int deltaY = (line.endY - line.startY);
	int deltaX = (line.endX - line.startX);

	//Slope		
	float m = abs(deltaY) / (float)abs(deltaX);

	if ((m < 1) && (deltaX > 0) && (deltaY <= 0)) //first octant
		return 1;

	//second octant;
	if ((m > 1) && (deltaX > 0) && (deltaY <= 0))
		return 2;
	// third octant;
	if ((m >= 1) && (deltaX < 0) && (deltaY <= 0))
		return 3;
	// 4th octant;
	if ((m < 1) && (deltaX < 0) && (deltaY <= 0))	
		return 4;
	// 5th octant;
	if ((m < 1) && (deltaX <= 0) && (deltaY >= 0))	
		return 5;
	// 6th octant;
	if ((m >= 1) && (deltaX <= 0) && (deltaY >= 0))
		return 6;
	// 7th octant;
	if ((m >= 1) && (deltaX >= 0) && (deltaY >= 0))
		return 7;
	// 8th octant;
	if ((m < 1) && (deltaX >= 0) && (deltaY >= 0))	
		return 8;

	return 0;
}

//Draws a new raster line using Bresenham's algorithm
void BresenhamDraw(BresenhamLine line, SDL_Renderer* renderer) {
	int tmpStartX = 0;
	int tmpStartY = 0;
	int tmpEndX = 0;
	int tmpEndY = 0;
	int tmpCurrentX = 0;
	int tmpCurrentY = 0;

	//initialize increments;
	int dy = abs(line.endY - line.startY);
	int dx = abs(line.endX - line.startX);

	int d, inc1, inc2;

	int octant = getOctant(line);

	switch (octant)
	{
	case 1:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		//initialize increments;
		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		//draw each point of the line;
		while (tmpCurrentX < tmpEndX)
		{
			//Draw current point
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;
		//TO DO:
	case 2:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;	//swap case;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY){
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentX;
			}
		}
		break;

	case 3:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;	//swap case;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY > tmpEndY){
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentX;
			}
		}
		break;

	case 4:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpEndX){
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentY;
			}
		}
		break;

	case 5:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX > tmpEndX){
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			--tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentY;
			}
		}
		break;

	case 6:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;	//swap case;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY <= tmpEndY){
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				--tmpCurrentX;
			}
		}
		break;

	case 7:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dx - dy;	//swap case;
		inc1 = 2 * dx;
		inc2 = 2 * (dx - dy);

		while (tmpCurrentY <= tmpEndY){
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentY;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentX;
			}
		}
		break;

	case 8:
		tmpStartX = tmpCurrentX = line.startX;
		tmpEndX = line.endX;
		tmpStartY = tmpCurrentY = line.startY;
		tmpEndY = line.endY;

		d = 2 * dy - dx;
		inc1 = 2 * dy;
		inc2 = 2 * (dy - dx);

		while (tmpCurrentX <= tmpEndX){
			SDL_RenderDrawPoint(renderer, tmpCurrentX, tmpCurrentY);
			++tmpCurrentX;

			if (d < 0)
				d += inc1;
			else
			{
				d += inc2;
				++tmpCurrentY;
			}
		}
		break;

	default:
		break;
	}
}

void plot_points(BresenhamCircle circle, SDL_Renderer* renderer, int x, int y) {
	
	//need to draw the circle from the middle;
	int middle1 = circle.centerX;
	int middle2 = circle.centerY;

	SDL_RenderDrawPoint(renderer, middle1 + x, middle2 + y);
	SDL_RenderDrawPoint(renderer, middle1 + x, middle2 - y);
	SDL_RenderDrawPoint(renderer, middle1 + -x,middle2 + y);
	SDL_RenderDrawPoint(renderer, middle1 - x, middle2 - y);
	SDL_RenderDrawPoint(renderer, middle1 + y, middle2 + x);
	SDL_RenderDrawPoint(renderer, middle1 - y, middle2 + x);
	SDL_RenderDrawPoint(renderer, middle1 + y, middle2 - x);
	SDL_RenderDrawPoint(renderer, middle1 - y, middle2 - x);
}


//Draws a new raster circle using Bresenham's algorithm
void BresenhamDraw(BresenhamCircle circle, SDL_Renderer* renderer) {

	int currentY = circle.radius;	//circle.radius represents the R variable;
	int d = 1/4 - circle.radius;	//the decision variable;
	int currentX = 0;
	//Go only one eighth of a circle;
	for (currentX = 0; currentX <= ceil(circle.radius / sqrt(2)); currentX++) {
		plot_points(circle, renderer, currentX, currentY);
		d += 2 * currentX + 1;		//increment the decision variable;

		if (d > 0) {
			d += 2 - 2 * currentY;	//increment the decision variable;
			currentY--;				//decrement the variable currentY;
		}
	}
}