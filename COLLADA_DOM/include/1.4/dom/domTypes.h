/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

#ifndef __DOM_TYPES_H__
#define __DOM_TYPES_H__

#include <dae/daeDomTypes.h>

typedef xsBoolean		domBool;
typedef xsDateTime		domDateTime;
typedef xsDouble		domFloat;
typedef xsLong		domInt;
typedef xsName		domName;
typedef xsString		domString;
typedef xsToken		domToken;
typedef xsUnsignedLong		domUint;
typedef daeTArray<domBool>		domListOfBools;
typedef daeTArray<domFloat>		domListOfFloats;
typedef xsHexBinaryArray		domListOfHexBinary;
typedef daeTArray<domInt>		domListOfInts;
typedef daeTArray<domName>		domListOfNames;
typedef daeTArray<domToken>		domListOfTokens;
typedef daeTArray<domUint>		domListOfUInts;
typedef domListOfBools		domBool2;
typedef domListOfBools		domBool3;
typedef domListOfBools		domBool4;
typedef domListOfFloats		domFloat2;
typedef domListOfFloats		domFloat3;
typedef domListOfFloats		domFloat4;
typedef domListOfFloats		domFloat7;
typedef domListOfFloats		domFloat2x2;
typedef domListOfFloats		domFloat3x3;
typedef domListOfFloats		domFloat4x4;
typedef domListOfFloats		domFloat2x3;
typedef domListOfFloats		domFloat2x4;
typedef domListOfFloats		domFloat3x2;
typedef domListOfFloats		domFloat3x4;
typedef domListOfFloats		domFloat4x2;
typedef domListOfFloats		domFloat4x3;
typedef domListOfInts		domInt2;
typedef domListOfInts		domInt3;
typedef domListOfInts		domInt4;
typedef domListOfInts		domInt2x2;
typedef domListOfInts		domInt3x3;
typedef domListOfInts		domInt4x4;
/**
 * This type is used for URI reference which can only reference a resource
 * declared within it's same document.
 */
typedef xsAnyURI		domURIFragmentType;
typedef domFloat4		domFx_color_common;
typedef xsString		domFx_draw_common;
typedef xsNonNegativeInteger		domGL_MAX_LIGHTS_index;
typedef xsNonNegativeInteger		domGL_MAX_CLIP_PLANES_index;
typedef xsNonNegativeInteger		domGL_MAX_TEXTURE_IMAGE_UNITS_index;
typedef xsFloat		domGl_alpha_value_type;
typedef xsFloat		domGlsl_float;
typedef xsInt		domGlsl_int;
typedef xsBoolean		domGlsl_bool;
typedef daeTArray<domGlsl_bool>		domGlsl_ListOfBool;
typedef daeTArray<domGlsl_float>		domGlsl_ListOfFloat;
typedef daeTArray<domGlsl_int>		domGlsl_ListOfInt;
typedef domGlsl_ListOfBool		domGlsl_bool2;
typedef domGlsl_ListOfBool		domGlsl_bool3;
typedef domGlsl_ListOfBool		domGlsl_bool4;
typedef domGlsl_ListOfFloat		domGlsl_float2;
typedef domGlsl_ListOfFloat		domGlsl_float3;
typedef domGlsl_ListOfFloat		domGlsl_float4;
typedef domGlsl_ListOfFloat		domGlsl_float2x2;
typedef domGlsl_ListOfFloat		domGlsl_float3x3;
typedef domGlsl_ListOfFloat		domGlsl_float4x4;
typedef domGlsl_ListOfInt		domGlsl_int2;
typedef domGlsl_ListOfInt		domGlsl_int3;
typedef domGlsl_ListOfInt		domGlsl_int4;
typedef xsToken		domGlsl_identifier;
typedef xsBoolean		domCg_bool;
typedef xsFloat		domCg_float;
typedef xsInt		domCg_int;
typedef xsFloat		domCg_half;
typedef xsFloat		domCg_fixed;
typedef xsBoolean		domCg_bool1;
typedef xsFloat		domCg_float1;
typedef xsInt		domCg_int1;
typedef xsFloat		domCg_half1;
typedef xsFloat		domCg_fixed1;
typedef daeTArray<domCg_bool>		domCg_ListOfBool;
typedef daeTArray<domCg_float>		domCg_ListOfFloat;
typedef daeTArray<domCg_int>		domCg_ListOfInt;
typedef daeTArray<domCg_half>		domCg_ListOfHalf;
typedef daeTArray<domCg_fixed>		domCg_ListOfFixed;
typedef domCg_ListOfBool		domCg_bool2;
typedef domCg_ListOfBool		domCg_bool3;
typedef domCg_ListOfBool		domCg_bool4;
typedef domCg_ListOfBool		domCg_bool1x1;
typedef domCg_ListOfBool		domCg_bool1x2;
typedef domCg_ListOfBool		domCg_bool1x3;
typedef domCg_ListOfBool		domCg_bool1x4;
typedef domCg_ListOfBool		domCg_bool2x1;
typedef domCg_ListOfBool		domCg_bool2x2;
typedef domCg_ListOfBool		domCg_bool2x3;
typedef domCg_ListOfBool		domCg_bool2x4;
typedef domCg_ListOfBool		domCg_bool3x1;
typedef domCg_ListOfBool		domCg_bool3x2;
typedef domCg_ListOfBool		domCg_bool3x3;
typedef domCg_ListOfBool		domCg_bool3x4;
typedef domCg_ListOfBool		domCg_bool4x1;
typedef domCg_ListOfBool		domCg_bool4x2;
typedef domCg_ListOfBool		domCg_bool4x3;
typedef domCg_ListOfBool		domCg_bool4x4;
typedef domCg_ListOfFloat		domCg_float2;
typedef domCg_ListOfFloat		domCg_float3;
typedef domCg_ListOfFloat		domCg_float4;
typedef domCg_ListOfFloat		domCg_float1x1;
typedef domCg_ListOfFloat		domCg_float1x2;
typedef domCg_ListOfFloat		domCg_float1x3;
typedef domCg_ListOfFloat		domCg_float1x4;
typedef domCg_ListOfFloat		domCg_float2x1;
typedef domCg_ListOfFloat		domCg_float2x2;
typedef domCg_ListOfFloat		domCg_float2x3;
typedef domCg_ListOfFloat		domCg_float2x4;
typedef domCg_ListOfFloat		domCg_float3x1;
typedef domCg_ListOfFloat		domCg_float3x2;
typedef domCg_ListOfFloat		domCg_float3x3;
typedef domCg_ListOfFloat		domCg_float3x4;
typedef domCg_ListOfFloat		domCg_float4x1;
typedef domCg_ListOfFloat		domCg_float4x2;
typedef domCg_ListOfFloat		domCg_float4x3;
typedef domCg_ListOfFloat		domCg_float4x4;
typedef domCg_ListOfInt		domCg_int2;
typedef domCg_ListOfInt		domCg_int3;
typedef domCg_ListOfInt		domCg_int4;
typedef domCg_ListOfInt		domCg_int1x1;
typedef domCg_ListOfInt		domCg_int1x2;
typedef domCg_ListOfInt		domCg_int1x3;
typedef domCg_ListOfInt		domCg_int1x4;
typedef domCg_ListOfInt		domCg_int2x1;
typedef domCg_ListOfInt		domCg_int2x2;
typedef domCg_ListOfInt		domCg_int2x3;
typedef domCg_ListOfInt		domCg_int2x4;
typedef domCg_ListOfInt		domCg_int3x1;
typedef domCg_ListOfInt		domCg_int3x2;
typedef domCg_ListOfInt		domCg_int3x3;
typedef domCg_ListOfInt		domCg_int3x4;
typedef domCg_ListOfInt		domCg_int4x1;
typedef domCg_ListOfInt		domCg_int4x2;
typedef domCg_ListOfInt		domCg_int4x3;
typedef domCg_ListOfInt		domCg_int4x4;
typedef domCg_ListOfHalf		domCg_half2;
typedef domCg_ListOfHalf		domCg_half3;
typedef domCg_ListOfHalf		domCg_half4;
typedef domCg_ListOfHalf		domCg_half1x1;
typedef domCg_ListOfHalf		domCg_half1x2;
typedef domCg_ListOfHalf		domCg_half1x3;
typedef domCg_ListOfHalf		domCg_half1x4;
typedef domCg_ListOfHalf		domCg_half2x1;
typedef domCg_ListOfHalf		domCg_half2x2;
typedef domCg_ListOfHalf		domCg_half2x3;
typedef domCg_ListOfHalf		domCg_half2x4;
typedef domCg_ListOfHalf		domCg_half3x1;
typedef domCg_ListOfHalf		domCg_half3x2;
typedef domCg_ListOfHalf		domCg_half3x3;
typedef domCg_ListOfHalf		domCg_half3x4;
typedef domCg_ListOfHalf		domCg_half4x1;
typedef domCg_ListOfHalf		domCg_half4x2;
typedef domCg_ListOfHalf		domCg_half4x3;
typedef domCg_ListOfHalf		domCg_half4x4;
typedef domCg_ListOfFixed		domCg_fixed2;
typedef domCg_ListOfFixed		domCg_fixed3;
typedef domCg_ListOfFixed		domCg_fixed4;
typedef domCg_ListOfFixed		domCg_fixed1x1;
typedef domCg_ListOfFixed		domCg_fixed1x2;
typedef domCg_ListOfFixed		domCg_fixed1x3;
typedef domCg_ListOfFixed		domCg_fixed1x4;
typedef domCg_ListOfFixed		domCg_fixed2x1;
typedef domCg_ListOfFixed		domCg_fixed2x2;
typedef domCg_ListOfFixed		domCg_fixed2x3;
typedef domCg_ListOfFixed		domCg_fixed2x4;
typedef domCg_ListOfFixed		domCg_fixed3x1;
typedef domCg_ListOfFixed		domCg_fixed3x2;
typedef domCg_ListOfFixed		domCg_fixed3x3;
typedef domCg_ListOfFixed		domCg_fixed3x4;
typedef domCg_ListOfFixed		domCg_fixed4x1;
typedef domCg_ListOfFixed		domCg_fixed4x2;
typedef domCg_ListOfFixed		domCg_fixed4x3;
typedef domCg_ListOfFixed		domCg_fixed4x4;
typedef xsToken		domCg_identifier;
typedef xsNonNegativeInteger		domGLES_MAX_LIGHTS_index;
typedef xsNonNegativeInteger		domGLES_MAX_CLIP_PLANES_index;
typedef xsNonNegativeInteger		domGLES_MAX_TEXTURE_COORDS_index;
typedef xsNonNegativeInteger		domGLES_MAX_TEXTURE_IMAGE_UNITS_index;
typedef xsNonNegativeInteger		domGles_texcombiner_argument_index_type;
typedef xsNCName		domGles_rendertarget_common;

