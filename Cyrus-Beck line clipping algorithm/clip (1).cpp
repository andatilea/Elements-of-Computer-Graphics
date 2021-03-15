#include "clip.h"
#include "vec3.h"

namespace egc {

	//Cyrus-Beck clipping algorithm
	//clipWindow specifies the vertices that define the clipping area in conterclockwise order
	//and can represent any convex polygon
	//function returns -1 if the line segment cannot be clipped

	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {

		//in order for the implemented Cyrus-Beck algorithm to work, I added in the "vec3.cpp" Source, all the operators implemented earlier in the Laboratory;

		std::vector<vec3> norm;
		vec3 d = vec3(-(clipWindow[0].y - clipWindow[clipWindow.size() - 1].y), (clipWindow[0].x - clipWindow[clipWindow.size() - 1].x), 1);
		norm.push_back(d);

		for (int i = 1; i < clipWindow.size(); i++) {

			vec3 dd = vec3(-(clipWindow[i].y - clipWindow[i - 1].y), (clipWindow[i].x - clipWindow[i - 1].x), 1);
			norm.push_back(dd);
		}


		if (p1 == p2) {
			//line generates to a point;
			return 0;
		}

		else {
			float tE = 0;
			float tL = 1;
			vec3 L = p2 - p1;

			for (int i = 0; i < clipWindow.size(); i++) {

				vec3 currentN = norm[i];
				vec3 l1 = p1 - clipWindow[i];
				vec3 l2 = p2 - clipWindow[i];

				float t;
				float f1 = dotProduct(currentN, l1);
				float f2 = dotProduct(currentN, l2);
				float f = dotProduct(currentN, L);

				if (f1 > 0 && f2 > 0)	return -1;

				if (f != 0) {

					vec3 n11 = norm[i] * (-1);

					//we calculate t;
					t = dotProduct(currentN, l1) / (dotProduct(n11, L));

					if (f < 0) {
						if (t > tE)
							tE = t;
					}
					if (f > 0) {
						if (t < tL) 
							tL = t;
					}
				}
			}
			if (tE > tL) {

				return -1;
			}
				else {

				vec3 p11 = p1 + L * tE;
				vec3 p22 = p1 + L * tL;

				p1 = p11;
				p2 = p22;
				}
			}
		return 0;
		}
	}

