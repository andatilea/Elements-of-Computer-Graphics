#include "clip.h"
#include <math.h>
#include <vector>
#include "include\SDL.h"
#include "vec3.h"

namespace egc {

	int xmin = INT_MAX;
	int ymin = INT_MAX;
	int xmax = -INT_MAX;
	int ymax = -INT_MAX;

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p)
	{
		std::vector<int> code;

		for (int i = 0; i < clipWindow.size(); i++) {

			if (clipWindow[i].x < xmin) {
				xmin = clipWindow[i].x;
			}
			if (clipWindow[i].y < ymin) {
				ymin = clipWindow[i].y;
			}
			if (clipWindow[i].x > xmax) {
				xmax = clipWindow[i].x;
			}
			if (clipWindow[i].y > ymax) {
				ymax = clipWindow[i].y;
			}
		}
		code.push_back(0);
		code.push_back(0);
		code.push_back(0);
		code.push_back(0);

		if (p.x < xmin) {
			code.at(3) = 1;
			code.push_back(1);
		}
		if (p.x > xmax) {
			code.at(2) = 1;
			code.push_back(1);
		}
		if (p.y < ymin) {
			code.at(0) = 1;
			code.push_back(1);
		}
		if (p.y > ymax) {
			code.at(1) = 1;
			code.push_back(1);
		}
		return code;
	}


	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {

		int i;
		for (i = 0; i < 4; i++)
		{
			if (cod1[i] == 1 && cod2[i] == 1) return true;
		}
		return false;
	}


	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {

		int i;
		for (i = 0; i < 4; i++)
		{
			if (cod1[i] == 1 || cod2[i] == 1) return false;
		}
		return true;
	}

	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {

		bool rejected = false;
		bool finished = false;

		for (int i = 0; i < clipWindow.size(); i++) {
			if (clipWindow[i].x < xmin) {
				xmin = clipWindow[i].x;
			}
			if (clipWindow[i].y < ymin) {
				ymin = clipWindow[i].y;
			}
			if (clipWindow[i].x > xmax) {
				xmax = clipWindow[i].x;
			}
			if (clipWindow[i].y > ymax) {
				ymax = clipWindow[i].y;
			}
		}

			while (finished == false)
			{
				std::vector<int> cod1 = computeCSCode(clipWindow, p1);
				std::vector<int> cod2 = computeCSCode(clipWindow, p2);

				rejected = simpleRejection(cod1, cod2);
				if (rejected == true) {
					finished = true;
				}
				else
				{
					bool accepted = simpleAcceptance(cod1, cod2);
					if (accepted == true) {
						finished = true;
					}
					else
					{
						int c = 0;
						for (int i = 0; i < cod1.size(); i++)
							if (cod1[i] == NULL)
							{
								c++;
							}
						//if it is inside;
						if (c == 4) 
						{
							vec3 temp = p1;
							p1 = p2;
							p2 = temp;

							std::vector<int> aux = cod1;
							cod1 = cod2;
							cod2 = aux;
						}
						if (cod1[0] == 1 && p1.y != p2.y)
						{
							//up
							p1.x = + p1.x + (p2.x - p1.x) * (ymin - p1.y) / (p2.y - p1.y);
							p1.y = ymin;
						}
						if (cod1[1] == 1 && p1.y != p2.y)
						{
							//down
							p1.x = p1.x + (p2.x - p1.x) * (ymax - p1.y) / (p2.y - p1.y);
							p1.y = ymax;
						}
						if (cod1[2] == 1 && p1.x != p2.x)
						{
							//right
							p1.y = p1.y + (p2.y - p1.y) * (xmax - p1.x) / (p2.x - p1.x);
							p1.x = xmax;
						}
						else if (cod1[3] == 1 && p1.x != p2.x)
						{
							//left
							p1.y = p1.y + (p2.y - p1.y) * (xmin - p1.x) / (p2.x - p1.x);
							p1.x = xmin;
						}
					}
				}
			}
			if (rejected == true)
			{
				return -1;
			}
			else return 0;

			return 1;
	}
}