/**
 * An enumuerated type specifying the acceptable morph methods.
 */
enum domMorphMethodType {
	MORPHMETHODTYPE_NORMALIZED,
	MORPHMETHODTYPE_RELATIVE,
	MORPHMETHODTYPE_COUNT = 2
};

/**
 * An enumerated type specifying the acceptable node types.
 */
enum domNodeType {
	NODETYPE_JOINT,
	NODETYPE_NODE,
	NODETYPE_COUNT = 2
};

/**
 * An enumerated type specifying the acceptable up-axis values.
 */
enum domUpAxisType {
	UPAXISTYPE_X_UP,
	UPAXISTYPE_Y_UP,
	UPAXISTYPE_Z_UP,
	UPAXISTYPE_COUNT = 3
};

/**
 * An enumerated type specifying the acceptable document versions.
 */
enum domVersionType {
	VERSIONTYPE_1_4_0,
	VERSIONTYPE_1_4_1,
	VERSIONTYPE_COUNT = 2
};

enum domFx_opaque_enum {
	FX_OPAQUE_ENUM_A_ONE,		/**< When a transparent opaque attribute is set to A_ONE, it means the transparency information will be taken from the alpha channel of the color, texture, or parameter supplying the value. The value of 1.0 is opaque in this mode. */
	FX_OPAQUE_ENUM_RGB_ZERO,		/**< When a transparent opaque attribute is set to RGB_ZERO, it means the transparency information will be taken from the red, green, and blue channels of the color, texture, or parameter supplying the value. Each channel is modulated independently. The value of 0.0 is opaque in this mode. */
	FX_OPAQUE_ENUM_COUNT = 2
};

enum domFx_surface_type_enum {
	FX_SURFACE_TYPE_ENUM_UNTYPED,		/**< When a surface's type attribute is set to UNTYPED, its type is initially unknown and established later by the context in which it is used, such as by a texture sampler that references it. A surface of any other type may be changed into an UNTYPED surface at run-time, as if it were created by <newparam>, using <setparam>. If there is a type mismatch between a <setparam> operation and what the run-time decides the type should be, the result is profile- and platform-specific behavior. */
	FX_SURFACE_TYPE_ENUM_1D,
	FX_SURFACE_TYPE_ENUM_2D,
	FX_SURFACE_TYPE_ENUM_3D,
	FX_SURFACE_TYPE_ENUM_RECT,
	FX_SURFACE_TYPE_ENUM_CUBE,
	FX_SURFACE_TYPE_ENUM_DEPTH,
	FX_SURFACE_TYPE_ENUM_COUNT = 7
};

enum domFx_surface_face_enum {
	FX_SURFACE_FACE_ENUM_POSITIVE_X,
	FX_SURFACE_FACE_ENUM_NEGATIVE_X,
	FX_SURFACE_FACE_ENUM_POSITIVE_Y,
	FX_SURFACE_FACE_ENUM_NEGATIVE_Y,
	FX_SURFACE_FACE_ENUM_POSITIVE_Z,
	FX_SURFACE_FACE_ENUM_NEGATIVE_Z,
	FX_SURFACE_FACE_ENUM_COUNT = 6
};

/**
 * The per-texel layout of the format.  The length of the string indicate
 * how many channels there are and the letter respresents the name of the
 * channel.  There are typically 0 to 4 channels.
 */
enum domFx_surface_format_hint_channels_enum {
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_RGB,		/**< RGB color  map */
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_RGBA,		/**< RGB color + Alpha map often used for color + transparency or other things packed into channel A like specular power */
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_L,		/**< Luminance map often used for light mapping */
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_LA,		/**< Luminance+Alpha map often used for light mapping */
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_D,		/**< Depth map often used for displacement, parellax, relief, or shadow mapping */
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_XYZ,		/**< Typically used for normal maps or 3component displacement maps. */
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_XYZW,		/**< Typically used for normal maps where W is the depth for relief or parrallax mapping */
	FX_SURFACE_FORMAT_HINT_CHANNELS_ENUM_COUNT = 7
};

/**
 * Each channel of the texel has a precision.  Typically these are all linked
 * together.  An exact format lay lower the precision of an individual channel
 * but applying a higher precision by linking the channels together may still
 * convey the same information.
 */
enum domFx_surface_format_hint_precision_enum {
	FX_SURFACE_FORMAT_HINT_PRECISION_ENUM_LOW,		/**< For integers this typically represents 8 bits.  For floats typically 16 bits. */
	FX_SURFACE_FORMAT_HINT_PRECISION_ENUM_MID,		/**< For integers this typically represents 8 to 24 bits.  For floats typically 16 to 32 bits. */
	FX_SURFACE_FORMAT_HINT_PRECISION_ENUM_HIGH,		/**< For integers this typically represents 16 to 32 bits.  For floats typically 24 to 32 bits. */
	FX_SURFACE_FORMAT_HINT_PRECISION_ENUM_COUNT = 3
};

/**
 * Each channel represents a range of values. Some example ranges are signed
 * or unsigned integers, or between between a clamped range such as 0.0f to
 * 1.0f, or high dynamic range via floating point
 */
