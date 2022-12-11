$input v_color0, v_normal

void main()
{
    gl_FragColor = vec4(abs(v_normal), 1.0);
	//gl_FragColor = v_color0;
}