#version 420 core

in vec3 outColor;
//in vec2 textureCord;
in vec4 gWorldPos;
in vec4 gObjectPos;
float d;
float lerp;
//uniform vec3 a_CameraPos;

//uniform sampler2D gSampler;
uniform float currentTime;
uniform vec3 color;
out vec4 finalColor;


float random(vec4  v)
{
	return fract(sin(dot(v.xyzw,
		vec4(12.9898f, 78.2332f, 37.7339f, 85.9745f)))*
		43758.5453123f);
}

//float Smooth(float x, float y)
//{
//	float corners = (Random(int(x) - 1, int(y) - 1) + Random(int(x) + 1, int(y) - 1) + Random(int(x) - 1, int(y) + 1) + Random(int(x) + 1, int(y) + 1)) / 16.0f;
//	float sides = (Random(int(x) - 1, int(y)) + Random(int(x) + 1, int(y)) + Random(int(x), int(y) - 1) + Random(int(x), int(y) + 1)) / 8.0f;
//	float center = Random(int(x), int(y)) / 4.0f;
//	return corners + sides + center;
//}

float Interpolate(float a, float b, float x)
{
	float ft = x * 3.1415927; 
	float f = (1 - cos(ft)) * 0.5f; 
	return a*(1-f) + b*f ;
}

float Noise(float x, float y, float z, float w)
{
	float fractional_X = fract(x);
	float  fractional_Y = fract(y);
	float fractional_Z = fract(z);
	float fractional_W = fract(w);

	//smooths
	//float v1 = Smooth(int(x), int(y));
	//float v2 = Smooth(int(x) + 1, int(y));
	//float v3 = Smooth(int(x), int(y) + 1);
	//float v4 = Smooth(int(x) + 1, int(y) + 1);

	float v1 = random(vec4(int(x), int(y), int(z), int(w)));
	float v2 = random(vec4(int(x) + 1, int(y), int(z), int(w)));
	float v3 = random(vec4(int(x), int(y) + 1, int(z), int(w)));
	float v4 = random(vec4(int(x) + 1, int(y) + 1, int(z), int(w)));

	float v5 = random(vec4(int(x), int(y), int(z) + 1, int(w)));
	float v6 = random(vec4(int(x) + 1, int(y), int(z) + 1, int(w)));
	float v7 = random(vec4(int(x), int(y) + 1, int(z) + 1, int(w)));
	float v8 = random(vec4(int(x) + 1, int(y) + 1, int(z) + 1, int(w)));

	float v9 = random(vec4(int(x), int(y), int(z), int(w) + 1));
	float v10 = random(vec4(int(x) + 1, int(y), int(z), int(w) + 1));
	float v11 = random(vec4(int(x), int(y) + 1, int(z), int(w) + 1));
	float v12 = random(vec4(int(x) + 1, int(y) + 1, int(z), int(w) + 1));

	float v13 = random(vec4(int(x), int(y), int(z) + 1, int(w) + 1));
	float v14 = random(vec4(int(x) + 1, int(y), int(z) + 1, int(w) + 1));
	float v15 = random(vec4(int(x), int(y) + 1, int(z) + 1, int(w) + 1));
	float v16 = random(vec4(int(x) + 1, int(y) + 1, int(z) + 1, int(w) + 1));

	// interpolates
	float i1 = Interpolate(v1, v2, fractional_X);
	float i2 = Interpolate(v3, v4, fractional_X);
	float i3 = Interpolate(v5, v6, fractional_X);
	float i4 = Interpolate(v7, v8, fractional_X);
	float i5 = Interpolate(v9, v10, fractional_X);
	float i6 = Interpolate(v11, v12, fractional_X);
	float i7 = Interpolate(v13, v14, fractional_X);
	float i8 = Interpolate(v15, v16, fractional_X);

	float i9 = Interpolate(i1, i2, fractional_Y);
	float i10 = Interpolate(i3, i4, fractional_Y);
	float i11 = Interpolate(i5, i6, fractional_Y);
	float i12 = Interpolate(i7, i8, fractional_Y);

	float i13 = Interpolate(i9, i10, fractional_Z);
	float i14 = Interpolate(i11, i12, fractional_Z);

	float final = Interpolate(i13, i14, fractional_W);

	return final;
}

float TotalNoisePerPoint(int x, int y, int z, int w)
{
	int octaves = 2;
	float zoom = 150.0f;
	float persistance = 0.5f;

	float total = 0.0f;

	for (int i = 0; i < octaves - 1; i++) {

		float frequency = pow(2, i) / zoom;
		float amplitude = pow(persistance, i);

		total += Noise(x * frequency, y * frequency, z * frequency, w * frequency) * amplitude;
	}

	return total;
}
void main(void)
{

	//d = distance(gWorldPos.xyz, a_CameraPos);
	//lerp = (d - 5.0f) / 10.0f;
	//lerp = clamp(lerp, 0.0, 1.0);
	//vec4 vFogColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	//vec3 localPos = vec3(gObjectPos.x - gWorldPos.x, gObjectPos.y - gWorldPos.y, gObjectPos.z - gWorldPos.z);
	vec3 fragDirection = normalize(gObjectPos.xyz);
	float perlinValue = TotalNoisePerPoint(
	int((fragDirection.x * 800) + 2000), 
	int((fragDirection.y * 800) + 2000), 
	int((fragDirection.z * 800) + 2000),
	int(currentTime * 400));
	//vec4 image = texture(gSampler, textureCord.st);
	perlinValue = (perlinValue + 1) / 2;
	//perlinValue = pow(perlinValue, 100);

	finalColor = vec4(color * perlinValue, 1.0f);
}