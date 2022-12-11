$input v_color0, v_normal, v_wpos

uniform vec4 u_base_color;

void main()
{
	
	// set up point light
	vec3 lightPos = vec3(0.0, 1.0, -3.0);
	vec3 lightDir = lightPos - v_wpos;
	
	// get diffuse lighting calculation
	float NdotL = dot(normalize(v_normal), normalize(lightDir));
    NdotL = max(0.0, NdotL);

	// set lit frag color
	vec4 litColor = vec4(vec3(NdotL), 1.0) * u_base_color;
	gl_FragColor = litColor;
}