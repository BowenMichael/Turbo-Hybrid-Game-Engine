$input a_position, a_normal, a_color0
$output v_color0, v_normal, v_wpos

#include "../../include/bgfx/tools/texturev/common.sh"

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_normal = a_normal;
    v_color0 = a_color0;
}