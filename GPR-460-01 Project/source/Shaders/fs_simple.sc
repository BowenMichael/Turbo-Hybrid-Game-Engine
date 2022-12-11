$input v_color0, v_normal, v_wpos

uniform vec4 u_base_color;

void main()
{
	
	//float NdotL = dot(normalize(v_normal), normalize(lightDir));
    //NdotL = max(0.0, NdotL);

    //gl_FragColor = vec4(abs(v_normal), 1.0);
	//gl_FragColor = gl_Position;
	gl_FragColor = u_base_color;
}