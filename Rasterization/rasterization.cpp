#include "rasterization.h"

namespace egc {

	float F_bc(const std::vector<egc::vec4>& triangleVertices, vec2 pixel) {		//Fbc(x,y)

		float yb = triangleVertices.at(1).y;
		float yc = triangleVertices.at(2).y;
		float term1 = (yb - yc) * pixel.x;

		float xc = triangleVertices.at(2).x;
		float xb = triangleVertices.at(1).x;
		float term2 = (xc - xb) * pixel.y;

		float term3 = xb * yc;
		float term4 = xc * yb;

		return(term1 + term2 + term3 - term4);
	}

	float F_bc2(const std::vector<egc::vec4>& triangleVertices) {					//Fbc(xa, ya)

		const egc::vec4 a = triangleVertices.at(0);

		float yb = triangleVertices.at(1).y;
		float yc = triangleVertices.at(2).y;
		float term1 = (yb - yc) * a.x;

		float xc = triangleVertices.at(2).x;
		float xb = triangleVertices.at(1).x;
		float term2 = (xc - xb) * a.y;

		float term3 = xb * yc;
		float term4 = xc * yb;

		return(term1 + term2 + term3 - term4);
	}

	float F_ac(const std::vector<egc::vec4>& triangleVertices, vec2 pixel) {		//Fac(x,y)

		float ya = triangleVertices.at(0).y;
		float yc = triangleVertices.at(2).y;
		float term1 = (ya - yc) * pixel.x;

		float xc = triangleVertices.at(2).x;
		float xa = triangleVertices.at(0).x;
		float term2 = (xc - xa) * pixel.y;

		float term3 = xa * yc;
		float term4 = xc * ya;

		return(term1 + term2 + term3 - term4);
	}

	float F_ac2(const std::vector<egc::vec4>& triangleVertices) {					//Fac(xb,yb)

		const egc::vec4 b = triangleVertices.at(1);

		float ya = triangleVertices.at(0).y;
		float yc = triangleVertices.at(2).y;
		float term1 = (ya - yc) * b.x;

		float xc = triangleVertices.at(2).x;
		float xa = triangleVertices.at(0).x;
		float term2 = (xc - xa) * b.y;

		float term3 = xa * yc;
		float term4 = xc * ya;

		return(term1 + term2 + term3 - term4);
	}


	void computeAlphaBetaGamma(const std::vector<egc::vec4>& triangleVertices, vec2 pixel, float& alpha, float& beta, float& gamma)
	{
		//TO DO - Compute alfa, beta and gamma => we use the function's input parameters as the return mechanism
		//Store the final results in the input parameters
		alpha = F_bc(triangleVertices, pixel);
		alpha  = alpha / F_bc2(triangleVertices);

		beta = F_ac(triangleVertices, pixel);
		beta = beta / F_ac2(triangleVertices);

		gamma = 1 - alpha - beta;
	}

	void rasterizeTriangle(SDL_Renderer* renderer, const std::vector<egc::vec4>& triangleVertices, const std::vector<egc::vec4>& triangleColors) {
		//TO DO - Implement the triangle rasterization algorithm
		float alpha, beta, gamma;
		vec2 pixel;
		int size = triangleVertices.size();
		vec4 color;
		const egc::vec4 color_a = triangleColors[0];
		const egc::vec4 color_b = triangleColors[1];
		const egc::vec4 color_c = triangleColors[2];
		int x_min = 0;
		int y_min = 0;
		int x_max = 0;
		int y_max = 0;
		for (int i = 1; i < size; i++) {
			float v_x = triangleVertices.at(i).x;
			float v_y = triangleVertices.at(i).y;
			if (x_min >v_x)		x_min = v_x;
			if (y_min > v_y)	y_min = v_y;
			if (x_max < v_x)	x_max = v_x;
			if (y_max < v_y)	y_max = v_y;
		}

		for (pixel.x = x_min; pixel.x <= x_max; pixel.x++) {
			for (pixel.y = y_min; pixel.y <= y_max; pixel.y++) {
				computeAlphaBetaGamma(triangleVertices, pixel, alpha, beta, gamma);
				if (0 < alpha && alpha < 1 &&
					0 < beta && beta < 1 &&
					0 < gamma && gamma < 1) {
					color = color_a * alpha + color_b * beta + color_c * gamma;
					
					SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.w);
					SDL_RenderDrawPoint(renderer, pixel.x, pixel.y);
				}
			}
		}
	}
}