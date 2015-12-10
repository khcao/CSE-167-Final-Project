
#define KERNEL_SIZE 9

// Gaussian kernel
// 1 2 1
// 2 4 2
// 1 2 1	
const float kernel[KERNEL_SIZE] = { 1.0/16.0, 2.0/16.0, 1.0/16.0,
				2.0/16.0, 4.0/16.0, 2.0/16.0,
				1.0/16.0, 2.0/16.0, 1.0/16.0 };

uniform sampler2D colorMap;
uniform float width;
uniform float height;

const float step_w = 1.0/width;
const float step_h = 1.0/height;

const vec2 offset[KERNEL_SIZE] = { vec2(-step_w, -step_h), vec2(0.0, -step_h), vec2(step_w, -step_h), 
				vec2(-step_w, 0.0), vec2(0.0, 0.0), vec2(step_w, 0.0), 
				vec2(-step_w, step_h), vec2(0.0, step_h), vec2(step_w, step_h) };
void main(void)
{
   int i = 0;
   vec4 sum = vec4(0.0);
   
   if(gl_TexCoord[0].s<0.495)
   {
	   for( i=0; i<KERNEL_SIZE; i++ )
	   {
			vec4 tmp = texture2D(colorMap, gl_TexCoord[0].st + offset[i]);
			sum += tmp * kernel[i];
	   }
   }
   else if( gl_TexCoord[0].s>0.505 )
   {
		sum = texture2D(colorMap, gl_TexCoord[0].xy);
   }
   else
   {
		sum = vec4(1.0, 0.0, 0.0, 1.0);
	}

   gl_FragColor = sum;
}