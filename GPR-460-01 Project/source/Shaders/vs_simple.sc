$input a_position, a_normal, a_color0
$output v_color0, v_normal, v_wpos

#include "../../include/bgfx/tools/texturev/common.sh"

void main()
{
	// set world pos for fs lighting calculations
	v_wpos = mul(u_model[0], vec4(a_position, 1.0) ).xyz;

	// convert normal to world space
	v_normal = mul(u_model[0], vec4(a_normal, 0.0)).xyz;

    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
    v_color0 = a_color0;
}