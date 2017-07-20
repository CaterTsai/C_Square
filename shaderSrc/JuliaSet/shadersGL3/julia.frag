#version 430

uniform sampler2DRect tex0;
uniform sampler2DRect pattern;
uniform float real;
uniform float imaginary;
uniform float width;
uniform float height;
uniform float rmin;
uniform float rmax;
uniform float imin;
uniform float imax;
uniform int iterMax;

in vec2 pos;
out vec4 outputColor;

void main()
{
	double distR = (rmax - rmin) * (pos.x / width);
	double distI = (imax - imin) * (pos.y / height);
	
	double r = rmin + distR;
	double i = imin + distI;
	double zabs = 0.0;
	double temp = 0.0;
	int n = 0;
	
	zabs = (r * r + i * i);
	while(n < iterMax && zabs < 4.0)
	{
		temp = r*r - i*i + real;
		i = 2 * r * i + imaginary;
		r = temp;
		
		zabs = (r * r + i * i);
		n++;
	}
	
	vec2 p_pos = vec2(float(n), 0);
	vec3 color;
	
	if(n == iterMax)
	{
		color = vec3(0.0);
	}
	else
	{
		color = texture2DRect(pattern, p_pos).rgb;
	}
	
	outputColor = vec4 (color, 1.0);
}