enum domFx_surface_format_hint_range_enum {
	FX_SURFACE_FORMAT_HINT_RANGE_ENUM_SNORM,		/**< Format is representing a decimal value that remains within the -1 to 1 range. Implimentation could be integer-fixedpoint or floats. */
	FX_SURFACE_FORMAT_HINT_RANGE_ENUM_UNORM,		/**< Format is representing a decimal value that remains within the 0 to 1 range. Implimentation could be integer-fixedpoint or floats. */
	FX_SURFACE_FORMAT_HINT_RANGE_ENUM_SINT,		/**< Format is representing signed integer numbers.  (ex. 8bits = -128 to 127) */
	FX_SURFACE_FORMAT_HINT_RANGE_ENUM_UINT,		/**< Format is representing unsigned integer numbers.  (ex. 8bits = 0 to 255) */
	FX_SURFACE_FORMAT_HINT_RANGE_ENUM_FLOAT,		/**< Format should support full floating point ranges.  High precision is expected to be 32bit. Mid precision may be 16 to 32 bit.  Low precision is expected to be 16 bit. */
	FX_SURFACE_FORMAT_HINT_RANGE_ENUM_COUNT = 5
};

/**
 * Additional hints about data relationships and other things to help the
 * application pick the best format.
 */
enum domFx_surface_format_hint_option_enum {
	FX_SURFACE_FORMAT_HINT_OPTION_ENUM_SRGB_GAMMA,		/**< colors are stored with respect to the sRGB 2.2 gamma curve rather than linear */
	FX_SURFACE_FORMAT_HINT_OPTION_ENUM_NORMALIZED3,		/**< the texel's XYZ/RGB should be normalized such as in a normal map. */
	FX_SURFACE_FORMAT_HINT_OPTION_ENUM_NORMALIZED4,		/**< the texel's XYZW/RGBA should be normalized such as in a normal map. */
	FX_SURFACE_FORMAT_HINT_OPTION_ENUM_COMPRESSABLE,		/**< The surface may use run-time compression.  Considering the best compression based on desired, channel, range, precision, and options */
	FX_SURFACE_FORMAT_HINT_OPTION_ENUM_COUNT = 4
};

enum domFx_sampler_wrap_common {
	FX_SAMPLER_WRAP_COMMON_NONE,
	FX_SAMPLER_WRAP_COMMON_WRAP,
	FX_SAMPLER_WRAP_COMMON_MIRROR,
	FX_SAMPLER_WRAP_COMMON_CLAMP,
	FX_SAMPLER_WRAP_COMMON_BORDER,
	FX_SAMPLER_WRAP_COMMON_COUNT = 5
};

enum domFx_sampler_filter_common {
	FX_SAMPLER_FILTER_COMMON_NONE,
	FX_SAMPLER_FILTER_COMMON_NEAREST,
	FX_SAMPLER_FILTER_COMMON_LINEAR,
	FX_SAMPLER_FILTER_COMMON_NEAREST_MIPMAP_NEAREST,
	FX_SAMPLER_FILTER_COMMON_LINEAR_MIPMAP_NEAREST,
	FX_SAMPLER_FILTER_COMMON_NEAREST_MIPMAP_LINEAR,
	FX_SAMPLER_FILTER_COMMON_LINEAR_MIPMAP_LINEAR,
	FX_SAMPLER_FILTER_COMMON_COUNT = 7
};

enum domFx_modifier_enum_common {
	FX_MODIFIER_ENUM_COMMON_CONST,
	FX_MODIFIER_ENUM_COMMON_UNIFORM,
	FX_MODIFIER_ENUM_COMMON_VARYING,
	FX_MODIFIER_ENUM_COMMON_STATIC,
	FX_MODIFIER_ENUM_COMMON_VOLATILE,
	FX_MODIFIER_ENUM_COMMON_EXTERN,
	FX_MODIFIER_ENUM_COMMON_SHARED,
	FX_MODIFIER_ENUM_COMMON_COUNT = 7
};

enum domFx_pipeline_stage_common {
	FX_PIPELINE_STAGE_COMMON_VERTEXPROGRAM,
	FX_PIPELINE_STAGE_COMMON_FRAGMENTPROGRAM,
	FX_PIPELINE_STAGE_COMMON_VERTEXSHADER,
	FX_PIPELINE_STAGE_COMMON_PIXELSHADER,
	FX_PIPELINE_STAGE_COMMON_COUNT = 4
};

enum domGl_blend_type {
	GL_BLEND_TYPE_ZERO = 0x0,
	GL_BLEND_TYPE_ONE = 0x1,
	GL_BLEND_TYPE_SRC_COLOR = 0x0300,
	GL_BLEND_TYPE_ONE_MINUS_SRC_COLOR = 0x0301,
	GL_BLEND_TYPE_DEST_COLOR = 0x0306,
	GL_BLEND_TYPE_ONE_MINUS_DEST_COLOR = 0x0307,
	GL_BLEND_TYPE_SRC_ALPHA = 0x0302,
	GL_BLEND_TYPE_ONE_MINUS_SRC_ALPHA = 0x0303,
	GL_BLEND_TYPE_DST_ALPHA = 0x0304,
	GL_BLEND_TYPE_ONE_MINUS_DST_ALPHA = 0x0305,
	GL_BLEND_TYPE_CONSTANT_COLOR = 0x8001,
	GL_BLEND_TYPE_ONE_MINUS_CONSTANT_COLOR = 0x8002,
	GL_BLEND_TYPE_CONSTANT_ALPHA = 0x8003,
	GL_BLEND_TYPE_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
	GL_BLEND_TYPE_SRC_ALPHA_SATURATE = 0x0308,
	GL_BLEND_TYPE_COUNT = 15
};

enum domGl_face_type {
	GL_FACE_TYPE_FRONT = 0x0404,
	GL_FACE_TYPE_BACK = 0x0405,
	GL_FACE_TYPE_FRONT_AND_BACK = 0x0408,
	GL_FACE_TYPE_COUNT = 3
};

enum domGl_blend_equation_type {
	GL_BLEND_EQUATION_TYPE_FUNC_ADD = 0x8006,
	GL_BLEND_EQUATION_TYPE_FUNC_SUBTRACT = 0x800A,
	GL_BLEND_EQUATION_TYPE_FUNC_REVERSE_SUBTRACT = 0x800B,
	GL_BLEND_EQUATION_TYPE_MIN = 0x8007,
	GL_BLEND_EQUATION_TYPE_MAX = 0x8008,
	GL_BLEND_EQUATION_TYPE_COUNT = 5
};

enum domGl_func_type {
	GL_FUNC_TYPE_NEVER = 0x0200,
	GL_FUNC_TYPE_LESS = 0x0201,
	GL_FUNC_TYPE_LEQUAL = 0x0203,
	GL_FUNC_TYPE_EQUAL = 0x0202,
	GL_FUNC_TYPE_GREATER = 0x0204,
	GL_FUNC_TYPE_NOTEQUAL = 0x0205,
	GL_FUNC_TYPE_GEQUAL = 0x0206,
	GL_FUNC_TYPE_ALWAYS = 0x0207,
	GL_FUNC_TYPE_COUNT = 8
};

enum domGl_stencil_op_type {
	GL_STENCIL_OP_TYPE_KEEP = 0x1E00,
	GL_STENCIL_OP_TYPE_ZERO = 0x0,
	GL_STENCIL_OP_TYPE_REPLACE = 0x1E01,
	GL_STENCIL_OP_TYPE_INCR = 0x1E02,
	GL_STENCIL_OP_TYPE_DECR = 0x1E03,
	GL_STENCIL_OP_TYPE_INVERT = 0x150A,
	GL_STENCIL_OP_TYPE_INCR_WRAP = 0x8507,
	GL_STENCIL_OP_TYPE_DECR_WRAP = 0x8508,
	GL_STENCIL_OP_TYPE_COUNT = 8
};

