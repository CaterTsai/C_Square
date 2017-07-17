#version 120

uniform sampler2DRect tex0;
uniform sampler2DRect pattern;
uniform float width;
uniform float height;
uniform float rmin;
uniform float rmax;
uniform float imin;
uniform float imax;
uniform int iterMax;

varying vec3 pos;

void main()
{
	float distR = (rmax - rmin) * (pos.x / width);
	float distI = (imax - imin) * (pos.y / height);
	
	float r0 = rmin + distR;
	float i0 = imin + distI;
	float r = r0;
	float i = i0;
	float zabs = 0.0;
	float temp = 0.0;
	int n = 0;
	
	zabs = (r * r + i * i);
	while(n < iterMax && zabs < 4.0)
	{
		temp = r*r - i*i + r0;
		i = 2 * r * i + i0;
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
		//color = vec3(float(n)/iterMax);
	}

	gl_FragColor.rgba = vec4 (color, 1.0);
}