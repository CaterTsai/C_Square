#version 150

uniform sampler2DRect tex0;
uniform float rmin;
uniform float rmax;
uniform float imin;
uniform float imax;
uniform int iterMax;

in vec2 pos;
out vec4 outputColor;

void main()
{
	float distR = (rmax - rmin) * pos.x;
	float distI = (imax - imin) * pos.y;
	
	float r0 = rmin + distR;
	float i0 = imin + distI;
	float r = 0.0;
	float i = 0.0;
	float temp = 0.0;
	int n = 0;
	
	while(n < iterMax && (r * r + i * i) < 4)
	{
		temp = r*r - i*i + r0;
		i = 2 * r * i + i0;
		r = temp;
		n++;
	}
	vec3 color;
	if(n == iterMax)
	{
		color = vec3(0.0);
	}
	else
	{
		color = vec3(sqrt(float(n) / iterMax));
	}
	
	outputColor = vec4 (1.0, 0.0, 0.0, 1.0);
}