enum domGl_material_type {
	GL_MATERIAL_TYPE_EMISSION = 0x1600,
	GL_MATERIAL_TYPE_AMBIENT = 0x1200,
	GL_MATERIAL_TYPE_DIFFUSE = 0x1201,
	GL_MATERIAL_TYPE_SPECULAR = 0x1202,
	GL_MATERIAL_TYPE_AMBIENT_AND_DIFFUSE = 0x1602,
	GL_MATERIAL_TYPE_COUNT = 5
};

enum domGl_fog_type {
	GL_FOG_TYPE_LINEAR = 0x2601,
	GL_FOG_TYPE_EXP = 0x0800,
	GL_FOG_TYPE_EXP2 = 0x0801,
	GL_FOG_TYPE_COUNT = 3
};

enum domGl_fog_coord_src_type {
	GL_FOG_COORD_SRC_TYPE_FOG_COORDINATE = 0x8451,
	GL_FOG_COORD_SRC_TYPE_FRAGMENT_DEPTH = 0x8452,
	GL_FOG_COORD_SRC_TYPE_COUNT = 2
};

enum domGl_front_face_type {
	GL_FRONT_FACE_TYPE_CW = 0x0900,
	GL_FRONT_FACE_TYPE_CCW = 0x0901,
	GL_FRONT_FACE_TYPE_COUNT = 2
};

enum domGl_light_model_color_control_type {
	GL_LIGHT_MODEL_COLOR_CONTROL_TYPE_SINGLE_COLOR = 0x81F9,
	GL_LIGHT_MODEL_COLOR_CONTROL_TYPE_SEPARATE_SPECULAR_COLOR = 0x81FA,
	GL_LIGHT_MODEL_COLOR_CONTROL_TYPE_COUNT = 2
};

enum domGl_logic_op_type {
	GL_LOGIC_OP_TYPE_CLEAR = 0x1500,
	GL_LOGIC_OP_TYPE_AND = 0x1501,
	GL_LOGIC_OP_TYPE_AND_REVERSE = 0x1502,
	GL_LOGIC_OP_TYPE_COPY = 0x1503,
	GL_LOGIC_OP_TYPE_AND_INVERTED = 0x1504,
	GL_LOGIC_OP_TYPE_NOOP = 0x1505,
	GL_LOGIC_OP_TYPE_XOR = 0x1506,
	GL_LOGIC_OP_TYPE_OR = 0x1507,
	GL_LOGIC_OP_TYPE_NOR = 0x1508,
	GL_LOGIC_OP_TYPE_EQUIV = 0x1509,
	GL_LOGIC_OP_TYPE_INVERT = 0x150A,
	GL_LOGIC_OP_TYPE_OR_REVERSE = 0x150B,
	GL_LOGIC_OP_TYPE_COPY_INVERTED = 0x150C,
	GL_LOGIC_OP_TYPE_NAND = 0x150E,
	GL_LOGIC_OP_TYPE_SET = 0x150F,
	GL_LOGIC_OP_TYPE_COUNT = 15
};

enum domGl_polygon_mode_type {
	GL_POLYGON_MODE_TYPE_POINT = 0x1B00,
	GL_POLYGON_MODE_TYPE_LINE = 0x1B01,
	GL_POLYGON_MODE_TYPE_FILL = 0x1B02,
	GL_POLYGON_MODE_TYPE_COUNT = 3
};

enum domGl_shade_model_type {
	GL_SHADE_MODEL_TYPE_FLAT = 0x1D00,
	GL_SHADE_MODEL_TYPE_SMOOTH = 0x1D01,
	GL_SHADE_MODEL_TYPE_COUNT = 2
};

enum domGlsl_pipeline_stage {
	GLSL_PIPELINE_STAGE_VERTEXPROGRAM,
	GLSL_PIPELINE_STAGE_FRAGMENTPROGRAM,
	GLSL_PIPELINE_STAGE_COUNT = 2
};

enum domCg_pipeline_stage {
	CG_PIPELINE_STAGE_VERTEX,
	CG_PIPELINE_STAGE_FRAGMENT,
	CG_PIPELINE_STAGE_COUNT = 2
};

enum domGles_texenv_mode_enums {
	GLES_TEXENV_MODE_ENUMS_REPLACE = 0x1E01,
	GLES_TEXENV_MODE_ENUMS_MODULATE = 0x2100,
	GLES_TEXENV_MODE_ENUMS_DECAL = 0x2101,
	GLES_TEXENV_MODE_ENUMS_BLEND = 0x0BE2,
	GLES_TEXENV_MODE_ENUMS_ADD = 0x0104,
	GLES_TEXENV_MODE_ENUMS_COUNT = 5
};

enum domGles_texcombiner_operatorRGB_enums {
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_REPLACE = 0x1E01,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_MODULATE = 0x2100,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_ADD = 0x0104,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_ADD_SIGNED = 0x8574,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_INTERPOLATE = 0x8575,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_SUBTRACT = 0x84E7,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_DOT3_RGB = 0x86AE,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_DOT3_RGBA = 0x86AF,
	GLES_TEXCOMBINER_OPERATORRGB_ENUMS_COUNT = 8
};

enum domGles_texcombiner_operatorAlpha_enums {
	GLES_TEXCOMBINER_OPERATORALPHA_ENUMS_REPLACE = 0x1E01,
	GLES_TEXCOMBINER_OPERATORALPHA_ENUMS_MODULATE = 0x2100,
	GLES_TEXCOMBINER_OPERATORALPHA_ENUMS_ADD = 0x0104,
	GLES_TEXCOMBINER_OPERATORALPHA_ENUMS_ADD_SIGNED = 0x8574,
	GLES_TEXCOMBINER_OPERATORALPHA_ENUMS_INTERPOLATE = 0x8575,
	GLES_TEXCOMBINER_OPERATORALPHA_ENUMS_SUBTRACT = 0x84E7,
	GLES_TEXCOMBINER_OPERATORALPHA_ENUMS_COUNT = 6
};

enum domGles_texcombiner_source_enums {
	GLES_TEXCOMBINER_SOURCE_ENUMS_TEXTURE = 0x1702,
	GLES_TEXCOMBINER_SOURCE_ENUMS_CONSTANT = 0x8576,
	GLES_TEXCOMBINER_SOURCE_ENUMS_PRIMARY = 0x8577,
	GLES_TEXCOMBINER_SOURCE_ENUMS_PREVIOUS = 0x8578,
	GLES_TEXCOMBINER_SOURCE_ENUMS_COUNT = 4
};

enum domGles_texcombiner_operandRGB_enums {
	GLES_TEXCOMBINER_OPERANDRGB_ENUMS_SRC_COLOR = 0x0300,
	GLES_TEXCOMBINER_OPERANDRGB_ENUMS_ONE_MINUS_SRC_COLOR = 0x0301,
	GLES_TEXCOMBINER_OPERANDRGB_ENUMS_SRC_ALPHA = 0x0302,
	GLES_TEXCOMBINER_OPERANDRGB_ENUMS_ONE_MINUS_SRC_ALPHA = 0x0303,
	GLES_TEXCOMBINER_OPERANDRGB_ENUMS_COUNT = 4
};

enum domGles_texcombiner_operandAlpha_enums {
	GLES_TEXCOMBINER_OPERANDALPHA_ENUMS_SRC_ALPHA = 0x0302,
	GLES_TEXCOMBINER_OPERANDALPHA_ENUMS_ONE_MINUS_SRC_ALPHA = 0x0303,
	GLES_TEXCOMBINER_OPERANDALPHA_ENUMS_COUNT = 2
};

enum domGles_sampler_wrap {
	GLES_SAMPLER_WRAP_REPEAT,
	GLES_SAMPLER_WRAP_CLAMP,
	GLES_SAMPLER_WRAP_CLAMP_TO_EDGE,
	GLES_SAMPLER_WRAP_MIRRORED_REPEAT,		/**< supported by GLES 1.1 only */
	GLES_SAMPLER_WRAP_COUNT = 4
};

enum domGles_stencil_op_type {
	GLES_STENCIL_OP_TYPE_KEEP = 0x1E00,
	GLES_STENCIL_OP_TYPE_ZERO = 0x0,
	GLES_STENCIL_OP_TYPE_REPLACE = 0x1E01,
	GLES_STENCIL_OP_TYPE_INCR = 0x1E02,
	GLES_STENCIL_OP_TYPE_DECR = 0x1E03,
	GLES_STENCIL_OP_TYPE_INVERT = 0x150A,
	GLES_STENCIL_OP_TYPE_COUNT = 6
};

enum domSpringType {
	SPRINGTYPE_LINEAR,
	SPRINGTYPE_ANGULAR,
	SPRINGTYPE_COUNT = 2
};

enum domGl_enumeration {
	GL_ENUMERATION_ZERO = 0x0,
	GL_ENUMERATION_ONE = 0x1,
	GL_ENUMERATION_SRC_COLOR = 0x0300,
	GL_ENUMERATION_ONE_MINUS_SRC_COLOR = 0x0301,
	GL_ENUMERATION_DEST_COLOR = 0x0306,
	GL_ENUMERATION_ONE_MINUS_DEST_COLOR = 0x0307,
	GL_ENUMERATION_SRC_ALPHA = 0x0302,
	GL_ENUMERATION_ONE_MINUS_SRC_ALPHA = 0x0303,
	GL_ENUMERATION_DST_ALPHA = 0x0304,
	GL_ENUMERATION_ONE_MINUS_DST_ALPHA = 0x0305,
	GL_ENUMERATION_CONSTANT_COLOR = 0x8001,
	GL_ENUMERATION_ONE_MINUS_CONSTANT_COLOR = 0x8002,
	GL_ENUMERATION_CONSTANT_ALPHA = 0x8003,
	GL_ENUMERATION_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
	GL_ENUMERATION_SRC_ALPHA_SATURATE = 0x0308,
	GL_ENUMERATION_FRONT = 0x0404,
	GL_ENUMERATION_BACK = 0x0405,
	GL_ENUMERATION_FRONT_AND_BACK = 0x0408,
	GL_ENUMERATION_FUNC_ADD = 0x8006,
	GL_ENUMERATION_FUNC_SUBTRACT = 0x800A,
	GL_ENUMERATION_FUNC_REVERSE_SUBTRACT = 0x800B,
	GL_ENUMERATION_MIN = 0x8007,
	GL_ENUMERATION_MAX = 0x8008,
	GL_ENUMERATION_NEVER = 0x0200,
	GL_ENUMERATION_LESS = 0x0201,
	GL_ENUMERATION_LEQUAL = 0x0203,
	GL_ENUMERATION_EQUAL = 0x0202,
	GL_ENUMERATION_GREATER = 0x0204,
	GL_ENUMERATION_NOTEQUAL = 0x0205,
	GL_ENUMERATION_GEQUAL = 0x0206,
	GL_ENUMERATION_ALWAYS = 0x0207,
	GL_ENUMERATION_KEEP = 0x1E00,
	GL_ENUMERATION_REPLACE = 0x1E01,
	GL_ENUMERATION_INCR = 0x1E02,
	GL_ENUMERATION_DECR = 0x1E03,
	GL_ENUMERATION_INVERT = 0x150A,
	GL_ENUMERATION_INCR_WRAP = 0x8507,
	GL_ENUMERATION_DECR_WRAP = 0x8508,
	GL_ENUMERATION_EMISSION = 0x1600,
	GL_ENUMERATION_AMBIENT = 0x1200,
	GL_ENUMERATION_DIFFUSE = 0x1201,
	GL_ENUMERATION_SPECULAR = 0x1202,
	GL_ENUMERATION_AMBIENT_AND_DIFFUSE = 0x1602,
	GL_ENUMERATION_LINEAR = 0x2601,
	GL_ENUMERATION_EXP = 0x0800,
	GL_ENUMERATION_EXP2 = 0x0801,
	GL_ENUMERATION_FOG_COORDINATE = 0x8451,
	GL_ENUMERATION_FRAGMENT_DEPTH = 0x8452,
	GL_ENUMERATION_CW = 0x0900,
	GL_ENUMERATION_CCW = 0x0901,
	GL_ENUMERATION_SINGLE_COLOR = 0x81F9,
	GL_ENUMERATION_SEPARATE_SPECULAR_COLOR = 0x81FA,
	GL_ENUMERATION_CLEAR = 0x1500,
	GL_ENUMERATION_AND = 0x1501,
	GL_ENUMERATION_AND_REVERSE = 0x1502,
	GL_ENUMERATION_COPY = 0x1503,
	GL_ENUMERATION_AND_INVERTED = 0x1504,
	GL_ENUMERATION_NOOP = 0x1505,
	GL_ENUMERATION_XOR = 0x1506,
	GL_ENUMERATION_OR = 0x1507,
	GL_ENUMERATION_NOR = 0x1508,
	GL_ENUMERATION_EQUIV = 0x1509,
	GL_ENUMERATION_OR_REVERSE = 0x150B,
	GL_ENUMERATION_COPY_INVERTED = 0x150C,
	GL_ENUMERATION_NAND = 0x150E,
	GL_ENUMERATION_SET = 0x150F,
	GL_ENUMERATION_POINT = 0x1B00,
	GL_ENUMERATION_LINE = 0x1B01,
	GL_ENUMERATION_FILL = 0x1B02,
	GL_ENUMERATION_FLAT = 0x1D00,
	GL_ENUMERATION_SMOOTH = 0x1D01,
	GL_ENUMERATION_COUNT = 72
};

enum domGles_enumeration {
	GLES_ENUMERATION_ZERO = 0x0,
	GLES_ENUMERATION_ONE = 0x1,
	GLES_ENUMERATION_SRC_COLOR = 0x0300,
	GLES_ENUMERATION_ONE_MINUS_SRC_COLOR = 0x0301,
	GLES_ENUMERATION_DEST_COLOR = 0x0306,
	GLES_ENUMERATION_ONE_MINUS_DEST_COLOR = 0x0307,
	GLES_ENUMERATION_SRC_ALPHA = 0x0302,
	GLES_ENUMERATION_ONE_MINUS_SRC_ALPHA = 0x0303,
	GLES_ENUMERATION_DST_ALPHA = 0x0304,
	GLES_ENUMERATION_ONE_MINUS_DST_ALPHA = 0x0305,
	GLES_ENUMERATION_CONSTANT_COLOR = 0x8001,
	GLES_ENUMERATION_ONE_MINUS_CONSTANT_COLOR = 0x8002,
	GLES_ENUMERATION_CONSTANT_ALPHA = 0x8003,
	GLES_ENUMERATION_ONE_MINUS_CONSTANT_ALPHA = 0x8004,
	GLES_ENUMERATION_SRC_ALPHA_SATURATE = 0x0308,
	GLES_ENUMERATION_FRONT = 0x0404,
	GLES_ENUMERATION_BACK = 0x0405,
	GLES_ENUMERATION_FRONT_AND_BACK = 0x0408,
	GLES_ENUMERATION_NEVER = 0x0200,
	GLES_ENUMERATION_LESS = 0x0201,
	GLES_ENUMERATION_LEQUAL = 0x0203,
	GLES_ENUMERATION_EQUAL = 0x0202,
	GLES_ENUMERATION_GREATER = 0x0204,
	GLES_ENUMERATION_NOTEQUAL = 0x0205,
	GLES_ENUMERATION_GEQUAL = 0x0206,
	GLES_ENUMERATION_ALWAYS = 0x0207,
	GLES_ENUMERATION_KEEP = 0x1E00,
	GLES_ENUMERATION_REPLACE = 0x1E01,
	GLES_ENUMERATION_INCR = 0x1E02,
	GLES_ENUMERATION_DECR = 0x1E03,
	GLES_ENUMERATION_INVERT = 0x150A,
	GLES_ENUMERATION_INCR_WRAP = 0x8507,
	GLES_ENUMERATION_DECR_WRAP = 0x8508,
	GLES_ENUMERATION_EMISSION = 0x1600,
	GLES_ENUMERATION_AMBIENT = 0x1200,
	GLES_ENUMERATION_DIFFUSE = 0x1201,
	GLES_ENUMERATION_SPECULAR = 0x1202,
	GLES_ENUMERATION_AMBIENT_AND_DIFFUSE = 0x1602,
	GLES_ENUMERATION_LINEAR = 0x2601,
	GLES_ENUMERATION_EXP = 0x0800,
	GLES_ENUMERATION_EXP2 = 0x0801,
	GLES_ENUMERATION_CW = 0x0900,
	GLES_ENUMERATION_CCW = 0x0901,
	GLES_ENUMERATION_SINGLE_COLOR = 0x81F9,
	GLES_ENUMERATION_SEPARATE_SPECULAR_COLOR = 0x81FA,
	GLES_ENUMERATION_CLEAR = 0x1500,
	GLES_ENUMERATION_AND = 0x1501,
	GLES_ENUMERATION_AND_REVERSE = 0x1502,
	GLES_ENUMERATION_COPY = 0x1503,
	GLES_ENUMERATION_AND_INVERTED = 0x1504,
	GLES_ENUMERATION_NOOP = 0x1505,
	GLES_ENUMERATION_XOR = 0x1506,
	GLES_ENUMERATION_OR = 0x1507,
	GLES_ENUMERATION_NOR = 0x1508,
	GLES_ENUMERATION_EQUIV = 0x1509,
	GLES_ENUMERATION_OR_REVERSE = 0x150B,
	GLES_ENUMERATION_COPY_INVERTED = 0x150C,
	GLES_ENUMERATION_NAND = 0x150E,
	GLES_ENUMERATION_SET = 0x150F,
	GLES_ENUMERATION_POINT = 0x1B00,
	GLES_ENUMERATION_LINE = 0x1B01,
	GLES_ENUMERATION_FILL = 0x1B02,
	GLES_ENUMERATION_FLAT = 0x1D00,
	GLES_ENUMERATION_SMOOTH = 0x1D01,
	GLES_ENUMERATION_COUNT = 65
};

//Element Type Enum
namespace COLLADA_TYPE
{
#ifdef _MSC_VER
	enum TypeEnum
	{
#else
	const int
#endif
		NO_TYPE = 0,
		ANY = 1,
		INPUTGLOBAL = 2,
		INPUTLOCAL = 3,
		INPUTLOCALOFFSET = 4,
		INSTANCEWITHEXTRA = 5,
		TARGETABLEFLOAT = 6,
		TARGETABLEFLOAT3 = 7,
		SURFACETYPE = 8,
		CURVETYPE = 9,
		FX_SURFACE_FORMAT_HINT_COMMON = 10,
		CHANNELS = 11,
		RANGE = 12,
		PRECISION = 13,
		OPTION = 14,
		FX_SURFACE_INIT_PLANAR_COMMON = 15,
		ALL = 16,
		FX_SURFACE_INIT_VOLUME_COMMON = 17,
		PRIMARY = 18,
		FX_SURFACE_INIT_CUBE_COMMON = 19,
		ORDER = 20,
		FACE = 21,
		FX_SURFACE_INIT_FROM_COMMON = 22,
		FX_SURFACE_COMMON = 23,
		FORMAT = 24,
		SIZE = 25,
		VIEWPORT_RATIO = 26,
		MIP_LEVELS = 27,
		MIPMAP_GENERATE = 28,
		FX_SAMPLER1D_COMMON = 29,
		SOURCE = 30,
		WRAP_S = 31,
		MINFILTER = 32,
		MAGFILTER = 33,
		MIPFILTER = 34,
		BORDER_COLOR = 35,
		MIPMAP_MAXLEVEL = 36,
		MIPMAP_BIAS = 37,
		FX_SAMPLER2D_COMMON = 38,
		WRAP_T = 39,
		FX_SAMPLER3D_COMMON = 40,
		WRAP_P = 41,
		FX_SAMPLERCUBE_COMMON = 42,
		FX_SAMPLERRECT_COMMON = 43,
		FX_SAMPLERDEPTH_COMMON = 44,
		FX_COLORTARGET_COMMON = 45,
		FX_DEPTHTARGET_COMMON = 46,
		FX_STENCILTARGET_COMMON = 47,
		FX_CLEARCOLOR_COMMON = 48,
		FX_CLEARDEPTH_COMMON = 49,
		FX_CLEARSTENCIL_COMMON = 50,
		FX_ANNOTATE_COMMON = 51,
		FX_INCLUDE_COMMON = 52,
		FX_NEWPARAM_COMMON = 53,
		SEMANTIC = 54,
		MODIFIER = 55,
		FX_CODE_PROFILE = 56,
		GL_SAMPLER1D = 57,
		GL_SAMPLER2D = 58,
		GL_SAMPLER3D = 59,
		GL_SAMPLERCUBE = 60,
		GL_SAMPLERRECT = 61,
		GL_SAMPLERDEPTH = 62,
		GLSL_NEWARRAY_TYPE = 63,
		GLSL_SETARRAY_TYPE = 64,
		GLSL_SURFACE_TYPE = 65,
		GENERATOR = 66,
		NAME = 67,
		GLSL_NEWPARAM = 68,
		GLSL_SETPARAM_SIMPLE = 69,
		GLSL_SETPARAM = 70,
		COMMON_FLOAT_OR_PARAM_TYPE = 71,
		FLOAT = 72,
		PARAM = 73,
		COMMON_COLOR_OR_TEXTURE_TYPE = 74,
		COLOR = 75,
		TEXTURE = 76,
		COMMON_TRANSPARENT_TYPE = 77,
		COMMON_NEWPARAM_TYPE = 78,
		FLOAT2 = 79,
		FLOAT3 = 80,
		FLOAT4 = 81,
		CG_SAMPLER1D = 82,
		CG_SAMPLER2D = 83,
		CG_SAMPLER3D = 84,
		CG_SAMPLERCUBE = 85,
		CG_SAMPLERRECT = 86,
		CG_SAMPLERDEPTH = 87,
		CG_CONNECT_PARAM = 88,
		CG_NEWARRAY_TYPE = 89,
		CG_SETARRAY_TYPE = 90,
		CG_SETUSER_TYPE = 91,
		CG_SURFACE_TYPE = 92,
		CG_NEWPARAM = 93,
		CG_SETPARAM_SIMPLE = 94,
		CG_SETPARAM = 95,
		GLES_TEXTURE_CONSTANT_TYPE = 96,
		GLES_TEXENV_COMMAND_TYPE = 97,
		GLES_TEXCOMBINER_ARGUMENTRGB_TYPE = 98,
		GLES_TEXCOMBINER_ARGUMENTALPHA_TYPE = 99,
		GLES_TEXCOMBINER_COMMANDRGB_TYPE = 100,
		GLES_TEXCOMBINER_COMMANDALPHA_TYPE = 101,
		GLES_TEXCOMBINER_COMMAND_TYPE = 102,
		GLES_TEXTURE_PIPELINE = 103,
		GLES_TEXTURE_UNIT = 104,
		SURFACE = 105,
		SAMPLER_STATE = 106,
		TEXCOORD = 107,
		GLES_SAMPLER_STATE = 108,
		GLES_NEWPARAM = 109,
		FX_SURFACE_INIT_COMMON = 110,
		INIT_AS_NULL = 111,
		INIT_AS_TARGET = 112,
		FX_ANNOTATE_TYPE_COMMON = 113,
		BOOL = 114,
		BOOL2 = 115,
		BOOL3 = 116,
		BOOL4 = 117,
		INT = 118,
		INT2 = 119,
		INT3 = 120,
		INT4 = 121,
		FLOAT2X2 = 122,
		FLOAT3X3 = 123,
		FLOAT4X4 = 124,
		STRING = 125,
		FX_BASIC_TYPE_COMMON = 126,
		FLOAT1X1 = 127,
		FLOAT1X2 = 128,
		FLOAT1X3 = 129,
		FLOAT1X4 = 130,
		FLOAT2X1 = 131,
		FLOAT2X3 = 132,
		FLOAT2X4 = 133,
		FLOAT3X1 = 134,
		FLOAT3X2 = 135,
		FLOAT3X4 = 136,
		FLOAT4X1 = 137,
		FLOAT4X2 = 138,
		FLOAT4X3 = 139,
		ENUM = 140,
		GL_PIPELINE_SETTINGS = 141,
		ALPHA_FUNC = 142,
		FUNC = 143,
		VALUE = 144,
		BLEND_FUNC = 145,
		SRC = 146,
		DEST = 147,
		BLEND_FUNC_SEPARATE = 148,
		SRC_RGB = 149,
		DEST_RGB = 150,
		SRC_ALPHA = 151,
		DEST_ALPHA = 152,
		BLEND_EQUATION = 153,
		BLEND_EQUATION_SEPARATE = 154,
		RGB = 155,
		ALPHA = 156,
		COLOR_MATERIAL = 157,
		MODE = 158,
		CULL_FACE = 159,
		DEPTH_FUNC = 160,
		FOG_MODE = 161,
		FOG_COORD_SRC = 162,
		FRONT_FACE = 163,
		LIGHT_MODEL_COLOR_CONTROL = 164,
		LOGIC_OP = 165,
		POLYGON_MODE = 166,
		SHADE_MODEL = 167,
		STENCIL_FUNC = 168,
		REF = 169,
		MASK = 170,
		STENCIL_OP = 171,
		FAIL = 172,
		ZFAIL = 173,
		ZPASS = 174,
		STENCIL_FUNC_SEPARATE = 175,
		FRONT = 176,
		BACK = 177,
		STENCIL_OP_SEPARATE = 178,
		STENCIL_MASK_SEPARATE = 179,
		LIGHT_ENABLE = 180,
		LIGHT_AMBIENT = 181,
		LIGHT_DIFFUSE = 182,
		LIGHT_SPECULAR = 183,
		LIGHT_POSITION = 184,
		LIGHT_CONSTANT_ATTENUATION = 185,
		LIGHT_LINEAR_ATTENUATION = 186,
		LIGHT_QUADRATIC_ATTENUATION = 187,
		LIGHT_SPOT_CUTOFF = 188,
		LIGHT_SPOT_DIRECTION = 189,
		LIGHT_SPOT_EXPONENT = 190,
		TEXTURE1D = 191,
		TEXTURE2D = 192,
		TEXTURE3D = 193,
		TEXTURECUBE = 194,
		TEXTURERECT = 195,
		TEXTUREDEPTH = 196,
		TEXTURE1D_ENABLE = 197,
		TEXTURE2D_ENABLE = 198,
		TEXTURE3D_ENABLE = 199,
		TEXTURECUBE_ENABLE = 200,
		TEXTURERECT_ENABLE = 201,
		TEXTUREDEPTH_ENABLE = 202,
		TEXTURE_ENV_COLOR = 203,
		TEXTURE_ENV_MODE = 204,
		CLIP_PLANE = 205,
		CLIP_PLANE_ENABLE = 206,
		BLEND_COLOR = 207,
		CLEAR_COLOR = 208,
		CLEAR_STENCIL = 209,
		CLEAR_DEPTH = 210,
		COLOR_MASK = 211,
		DEPTH_BOUNDS = 212,
		DEPTH_MASK = 213,
		DEPTH_RANGE = 214,
		FOG_DENSITY = 215,
		FOG_START = 216,
		FOG_END = 217,
		FOG_COLOR = 218,
		LIGHT_MODEL_AMBIENT = 219,
		LIGHTING_ENABLE = 220,
		LINE_STIPPLE = 221,
		LINE_WIDTH = 222,
		MATERIAL_AMBIENT = 223,
		MATERIAL_DIFFUSE = 224,
		MATERIAL_EMISSION = 225,
		MATERIAL_SHININESS = 226,
		MATERIAL_SPECULAR = 227,
		MODEL_VIEW_MATRIX = 228,
		POINT_DISTANCE_ATTENUATION = 229,
		POINT_FADE_THRESHOLD_SIZE = 230,
		POINT_SIZE = 231,
		POINT_SIZE_MIN = 232,
		POINT_SIZE_MAX = 233,
		POLYGON_OFFSET = 234,
		PROJECTION_MATRIX = 235,
		SCISSOR = 236,
		STENCIL_MASK = 237,
		ALPHA_TEST_ENABLE = 238,
		AUTO_NORMAL_ENABLE = 239,
		BLEND_ENABLE = 240,
		COLOR_LOGIC_OP_ENABLE = 241,
		COLOR_MATERIAL_ENABLE = 242,
		CULL_FACE_ENABLE = 243,
		DEPTH_BOUNDS_ENABLE = 244,
		DEPTH_CLAMP_ENABLE = 245,
		DEPTH_TEST_ENABLE = 246,
		DITHER_ENABLE = 247,
		FOG_ENABLE = 248,
		LIGHT_MODEL_LOCAL_VIEWER_ENABLE = 249,
		LIGHT_MODEL_TWO_SIDE_ENABLE = 250,
		LINE_SMOOTH_ENABLE = 251,
		LINE_STIPPLE_ENABLE = 252,
		LOGIC_OP_ENABLE = 253,
		MULTISAMPLE_ENABLE = 254,
		NORMALIZE_ENABLE = 255,
		POINT_SMOOTH_ENABLE = 256,
		POLYGON_OFFSET_FILL_ENABLE = 257,
		POLYGON_OFFSET_LINE_ENABLE = 258,
		POLYGON_OFFSET_POINT_ENABLE = 259,
		POLYGON_SMOOTH_ENABLE = 260,
		POLYGON_STIPPLE_ENABLE = 261,
		RESCALE_NORMAL_ENABLE = 262,
		SAMPLE_ALPHA_TO_COVERAGE_ENABLE = 263,
		SAMPLE_ALPHA_TO_ONE_ENABLE = 264,
		SAMPLE_COVERAGE_ENABLE = 265,
		SCISSOR_TEST_ENABLE = 266,
		STENCIL_TEST_ENABLE = 267,
		GLSL_PARAM_TYPE = 268,
		CG_PARAM_TYPE = 269,
		BOOL1 = 270,
		BOOL1X1 = 271,
		BOOL1X2 = 272,
		BOOL1X3 = 273,
		BOOL1X4 = 274,
		BOOL2X1 = 275,
		BOOL2X2 = 276,
		BOOL2X3 = 277,
		BOOL2X4 = 278,
		BOOL3X1 = 279,
		BOOL3X2 = 280,
		BOOL3X3 = 281,
		BOOL3X4 = 282,
		BOOL4X1 = 283,
		BOOL4X2 = 284,
		BOOL4X3 = 285,
		BOOL4X4 = 286,
		FLOAT1 = 287,
		INT1 = 288,
		INT1X1 = 289,
		INT1X2 = 290,
		INT1X3 = 291,
		INT1X4 = 292,
		INT2X1 = 293,
		INT2X2 = 294,
		INT2X3 = 295,
		INT2X4 = 296,
		INT3X1 = 297,
		INT3X2 = 298,
		INT3X3 = 299,
		INT3X4 = 300,
		INT4X1 = 301,
		INT4X2 = 302,
		INT4X3 = 303,
		INT4X4 = 304,
		HALF = 305,
		HALF1 = 306,
		HALF2 = 307,
		HALF3 = 308,
		HALF4 = 309,
		HALF1X1 = 310,
		HALF1X2 = 311,
		HALF1X3 = 312,
		HALF1X4 = 313,
		HALF2X1 = 314,
		HALF2X2 = 315,
		HALF2X3 = 316,
		HALF2X4 = 317,
		HALF3X1 = 318,
		HALF3X2 = 319,
		HALF3X3 = 320,
		HALF3X4 = 321,
		HALF4X1 = 322,
		HALF4X2 = 323,
		HALF4X3 = 324,
		HALF4X4 = 325,
		FIXED = 326,
		FIXED1 = 327,
		FIXED2 = 328,
		FIXED3 = 329,
		FIXED4 = 330,
		FIXED1X1 = 331,
		FIXED1X2 = 332,
		FIXED1X3 = 333,
		FIXED1X4 = 334,
		FIXED2X1 = 335,
		FIXED2X2 = 336,
		FIXED2X3 = 337,
		FIXED2X4 = 338,
		FIXED3X1 = 339,
		FIXED3X2 = 340,
		FIXED3X3 = 341,
		FIXED3X4 = 342,
		FIXED4X1 = 343,
		FIXED4X2 = 344,
		FIXED4X3 = 345,
		FIXED4X4 = 346,
		GLES_PIPELINE_SETTINGS = 347,
		TEXTURE_PIPELINE = 348,
		LIGHT_LINEAR_ATTENUTATION = 349,
		TEXTURE_PIPELINE_ENABLE = 350,
		GLES_BASIC_TYPE_COMMON = 351,
		COLLADA = 352,
		SCENE = 353,
		IDREF_ARRAY = 354,
		NAME_ARRAY = 355,
		BOOL_ARRAY = 356,
		FLOAT_ARRAY = 357,
		INT_ARRAY = 358,
		ACCESSOR = 359,
		TECHNIQUE_COMMON = 360,
		GEOMETRY = 361,
		MESH = 362,
		SPLINE = 363,
		CONTROL_VERTICES = 364,
		BREP = 365,
		CURVES = 366,
		EDGES = 367,
		WIRES = 368,
		VCOUNT = 369,
		FACES = 370,
		SHELLS = 371,
		SOLIDS = 372,
		LINE = 373,
		ORIGIN = 374,
		DIRECTION = 375,
		CIRCLE = 376,
		RADIUS = 377,
		ELLIPSE = 378,
		PARABOLA = 379,
		FOCAL = 380,
		LINEAR_EXTRUSION_SURFACE = 381,
		REVOLUTION_SURFACE = 382,
		AXIS = 383,
		HYPERBOLA = 384,
		SURFACES = 385,
		CYLINDRICAL = 386,
		CONE = 387,
		HALF_APEX = 388,
		TORUS = 389,
		SIDREF_ARRAY = 390,
		P = 391,
		LINES = 392,
		LINESTRIPS = 393,
		POLYGONS = 394,
		PH = 395,
		H = 396,
		POLYLIST = 397,
		TRIANGLES = 398,
		TRIFANS = 399,
		TRISTRIPS = 400,
		VERTICES = 401,
		LOOKAT = 402,
		MATRIX = 403,
		ROTATE = 404,
		SCALE = 405,
		SKEW = 406,
		TRANSLATE = 407,
		IMAGE = 408,
		DATA = 409,
		INIT_FROM = 410,
		LIGHT = 411,
		AMBIENT = 412,
		DIRECTIONAL = 413,
		POINT = 414,
		SPOT = 415,
		MATERIAL = 416,
		CAMERA = 417,
		OPTICS = 418,
		ORTHOGRAPHIC = 419,
		PERSPECTIVE = 420,
		IMAGER = 421,
		ANIMATION = 422,
		ANIMATION_CLIP = 423,
		CHANNEL = 424,
		SAMPLER = 425,
		CONTROLLER = 426,
		SKIN = 427,
		BIND_SHAPE_MATRIX = 428,
		JOINTS = 429,
		VERTEX_WEIGHTS = 430,
		V = 431,
		MORPH = 432,
		TARGETS = 433,
		ASSET = 434,
		CONTRIBUTOR = 435,
		AUTHOR = 436,
		AUTHORING_TOOL = 437,
		COMMENTS = 438,
		COPYRIGHT = 439,
		SOURCE_DATA = 440,
		CREATED = 441,
		KEYWORDS = 442,
		MODIFIED = 443,
		REVISION = 444,
		SUBJECT = 445,
		TITLE = 446,
		UNIT = 447,
		UP_AXIS = 448,
		EXTRA = 449,
		TECHNIQUE = 450,
		NODE = 451,
		VISUAL_SCENE = 452,
		EVALUATE_SCENE = 453,
		RENDER = 454,
		LAYER = 455,
		BIND_MATERIAL = 456,
		INSTANCE_CAMERA = 457,
		INSTANCE_CONTROLLER = 458,
		SKELETON = 459,
		INSTANCE_EFFECT = 460,
		TECHNIQUE_HINT = 461,
		SETPARAM = 462,
		INSTANCE_FORCE_FIELD = 463,
		INSTANCE_GEOMETRY = 464,
		INSTANCE_LIGHT = 465,
		INSTANCE_MATERIAL = 466,
		BIND = 467,
		BIND_VERTEX_INPUT = 468,
		INSTANCE_NODE = 469,
		INSTANCE_PHYSICS_MATERIAL = 470,
		INSTANCE_PHYSICS_MODEL = 471,
		INSTANCE_RIGID_BODY = 472,
		ANGULAR_VELOCITY = 473,
		VELOCITY = 474,
		DYNAMIC = 475,
		MASS_FRAME = 476,
		SHAPE = 477,
		HOLLOW = 478,
		INSTANCE_RIGID_CONSTRAINT = 479,
		LIBRARY_ANIMATIONS = 480,
		LIBRARY_ANIMATION_CLIPS = 481,
		LIBRARY_CAMERAS = 482,
		LIBRARY_CONTROLLERS = 483,
		LIBRARY_GEOMETRIES = 484,
		LIBRARY_EFFECTS = 485,
		LIBRARY_FORCE_FIELDS = 486,
		LIBRARY_IMAGES = 487,
		LIBRARY_LIGHTS = 488,
		LIBRARY_MATERIALS = 489,
		LIBRARY_NODES = 490,
		LIBRARY_PHYSICS_MATERIALS = 491,
		LIBRARY_PHYSICS_MODELS = 492,
		LIBRARY_PHYSICS_SCENES = 493,
		LIBRARY_VISUAL_SCENES = 494,
		FX_PROFILE_ABSTRACT = 495,
		EFFECT = 496,
		GL_HOOK_ABSTRACT = 497,
		PROFILE_GLSL = 498,
		PASS = 499,
		DRAW = 500,
		SHADER = 501,
		COMPILER_TARGET = 502,
		COMPILER_OPTIONS = 503,
		PROFILE_COMMON = 504,
		CONSTANT = 505,
		LAMBERT = 506,
		PHONG = 507,
		BLINN = 508,
		PROFILE_CG = 509,
		PROFILE_GLES = 510,
		COLOR_TARGET = 511,
		DEPTH_TARGET = 512,
		STENCIL_TARGET = 513,
		COLOR_CLEAR = 514,
		DEPTH_CLEAR = 515,
		STENCIL_CLEAR = 516,
		BOX = 517,
		HALF_EXTENTS = 518,
		PLANE = 519,
		EQUATION = 520,
		SPHERE = 521,
		ELLIPSOID = 522,
		CYLINDER = 523,
		HEIGHT = 524,
		TAPERED_CYLINDER = 525,
		RADIUS1 = 526,
		RADIUS2 = 527,
		CAPSULE = 528,
		TAPERED_CAPSULE = 529,
		CONVEX_MESH = 530,
		FORCE_FIELD = 531,
		PHYSICS_MATERIAL = 532,
		PHYSICS_SCENE = 533,
		RIGID_BODY = 534,
		RIGID_CONSTRAINT = 535,
		REF_ATTACHMENT = 536,
		ATTACHMENT = 537,
		ENABLED = 538,
		INTERPENETRATE = 539,
		LIMITS = 540,
		SWING_CONE_AND_TWIST = 541,
		LINEAR = 542,
		SPRING = 543,
		ANGULAR = 544,
		PHYSICS_MODEL = 545
#ifdef _MSC_VER
	};
#else
	;
#endif
};

#endif
